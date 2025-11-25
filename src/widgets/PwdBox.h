/*
 * Pwd.h
 *
 *  Created on: Nov 13, 2025
 *      Author: morgoth
 */

#ifndef LIBRARIES_LVGLCPP_SRC_WIDGETS_PWDBOX_H_
#define LIBRARIES_LVGLCPP_SRC_WIDGETS_PWDBOX_H_

#include "Object.h"

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    lv_obj_t obj;
    //lv_obj_t * content;
    lv_obj_t * text1;
    lv_obj_t * textArea1;
    lv_obj_t * btns;
    lv_obj_t * kbd;
    lv_obj_t * text2;
    lv_obj_t * textArea2;
    lv_obj_t * text3;
    lv_obj_t * textArea3;
} lv_pwdbox_t;

lv_obj_t * lv_pwdbox_create(lv_obj_t * parent, bool changePwd);
const char * lv_msgbox_get_text1(lv_obj_t * obj);
const char * lv_msgbox_get_text2(lv_obj_t * obj);
const char * lv_msgbox_get_text3(lv_obj_t * obj);
lv_obj_t * lv_pwdbox_get_btns(lv_obj_t * obj);
uint16_t lv_pwdbox_get_active_btn(lv_obj_t * mbox);
const char * lv_pwdbox_get_active_btn_text(lv_obj_t * mbox);
void lv_pwdbox_close(lv_obj_t * mbox);
void lv_pwdbox_close_async(lv_obj_t * dialog);
#ifdef __cplusplus
}
#endif
namespace lvgl {
	namespace widget {
		class PwdBox : public Object {
			public:
					PwdBox(lv_obj_t * parent, bool changePwd) {
					_obj = lv_pwdbox_create(parent, changePwd);
					_child = NULL;
					_childs = NULL;
				}
					PwdBox(bool changePwd) {
					_obj = lv_pwdbox_create(NULL, changePwd);
					_child = NULL;
					_childs = NULL;
				}
					PwdBox(Object *parent, bool changePwd) {
					_obj = lv_pwdbox_create(parent->GetObj(), changePwd);
					_child = NULL;
					_childs = NULL;
				}
					PwdBox(Object &parent, bool changePwd) {
					if(((Object)parent).GetObj()) {
						_obj = lv_pwdbox_create(((Object)parent).GetObj(), changePwd);
					} else {
						_obj = lv_pwdbox_create(NULL, changePwd);
					}
					_child = NULL;
					_childs = NULL;
				}
				/**
				 * Create an empty btnMatrix object, this is useful when used as a child.
				 */
					PwdBox() {
					_obj = NULL;
					_child = NULL;
					_childs = NULL;
				}

					PwdBox(lv_obj_t *object, bool changePwd, bool isNew) {
					_obj = object;
					_childs = NULL;
					_child = NULL;
				}
					PwdBox(Object *object, bool changePwd, bool isNew) {
					_obj = object->GetObj();
					_childs = object->GetChilds();
					_child = NULL;
				}
					PwdBox(Object &object, bool changePwd, bool isNew) {
					_obj = ((Object)object).GetObj();
					_childs = ((Object)object).GetChilds();
					_child = NULL;
				}

				~PwdBox() {

				}

				/**
				 * Set the object pointer when used as a child.
				 */
				inline PwdBox *SetObj(lv_obj_t *obj) {
					_obj = obj;
					return this;
				}

				inline lv_obj_t *GetObj() {
					return _obj;
				}

				/**********************
				 * GLOBAL PROTOTYPES
				 **********************/

				/*=====================
				 * Setter functions
				 *====================*/

				/*=====================
				 * Getter functions
				 *====================*/

				const char *GetPwdOldPwd() {
					return lv_msgbox_get_text1(_obj);
				}

				const char *GetPwd1() {
					return lv_msgbox_get_text2(_obj);
				}

				const char *GetPwd2() {
					return lv_msgbox_get_text3(_obj);
				}

				lv_obj_t * GetBtns() {
				    return lv_pwdbox_get_btns(_obj);
				}

				uint16_t GetActiveBtn() {
				    return lv_pwdbox_get_active_btn(_obj);
				}

				const char * GetActiveBtnText() {
				    return lv_pwdbox_get_active_btn_text(_obj);
				}

				void Close() {
					lv_pwdbox_close(_obj);
				}

				void CloseAsync() {
					lv_pwdbox_close_async(_obj);
				}

		};
	}
}
#ifdef __cplusplus
extern "C" {
#endif
extern const lv_obj_class_t lv_pwdbox_class;
extern const lv_obj_class_t lv_pwdbox_content_class;
extern const lv_obj_class_t lv_pwdbox_backdrop_class;
#ifdef __cplusplus
}
#endif

#endif /* LIBRARIES_LVGLCPP_SRC_WIDGETS_PWDBOX_H_ */
