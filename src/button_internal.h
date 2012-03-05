
#include "hidapi.h"

typedef struct emergencybutton_handle_ {
	struct hid_device* dev;
} emergencybutton_handle_;

typedef enum {
	EMERGENCYBUTTON_LOG_FATAL = 0,
	EMERGENCYBUTTON_LOG_ERROR,
	EMERGENCYBUTTON_LOG_WARNING,
	EMERGENCYBUTTON_LOG_NOTICE,
	EMERGENCYBUTTON_LOG_INFO,
	EMERGENCYBUTTON_LOG_DEBUG,
	EMERGENCYBUTTON_LOG_SPEW,
	EMERGENCYBUTTON_LOG_FLOOD,
} emergencybutton_loglevel;

void eb_log(emergencybutton_loglevel level, const char *fmt, ...);

#define EB_LOG(level, ...) eb_log(level, __VA_ARGS__)

#define EB_FATAL(...) EB_LOG(EMERGENCYBUTTON_LOG_FATAL, __VA_ARGS__)
#define EB_ERROR(...) EB_LOG(EMERGENCYBUTTON_LOG_ERROR, __VA_ARGS__)
#define EB_WARNING(...) EB_LOG(EMERGENCYBUTTON_LOG_WARNING, __VA_ARGS__)
#define EB_NOTICE(...) EB_LOG(EMERGENCYBUTTON_LOG_NOTICE, __VA_ARGS__)
#define EB_INFO(...) EB_LOG(EMERGENCYBUTTON_LOG_INFO, __VA_ARGS__)
#define EB_DEBUG(...) EB_LOG(EMERGENCYBUTTON_LOG_DEBUG, __VA_ARGS__)
#define EB_SPEW(...) EB_LOG(EMERGENCYBUTTON_LOG_SPEW, __VA_ARGS__)
#define EB_FLOOD(...) EB_LOG(EMERGENCYBUTTON_LOG_FLOOD, __VA_ARGS__)

