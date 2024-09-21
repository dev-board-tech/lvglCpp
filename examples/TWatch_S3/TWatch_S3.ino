/**
 * @file      TWatch_S3.ino
 * @author    Lewis He (lewishe@outlook.com), modified Iulian Gheorghiu
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xinyuan Electronic Technology Co., Ltd
 * @date      2023-04-05
 * @note      Arduino esp version 2.0.9 Setting , not support esp 3.x
 *            Tools ->
 *                  Board:"ESP32S3 Dev Module"
 *                  USB CDC On Boot:"Enable"
 *                  CPU Frequency: "240MHz (WiFi)"
 *                  Core Debug Level: "Verbose"
 *                  USB DFU On Boot: "Disabled"
 *                  Erase All Flash Before Sketch Upload: "Disabled"
 *                  Events Run On: "Core 1"
 *                  Flash Mode: "QI0 80MHz"
 *                  Flash Size: "16MB (128Mb)"
 *                  JTAG Adapter: "Disabled"
 *                  Arduino Runs On: "Core 1"
 *                  USB Firmware MSC On Boot: "Disabled"
 *                  Partition Scheme: "16M Flash (3MB APP/9.9MB FATFS)"
 *                  PSRAM: "OPI PSRAM"
 *                  Upload Mode: "UART0/Hardware CDC"
 *                  Upload Speed: "921600"
 *                  USB Mode: "Hardware CDC and JTAG"
 *                  Programmer: "Esptool"
 */

 /*
 Dependencies:
 https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library
 https://github.com/Xinyuan-LilyGO/T-Watch-Deps
 https://github.com/dev-board-tech/lvglCpp
 */

#include "conf.h"

#include <LilyGoLib.h>
#include <LV_Helper.h>

#include <FS.h>
#include "FFat.h"

#ifdef USE_RADIO_SX1262
SX1262 radio = newModule();
#elif  defined(USE_RADIO_SX1280)
SX1280 radio = newModule();
#endif

#include <WiFi.h>
#include <driver/i2s.h>
#include <driver/gpio.h>

#include "app_IrTvRemote.h"
#include "app_IrAcRemote.h"

#include <IRsend.h>
IRsend irsend(BOARD_IR_PIN);

const char deviceCfgFileName[] = "/deviceCfg.cfg";
uint8_t lcdBacklight = 50;
uint8_t cpuIdleFreq = 10;
uint8_t cpuMaxFreq = 80;

#define DEFAULT_SCREEN_TIMEOUT                  (15*1000)

LV_IMG_DECLARE(clock_face);
LV_IMG_DECLARE(clock_hour_hand);
LV_IMG_DECLARE(clock_minute_hand);
LV_IMG_DECLARE(clock_second_hand);

LV_IMG_DECLARE(watch_if);
LV_IMG_DECLARE(watch_bg);
LV_IMG_DECLARE(watch_if_hour);
LV_IMG_DECLARE(watch_if_min);
LV_IMG_DECLARE(watch_if_sec);

LV_IMG_DECLARE(watch_if_bg2);
LV_IMG_DECLARE(watch_if_hour2);
LV_IMG_DECLARE(watch_if_min2);
LV_IMG_DECLARE(watch_if_sec2);

LV_FONT_DECLARE(font_siegra);
LV_FONT_DECLARE(font_sandbox);
LV_FONT_DECLARE(font_jetBrainsMono);
LV_FONT_DECLARE(font_firacode_60);
LV_FONT_DECLARE(font_ununtu_18);


LV_IMG_DECLARE(img_usb_plug);

LV_IMG_DECLARE(charge_done_battery);

LV_IMG_DECLARE(watch_if_5);
LV_IMG_DECLARE(watch_if_6);
LV_IMG_DECLARE(watch_if_8);


static lv_obj_t *battery_percent;
static lv_obj_t *weather_celsius;
static lv_obj_t *step_counter;

static lv_obj_t *hour_img;
static lv_obj_t *min_img;
static lv_obj_t *sec_img;
static lv_obj_t *tileview;
static lv_obj_t *radio_ta;
static lv_obj_t *wifi_table_list;
static lv_obj_t *label_datetime;
static lv_obj_t *charge_cont;
static lv_obj_t *gnss_label;

static lv_timer_t *clockTimer;

static lv_style_t button_default_style;
static lv_style_t button_press_style;
// Save the ID of the current page
static uint8_t pageId = 0;
// Flag used to indicate whether to use light sleep, currently unavailable
static bool lightSleep = false;
// Flag used for acceleration interrupt status
static bool sportsIrq = false;
// Flag used to indicate whether recording is enabled
static bool recordFlag = false;
// Flag used for PMU interrupt trigger status
static bool pmuIrq = false;
// Flag used to select whether to turn off the screen
static bool canScreenOff = true;
// Flag used to detect USB insertion status
static bool usbPlugIn = false;
// Save transmission states between loops
static int transmissionState = RADIOLIB_ERR_NONE;
// Flag to indicate transmission or reception state
static bool transmitFlag = false;
// Save pedometer steps
static uint32_t stepCounter = 0;
// Save Radio Transmit Interval
static uint32_t configTransmitInterval = 0;
// Save brightness value
static RTC_DATA_ATTR int brightnessLevel = 0;


typedef  struct _lv_datetime {
    lv_obj_t *obj;
    const char *name;
    uint16_t minVal;
    uint16_t maxVal;
    uint16_t defaultVal;
    uint8_t digitFormat;
} lv_datetime_t;

static lv_datetime_t lv_datetime [] = {
    {NULL, "Year", 2023, 2099, 2023, 4},
    {NULL, "Mon", 1, 12, 4, 2},
    {NULL, "Day", 1, 30, 12, 2},
    {NULL, "Hour", 0, 24, 22, 2},
    {NULL, "Min", 0, 59, 30, 2},
    {NULL, "Sec", 0, 59, 0, 2}
};

void initUi();

void productPinmap(lv_obj_t *parent);
void analogclock(lv_obj_t *parent);

void datetimeVeiw(lv_obj_t *parent);
void lilygo_qrcode(lv_obj_t *parent);

void settingPMU();
void settingSensor();
void settingPlayer();
void settingIRRemote();
void settingButtonStyle();
void PMUHandler();
void lowPowerEnergyHandler();
void destoryChargeUI();

#ifdef USE_RADIO_SX1262
const char *radio_freq_list =
    "433MHz\n"
    "470MHz\n"
    "868MHz\n"
    "915MHz\n"
    "923MHz";
const float radio_freq_args_list[] = {433.0, 470.0, 868.0, 915.0, 923.0};

const char *radio_bandwidth_list =
    "125KHz\n"
    "250KHz\n"
    "500KHz";
const float radio_bandwidth_args_list[] = {125.0, 250.0, 500.0};

const char *radio_power_level_list =
    "2dBm\n"
    "5dBm\n"
    "10dBm\n"
    "12dBm\n"
    "17dBm\n"
    "20dBm\n"
    "22dBm";
