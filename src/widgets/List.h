/*
 * List.h
 *
 *      Author: Iulian Gheorghiu
 */
#ifndef LVGLCPP_SRC_LIST_H_
#define LVGLCPP_SRC_LIST_H_

#include <stdio.h>
#include <stdarg.h>

#include "Object.h"
#include "Button.h"
#include "Label.h"

namespace lvgl {
	namespace widget {
		class List : public Object {
		public:
			List(lv_obj_t *parent) {
				_obj = lv_list_create(parent);
			}
			List(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_list_create(parent->GetObj());
				} else {
					_obj = lv_list_create(NULL);
				}
			}
			List(Object parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_list_create(((Object)parent).GetObj());
				} else {
					_obj = lv_list_create(NULL);
				}
			}
			List(lv_obj_t *parent, bool isNew) {
				_obj = parent;
			}
			List(Object *parent, bool isNew) {
				_obj = parent->GetObj();
			}
			List(Object parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
			}

			~List() {

			}

			/**
			 * Set the object pointer when used as a child.
			 */
			inline List *SetObj(lv_obj_t *obj) {
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

			/**
			 * Set a new text for a Label. Memory will be allocated to store the text by the Label.
			 * @param obj           pointer to a Label object
			 * @param text          '\0' terminated character string. NULL to refresh with the current text.
			 */
			inline List *addText(const char * text) {
				lv_list_add_text(_obj, text);
				return this;
			}

			/**
			 * Set a new formatted text for a Btn. Memory will be allocated to store the text by the Btn.
			 * @param obj           pointer to a Btn object
			 * @param fmt           `printf`-like format
			 * @example lv_label_set_text_fmt(label1, "%d user", user_num);
			 */
			inline Label *AddText(const char * fmt, ...) {
				va_list args;
				va_start(args, fmt);
				int size = vsnprintf(NULL, 0, fmt, args);
				va_end(args);
				char buffer[size + 1];
				va_start(args, fmt);
				vsnprintf(buffer, size + 1, fmt, args);
				va_end(args);
				Label *label = new Label(lv_list_add_text(_obj, buffer), false);
				return label;
			}

			/**
			 * Set a new text for a Btn. Memory will be allocated to store the text by the Btn.
			 * @param text          '\0' terminated character string. NULL to refresh with the current text.
			 */
			//inline List *addBtn(const void * icon, const char * text) {
			//	lv_list_add_btn(_obj, icon, text);
			//	return this;
			//}

			/**
			 * Set a new formatted text for a Btn. Memory will be allocated to store the text by the Btn.	 * @param obj           pointer to a Label object
			 * @param fmt           `printf`-like format
			 * @example lv_label_set_text_fmt(label1, "%d user", user_num);
			 */
			inline Button *AddButton(const void * icon, const char * fmt, ...) {
				va_list args;
				va_start(args, fmt);
				int size = vsnprintf(NULL, 0, fmt, args);
				va_end(args);
				char buffer[size + 1];
				va_start(args, fmt);
				vsnprintf(buffer, size + 1, fmt, args);
				va_end(args);
				Button *btn = new Button(lv_list_add_btn(_obj, icon, buffer), false);
				return btn;
			}
			
			inline List *SetBtnText(Button * btn, const char * text) {
				if(!btn || !btn->GetObj() || !text)
					return this;
				uint32_t i;
				for(i = 0; i < lv_obj_get_child_cnt(btn->GetObj()); i++) {
					lv_obj_t * child = lv_obj_get_child(btn->GetObj(), i);
					if(lv_obj_check_type(child, &lv_label_class)) {
						lv_label_set_text(child, text);
						return this;
					}
				}
				lv_obj_t * label = lv_label_create(btn->GetObj());
				lv_label_set_text(label, text);
				lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
				lv_obj_set_flex_grow(label, 1);
				return this;
			}

			void SetBtnText(Button * btn, const char *fmt, ...) {
				if(!btn || !btn->GetObj() || !fmt)
					return;
				va_list args;
				va_start(args, fmt);
				int size = vsnprintf(NULL, 0, fmt, args);
				va_end(args);
				char buffer[size + 1];
				va_start(args, fmt);
				vsnprintf(buffer, size + 1, fmt, args);
				va_end(args);

				uint32_t i;
				for(i = 0; i < lv_obj_get_child_cnt(btn->GetObj()); i++) {
					lv_obj_t * child = lv_obj_get_child(btn->GetObj(), i);
					if(lv_obj_check_type(child, &lv_label_class)) {
						lv_label_set_text(child, buffer);
						return;
					}
				}
				lv_obj_t * label = lv_label_create(btn->GetObj());
				lv_label_set_text(label, buffer);
				lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
				lv_obj_set_flex_grow(label, 1);
			}

			void SetBtnImg(Button * btn, const void * icon) {
				if(!btn || !btn->GetObj() || !icon)
					return;
				uint32_t i;
				for(i = 0; i < lv_obj_get_child_cnt(btn->GetObj()); i++) {
					lv_obj_t * child = lv_obj_get_child(btn->GetObj(), i);
					if(lv_obj_check_type(child, &lv_img_class)) {
						lv_img_set_src(child, icon);
						return;
					}
				}
				lv_obj_t * img = lv_img_create(btn->GetObj());
				lv_img_set_src(img, icon);
			}

			void SetBtnImgText(Button * btn, const void * icon, const char *text) {
				if(!btn || !btn->GetObj() || !icon || !text)
					return;
				SetBtnImg(btn, icon);
				uint32_t i;
				for(i = 0; i < lv_obj_get_child_cnt(btn->GetObj()); i++) {
					lv_obj_t * child = lv_obj_get_child(btn->GetObj(), i);
					if(lv_obj_check_type(child, &lv_label_class)) {
						lv_label_set_text(child, text);
						return;
					}
				}
				lv_obj_t * label = lv_label_create(btn->GetObj());
				lv_label_set_text(label, text);
				lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
				lv_obj_set_flex_grow(label, 1);
			}

			void SetBtnImgText(Button * btn, const void * icon, const char *fmt, ...) {
				if(!btn || !btn->GetObj() || !icon || !fmt)
					return;
				SetBtnImg(btn, icon);
				va_list args;
				va_start(args, fmt);
				int size = vsnprintf(NULL, 0, fmt, args);
				va_end(args);
				char buffer[size + 1];
				va_start(args, fmt);
				vsnprintf(buffer, size + 1, fmt, args);
				va_end(args);

				uint32_t i;
				for(i = 0; i < lv_obj_get_child_cnt(btn->GetObj()); i++) {
					lv_obj_t * child = lv_obj_get_child(btn->GetObj(), i);
					if(lv_obj_check_type(child, &lv_label_class)) {
						lv_label_set_text(child, buffer);
						return;
					}
				}
				lv_obj_t * label = lv_label_create(btn->GetObj());
				lv_label_set_text(label, buffer);
				lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
				lv_obj_set_flex_grow(label, 1);
			}

			/*=====================
			 * Getter functions
			 *====================*/

			/**
			 * Get the text of a Btn
			 * @param obj       pointer to a Label object
			 * @return          the text of the Label
			 */
			inline const char *GetBtnText(Button * btn) {
				return lv_list_get_btn_text(_obj, btn->GetObj());
			}

		};
	} /* namespace widget */
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_LABEL_H_ */
