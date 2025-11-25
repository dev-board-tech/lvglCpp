/*
 * Pwd.cpp
 *
 *  Created on: Nov 13, 2025
 *      Author: morgoth
 */

#include "PwdBox.h"

#ifdef __cplusplus
extern "C" {
#endif
/*********************
 *      DEFINES
 *********************/
#define LV_PWDBOX_FLAG_AUTO_PARENT  LV_OBJ_FLAG_WIDGET_1        /*Mark that the parent was automatically created*/
#define MY_CLASS    &lv_pwdbox_class
/**********************
 *  STATIC VARIABLES
 **********************/
static const char pwdPwd[] = "Password:";
static const char pwdOldPwd[] = "Old password:";
static const char pwdNewPwd[] = "New password:";
static const char pwdRepeatPwd[] = "Repeat new password:";

static const char *pwdBtns[] = {
	"Ok",
	"Cancel",
	""
};
extern const lv_obj_class_t lv_obj_class;
const lv_obj_class_t lv_pwdbox_class = {
    .base_class = &lv_obj_class,
    .width_def = LV_DPI_DEF * 2,
    .height_def = LV_SIZE_CONTENT,
    .instance_size = sizeof(lv_pwdbox_t)
};

const lv_obj_class_t lv_pwdbox_content_class = {
    .base_class = &lv_obj_class,
    .width_def = LV_PCT(100),
    .height_def = LV_SIZE_CONTENT,
    .instance_size = sizeof(lv_obj_t)
};

const lv_obj_class_t lv_pwdbox_backdrop_class = {
    .base_class = &lv_obj_class,
    .width_def = LV_PCT(100),
    .height_def = LV_PCT(100),
    .instance_size = sizeof(lv_obj_t)
};

static lv_pwdbox_t * pwdbox;
static lv_obj_t * obj;
static bool chngPwd;

static const char * kbUserNameMapL[] = {
                          "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", LV_SYMBOL_BACKSPACE, "\n",
                          "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "\n",
						  "AB", "a", "s", "d", "f", "g", "h", "j", "k", "l", "\n",
                          "z", "x", "c", "v", "b", "n", "m", "_", LV_SYMBOL_OK, NULL
                        };

static const char * kbUserNameMapU[] = {
                          "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", LV_SYMBOL_BACKSPACE, "\n",
                          "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "\n",
						  "ab", "A", "S", "D", "F", "G", "H", "J", "K", "L", "\n",
                          "Z", "X", "C", "V", "B", "N", "M", "_", LV_SYMBOL_OK, NULL
                        };

/*Set the relative width of the buttons and other controls*/
static const lv_btnmatrix_ctrl_t kbUserNameCtrl[] = {
                          4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6,
                          4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						  5, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                          4, 4, 4, 4, 4, 4, 4, 4, 6
                        };

lv_obj_t * lv_pwdbox_create(lv_obj_t * parent, bool changePwd) {
    LV_LOG_INFO("begin");
    bool auto_parent = false;
    if(parent == NULL) {
        auto_parent = true;
        parent = lv_obj_class_create_obj(&lv_pwdbox_backdrop_class, lv_layer_top());
        LV_ASSERT_MALLOC(parent);
        lv_obj_class_init_obj(parent);
        lv_obj_clear_flag(parent, LV_OBJ_FLAG_IGNORE_LAYOUT);
        lv_obj_set_size(parent, LV_PCT(100), LV_PCT(100));
    }

    obj = lv_obj_class_create_obj(&lv_pwdbox_class, parent);
    LV_ASSERT_MALLOC(obj);
    if(obj == NULL) return NULL;
    lv_obj_class_init_obj(obj);
    pwdbox = (lv_pwdbox_t *)obj;
    chngPwd = changePwd;

    if(auto_parent) lv_obj_add_flag(obj, LV_PWDBOX_FLAG_AUTO_PARENT);

    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_row(obj, 7, NULL);
    lv_obj_set_style_pad_column(obj, 7, NULL);
	lv_obj_set_style_pad_all(obj, 10, NULL);
	lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_LIGHT_BLUE), NULL);
	lv_obj_set_style_bg_opa(obj, 0xFFFFFFFF, NULL);

	pwdbox->text1 = lv_label_create(obj);
	LV_ASSERT_NULL(pwdbox->text1);
	lv_label_set_text(pwdbox->text1, changePwd ? pwdOldPwd : pwdPwd);
	lv_label_set_long_mode(pwdbox->text1, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(pwdbox->text1, lv_pct(100));

	pwdbox->textArea1 = lv_textarea_create(obj);
	LV_ASSERT_NULL(pwdbox->textArea1);
	lv_obj_set_width(pwdbox->textArea1, lv_pct(100));
	lv_textarea_set_one_line(pwdbox->textArea1, true);
	lv_textarea_set_password_mode(pwdbox->textArea1, true);
	lv_obj_add_event_cb(pwdbox->textArea1, (lv_event_cb_t)([](lv_event_t *e) {
		lv_obj_t *ta = lv_event_get_target(e);
		uint32_t btn_id = lv_keyboard_get_selected_btn(ta);
		const char * txt = lv_keyboard_get_btn_text(ta, btn_id);
		lv_keyboard_set_mode(pwdbox->kbd, LV_KEYBOARD_MODE_USER_1);
		lv_keyboard_set_textarea(pwdbox->kbd, pwdbox->textArea1);
		lv_obj_clear_flag(pwdbox->kbd, LV_OBJ_FLAG_HIDDEN);
		if(chngPwd) {
			lv_obj_clear_state(pwdbox->textArea2, LV_STATE_FOCUSED);
			lv_obj_clear_state(pwdbox->textArea3, LV_STATE_FOCUSED);
		}
		int to = (int)lvgl::widget::Object::EventGetUserData(e);
		lv_obj_scroll_to_y(obj, to, LV_ANIM_ON);
	}), LV_EVENT_CLICKED, (void *)0);

	if(!changePwd) {
		pwdbox->text2 = NULL;
		pwdbox->textArea2 = NULL;
		pwdbox->text3 = NULL;
		pwdbox->textArea3 = NULL;
	} else {
	    pwdbox->text2 = lv_label_create(obj);
		LV_ASSERT_NULL(pwdbox->text2);
	    lv_label_set_text(pwdbox->text2, pwdNewPwd);
	    lv_label_set_long_mode(pwdbox->text2, LV_LABEL_LONG_WRAP);
	    lv_obj_set_width(pwdbox->text2, lv_pct(100));

	    pwdbox->textArea2 = lv_textarea_create(obj);
		LV_ASSERT_NULL(pwdbox->textArea2);
	    lv_obj_set_width(pwdbox->textArea2, lv_pct(100));
	    lv_textarea_set_one_line(pwdbox->textArea2, true);
	    lv_textarea_set_password_mode(pwdbox->textArea2, true);
		lv_obj_add_event_cb(pwdbox->textArea2, (lv_event_cb_t)([](lv_event_t *e) {
			lv_keyboard_set_mode(pwdbox->kbd, LV_KEYBOARD_MODE_USER_1);
			lv_keyboard_set_textarea(pwdbox->kbd, pwdbox->textArea2);
			lv_obj_clear_flag(pwdbox->kbd, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_state(pwdbox->textArea1, LV_STATE_FOCUSED);
			lv_obj_clear_state(pwdbox->textArea3, LV_STATE_FOCUSED);
			int to = (int)lvgl::widget::Object::EventGetUserData(e);
			lv_obj_scroll_to_y(obj, to, LV_ANIM_ON);
		}), LV_EVENT_CLICKED, (void *)65);

		pwdbox->text3 = lv_label_create(obj);
		LV_ASSERT_NULL(pwdbox->text3);
	    lv_label_set_text(pwdbox->text3, pwdRepeatPwd);
	    lv_label_set_long_mode(pwdbox->text3, LV_LABEL_LONG_WRAP);
	    lv_obj_set_width(pwdbox->text3, lv_pct(100));

	    pwdbox->textArea3 = lv_textarea_create(obj);
		LV_ASSERT_NULL(pwdbox->textArea3);
	    lv_obj_set_width(pwdbox->textArea3, lv_pct(100));
	    lv_textarea_set_one_line(pwdbox->textArea3, true);
	    lv_textarea_set_password_mode(pwdbox->textArea3, true);
		lv_obj_add_event_cb(pwdbox->textArea3, (lv_event_cb_t)([](lv_event_t *e) {
			lv_keyboard_set_mode(pwdbox->kbd, LV_KEYBOARD_MODE_USER_1);
			lv_keyboard_set_textarea(pwdbox->kbd, pwdbox->textArea3);
			lv_obj_clear_flag(pwdbox->kbd, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_state(pwdbox->textArea1, LV_STATE_FOCUSED);
			lv_obj_clear_state(pwdbox->textArea2, LV_STATE_FOCUSED);
			int to = (int)lvgl::widget::Object::EventGetUserData(e);
			lv_obj_scroll_to_y(obj, to, LV_ANIM_ON);
		}), LV_EVENT_CLICKED, (void *)170);

	}

	pwdbox->kbd = lv_keyboard_create(parent);
	LV_ASSERT_NULL(pwdbox->kbd);
	lv_obj_set_size(pwdbox->kbd, lv_obj_get_width(parent) - 4, lv_obj_get_height(parent) / 2);
	lv_keyboard_set_textarea(pwdbox->kbd, pwdbox->textArea1);
	lv_obj_add_state(pwdbox->textArea1, LV_STATE_FOCUSED);
	lv_keyboard_set_mode(pwdbox->kbd, LV_KEYBOARD_MODE_USER_1);
	lv_keyboard_set_map(pwdbox->kbd, LV_KEYBOARD_MODE_USER_1, kbUserNameMapL, kbUserNameCtrl);
	lv_keyboard_set_map(pwdbox->kbd, LV_KEYBOARD_MODE_USER_2, kbUserNameMapU, kbUserNameCtrl);
	lv_obj_add_event_cb(pwdbox->kbd, (lv_event_cb_t)([](lv_event_t *e) {
		lv_event_code_t code = lv_event_get_code(e);
		if(code == LV_EVENT_VALUE_CHANGED) {
			lv_obj_t * kb = lv_event_get_target(e);
			const char * btn_txt = lv_keyboard_get_btn_text(kb, lv_keyboard_get_selected_btn(kb));
			if(btn_txt) {
				if(strcmp(btn_txt, LV_SYMBOL_OK) == NULL) {
					if(chngPwd) {
						if(lv_keyboard_get_textarea(kb) == pwdbox->textArea1) {
							lv_keyboard_set_textarea(pwdbox->kbd, pwdbox->textArea2);
							lv_obj_clear_state(pwdbox->textArea1, LV_STATE_FOCUSED);
							lv_obj_add_state(pwdbox->textArea2, LV_STATE_FOCUSED);
							lv_obj_scroll_to_y(obj, 65, LV_ANIM_ON);
						} else if(lv_keyboard_get_textarea(kb) == pwdbox->textArea2) {
							lv_keyboard_set_textarea(pwdbox->kbd, pwdbox->textArea3);
							lv_obj_clear_state(pwdbox->textArea2, LV_STATE_FOCUSED);
							lv_obj_add_state(pwdbox->textArea3, LV_STATE_FOCUSED);
							lv_obj_scroll_to_y(obj, 170, LV_ANIM_ON);
						}
					}
				} else if(strcmp(btn_txt, "AB") == NULL) {
					lv_keyboard_set_mode(pwdbox->kbd, LV_KEYBOARD_MODE_USER_2);
					lv_textarea_del_char(lv_keyboard_get_textarea(kb));
					lv_textarea_del_char(lv_keyboard_get_textarea(kb));
				} else if(strcmp(btn_txt, "ab") == NULL) {
					lv_keyboard_set_mode(pwdbox->kbd, LV_KEYBOARD_MODE_USER_1);
					lv_textarea_del_char(lv_keyboard_get_textarea(kb));
					lv_textarea_del_char(lv_keyboard_get_textarea(kb));
				}
			}
		}
	}), LV_EVENT_ALL, NULL);

    pwdbox->btns = lv_btnmatrix_create(obj);
	lv_btnmatrix_set_map(pwdbox->btns, pwdBtns);
	lv_btnmatrix_set_btn_ctrl_all(pwdbox->btns, LV_BTNMATRIX_CTRL_CLICK_TRIG | LV_BTNMATRIX_CTRL_NO_REPEAT);
	uint32_t btn_cnt = 0;
	while(pwdBtns[btn_cnt] && pwdBtns[btn_cnt][0] != '\0') {
		btn_cnt++;
	}
	const lv_font_t * font = lv_obj_get_style_text_font(pwdbox->btns, LV_PART_ITEMS);
	lv_coord_t btn_h = lv_font_get_line_height(font) + LV_DPI_DEF / 10;
	lv_obj_set_size(pwdbox->btns, btn_cnt * (2 * LV_DPI_DEF / 3), btn_h);
	lv_obj_set_style_max_width(pwdbox->btns, lv_pct(100), 0);
	lv_obj_add_flag(pwdbox->btns, LV_OBJ_FLAG_EVENT_BUBBLE);    /*To see the event directly on the pwd box*/
	lv_obj_set_style_pad_all(pwdbox->btns, 0, NULL);
	lv_obj_set_style_bg_color(pwdbox->btns, lv_palette_main(LV_PALETTE_LIGHT_BLUE), NULL);
	lv_obj_set_style_border_width(pwdbox->btns, 0, NULL);

	if(changePwd) {
		lv_obj_set_y(obj, 0);
		lv_obj_set_height(obj, lv_obj_get_height(parent) / 2);
	} else {
		lv_obj_set_y(obj, 10);

	}
	return obj;
}

const char * lv_msgbox_get_text1(lv_obj_t * obj) {
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_pwdbox_t * pwdbox = (lv_pwdbox_t *)obj;
    return lv_textarea_get_text(pwdbox->textArea1);
}

const char * lv_msgbox_get_text2(lv_obj_t * obj) {
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_pwdbox_t * pwdbox = (lv_pwdbox_t *)obj;
    return lv_textarea_get_text(pwdbox->textArea2);
}

const char * lv_msgbox_get_text3(lv_obj_t * obj) {
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_pwdbox_t * pwdbox = (lv_pwdbox_t *)obj;
    return lv_textarea_get_text(pwdbox->textArea3);
}

lv_obj_t * lv_pwdbox_get_btns(lv_obj_t * obj) {
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_pwdbox_t * pwdbox = (lv_pwdbox_t *)obj;
    return pwdbox->btns;
}

uint16_t lv_pwdbox_get_active_btn(lv_obj_t * pwdbox) {
    LV_ASSERT_OBJ(pwdbox, MY_CLASS);
    lv_obj_t * btnm = lv_pwdbox_get_btns(pwdbox);
    return lv_btnmatrix_get_selected_btn(btnm);
}

const char * lv_pwdbox_get_active_btn_text(lv_obj_t * pwdbox) {
    LV_ASSERT_OBJ(pwdbox, MY_CLASS);
    lv_obj_t * btnm = lv_pwdbox_get_btns(pwdbox);
    return lv_btnmatrix_get_btn_text(btnm, lv_btnmatrix_get_selected_btn(btnm));
}

void lv_pwdbox_close(lv_obj_t * pwdbox) {
    LV_ASSERT_OBJ(pwdbox, MY_CLASS);
    if(lv_obj_has_flag(pwdbox, LV_PWDBOX_FLAG_AUTO_PARENT)) lv_obj_del(lv_obj_get_parent(pwdbox));
    else lv_obj_del(pwdbox);
}

void lv_pwdbox_close_async(lv_obj_t * dialog) {
    LV_ASSERT_OBJ(dialog, MY_CLASS);
    if(lv_obj_has_flag(dialog, LV_PWDBOX_FLAG_AUTO_PARENT)) lv_obj_del_async(lv_obj_get_parent(dialog));
    else lv_obj_del_async(dialog);
}
#ifdef __cplusplus
}
#endif

