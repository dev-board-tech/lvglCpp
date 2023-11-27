#ifndef __CONF_H__
#define __CONF_H__

#include <stdio.h>
#include <stdarg.h>
#include "Arduino.h"

#define BUILD_ON_SLOEBER				true

#define USE_MESH  true

#define OTA_PART_SIZE 1024 //How many bytes to send per OTA data packet

#define TAB_GENERAL_FANS_OFFSET_Y       40
#define TAB_GENERAL_FANS_OFFSET_X       18

//ERROR | MESH_STATUS | CONNECTION | SYNC |
// COMMUNICATION | GENERAL | MSG_TYPES | REMOTE
#define MESH_DBG_LEVEL                  ERROR
#define DEVICE_DEBUG                    true

#define MESH_PREFIX "hallCtlMeshNetwork"
#define MESH_PASSWORD "32djityjvio4touwy8otidytw38"
#define MESH_PORT 5555

#define FUNCTION_CENTER                 1
#define FUNCTION_FAN_CTL_1              2
#define FUNCTION_FAN_CTL_2              3
#define FUNCTION_SHUTTER_CTL            4

//#define MODULE_FUNCTION   FUNCTION_UPDATER // AI Thinker ESP32-CAM, 240Mhz, Flash Size 4MB, Partition Scheme: 1.9MB APP with OTA/190KB SPIFFS
// Board	ESP32S3 Dev Module
// USB CDC On Boot	Enabled
// CPU Frequency	240MHz (WiFi)
// Core Debug Level	None
// USB DFU On Boot	Enabled
// Events Run On	Core 1
// Flash Mode	QIO 80MHz
// Flash Size	16MB (128Mb)
// JTAG Adapter	Integrated USB JTAG
// Arduino Runs On	Core 1
// USB Firmware MSC On Boot	Disabled
// Partition Scheme	Huge APP (3MB APP/9.9MB FATFS)
// PSRAM	OPI PSRAM
// USB Mode	Hardware CDC and JTAG
#define MODULE_FUNCTION   FUNCTION_CENTER 
//#define MODULE_FUNCTION   FUNCTION_FAN_CTL_1 // ESP32-WROOM-DA, 240Mhz, Flash Size 4MB, Partition Scheme: 1.9MB APP with OTA/190KB SPIFFS
//#define MODULE_FUNCTION   FUNCTION_FAN_CTL_2 // ESP32-WROOM-DA, 240Mhz, Flash Size 4MB, Partition Scheme: 1.9MB APP with OTA/190KB SPIFFS
//#define MODULE_FUNCTION   FUNCTION_SHUTTER_CTL // ESP32-WROOM-DA, 240Mhz, Flash Size 4MB, Partition Scheme: 1.9MB APP with OTA/190KB SPIFFS

#if MODULE_FUNCTION == FUNCTION_CENTER
#define OTA_NAME  "ota-center"
#define MOD_NAME  "center"
#define MOD_NAME_FAN1       "fan-ctl-1"
#define MOD_NAME_FAN2       "fan-ctl-2"
#define MOD_NAME_SHUTTER    "shutter-ctl"
#elif MODULE_FUNCTION == FUNCTION_FAN_CTL_1
#define OTA_NAME  "ota-fan-ctl-1"
#define MOD_NAME  "fan-ctl-1"
#elif MODULE_FUNCTION == FUNCTION_FAN_CTL_2
#define OTA_NAME  "ota-fan-ctl-2"
#define MOD_NAME  "fan-ctl-2"
#elif MODULE_FUNCTION == FUNCTION_SHUTTER_CTL
#define OTA_NAME  "ota-shutter-ctl-1"
#define MOD_NAME  "shutter-ctl1"
#endif

#endif //__CONF_H__