const float radio_power_args_list[] = {2, 5, 10, 12, 17, 20, 22};

#define RADIO_DEFAULT_FREQ          868.0
#define RADIO_DEFAULT_BW            250.0
#define RADIO_DEFAULT_SF            10
#define RADIO_DEFAULT_CR            6
#define RADIO_DEFAULT_CUR_LIMIT     140
#define RADIO_DEFAULT_POWER_LEVEL   22

#elif  defined(USE_RADIO_SX1280)

#define RADIO_DEFAULT_FREQ          2492.0
#define RADIO_DEFAULT_BW            203.125
#define RADIO_DEFAULT_SF            10
#define RADIO_DEFAULT_CR            6
#define RADIO_DEFAULT_POWER_LEVEL   13

const char *radio_freq_list =
    "2400MHz\n"
    "2412MHz\n"
    "2422MHz\n"
    "2432MHz\n"
    "2442MHz\n"
    "2452MHz\n"
    "2462MHz\n"
    "2472MHz\n"
    "2482MHz\n"
    "2492MHz\n"
    "2498MHz\n"
    "2500MHz";
const float radio_freq_args_list[] = {2400.0,
                                      2412.0, 2422.0, 2432.0,
                                      2442.0, 2452.0, 2462.0,
                                      2472.0, 2482.0, 2492.0,
                                      2500.0
                                     };

const char *radio_bandwidth_list =
    "203.125KHz\n"
    "406.25KHz\n"
    "812.5KHz\n"
    "1625.0KHz";
const float radio_bandwidth_args_list[] = {203.125, 406.25, 812.5, 1625.0};
const char *radio_power_level_list =

    /* "-18dBm\n"
     "-17dBm\n"
     "-16dBm\n"
     "-15dBm\n"
     "-14dBm\n"
     "-13dBm\n"
     "-12dBm\n"
     "-11dBm\n"
     "-10dBm\n"
     "-9dBm\n"
     "-8dBm\n"
     "-7dBm\n"
     "-6dBm\n"
     "-5dBm\n"
     "-4dBm\n"
     "-3dBm\n"
     "-2dBm\n"
     "-1dBm\n"
     */
    "0dBm\n"
    "1dBm\n"
    "2dBm\n"
    "3dBm\n"
    "4dBm\n"
    "5dBm\n"
    "6dBm\n"
    "7dBm\n"
    "8dBm\n"
    "9dBm\n"
    "10dBm\n"
    "11dBm\n"
    "12dBm\n"
    "13dBm";

const float radio_power_args_list[] = {
    // -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8,
    //     -7, -6, -5, -4, -3, -2, -1,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
};
#endif

static void deviceSaveConfig() {
  File cfgFile = FFat.open(deviceCfgFileName, "w");
  if(cfgFile) {
    JsonDocument docNew;
    docNew["lcdBacklight"] = lcdBacklight;
    docNew["cpuIdleFreq"] = cpuIdleFreq;
    docNew["cpuMaxFreq"] = cpuMaxFreq;
    if (serializeJson(docNew, cfgFile) == 0) {
      Serial.printf_P(PSTR("ERR: Failed to write deviceCfg.cfg file\n"));
    }
    cfgFile.flush();
    cfgFile.close();
  }
  setCpuFrequencyMhz(cpuMaxFreq);
}


void setup() {
  // Stop wifi
  WiFi.mode(WIFI_MODE_NULL);

  btStop();

  setCpuFrequencyMhz(cpuMaxFreq);

  Serial.begin(115200);

  if(!FFat.begin()){
      Serial.println("FFat Mount Failed");
  } else {
    Serial.printf_P(PSTR("Total space: %10u\n"), FFat.totalBytes());
    Serial.printf_P(PSTR("Free space: %10u\n"), FFat.freeBytes());
  }

  watch.begin(&Serial);

  watch.initMicrophone();

  settingPMU();

  settingSensor();

  settingIRRemote();

  File cfgFile = FFat.open(deviceCfgFileName, "r");
  if(!cfgFile) {
    Serial.printf_P(PSTR("WARNING: deviceCfg.cfg file not found, create one\n"));
    cfgFile = FFat.open(deviceCfgFileName, "w");
    JsonDocument docNew;
    docNew["lcdBacklight"] = lcdBacklight;
    docNew["cpuIdleFreq"] = cpuIdleFreq;
    docNew["cpuMaxFreq"] = cpuMaxFreq;
    if (serializeJson(docNew, cfgFile) == 0) {
      Serial.printf_P(PSTR("ERR: Failed to write deviceCfg.cfg file\n"));
    }
    cfgFile.flush();
    cfgFile.close();
    cfgFile = FFat.open(deviceCfgFileName, "r");
    if(!cfgFile) {
      Serial.printf_P(PSTR("ERR: Failed to reload deviceCfg.cfg file\n"));
    }
  }
// Load deviceCfg.cfg
  JsonDocument docR;
  DeserializationError error = deserializeJson(docR, cfgFile);
  if (!error) {
    if(docR.containsKey("lcdBacklight")) {
      lcdBacklight = docR["lcdBacklight"];
    }
    if(docR.containsKey("lcdBacklight")) {
      cpuIdleFreq = docR["cpuIdleFreq"];
      if(!cpuIdleFreq) {
        cpuIdleFreq = 10;
      }
    }
    if(docR.containsKey("lcdBacklight")) {
      cpuMaxFreq = docR["cpuMaxFreq"];
      if(!cpuMaxFreq) {
        cpuMaxFreq = 80;
      }
    }
    Serial.printf_P(PSTR("OK: Load deviceCfg.cfg\n"));
  }
  if(cfgFile) {
    cfgFile.close();
  }
  setCpuFrequencyMhz(cpuMaxFreq);
  Serial.printf((char *)"CPU Idle Frequency = %uMhz\n", cpuIdleFreq);
  Serial.printf((char *)"CPU Max Frequency = %uMhz\n", cpuMaxFreq);
  watch.setBrightness(lcdBacklight);

  beginLvglHelper(false);

  settingButtonStyle();

  initUi();

  usbPlugIn =  watch.isVbusIn();
}

