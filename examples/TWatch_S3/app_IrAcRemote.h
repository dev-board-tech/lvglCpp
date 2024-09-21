#ifndef __APP_IR_AC_REMOTE_H__
#define __APP_IR_AC_REMOTE_H__

#include "conf.h"

#include <Arduino.h>

#include <LilyGoLib.h>
#include <LV_Helper.h>
#if __IN_ECLIPSE__
#include "../../src/lvglCpp.h"
#else
#include <lvglCpp.h>
#endif


#include "irTvCodes.h"

#include <FS.h>
#include "FFat.h"
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <ir_LG.h>
#include <IRsend.h>
extern IRsend irsend;
static IRLgAc ac(BOARD_IR_PIN);  // Set the GPIO to be used to sending the message.

static int selectedAc = 0;

static bool acPower = false;
static uint8_t acTemperature = 18;
static uint8_t acFanPower = 3;
static uint8_t acMode = 0;
static uint8_t acVSwing = 5;
static uint8_t acHSwing = 0;

const char irAcCfgFileName[] = "/IrAcRemote.cfg";

static void acSendCommands() {
  ac.setPower(true);
  int fanPwr = acFanPower;
  if(acFanPower > kLgAcFanMedium) {
    fanPwr++;
  }
  uint32_t vSwing;
  switch(acVSwing) {
    case 0: vSwing = kLgAcSwingVLowest; break;
    case 1: vSwing = kLgAcSwingVLow; break;
    case 2: vSwing = kLgAcSwingVMiddle; break;
    case 3: vSwing = kLgAcSwingVUpperMiddle; break;
    case 4: vSwing = kLgAcSwingVHigh; break;
    case 5: vSwing = kLgAcSwingVHighest; break;
    case 6: vSwing = kLgAcSwingVSwing; break;
    case 7: vSwing = kLgAcSwingVOff; break;
    default: return;
  }
  uint32_t hSwing;
  switch(acHSwing) {
    case 0:hSwing = kLgAcSwingHAuto; break;
    case 1:hSwing = kLgAcSwingHOff; break;
    default: return;
  }
  ac.setFan(fanPwr);
  ac.setMode(acMode);
  ac.setTemp(acTemperature + 18);
  ac.setSwingV(vSwing);
  ac.setSwingH(hSwing);
  ac.send();
}

static void irAcSaveConfig() {
    File cfgFile = FFat.open(irAcCfgFileName, "w");
    if(cfgFile) {
      JsonDocument docNew;
      docNew["selectedAc"] = selectedAc;
      docNew["acPower"] = acPower;
      docNew["acTemperature"] = acTemperature;
      docNew["acFanPower"] = acFanPower;
      docNew["acMode"] = acMode;
      docNew["acVSwing"] = acVSwing;
      docNew["acHSwing"] = acHSwing;
      if (serializeJson(docNew, cfgFile) == 0) {
        Serial.printf_P(PSTR("ERR: Failed to write IrAcRemote.cfg file\n"));
      }
      cfgFile.flush();
      cfgFile.close();
    }
}

