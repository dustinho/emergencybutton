#include "button_internal.h"
#include <libemergencybutton/emergencybutton.h>
#include "hidapi.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static emergencybutton_loglevel emergencybutton_current_loglevel = EMERGENCYBUTTON_LOG_DEBUG;

emergencybutton_handle* emergencybutton_open() {
	struct hid_device_info *devs, *cur_dev;
	hid_device* handle = NULL;

	devs = hid_enumerate(0x0, 0x0);
	cur_dev = devs;
	while(cur_dev) {
		EB_DEBUG("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
		cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
		EB_DEBUG("\n");
		EB_DEBUG("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
		EB_DEBUG("  Product:      %ls\n", cur_dev->product_string);
		EB_DEBUG("\n");
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);
	// Try opening the device
	handle = hid_open(0x1d34, 0x000d, NULL);
	if (!handle) {
		EB_ERROR("Failed to open HID device\n");
		return NULL;
	} else {
		EB_DEBUG("Opened device successfully.\n");
	}
	emergencybutton_handle* retval = malloc(sizeof(emergencybutton_handle));
	memset(retval, 0, sizeof(*retval));
	retval->dev = handle;
	return retval;
}

button_state emergencybutton_poll(emergencybutton_handle* dev) {
	EB_DEBUG("emergencybutton_poll entered\n");
	int res = 0;
	unsigned char data[256];
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;
	data[8] = 2;
	EB_DEBUG("Sending OUT report\n");
	res = hid_write(dev->dev, data, 9);
	EB_DEBUG("Sent OUT report, %d bytes sent\n", res);

	EB_DEBUG("About to request report IN\n");
	res = hid_read(dev->dev, data, 8);
	EB_DEBUG("Got report IN: %d bytes:", res);
	int i;
	for(i = 0 ; i < res ; i++) {
		EB_DEBUG(" %02X", data[i]);
	}
	EB_DEBUG("\n");
	switch(data[0]) {
		case 0x15:
			return BUTTON_CLOSED;
		case 0x16:
			return BUTTON_PRESSED;
		case 0x17:
			return BUTTON_ARMED;
		default:
			EB_ERROR("WTF I don't know that kind of button mode: %02X\n", data[0]);
	}
	return BUTTON_CLOSED;
}
void emergencybutton_close(emergencybutton_handle* dev) {
	if (dev) {
		hid_close(dev->dev);
		free(dev);
	}
}

void eb_log(emergencybutton_loglevel level, const char *fmt, ...)
{
	va_list args;
	if (level > emergencybutton_current_loglevel)
		return;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

