#ifndef __APP_IR_TV_REMOTE_H__
#define __APP_IR_TV_REMOTE_H__

#include "conf.h"

#include <LilyGoLib.h>
#include <LV_Helper.h>
#if __IN_ECLIPSE__
#include "../../src/lvglCpp.h"
#else
#include <lvglCpp.h>
#endif


#include "irTvCodes.h"

#include <IRsend.h>
extern IRsend irsend;

static int selectedTvMode = (int)irTvCodes::SAMSUNG;

void sendIrTv(irTvCodes::type_e mode, unsigned long code) {
  Serial.printf("%d, %d\nselectedMode", (int)mode, code);
  switch(mode) {
    case irTvCodes::SONY:
      irsend.sendSony(code);
      return;
    case irTvCodes::PANASONIC:
      irsend.sendPanasonic64(code);
      return;
    case irTvCodes::LG:
      irsend.sendLG(code);
      return;
    case irTvCodes::JVC:
      irsend.sendJVC(code);
      return;
    case irTvCodes::SHARP:
      irsend.sendSharpRaw(code);
      return;
    case irTvCodes::SAMSUNG:
      irsend.sendSAMSUNG(code);
      return;
    case irTvCodes::NEC:
      irsend.sendNEC(code);
      return;
    /*case TECHNIKA:
      irsend.sendPanasonic64(code);
      return;*/
    default:
      return;
  }
}

