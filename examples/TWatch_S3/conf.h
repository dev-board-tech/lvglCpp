#ifndef __CONF_H__
#define __CONF_H__

#include <LilyGoLib.h>
#include <LV_Helper.h>

#define CORE_SLEEP_FREQ 10
#define CORE_RUN_FREQ   80

//! Two transceivers, SX1262 and SX1280, are defined based on the actual model
// #define USE_RADIO_SX1280
#define USE_RADIO_SX1262
#define ENABLE_IR_SENDER

#define DEFAULT_COLOR                           (lv_color_make(252, 218, 72))

#endif