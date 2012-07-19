#ifdef __cplusplus
extern "C" {
#endif

// Opaque struct
struct emergencybutton_handle_;
typedef struct emergencybutton_handle_ emergencybutton_handle;

typedef enum {
	BUTTON_CLOSED = 0,
	BUTTON_ARMED = 1,
	BUTTON_PRESSED = 2,
} button_state;

emergencybutton_handle* emergencybutton_open();
button_state emergencybutton_poll(emergencybutton_handle*);
void emergencybutton_close(emergencybutton_handle*);

#ifdef __cplusplus
}
#endif
