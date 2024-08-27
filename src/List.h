#ifndef LVGLCPP_SRC_LIST_H_
#define LVGLCPP_SRC_LIST_H_

#include <stdio.h>
#include <stdarg.h>

#include "Object.h"
#include "Button.h"
#include "Label.h"

namespace lvgl {
class List : public Object {
public:
	List(lv_obj_t *parent = NULL) {
		if(parent) {
			_obj = lv_list_create(parent);
		} else {
			_obj = lv_list_create(lv_scr_act());
		}
		_child = NULL;
		_childs = NULL;
	}
	/**
	 * Create an empty btnMatrix object, this is useful when used as a child.
	 */
	List() {
		_obj = NULL;
		_child = NULL;
		_childs = NULL;
	}

	~List() {

	}

	/**
	 * Set the object pointer when used as a child.
	 */
	inline List *setObj(lv_obj_t *obj) {
		_obj = obj;
		return this;
	}

	inline lv_obj_t *getObj() {
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
	inline lvgl::Label addText(const char * fmt, ...) {
		va_list args;
		va_start(args, fmt);
		int size = vsnprintf(NULL, 0, fmt, args);
		va_end(args);
		char buffer[size + 1];
		va_start(args, fmt);
		vsnprintf(buffer, size + 1, fmt, args);
		va_end(args);
		lvgl::Label label;
		label.setObj(lv_list_add_text(_obj, buffer));
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
	inline lvgl::Button addBtn(const void * icon, const char * fmt, ...) {
		va_list args;
		va_start(args, fmt);
		int size = vsnprintf(NULL, 0, fmt, args);
		va_end(args);
		char buffer[size + 1];
		va_start(args, fmt);
		vsnprintf(buffer, size + 1, fmt, args);
		va_end(args);
		lvgl::Button btn;
		btn.setObj(lv_list_add_btn(_obj, icon, buffer));
		return btn;
	}
	
	inline List *setBtnText(Button * btn, const char * text) {
		if(!btn || !btn->getObj() || !text)
			return this;
		uint32_t i;
		for(i = 0; i < lv_obj_get_child_cnt(btn->getObj()); i++) {
			lv_obj_t * child = lv_obj_get_child(btn->getObj(), i);
			if(lv_obj_check_type(child, &lv_label_class)) {
				lv_label_set_text(child, text);
				return this;
			}
		}
		lv_obj_t * label = lv_label_create(btn->getObj());
		lv_label_set_text(label, text);
		lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
		lv_obj_set_flex_grow(label, 1);
		return this;
	}

	void setBtnText(Button * btn, const char *fmt, ...) {
		if(!btn || !btn->getObj() || !fmt)
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
		for(i = 0; i < lv_obj_get_child_cnt(btn->getObj()); i++) {
			lv_obj_t * child = lv_obj_get_child(btn->getObj(), i);
			if(lv_obj_check_type(child, &lv_label_class)) {
				lv_label_set_text(child, buffer);
				return;
			}
		}
		lv_obj_t * label = lv_label_create(btn->getObj());
		lv_label_set_text(label, buffer);
		lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
		lv_obj_set_flex_grow(label, 1);
	}

	void setBtnImg(Button * btn, const void * icon) {
		if(!btn || !btn->getObj() || !icon)
			return;
		uint32_t i;
		for(i = 0; i < lv_obj_get_child_cnt(btn->getObj()); i++) {
			lv_obj_t * child = lv_obj_get_child(btn->getObj(), i);
			if(lv_obj_check_type(child, &lv_img_class)) {
				lv_img_set_src(child, icon);
				return;
			}
		}
		lv_obj_t * img = lv_img_create(btn->getObj());
		lv_img_set_src(img, icon);
	}

	void setBtnImgText(Button * btn, const void * icon, const char *text) {
		if(!btn || !btn->getObj() || !icon || !text)
			return;
		setBtnImg(btn, icon);
		uint32_t i;
		for(i = 0; i < lv_obj_get_child_cnt(btn->getObj()); i++) {
			lv_obj_t * child = lv_obj_get_child(btn->getObj(), i);
			if(lv_obj_check_type(child, &lv_label_class)) {
				lv_label_set_text(child, text);
				return;
			}
		}
		lv_obj_t * label = lv_label_create(btn->getObj());
		lv_label_set_text(label, text);
		lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
		lv_obj_set_flex_grow(label, 1);
	}

	void setBtnImgText(Button * btn, const void * icon, const char *fmt, ...) {
		if(!btn || !btn->getObj() || !icon || !fmt)
			return;
		setBtnImg(btn, icon);
		va_list args;
		va_start(args, fmt);
		int size = vsnprintf(NULL, 0, fmt, args);
		va_end(args);
		char buffer[size + 1];
		va_start(args, fmt);
		vsnprintf(buffer, size + 1, fmt, args);
		va_end(args);

		uint32_t i;
		for(i = 0; i < lv_obj_get_child_cnt(btn->getObj()); i++) {
			lv_obj_t * child = lv_obj_get_child(btn->getObj(), i);
			if(lv_obj_check_type(child, &lv_label_class)) {
				lv_label_set_text(child, buffer);
				return;
			}
		}
		lv_obj_t * label = lv_label_create(btn->getObj());
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
	inline const char *getBtnText(Button * btn) {
		return lv_list_get_btn_text(_obj, btn->getObj());
	}

};

} /* namespace lvgl */

#endif /* LVGLCPP_SRC_LABEL_H_ */
