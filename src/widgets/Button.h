/*
 * Button.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_BUTTON_H_
#define LVGLCPP_SRC_BUTTON_H_

#include <stdio.h>
#include <stdarg.h>

#include "Label.h"
#include "Object.h"
#include "Window.h"


namespace lvgl {
	namespace widget {
		class Button : public Object {
		private:
			Label *_label;
		public:
			Button(lv_obj_t *parent) {
				_obj = lv_btn_create(parent);
				_label = NULL;
			}

			Button(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_btn_create(parent->GetObj());
				} else {
					_obj = lv_btn_create(NULL);
				}
				_label = NULL;
			}

			Button(Object parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_btn_create(((Object)parent).GetObj());
				} else {
					_obj = lv_btn_create(NULL);
				}
				_label = NULL;
			}

			Button(lv_obj_t *parent, char *fmt, ...) {
				_obj = lv_btn_create(parent);
				if(fmt == NULL || fmt[0] == 0) {
					_label = NULL;
					return;
				}
				_label = new Label(_obj);
				va_list args;
				va_start(args, fmt);
				int size = vsnprintf(NULL, 0, fmt, args);
				va_end(args);
				char buffer[size + 1];
				va_start(args, fmt);
				vsnprintf(buffer, size + 1, fmt, args);
				va_end(args);
				lv_label_set_text(_label->GetObj(), buffer);
				lv_obj_align(_label->GetObj(), LV_ALIGN_CENTER, 0, 0);
			}

			Button(Object *parent, char *fmt, ...) {
				_obj = lv_btn_create(parent->GetObj());
				if(fmt == NULL || fmt[0] == 0) {
					_label = NULL;
					return;
				}
				_label = new Label(_obj);
				va_list args;
				va_start(args, fmt);
				int size = vsnprintf(NULL, 0, fmt, args);
				va_end(args);
				char buffer[size + 1];
				va_start(args, fmt);
				vsnprintf(buffer, size + 1, fmt, args);
				va_end(args);
				lv_label_set_text(_label->GetObj(), buffer);
				lv_obj_align(_label->GetObj(), LV_ALIGN_CENTER, 0, 0);
			}

			Button(Object parent, char *fmt, ...) {
				_obj = lv_btn_create(((Object)parent).GetObj());
				if(fmt == NULL || fmt[0] == 0) {
					_label = NULL;
					return;
				}
				_label = new Label(_obj);
				va_list args;
				va_start(args, fmt);
				int size = vsnprintf(NULL, 0, fmt, args);
				va_end(args);
				char buffer[size + 1];
				va_start(args, fmt);
				vsnprintf(buffer, size + 1, fmt, args);
				va_end(args);
				lv_label_set_text(_label->GetObj(), buffer);
				lv_obj_align(_label->GetObj(), LV_ALIGN_CENTER, 0, 0);
			}

			Button(lv_obj_t *parent, bool isNew) {
				_obj = parent;
			}
			Button(Object *parent, bool isNew) {
				_obj = parent->GetObj();
			}

			Button(Object parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
			}

			~Button() {

			}

			/**
			 * Set the object pointer when used as a child.
			 */
			inline Button *SetObj(lv_obj_t *obj) {
				_obj = obj;
				return this;
			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

			inline Label *GetLabel() {
				return _label;
			}
			
		};
	}
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_BUTTON_H_ */