void irTvRemoteVeiw(lv_obj_t *parent) {
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

  lvgl::widget::Label title = lvgl::widget::Label(&cont, "TV Remote");
  title.SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);

  lvgl::widget::Object cont1 = lvgl::widget::Object(&cont);
  cont1.SetSize(180, 180);
  cont1.SetScrollbarMode(LV_SCROLLBAR_MODE_OFF);
  cont1.SetFlexFlow(LV_FLEX_FLOW_ROW_WRAP);
  cont1.AddStyle(&cont1_style, LV_PART_MAIN);

  lvgl::widget::DropDown *dd = new lvgl::widget::DropDown(&cont1, "SONY\n"
                          "PANASONIC\n"
                          "LG\n"
                          "JVC\n"
                          "SHARP\n"
                          "SAMSUNG\n"
                          "NEC\n"
                          "BOMB"
                          );
  dd->SetSelected(5);
  dd->SetSize(130, 50);
  dd->AddEventCbValueChanged([](lv_event_t *e) {
    //char buf[32];
    lvgl::widget::DropDown obj(lvgl::widget::Object::EventGetTarget(e), false);
    //obj.getSelectedStr(buf, sizeof(buf));
    uint32_t id = obj.GetSelected();
    selectedTvMode = id + 1;
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
  label = new lvgl::widget::Label(ir_btn, "PWR");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    delay(2000);
    watch.setWaveform(0, 78);
    watch.run();
    if(selectedTvMode == irTvCodes::END) {
      for(int i = 1; i < irTvCodes::END; i++) {
        sendIrTv((irTvCodes::type_e)i, irTvCodes::getPowerCode((irTvCodes::type_e)i));
        delay(100);
      }
    } else {
      sendIrTv((irTvCodes::type_e)selectedTvMode, irTvCodes::getPowerCode((irTvCodes::type_e)selectedTvMode));
    }
    watch.setWaveform(0, 78);
    watch.run();
  });


  ir_btn = new lvgl::widget::Button(&cont1);
  ir_btn->SetSize(130, 50);
  ir_btn->AddStyle(&style_def, LV_PART_MAIN);
  ir_btn->SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);
  label = new lvgl::widget::Label(ir_btn, "CHAN UP");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    watch.setWaveform(0, 78);
    watch.run();
    if(selectedTvMode == irTvCodes::END) {
      for(int i = 1; i < irTvCodes::END; i++) {
        sendIrTv((irTvCodes::type_e)i, irTvCodes::getChanUpCode((irTvCodes::type_e)i));
        delay(100);
      }
    } else {
      sendIrTv((irTvCodes::type_e)selectedTvMode, irTvCodes::getChanUpCode((irTvCodes::type_e)selectedTvMode));
    }
    watch.setWaveform(0, 78);
    watch.run();
  });

  ir_btn = new lvgl::widget::Button(&cont1);
  ir_btn->SetSize(130, 50);
  ir_btn->AddStyle(&style_def, LV_PART_MAIN);
  ir_btn->SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);
  label = new lvgl::widget::Label(ir_btn, "CHAN DN");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    watch.setWaveform(0, 78);
    watch.run();
    if(selectedTvMode == irTvCodes::END) {
      for(int i = 1; i < irTvCodes::END; i++) {
        sendIrTv((irTvCodes::type_e)i, irTvCodes::getChanDownCode((irTvCodes::type_e)i));
        delay(100);
      }
    } else {
      sendIrTv((irTvCodes::type_e)selectedTvMode, irTvCodes::getChanDownCode((irTvCodes::type_e)selectedTvMode));
    }
    watch.setWaveform(0, 78);
    watch.run();
  });

  ir_btn = new lvgl::widget::Button(&cont1);
  ir_btn->SetSize(130, 50);
  ir_btn->AddStyle(&style_def, LV_PART_MAIN);
  ir_btn->SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);
  label = new lvgl::widget::Label(ir_btn, "VOL UP");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    if(selectedTvMode == irTvCodes::END) {
      for(int i = 1; i < irTvCodes::END; i++) {
        sendIrTv((irTvCodes::type_e)i, irTvCodes::getVolUpCode((irTvCodes::type_e)i));
        delay(100);
      }
    } else {
      sendIrTv((irTvCodes::type_e)selectedTvMode, irTvCodes::getVolUpCode((irTvCodes::type_e)selectedTvMode));
    }
  });

  ir_btn = new lvgl::widget::Button(&cont1);
  ir_btn->SetSize(130, 50);
  ir_btn->AddStyle(&style_def, LV_PART_MAIN);
  ir_btn->SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);
  label = new lvgl::widget::Label(ir_btn, "VOL DN");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    if(selectedTvMode == irTvCodes::END) {
      for(int i = 1; i < irTvCodes::END; i++) {
        sendIrTv((irTvCodes::type_e)i, irTvCodes::getVolDownCode((irTvCodes::type_e)i));
        delay(100);
      }
    } else {
      sendIrTv((irTvCodes::type_e)selectedTvMode, irTvCodes::getVolDownCode((irTvCodes::type_e)selectedTvMode));
    }
  });

  ir_btn = new lvgl::widget::Button(&cont1);
  ir_btn->SetSize(130, 50);
  ir_btn->AddStyle(&style_def, LV_PART_MAIN);
  ir_btn->SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);
  label = new lvgl::widget::Label(ir_btn, "CHANGE SOURCE");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    watch.setWaveform(0, 78);
    watch.run();
    if(selectedTvMode == irTvCodes::END) {
      for(int i = 1; i < irTvCodes::END; i++) {
        sendIrTv((irTvCodes::type_e)i, irTvCodes::getSourceCode((irTvCodes::type_e)i));
        delay(100);
      }
    } else {
      sendIrTv((irTvCodes::type_e)selectedTvMode, irTvCodes::getSourceCode((irTvCodes::type_e)selectedTvMode));
    }
    watch.setWaveform(0, 78);
    watch.run();
  });

  ir_btn = new lvgl::widget::Button(&cont1);
  ir_btn->SetSize(130, 50);
  ir_btn->AddStyle(&style_def, LV_PART_MAIN);
  ir_btn->SetAlign(LV_ALIGN_OUT_LEFT_TOP, 5, 5);
  label = new lvgl::widget::Label(ir_btn, "CHANGE MEDIA");
  label->SetCenter();
  label->SetStyleTextColor(lv_color_black(), LV_PART_MAIN);
  label->AddEventCbClicked([](lv_event_t *e) {
    watch.setWaveform(0, 78);
    watch.run();
    if(selectedTvMode == irTvCodes::END) {
      for(int i = 1; i < irTvCodes::END; i++) {
        sendIrTv((irTvCodes::type_e)i, irTvCodes::getMediaCode((irTvCodes::type_e)i));
        delay(100);
      }
    } else {
      sendIrTv((irTvCodes::type_e)selectedTvMode, irTvCodes::getMediaCode((irTvCodes::type_e)selectedTvMode));
    }
    watch.setWaveform(0, 78);
    watch.run();
  });
}

#endif