static void charge_anim_cb(void *obj, int32_t v)
{
    lv_obj_t *arc = (lv_obj_t *)obj;
    static uint32_t last_check_interval;
    static int battery_percent;
    if (last_check_interval < millis()) {
        battery_percent =  watch.getBatteryPercent();
        lv_obj_t *label_percent =  (lv_obj_t *)lv_obj_get_user_data(arc);
        if (battery_percent != - 1) {
            lv_label_set_text_fmt(label_percent, "%d%%", battery_percent);
            lv_obj_set_style_text_font(label_percent, &lv_font_montserrat_22, LV_PART_MAIN);
            lv_obj_t *img_chg =  (lv_obj_t *)lv_obj_get_user_data(label_percent);
            lv_obj_align_to(label_percent, img_chg, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
            lv_obj_clear_flag(arc, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_label_set_long_mode(label_percent, LV_LABEL_LONG_WRAP);
            lv_obj_set_style_text_font(label_percent, &lv_font_montserrat_14, LV_PART_MAIN);
            lv_obj_set_width(label_percent, lv_pct(90));
            lv_label_set_text(label_percent, "Please turn the battery switch to ON");
            lv_obj_add_flag(arc, LV_OBJ_FLAG_HIDDEN);
        }
        if (battery_percent == 100) {
            lv_obj_t *img =  (lv_obj_t *)lv_obj_get_user_data(label_percent);
            lv_anim_del(arc, charge_anim_cb);
            lv_arc_set_value(arc, 100);
            lv_img_set_src(img, &charge_done_battery);
        }
        last_check_interval = millis() + 2000;
    }
    if (v >= battery_percent) {
        return;
    }
    lv_arc_set_value(arc, v);
}


void createChargeUI()
{
    if (charge_cont) {
        return;
    }

    static lv_style_t cont_style;
    lv_style_init(&cont_style);
    lv_style_set_bg_opa(&cont_style, LV_OPA_100);
    lv_style_set_bg_color(&cont_style, lv_color_black());
    lv_style_set_radius(&cont_style, 0);
    lv_style_set_border_width(&cont_style, 0);

    charge_cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(charge_cont, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_add_style(charge_cont, &cont_style, LV_PART_MAIN);
    lv_obj_center(charge_cont);

    lv_obj_add_event_cb(charge_cont, [](lv_event_t *e) {
        destoryChargeUI();
    }, LV_EVENT_PRESSED, NULL);

    int battery_percent =  watch.getBatteryPercent();
    static int last_battery_percent = 0;

    lv_obj_t *arc = lv_arc_create(charge_cont);
    lv_obj_set_size(arc, LV_PCT(90), LV_PCT(90));
    lv_arc_set_rotation(arc, 0);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_obj_set_style_arc_color(arc, lv_color_make(19, 161, 14), LV_PART_INDICATOR);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_center(arc);

    lv_obj_t *img_chg = lv_img_create(charge_cont);
    lv_obj_set_style_bg_opa(img_chg, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_img_recolor(img_chg, lv_color_make(19, 161, 14), LV_PART_ANY);

    lv_obj_t *label_percent = lv_label_create(charge_cont);
    lv_obj_set_style_text_font(label_percent, &lv_font_montserrat_28, LV_PART_MAIN);
    lv_obj_set_style_text_color(label_percent, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text_fmt(label_percent, "%d%%", battery_percent);

    //set user data
    lv_obj_set_user_data(arc, label_percent);
    lv_obj_set_user_data(label_percent, img_chg);

    lv_img_set_src(img_chg, &charge_done_battery);

    if (battery_percent == 100) {
        lv_arc_set_value(arc, 100);
        lv_img_set_src(img_chg, &charge_done_battery);
    } else {
        lv_img_set_src(img_chg, &img_usb_plug);
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, arc);
        lv_anim_set_start_cb(&a, [](lv_anim_t *a) {
            lv_obj_t *arc = (lv_obj_t *)a->var;
            lv_arc_set_value(arc, 0);
        });

        lv_anim_set_exec_cb(&a, charge_anim_cb);
        lv_anim_set_time(&a, 1000);
        lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
        lv_anim_set_repeat_delay(&a, 500);
        lv_anim_set_values(&a, 0, 100);
        lv_anim_start(&a);
    }
    lv_obj_center(img_chg);
    lv_obj_align_to(label_percent, img_chg, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);


    lv_task_handler();
}


void destoryChargeUI()
{
    if (!charge_cont) {
        return;
    }
    lv_obj_del(charge_cont);
    charge_cont = NULL;
}


void PMUHandler()
{
    if (pmuIrq) {
        pmuIrq = false;
        watch.readPMU();
        if (watch.isVbusInsertIrq()) {
            Serial.println(PSTR("isVbusInsert"));
            createChargeUI();
            watch.incrementalBrightness(brightnessLevel);
            usbPlugIn = true;
        }
        if (watch.isVbusRemoveIrq()) {
            Serial.println(PSTR("isVbusRemove"));
            destoryChargeUI();
            watch.incrementalBrightness(brightnessLevel);
            usbPlugIn = false;
        }
        if (watch.isBatChagerDoneIrq()) {
            Serial.println(PSTR("isBatChagerDone"));
        }
        if (watch.isBatChagerStartIrq()) {
            Serial.println(PSTR("isBatChagerStart"));
        }
        // Clear watch Interrupt Status Register
        watch.clearPMU();
    }
}

void SensorHandler()
{
    if (sportsIrq) {
        sportsIrq = false;
        // The interrupt status must be read after an interrupt is detected
        uint16_t status = watch.readBMA();
        Serial.printf("Accelerometer interrupt mask : 0x%x\n", status);

        if (watch.isPedometer()) {
            stepCounter = watch.getPedometerCounter();
            Serial.printf("Step count interrupt,step Counter:%u\n", stepCounter);
        }
        if (watch.isActivity()) {
            Serial.println("Activity interrupt");
        }
        if (watch.isTilt()) {
            Serial.println("Tilt interrupt");
        }
        if (watch.isDoubleTap()) {
            Serial.println("DoubleTap interrupt");
        }
        if (watch.isAnyNoMotion()) {
            Serial.println("Any motion / no motion interrupt");
        }
    }
}


void lowPowerEnergyHandler()
{
    Serial.println(PSTR("Enter light sleep mode!"));
    brightnessLevel = watch.getBrightness();
    watch.decrementBrightness(0);

    watch.clearPMU();

    watch.configreFeatureInterrupt(
        SensorBMA423::INT_STEP_CNTR |   // Pedometer interrupt
        SensorBMA423::INT_ACTIVITY |    // Activity interruption
        SensorBMA423::INT_TILT |        // Tilt interrupt
        // SensorBMA423::INT_WAKEUP |      // DoubleTap interrupt
        SensorBMA423::INT_ANY_NO_MOTION,// Any  motion / no motion interrupt
        false);

    sportsIrq = false;
    pmuIrq = false;
    //TODO: Low power consumption not debugged
    if (lightSleep) {
        esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
        // esp_sleep_enable_ext1_wakeup(1ULL << BOARD_BMA423_INT1, ESP_EXT1_WAKEUP_ANY_HIGH);
        // esp_sleep_enable_ext1_wakeup(1ULL << BOARD_PMU_INT, ESP_EXT1_WAKEUP_ALL_LOW);

        gpio_wakeup_enable ((gpio_num_t)BOARD_PMU_INT, GPIO_INTR_LOW_LEVEL);
        gpio_wakeup_enable ((gpio_num_t)BOARD_BMA423_INT1, GPIO_INTR_HIGH_LEVEL);
        esp_sleep_enable_gpio_wakeup ();
        esp_light_sleep_start();
    } else {

        setCpuFrequencyMhz(cpuIdleFreq);
        // setCpuFrequencyMhz(80);
        while (!pmuIrq && !sportsIrq && !watch.getTouched()) {
            delay(300);
            // gpio_wakeup_enable ((gpio_num_t)BOARD_TOUCH_INT, GPIO_INTR_LOW_LEVEL);
            // esp_sleep_enable_timer_wakeup(3 * 1000);
            // esp_light_sleep_start();
        }

        setCpuFrequencyMhz(cpuMaxFreq);
    }

    // Clear Interrupts in Loop
    // watch.readBMA();
    // watch.clearPMU();

    watch.configreFeatureInterrupt(
        SensorBMA423::INT_STEP_CNTR |   // Pedometer interrupt
        SensorBMA423::INT_ACTIVITY |    // Activity interruption
        SensorBMA423::INT_TILT |        // Tilt interrupt
        // SensorBMA423::INT_WAKEUP |      // DoubleTap interrupt
        SensorBMA423::INT_ANY_NO_MOTION,// Any  motion / no motion interrupt
        true);


    lv_disp_trig_activity(NULL);
    // Run once
    lv_task_handler();

    watch.incrementalBrightness(brightnessLevel);
}

void loop()
{
    SensorHandler();

    PMUHandler();

    bool screenTimeout = lv_disp_get_inactive_time(NULL) < DEFAULT_SCREEN_TIMEOUT;
    if (screenTimeout ||
            !canScreenOff ||
            usbPlugIn) {
        if (!screenTimeout) {
            if (usbPlugIn) {
                createChargeUI();
            }
            lv_disp_trig_activity(NULL);
        }
        lv_task_handler();
        delay(2);
    } else {
        lowPowerEnergyHandler();
    }

}

void tileview_change_cb(lv_event_t *e) {
  static uint16_t lastPageID = 0;
  lv_obj_t *tileview = lv_event_get_target(e);
  pageId = lv_obj_get_index(lv_tileview_get_tile_act(tileview));
  lv_event_code_t c = lv_event_get_code(e);
  /*Serial.print("Code : ");
  Serial.print(c);
  uint32_t count =  lv_obj_get_child_cnt(tileview);
  Serial.print(" Count:");
  Serial.print(count);
  Serial.print(" pageId:");
  Serial.println(pageId);*/

  {
    /*if (WiFi.getMode() != WIFI_OFF ) {
      WiFi.removeEvent(WiFiEvent_t::ARDUINO_EVENT_WIFI_SCAN_DONE);
      WiFi.mode(WIFI_OFF);
      Serial.println("WiFi.mode(WIFI_OFF);");
    }
    canScreenOff = true;*/
  }
  lastPageID = pageId;
}

void initUi()
{

    static lv_style_t bgStyle;
    lv_style_init(&bgStyle);
    lv_style_set_bg_color(&bgStyle, lv_color_black());

    tileview = lv_tileview_create(lv_scr_act());
    lv_obj_add_style(tileview, &bgStyle, LV_PART_MAIN);
    lv_obj_set_size(tileview, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_add_event_cb(tileview, tileview_change_cb, LV_EVENT_VALUE_CHANGED, NULL);
    int pId = 0;

    lv_obj_t *t1 = lv_tileview_add_tile(tileview, 0, 0, LV_DIR_HOR);
    pId++;
    lv_obj_t *t2 = lv_tileview_add_tile(tileview, 1, 0, LV_DIR_HOR | LV_DIR_BOTTOM);
    pId++;
    lv_obj_t *t2_1 = lv_tileview_add_tile(tileview, 1, 1, LV_DIR_TOP | LV_DIR_BOTTOM);
    pId++;
    lv_obj_t *t2_2 = lv_tileview_add_tile(tileview, 1, 2, LV_DIR_TOP);
    pId++;

    lv_obj_t *t3 = lv_tileview_add_tile(tileview, 2, 0, LV_DIR_HOR | LV_DIR_BOTTOM);
    pId++;
    lv_obj_t *t3_1 = lv_tileview_add_tile(tileview, 2, 1, LV_DIR_TOP);
    pId++;


    productPinmap(t1);
    analogclock(t2);
    deviceSettings(t2_1);
    datetimeVeiw(t2_2);
    irTvRemoteVeiw(t3);
    irAcRemoteVeiw(t3_1);

    lv_disp_trig_activity(NULL);

    lv_obj_set_tile(tileview, t2, LV_ANIM_OFF);
}

static void draw_part_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t *dsc = lv_event_get_draw_part_dsc(e);
    /*If the cells are drawn...*/
    if (dsc->part == LV_PART_ITEMS) {
        uint32_t row = dsc->id / lv_table_get_col_cnt(obj);
        uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);

        /*Make the texts in the first cell center aligned*/
        if (row == 0) {
            dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
            dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_BLUE), dsc->rect_dsc->bg_color, LV_OPA_20);
            dsc->rect_dsc->bg_opa = LV_OPA_COVER;
        }
        /*In the first column align the texts to the right*/
        else if (col == 0) {
            dsc->label_dsc->align = LV_TEXT_ALIGN_RIGHT;
        }

        /*MAke every 2nd row grayish*/
        if ((row != 0 && row % 2) == 0) {
            dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_GREY), dsc->rect_dsc->bg_color, LV_OPA_10);
            dsc->rect_dsc->bg_opa = LV_OPA_COVER;
        }
    }
}