void irAcRemoteVeiw(lv_obj_t *parent) {
  File cfgFile = FFat.open(irAcCfgFileName, "r");
  if(!cfgFile) {
    Serial.printf_P(PSTR("WARNING: IrAcRemote.cfg file not found, create one\n"));
    cfgFile = FFat.open(irAcCfgFileName, "w");
    JsonDocument docNew;
    docNew["selectedAc"] = selectedAc;
    docNew["acPower"] = acPower;
    docNew["acTemperature"] = acTemperature;
    docNew["acFanPower"] = acFanPower;
    docNew["acMode"] = acMode;
    docNew["acVSwing"] = acVSwing;
    docNew["acHSwing"] = acHSwing;
    if (serializeJson(docNew, cfgFile) == 0) {
      Serial.printf_P(PSTR("ERR: Failed to write IrAcRemote.cfg file\n"));
    }
    cfgFile.flush();
    cfgFile.close();
    cfgFile = FFat.open(irAcCfgFileName, "r");
    if(!cfgFile) {
      Serial.printf_P(PSTR("ERR: Failed to reload IrAcRemote.cfg file\n"));
    }
  }
// Load IrAcRemote.cfg
  JsonDocument docR;
  DeserializationError error = deserializeJson(docR, cfgFile);
  if (!error) {
    selectedAc = docR["selectedAc"];
    acPower = docR["acPower"];
    acTemperature = docR["acTemperature"];
    acFanPower = docR["acFanPower"];
    acMode = docR["acMode"];
    acVSwing = docR["acVSwing"];
    acHSwing = docR["acHSwing"];
    Serial.printf_P(PSTR("OK: Load IrAcRemote.cfg\n"));
  }
  if(cfgFile) {
    cfgFile.close();
  }

  ac.begin();
  /*Properties to transition*/  
  static lvgl::style::Prop props = lvgl::style::Prop();
  props.Add(LV_STYLE_TRANSFORM_WIDTH);
  props.Add(LV_STYLE_TRANSFORM_HEIGHT);
  props.Add(LV_STYLE_TEXT_LETTER_SPACE);
  /*Transition descriptor when going back to the default state.
    *Add some delay to be sure the press transition is visible even if the press was very short*/
  static lvgl::style::Transition transition_dsc_def = lvgl::style::Transition(props, lv_anim_path_overshoot, 250, 100);
  /*Transition descriptor when going to pressed state.
    *No delay, go to presses state immediately*/
  static lvgl::style::Transition transition_dsc_pr = lvgl::style::Transition(props, lv_anim_path_ease_in_out, 250);
  /////////////////////////////!!!!!!!!!!!!!!!!!!!

  static lvgl::Style cont_style = lvgl::Style();
  cont_style.SetBgOpacity(LV_OPA_TRANSP);
  cont_style.SetBgImageOpacity(LV_OPA_TRANSP);
  cont_style.SetLineOpacity(LV_OPA_TRANSP);
  cont_style.SetBorderWidth(0);
  cont_style.SetTextColor(DEFAULT_COLOR);

  lvgl::widget::Object cont = lvgl::widget::Object(parent);
  cont.SetSize(lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
  cont.SetScrollbarMode(LV_SCROLLBAR_MODE_OFF);
  cont.SetFlexFlow(LV_FLEX_FLOW_COLUMN);
  cont.SetScrollDirection(LV_DIR_VER);
  cont.AddStyle(&cont_style, LV_PART_MAIN);

  static lvgl::Style cont1_style = lvgl::Style();
  cont1_style.SetBgOpacity(LV_OPA_TRANSP);
  cont1_style.SetBgImageOpacity(LV_OPA_TRANSP);
  cont1_style.SetLineOpacity(LV_OPA_TRANSP);
  cont1_style.SetTextColor(lv_color_white());
  cont1_style.SetBorderWidth(5);
  cont1_style.SetBorderColor(DEFAULT_COLOR);
  cont1_style.SetOutlineColor(DEFAULT_COLOR);

  lvgl::widget::Label title = lvgl::widget::Label(&cont, "AC Remote");
  title.SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);

  lvgl::widget::Object cont1 = lvgl::widget::Object(&cont);
  cont1.SetSize(180, 180);
  cont1.SetScrollbarMode(LV_SCROLLBAR_MODE_OFF);
  cont1.SetFlexFlow(LV_FLEX_FLOW_ROW_WRAP);
  cont1.AddStyle(&cont1_style, LV_PART_MAIN);

  lvgl::widget::DropDown *dd;
  dd = new lvgl::widget::DropDown(&cont1, "LG");
  dd->SetSelected(selectedAc);
  dd->SetSize(130, 50);
  dd->AddEventCbValueChanged([](lv_event_t *e) {
    //char buf[32];
    lvgl::widget::DropDown obj(lvgl::widget::Object::EventGetTarget(e), false);
    //obj.getSelectedStr(buf, sizeof(buf));
    uint32_t id = obj.GetSelected();
    selectedAc = id + 1;
  });

  /*Add only the new transition to he default state*/
  static lvgl::Style style_def = lvgl::Style();
  style_def.SetTransition(transition_dsc_def.Get());
  style_def.SetBgColor(lv_palette_main(LV_PALETTE_YELLOW));
  style_def.SetBgGradientColor(lv_palette_darken(LV_PALETTE_YELLOW, 2));

  lvgl::widget::Button *ir_btn;
  lvgl::widget::Label *label;

  ir_btn = new lvgl::widget::Button(&cont1);
  ir_btn->SetSize(130, 50);
  ir_btn->AddStyle(&style_def, LV_PART_MAIN);
  ir_btn->SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);
  label = new lvgl::widget::Label(ir_btn, "AC Off");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    acPower = false;
    acSendCommands();
  });

  ir_btn = new lvgl::widget::Button(&cont1);
  ir_btn->SetSize(130, 50);
  ir_btn->AddStyle(&style_def, LV_PART_MAIN);
  ir_btn->SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);
  label = new lvgl::widget::Label(ir_btn, "AC On");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    acPower = true;
    acSendCommands();
  });

