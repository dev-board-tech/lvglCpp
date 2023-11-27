#include "dbg.h"
#include "conf.h"

#include <Arduino.h>
void DBG_print(String str) {
	if(DEVICE_DEBUG)
	Serial.print(str);
}

void DBG_print(char *str) {
	if(DEVICE_DEBUG)
		Serial.print(str);
}

void DBG_println(String str) {
	if(DEVICE_DEBUG)
		Serial.println(str);
}

void DBG_println(char *str) {
	if(DEVICE_DEBUG)
		Serial.println(str);
}

void DBG_printf(char *fmt, ...) {
#if DEVICE_DEBUG
	va_list args;
	va_start(args, fmt);
	int size = vsnprintf(NULL, 0, fmt, args);
	va_end(args);
	char buffer[size + 1];
	va_start(args, fmt);
	vsnprintf(buffer, size + 1, fmt, args);
	va_end(args);
	Serial.print(buffer);
#endif
}