void productPinmap(lv_obj_t *parent)
{

    struct  board_struct {
        const char *func_name;
        const uint8_t pin;
    } __lilygo[] = {
        {"TFT MOSI", BOARD_TFT_MOSI},
        {"TFT SCK", BOARD_TFT_SCLK},
        {"TFT CS", BOARD_TFT_CS},
        {"TFT DC", BOARD_TFT_DC},
        {"TFT BL", BOARD_TFT_BL},
        {"TOUCH SDA", BOARD_TOUCH_SDA},
        {"TOUCH SCL", BOARD_TOUCH_SCL},
        {"TOUCH INT", BOARD_TOUCH_INT},
        {"SENSOR SDA", BOARD_I2C_SDA},
        {"SENSOR SCL", BOARD_I2C_SCL},
        {"RTC INT", BOARD_RTC_INT_PIN},
        {"PMU INT", BOARD_PMU_INT},
        {"SENSOR INT", BOARD_BMA423_INT1},
        {"IR Remote", BOARD_IR_PIN},
        {"DAC BCK", BOARD_DAC_IIS_BCK},
        {"DAC WS", BOARD_DAC_IIS_WS},
        {"DAC DOUT", BOARD_DAC_IIS_DOUT},
        {"RADIO SCK", BOARD_RADIO_SCK},
        {"RADIO MISO", BOARD_RADIO_MISO},
        {"RADIO MOSI", BOARD_RADIO_MOSI},
        {"RADIO CS", BOARD_RADIO_SS},
        {"RADIO DIO1", BOARD_RADIO_DI01},
        {"RADIO RST", BOARD_RADIO_RST},
        {"RADIO BUSY", BOARD_RADIO_BUSY},
        {"MIC DOUT", BOARD_MIC_DATA},
        {"MIC SCK", BOARD_MIC_CLOCK}
    };

    static lv_style_t cont_style;
    lv_style_init(&cont_style);
    lv_style_set_bg_opa(&cont_style, LV_OPA_100);
    lv_style_set_bg_img_opa(&cont_style, LV_OPA_100);
    lv_style_set_bg_color(&cont_style, lv_color_black());
    // lv_style_set_line_opa(&cont_style, LV_OPA_TRANSP);
    lv_style_set_border_width(&cont_style, 0);
    lv_style_set_text_color(&cont_style, DEFAULT_COLOR);


    lv_obj_t *table = lv_table_create(parent);
    lv_obj_set_scrollbar_mode(table, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(table, LV_DIR_VER);
    lv_obj_add_style(table, &cont_style, LV_PART_SCROLLBAR);
    lv_obj_add_style(table, &cont_style, LV_PART_ITEMS);
    lv_obj_add_style(table, &cont_style, LV_PART_MAIN);

    lv_table_set_cell_value(table, 0, 0, "Name");
    lv_table_set_cell_value(table, 0, 1, "GPIO");
    for (int i = 1; i < sizeof(__lilygo) / sizeof(__lilygo[0]); ++i) {
        lv_table_set_cell_value_fmt(table, i, 0, "%s", __lilygo[i].func_name);
        lv_table_set_cell_value_fmt(table, i, 1, "%d", __lilygo[i].pin);
    }

    lv_obj_add_event_cb(table, draw_part_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

}

void lilygo_qrcode(lv_obj_t *parent, const char *url, const char *str)
{
    lv_color_t bg_color = lv_palette_lighten(LV_PALETTE_YELLOW, 5);
    lv_color_t fg_color = lv_palette_darken(LV_PALETTE_YELLOW, 4);
    lv_coord_t size = 150;
    lv_obj_t *qr = lv_qrcode_create(parent, size, fg_color, bg_color);

    lv_qrcode_update(qr, url, strlen(url));
    lv_obj_center(qr);
    /*Add a border with bg_color*/
    lv_obj_set_style_border_color(qr, bg_color, 0);
    lv_obj_set_style_border_width(qr, 5, 0);

    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, str );
    lv_obj_set_style_text_color(label, DEFAULT_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &font_sandbox, LV_PART_MAIN);
    lv_obj_align_to(label, qr, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

void analogclock(lv_obj_t *parent)
{
    bool antialias = true;
    lv_img_header_t header;

    const void *clock_filename = &clock_face;
    const void *hour_filename = &clock_hour_hand;
    const void *min_filename = &clock_minute_hand;
    const void *sec_filename = &clock_second_hand;

    lv_obj_t *clock_bg =  lv_img_create(parent);
    lv_img_set_src(clock_bg, clock_filename);
    lv_obj_set_size(clock_bg, 240, 240);
    lv_obj_center(clock_bg);


    hour_img = lv_img_create(parent);
    lv_img_decoder_get_info(hour_filename, &header);
    lv_img_set_src(hour_img, hour_filename);
    lv_obj_center(hour_img);
    lv_img_set_pivot(hour_img, header.w / 2, header.h / 2);
    lv_img_set_antialias(hour_img, antialias);

    lv_img_decoder_get_info(min_filename, &header);
    min_img = lv_img_create(parent);
    lv_img_set_src(min_img,  min_filename);
    lv_obj_center(min_img);
    lv_img_set_pivot(min_img, header.w / 2, header.h / 2);
    lv_img_set_antialias(min_img, antialias);

    lv_img_decoder_get_info(sec_filename, &header);
    sec_img = lv_img_create(parent);
    lv_img_set_src(sec_img,  sec_filename);
    lv_obj_center(sec_img);
    lv_img_set_pivot(sec_img, header.w / 2, header.h / 2);
    lv_img_set_antialias(sec_img, antialias);

    static lv_style_t label_style;
    lv_style_init(&label_style);
    lv_style_set_text_color(&label_style, lv_color_white());

    battery_percent = lv_label_create(parent);
    lv_label_set_text(battery_percent, "100");
    lv_obj_align(battery_percent, LV_ALIGN_LEFT_MID, 68, -10);
    lv_obj_add_style(battery_percent, &label_style, LV_PART_MAIN);

    weather_celsius = lv_label_create(parent);
    lv_label_set_text(weather_celsius, "23°C");
    lv_obj_align(weather_celsius, LV_ALIGN_RIGHT_MID, -62, -2);
    lv_obj_add_style(weather_celsius, &label_style, LV_PART_MAIN);

    step_counter = lv_label_create(parent);
    lv_label_set_text(step_counter, "6688");
    lv_obj_align(step_counter, LV_ALIGN_BOTTOM_MID, 0, -55);
    lv_obj_add_style(step_counter, &label_style, LV_PART_MAIN);

    clockTimer =   lv_timer_create([](lv_timer_t *timer) {

        time_t now;
        struct tm  timeinfo;
        time(&now);
        localtime_r(&now, &timeinfo);

        lv_img_set_angle(
            hour_img, ((timeinfo.tm_hour) * 300 + ((timeinfo.tm_min) * 5)) % 3600);
        lv_img_set_angle(min_img, (timeinfo.tm_min) * 60);

        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, sec_img);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_angle);
        lv_anim_set_values(&a, (timeinfo.tm_sec * 60) % 3600,
                           (timeinfo.tm_sec + 1) * 60);
        lv_anim_set_time(&a, 1000);
        lv_anim_start(&a);

        // Update step counter
        lv_label_set_text_fmt(step_counter, "%u", stepCounter);

        // Update battery percent
        int percent = watch.getBatteryPercent();
        lv_label_set_text_fmt(battery_percent, "%d%%", percent == -1 ? 0 : percent);

        // float  temp = watch.readBmaTemp();
        // Serial.print(temp);
        // Serial.println("*C");
        // lv_label_set_text_fmt(weather_celsius, "%d°C", (int)temp);

    },
    1000, NULL);
}

static void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    lv_obj_t *slider_label =  (lv_obj_t *)lv_event_get_user_data(e);
    uint8_t level = (uint8_t)lv_slider_get_value(slider);
    int percentage = map(level, 0, 255, 0, 100);
    lv_label_set_text_fmt(slider_label, "%u%%", percentage);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_CENTER, 0, 0);
    watch.setBrightness(level);
    lcdBacklight = level;
}

