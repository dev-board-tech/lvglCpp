/*
 * button.h
 *
 *  Created on: Nov 27, 2023
 *      Author: morgoth
 */

#ifndef LVGLCPP_SRC_BUTTON_H_
#define LVGLCPP_SRC_BUTTON_H_

#include <stdarg.h>

#include "Label.h"
#include "Object.h"


namespace lvgl {
class Button : public Object {
private:
	Label *_label;
public:
	Button(lv_obj_t *parent) {
		if(parent) {
			_obj = lv_btn_create(parent);
		} else {
			_obj = lv_btn_create(lv_scr_act());
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
		lv_label_set_text(_label->getObj(), buffer);
		lv_obj_align(_label->getObj(), LV_ALIGN_CENTER, 0, 0);
	}
	/**
	 * Create an empty btnMatrix object, this is useful when used as a child.
	 */
	Button() {
		_obj = NULL;
		_child = NULL;
		_childs = NULL;
	}

	~Button() {

	}

	/**
	 * Set the object pointer when used as a child.
	 */
	inline Button *setObj(lv_obj_t *obj) {
		_obj = obj;
		return this;
	}

	inline lv_obj_t *getObj() {
		return _obj;
	}

	inline Label *getLabel() {
		return _label;
	}
	
};

} /* namespace lvgl */

#endif /* LVGLCPP_SRC_BUTTON_H_ */
