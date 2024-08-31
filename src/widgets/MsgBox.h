/*
 * MsgBox.h
 *
 *      Author: Iulian Gheorghiu
 */
#ifndef LVGLCPP_SRC_MSGBOX_H_
#define LVGLCPP_SRC_MSGBOX_H_

#include "Object.h"
#include "Button.h"
#include "Label.h"
#include "ButtonMatrix.h"

namespace lvgl {
	namespace widget {
		class MsgBox : public Object {
		public:
			MsgBox(lv_obj_t * parent, const char * title, const char * txt, const char * btn_txts[], bool add_close_btn = true) {
				if(parent) {
					_obj = lv_msgbox_create(parent, title, txt, btn_txts, add_close_btn);
				} else {
					_obj = lv_msgbox_create(lv_scr_act(), title, txt, btn_txts, add_close_btn);
				}
				_child = NULL;
				_childs = NULL;
			}
			/**
			 * Create an empty btnMatrix object, this is useful when used as a child.
			 */
			MsgBox() {
				_obj = NULL;
				_child = NULL;
				_childs = NULL;
			}

			~MsgBox() {

			}

			/**
			 * Set the object pointer when used as a child.
			 */
			inline MsgBox *SetObj(lv_obj_t *obj) {
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
			 
			 inline Label GetTitle() {
				Label label;
				label.SetObj(lv_msgbox_get_title(_obj));
				return label;
			 }

			 inline Button GetCloseBtn() {
				Button button;
				button.SetObj(lv_msgbox_get_close_btn(_obj));
				return button;
			 }

			 inline Label GetText() {
				Label label;
				label.SetObj(lv_msgbox_get_text(_obj));
				return label;
			 }

			 inline ButtonMatrix GetBtns() {
				ButtonMatrix btns;
				btns.SetObj(lv_msgbox_get_btns(_obj));
				return btns;
			 }
			 
			 inline uint16_t GetActiveBtn() {
			 	return lv_msgbox_get_active_btn(_obj);
			 }
			 
			 inline const char * GetActiveBtnText() {
			 	 return lv_msgbox_get_active_btn_text(_obj);
			 }
			 
			 inline MsgBox *close() {
			 	 lv_msgbox_close(_obj);
			 	 return this;
			 }
			 
			 inline MsgBox *closeAsync() {
			 	 lv_msgbox_close_async(_obj);
			 	 return this;
			 }
		};
	} /* namespace widget */
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_LABEL_H_ */