void deviceSettings(lv_obj_t *parent) {
  /*Create a transition*/
  static const lv_style_prop_t props[] = {LV_STYLE_BG_COLOR, LV_STYLE_PROP_INV};
  static lv_style_transition_dsc_t transition_dsc;
  lv_style_transition_dsc_init(&transition_dsc, props, lv_anim_path_linear, 300, 0, NULL);

  static lv_style_t style_indicator;
  static lv_style_t style_knob;

  lv_style_init(&style_indicator);
  lv_style_set_bg_opa(&style_indicator, LV_OPA_COVER);
  lv_style_set_bg_color(&style_indicator, DEFAULT_COLOR);
  lv_style_set_radius(&style_indicator, LV_RADIUS_CIRCLE);
  lv_style_set_transition(&style_indicator, &transition_dsc);

  lv_style_init(&style_knob);
  lv_style_set_bg_opa(&style_knob, LV_OPA_COVER);
  lv_style_set_bg_color(&style_knob, DEFAULT_COLOR);
  lv_style_set_border_color(&style_knob, lv_palette_darken(LV_PALETTE_YELLOW, 2));
  lv_style_set_border_width(&style_knob, 2);
  lv_style_set_radius(&style_knob, LV_RADIUS_CIRCLE);
  lv_style_set_pad_all(&style_knob, 6); /*Makes the knob larger*/
  lv_style_set_transition(&style_knob, &transition_dsc);

  static lv_style_t label_style;
  lv_style_init(&label_style);
  lv_style_set_text_color(&label_style, lv_color_white());

// Backlight
  lv_obj_t *label = lv_label_create(parent);
  lv_obj_add_style(label, &label_style, LV_PART_MAIN);
  lv_label_set_text(label, "Backlight");
  lv_obj_set_style_text_font(label, &font_jetBrainsMono, LV_PART_MAIN);
  lv_obj_set_style_text_color(label, DEFAULT_COLOR, LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 5);


  /*Create a slider and add the style*/
  lv_obj_t *slider = lv_slider_create(parent);
  lv_obj_set_size(slider, 150, 30);
  lv_slider_set_range(slider, 5, 255);
  lv_obj_add_style(slider, &style_indicator, LV_PART_INDICATOR);
  lv_obj_add_style(slider, &style_knob, LV_PART_KNOB);
  lv_obj_align_to(slider, label, LV_ALIGN_OUT_BOTTOM_LEFT, 30, 15);
  lv_slider_set_value(slider, lcdBacklight, LV_ANIM_OFF);

  /*Create a label below the slider*/
  lv_obj_t *slider_label = lv_label_create(parent);
  lv_label_set_text_fmt(slider_label, "%u%%", map(lcdBacklight, 0, 255, 0, 100));
  lv_obj_set_style_text_color(slider_label, lv_color_white(), LV_PART_MAIN);
  lv_obj_align_to(slider_label, slider, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(slider, [](lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    lv_obj_t *slider_label =  (lv_obj_t *)lv_event_get_user_data(e);
    uint8_t level = (uint8_t)lv_slider_get_value(slider);
    int percentage = map(level, 0, 255, 0, 100);
    lv_label_set_text_fmt(slider_label, "%u%%", percentage);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_CENTER, 0, 0);
    watch.setBrightness(level);
    lcdBacklight = level;
  }, LV_EVENT_VALUE_CHANGED, slider_label);

  lv_obj_t *sliderLast = slider;
// CPU Idle freq
  label = lv_label_create(parent);
  lv_obj_add_style(label, &label_style, LV_PART_MAIN);
  lv_label_set_text(label, "CPU Idle Freq");
  lv_obj_set_style_text_font(label, &font_jetBrainsMono, LV_PART_MAIN);
  lv_obj_set_style_text_color(label, DEFAULT_COLOR, LV_PART_MAIN);
  lv_obj_align_to(label, sliderLast, LV_ALIGN_OUT_BOTTOM_LEFT, -30, 15);


  /*Create a slider and add the style*/
  slider = lv_slider_create(parent);
  lv_obj_set_size(slider, 150, 30);
  lv_slider_set_range(slider, 1, 2);
  lv_obj_add_style(slider, &style_indicator, LV_PART_INDICATOR);
  lv_obj_add_style(slider, &style_knob, LV_PART_KNOB);
  lv_obj_align_to(slider, label, LV_ALIGN_OUT_BOTTOM_LEFT, 30, 15);
  lv_slider_set_value(slider, cpuIdleFreq / 10, LV_ANIM_OFF);

  /*Create a label below the slider*/
  slider_label = lv_label_create(parent);
  lv_label_set_text_fmt(slider_label, "%uMhz", cpuIdleFreq);
  lv_obj_set_style_text_color(slider_label, lv_color_white(), LV_PART_MAIN);
  lv_obj_align_to(slider_label, slider, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(slider, [](lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    lv_obj_t *slider_label =  (lv_obj_t *)lv_event_get_user_data(e);
    uint8_t level = (uint8_t)lv_slider_get_value(slider);
    lv_label_set_text_fmt(slider_label, "%uMhz", level * 10);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_CENTER, 0, 0);
    cpuIdleFreq = level * 10;
  }, LV_EVENT_VALUE_CHANGED, slider_label);
  sliderLast = slider;

// CPU Max freq
  label = lv_label_create(parent);
  lv_obj_add_style(label, &label_style, LV_PART_MAIN);
  lv_label_set_text(label, "CPU Max Freq");
  lv_obj_set_style_text_font(label, &font_jetBrainsMono, LV_PART_MAIN);
  lv_obj_set_style_text_color(label, DEFAULT_COLOR, LV_PART_MAIN);
  lv_obj_align_to(label, sliderLast, LV_ALIGN_OUT_BOTTOM_LEFT, -30, 15);


  /*Create a slider and add the style*/
  slider = lv_slider_create(parent);
  lv_obj_set_size(slider, 150, 30);
  lv_slider_set_range(slider, 1, 3);
  lv_obj_add_style(slider, &style_indicator, LV_PART_INDICATOR);
  lv_obj_add_style(slider, &style_knob, LV_PART_KNOB);
  lv_obj_align_to(slider, label, LV_ALIGN_OUT_BOTTOM_LEFT, 30, 15);
  lv_slider_set_value(slider, cpuMaxFreq / 80, LV_ANIM_OFF);

  /*Create a label below the slider*/
  slider_label = lv_label_create(parent);
  lv_label_set_text_fmt(slider_label, "%uMhz", cpuMaxFreq);
  lv_obj_set_style_text_color(slider_label, lv_color_white(), LV_PART_MAIN);
  lv_obj_align_to(slider_label, slider, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(slider, [](lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    lv_obj_t *slider_label =  (lv_obj_t *)lv_event_get_user_data(e);
    uint8_t level = (uint8_t)lv_slider_get_value(slider);
    lv_label_set_text_fmt(slider_label, "%uMhz", level * 80);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_CENTER, 0, 0);
    cpuMaxFreq = level * 80;
  }, LV_EVENT_VALUE_CHANGED, slider_label);

  /*Properties to transition*/
  static lv_style_prop_t props_def[] = {
    LV_STYLE_TRANSFORM_WIDTH,
    LV_STYLE_TRANSFORM_HEIGHT,
    LV_STYLE_TEXT_LETTER_SPACE,
    LV_STYLE_PROP_INV
  };

  /*Transition descriptor when going back to the default state.
    *Add some delay to be sure the press transition is visible even if the press was very short*/
  static lv_style_transition_dsc_t transition_dsc_def;
  lv_style_transition_dsc_init(&transition_dsc_def, props_def, lv_anim_path_overshoot, 250, 100, NULL);

  /*Transition descriptor when going to pressed state.
    *No delay, go to presses state immediately*/
  static lv_style_transition_dsc_t transition_dsc_pr;
  lv_style_transition_dsc_init(&transition_dsc_pr, props_def, lv_anim_path_ease_in_out, 250, 0, NULL);

  /*Add only the new transition to he default state*/
  static lv_style_t style_def;
  lv_style_init(&style_def);
  lv_style_set_transition(&style_def, &transition_dsc_def);
  lv_style_set_bg_color(&style_def, lv_palette_main(LV_PALETTE_YELLOW));
  lv_style_set_bg_grad_color(&style_def, lv_palette_darken(LV_PALETTE_YELLOW, 2));

  lv_obj_t *cfg_btn = lv_btn_create(parent);
  lv_obj_set_width(cfg_btn, 130);
  lv_obj_set_height(cfg_btn, 50);
  //lv_obj_add_style(cfg_btn, &style_pr, LV_STATE_PRESSED);
  lv_obj_add_style(cfg_btn, &style_def, LV_PART_MAIN);
  lv_obj_align_to(cfg_btn, slider, LV_ALIGN_OUT_BOTTOM_LEFT, 30, 15);
  lv_obj_t *cfg_label = lv_label_create(cfg_btn);
  lv_label_set_text(cfg_label, "Save CFG");
  lv_obj_center(cfg_label);
  lv_obj_set_style_text_color(cfg_label, lv_color_black(), LV_PART_MAIN);
  lv_obj_add_event_cb(cfg_btn, [](lv_event_t *e) {
    deviceSaveConfig();
  }, LV_EVENT_CLICKED, NULL);
}


