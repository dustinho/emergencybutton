#include "emergencybutton.h"
#include <stdio.h>
#include <unistd.h>

#include <vector>

int main(void) {
	button_state last_state = (button_state)-1;
	while(1) {
		emergencybutton_handle* dev = emergencybutton_open();
		usleep(10000);
		button_state state = emergencybutton_poll(dev);
		if (state != last_state) {
			last_state = state;
			switch(state) {
				case BUTTON_CLOSED:
					printf("Button is closed\n");
					break;
				case BUTTON_ARMED:
					printf("Button is armed\n");
					break;
				case BUTTON_PRESSED:
					printf("Button is pressed OH NO!\n");
					break;
			}
		}
		emergencybutton_close(dev);
	}
	return 0;
}
