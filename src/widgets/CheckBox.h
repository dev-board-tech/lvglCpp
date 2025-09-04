/*
 * CheckBox.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_CHECKBOX_H_
#define LVGLCPP_SRC_CHECKBOX_H_

#include "Object.h"

namespace lvgl {
	namespace widget {
		class CheckBox : public Object {
		public:
			CheckBox(lv_obj_t *parent) {
				_obj = lv_checkbox_create(parent);
				_child = NULL;
				_childs = NULL;
			}
			CheckBox(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_checkbox_create(parent->GetObj());
				} else {
					_obj = lv_checkbox_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			CheckBox(Object &parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_checkbox_create(((Object)parent).GetObj());
				} else {
					_obj = lv_checkbox_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			CheckBox(Object *parent, bool isNew) {
				_obj = parent->GetObj();
				_childs = parent->GetChilds();
				_child = NULL;
			}
			CheckBox(Object &parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
				_childs = ((Object)parent).GetChilds();
				_child = NULL;
			}
			virtual ~CheckBox() {

			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

			/*=====================
			 * Setter functions
			 *====================*/

			/**
			 * Set the text of a check box. `txt` will be copied and may be deallocated
			 * after this function returns.
			 * @param cb    pointer to a check box
			 * @param txt   the text of the check box. NULL to refresh with the current text.
			 */
			inline CheckBox *SetText(const char * txt) {
				lv_checkbox_set_text(_obj, txt);
				return this;
			}

			/**
			 * Set the text of a check box. `txt` must not be deallocated during the life
			 * of this checkbox.
			 * @param cb    pointer to a check box
			 * @param txt   the text of the check box.
			 */
			inline CheckBox *SetTextStatic(const char * txt) {
				lv_checkbox_set_text_static(_obj, txt);
				return this;
			}

		};
	}
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_CHECKBOX_H_ */