static void lv_spinbox_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        bool *inc =  (bool *)lv_event_get_user_data(e);
        lv_obj_t *target = lv_event_get_current_target(e);
        lv_datetime_t *datetime_obj =  (lv_datetime_t *)lv_obj_get_user_data(target);
        if (!datetime_obj) {
            Serial.println(PSTR("datetime_obj is null"));
            return;
        }
        Serial.print(datetime_obj->name);

        if (*inc) {
            lv_spinbox_increment(datetime_obj->obj);
        } else {
            lv_spinbox_decrement(datetime_obj->obj);
        }

    }
}

lv_obj_t *createAdjustButton(lv_obj_t *parent, const char *txt, lv_event_cb_t event_cb, void *user_data)
{
    static lv_style_t cont_style;
    lv_style_init(&cont_style);
    lv_style_set_bg_opa(&cont_style, LV_OPA_TRANSP);
    lv_style_set_bg_img_opa(&cont_style, LV_OPA_TRANSP);
    lv_style_set_text_color(&cont_style, DEFAULT_COLOR);

    lv_obj_t *label_cont = lv_obj_create(parent);
    lv_obj_set_size(label_cont, 210, 90);
    lv_obj_set_scrollbar_mode(label_cont, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_set_flex_flow(label_cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_scroll_dir(label_cont, LV_DIR_NONE);
    lv_obj_set_style_pad_top(label_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(label_cont, 2, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(label_cont, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(label_cont, 5, LV_PART_MAIN);
    lv_obj_set_style_border_color(label_cont, DEFAULT_COLOR, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(label_cont);
    lv_label_set_text(label, txt);
    lv_obj_set_style_text_font(label, &font_siegra, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, DEFAULT_COLOR, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 5, 0);


    lv_obj_t *cont = lv_obj_create(label_cont);
    lv_obj_set_size(cont, 185, 45);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_scroll_dir(cont, LV_DIR_NONE);
    lv_obj_align_to(cont, label, LV_ALIGN_OUT_BOTTOM_LEFT, -6, 5);

    lv_obj_set_style_pad_all(cont, 1, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN);

    lv_coord_t w = 50;
    lv_coord_t h = 40;
    lv_obj_t *btn = lv_btn_create(cont);
    lv_obj_set_size(btn, w, h);
    lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_PLUS, 0);
    lv_obj_add_style(btn, &button_default_style, LV_PART_MAIN);
    lv_obj_add_style(btn, &button_press_style, LV_STATE_PRESSED);



    static bool increment = 1;
    static bool decrement = 0;
    lv_obj_set_user_data(btn, user_data);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, &increment);

    lv_obj_t *spinbox = lv_spinbox_create(cont);
    lv_spinbox_set_step(spinbox, 1);
    lv_spinbox_set_rollover(spinbox, false);
    lv_spinbox_set_cursor_pos(spinbox, 0);

    if (user_data) {
        lv_datetime_t *datetime_obj = (lv_datetime_t *)user_data;
        lv_spinbox_set_digit_format(spinbox, datetime_obj->digitFormat, 0);
        lv_spinbox_set_range(spinbox, datetime_obj->minVal, datetime_obj->maxVal);
        lv_spinbox_set_value(spinbox, datetime_obj->defaultVal);
    }
    lv_obj_set_width(spinbox, 65);
    lv_obj_set_height(spinbox, h + 2);

    lv_obj_set_style_bg_opa(spinbox, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_text_color(spinbox, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_color(spinbox, DEFAULT_COLOR, LV_PART_MAIN);
    lv_obj_set_style_text_font(spinbox, &font_sandbox, LV_PART_MAIN);

    // lv_obj_set_style_bg_opa(spinbox, LV_OPA_TRANSP, LV_PART_SELECTED);
    // lv_obj_set_style_bg_opa(spinbox, LV_OPA_TRANSP, LV_PART_KNOB);
    lv_obj_set_style_bg_opa(spinbox, LV_OPA_TRANSP, LV_PART_CURSOR);


    btn = lv_btn_create(cont);
    lv_obj_set_size(btn, w, h);
    lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_MINUS, 0);
    lv_obj_add_style(btn, &button_default_style, LV_PART_MAIN);
    lv_obj_add_style(btn, &button_press_style, LV_STATE_PRESSED);
    lv_obj_set_user_data(btn, user_data);
    // lv_obj_add_event_cb(btn, lv_spinbox_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, &decrement);

    return spinbox;
}

static void datetime_event_handler(lv_event_t *e)
{
    Serial.println("Save setting datetime.");
    int32_t year =  lv_spinbox_get_value(lv_datetime[0].obj);
    int32_t month =  lv_spinbox_get_value(lv_datetime[1].obj);
    int32_t day =  lv_spinbox_get_value(lv_datetime[2].obj);
    int32_t hour =  lv_spinbox_get_value(lv_datetime[3].obj);
    int32_t minute =  lv_spinbox_get_value(lv_datetime[4].obj);
    int32_t second =  lv_spinbox_get_value(lv_datetime[5].obj);

    Serial.printf_P(PSTR("Y=%dM=%dD=%d H:%dM:%dS:%d\n"), year, month, day,
                  hour, minute, second);

    watch.setDateTime(year, month, day, hour, minute, second);

    // Reading time synchronization from RTC to system time
    watch.hwClockRead();
}

void datetimeVeiw(lv_obj_t *parent)
{
    //set default datetime
    time_t now;
    struct tm  info;
    time(&now);
    localtime_r(&now, &info);
    lv_datetime[0].defaultVal = info.tm_year + 1900;
    lv_datetime[1].defaultVal = info.tm_mon + 1;
    lv_datetime[2].defaultVal = info.tm_mday;
    lv_datetime[3].defaultVal = info.tm_hour;
    lv_datetime[4].defaultVal = info.tm_min ;
    lv_datetime[5].defaultVal = info.tm_sec ;


    static lv_style_t cont_style;
    lv_style_init(&cont_style);
    lv_style_set_bg_opa(&cont_style, LV_OPA_TRANSP);
    lv_style_set_bg_img_opa(&cont_style, LV_OPA_TRANSP);
    lv_style_set_line_opa(&cont_style, LV_OPA_TRANSP);
    lv_style_set_border_width(&cont_style, 0);
    lv_style_set_text_color(&cont_style, DEFAULT_COLOR);

    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_set_size(cont, lv_disp_get_hor_res(NULL), 400);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_add_style(cont, &cont_style, LV_PART_MAIN);

    for (int i = 0; i < sizeof(lv_datetime) / sizeof(lv_datetime[0]); ++i) {
        lv_datetime[i].obj =  createAdjustButton(cont, lv_datetime[i].name, lv_spinbox_event_cb, &(lv_datetime[i]));
    }

    lv_obj_t *btn_cont = lv_obj_create(cont);
    lv_obj_set_size(btn_cont, 210, 60);
    lv_obj_set_scrollbar_mode(btn_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(btn_cont, LV_DIR_NONE);
    lv_obj_set_style_pad_top(btn_cont, 5, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(btn_cont, 5, LV_PART_MAIN);
    lv_obj_set_style_border_opa(btn_cont, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(btn_cont, LV_OPA_TRANSP, LV_PART_MAIN);

    lv_obj_t *btn = lv_btn_create(btn_cont);
    lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_SAVE, 0);
    lv_obj_set_size(btn, 180, 50);
    lv_obj_add_style(btn, &button_default_style, LV_PART_MAIN);
    lv_obj_add_style(btn, &button_press_style, LV_STATE_PRESSED);
    lv_obj_add_event_cb(btn, datetime_event_handler, LV_EVENT_CLICKED, NULL);
}

void settingButtonStyle()
{
    /*Init the button_default_style for the default state*/
    lv_style_init(&button_default_style);

    lv_style_set_radius(&button_default_style, 3);

    lv_style_set_bg_opa(&button_default_style, LV_OPA_100);
    lv_style_set_bg_color(&button_default_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_bg_grad_color(&button_default_style, lv_palette_darken(LV_PALETTE_YELLOW, 2));
    lv_style_set_bg_grad_dir(&button_default_style, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&button_default_style, LV_OPA_40);
    lv_style_set_border_width(&button_default_style, 2);
    lv_style_set_border_color(&button_default_style, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&button_default_style, 8);
    lv_style_set_shadow_color(&button_default_style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_ofs_y(&button_default_style, 8);

    lv_style_set_outline_opa(&button_default_style, LV_OPA_COVER);
    lv_style_set_outline_color(&button_default_style, lv_palette_main(LV_PALETTE_YELLOW));

    lv_style_set_text_color(&button_default_style, lv_color_white());
    lv_style_set_pad_all(&button_default_style, 10);

    /*Init the pressed button_default_style*/
    lv_style_init(&button_press_style);

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&button_press_style, 30);
    lv_style_set_outline_opa(&button_press_style, LV_OPA_TRANSP);

    lv_style_set_translate_y(&button_press_style, 5);
    lv_style_set_shadow_ofs_y(&button_press_style, 3);
    lv_style_set_bg_color(&button_press_style, lv_palette_darken(LV_PALETTE_YELLOW, 2));
    lv_style_set_bg_grad_color(&button_press_style, lv_palette_darken(LV_PALETTE_YELLOW, 4));

    /*Add a transition to the outline*/
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, LV_STYLE_PROP_INV};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_set_transition(&button_press_style, &trans);

}

/*
 ************************************
 *      HARDWARE SETTING            *
 ************************************
*/
void setSportsFlag()
{
    sportsIrq = true;
}

void settingSensor()
{

    //Default 4G ,200HZ
    watch.configAccelerometer();

    watch.enableAccelerometer();

    watch.enablePedometer();

    watch.configInterrupt();

    watch.enableFeature(SensorBMA423::FEATURE_STEP_CNTR |
                        SensorBMA423::FEATURE_ANY_MOTION |
                        SensorBMA423::FEATURE_NO_MOTION |
                        SensorBMA423::FEATURE_ACTIVITY |
                        SensorBMA423::FEATURE_TILT |
                        SensorBMA423::FEATURE_WAKEUP,
                        true);


    watch.enablePedometerIRQ();
    watch.enableTiltIRQ();
    watch.enableWakeupIRQ();
    watch.enableAnyNoMotionIRQ();
    watch.enableActivityIRQ();


    watch.attachBMA(setSportsFlag);

}

void setPMUFlag()
{
    pmuIrq = true;
}

void settingPMU()
{
    watch.clearPMU();

    watch.disableIRQ(XPOWERS_AXP2101_ALL_IRQ);
    // Enable the required interrupt function
    watch.enableIRQ(
        // XPOWERS_AXP2101_BAT_INSERT_IRQ    | XPOWERS_AXP2101_BAT_REMOVE_IRQ      |   //BATTERY
        XPOWERS_AXP2101_VBUS_INSERT_IRQ   | XPOWERS_AXP2101_VBUS_REMOVE_IRQ     |   //VBUS
        XPOWERS_AXP2101_PKEY_SHORT_IRQ    | XPOWERS_AXP2101_PKEY_LONG_IRQ       |  //POWER KEY
        XPOWERS_AXP2101_BAT_CHG_DONE_IRQ  | XPOWERS_AXP2101_BAT_CHG_START_IRQ       //CHARGE
        // XPOWERS_AXP2101_PKEY_NEGATIVE_IRQ | XPOWERS_AXP2101_PKEY_POSITIVE_IRQ   |   //POWER KEY
    );
    watch.attachPMU(setPMUFlag);

}

void settingIRRemote() {
    irsend.begin();
}