// Select acTemperature
  dd = new lvgl::widget::DropDown(&cont1, "18°C\n19°C\n20°C\n21°C\n"
                              "22°C\n23°C\n24°C\n25°C\n"
                              "26°C\n27°C\n28°C\n29°C\n30°C");
  dd->AddFlag(LV_OBJ_FLAG_EVENT_BUBBLE);
  dd->SetSelected(acTemperature);
  dd->SetSize(130, 50);
  dd->AddEventCbValueChanged([](lv_event_t *e) {
    lvgl::widget::DropDown obj(lvgl::widget::Object::EventGetTarget(e), false);
    uint32_t id = obj.GetSelected();
    acTemperature = id;
    acSendCommands();
  });

// Select fan power
  dd = new lvgl::widget::DropDown(&cont1, "Fan LLow\n"
                                  "Fan Low\n"
                                  "Fan Med\n"
                                  "Fan Max\n"
                                  "Fan Auto");
  dd->AddFlag(LV_OBJ_FLAG_EVENT_BUBBLE);
  dd->SetSelected(acTemperature);
  dd->SetSize(130, 50);
  dd->AddEventCbValueChanged([](lv_event_t *e) {
    lvgl::widget::DropDown obj(lvgl::widget::Object::EventGetTarget(e), false);
    uint32_t id = obj.GetSelected();
    acFanPower = id;
    acSendCommands();
  });

// Select ac mode
  dd = new lvgl::widget::DropDown(&cont1, "Mode Cool\n"
                                  "Mode Dry\n"
                                  "Mode Fan\n"
                                  "Mode Auto\n"
                                  "Mode Heat");
  dd->AddFlag(LV_OBJ_FLAG_EVENT_BUBBLE);
  dd->SetSelected(acTemperature);
  dd->SetSize(130, 50);
  dd->AddEventCbValueChanged([](lv_event_t *e) {
   lvgl::widget::DropDown obj(lvgl::widget::Object::EventGetTarget(e), false);
    uint32_t id = obj.GetSelected();
    acMode = id;
    acSendCommands();
  });

// Select V Swing mode
  dd = new lvgl::widget::DropDown(&cont1, "Swing VLowest\n"
                                  "Swing VLow\n"
                                  "Swing VMid\n"
                                  "Swing VUpMid\n"
                                  "Swing VHigh\n"
                                  "Swing VHighest\n"
                                  "Swing VSwing\n"
                                  "Swing VOff");
  dd->AddFlag(LV_OBJ_FLAG_EVENT_BUBBLE);
  dd->SetSelected(acTemperature);
  dd->SetSize(130, 50);
  dd->AddEventCbValueChanged([](lv_event_t *e) {
    lvgl::widget::DropDown obj(lvgl::widget::Object::EventGetTarget(e), false);
    uint32_t id = obj.GetSelected();
    acVSwing = id;
    acSendCommands();
  });


// Select V Swing mode
  dd = new lvgl::widget::DropDown(&cont1, "Swing HAuto\n"
                                  "Swing HOff");
  dd->AddFlag(LV_OBJ_FLAG_EVENT_BUBBLE);
  dd->SetSelected(acTemperature);
  dd->SetSize(130, 50);
  dd->AddEventCbValueChanged([](lv_event_t *e) {
    lvgl::widget::DropDown obj(lvgl::widget::Object::EventGetTarget(e), false);
    uint32_t id = obj.GetSelected();
    acHSwing = id;
    acSendCommands();
  });

  ir_btn = new lvgl::widget::Button(&cont1);
  ir_btn->SetSize(130, 50);
  ir_btn->AddStyle(&style_def, LV_PART_MAIN);
  ir_btn->SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);
  label = new lvgl::widget::Label(ir_btn, "Save CFG");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    irAcSaveConfig();
  });
}








#endif