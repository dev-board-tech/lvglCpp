/*
 * Switch.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_SWITCH_H_
#define LVGLCPP_SRC_SWITCH_H_

#include "Object.h"

namespace lvgl {
	namespace widget {
		class Switch : public Object {
		public:
			Switch(lv_obj_t *parent) {
				_obj = lv_switch_create(parent);
				_child = NULL;
				_childs = NULL;
			}
			Switch(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_switch_create(parent->GetObj());
				} else {
					_obj = lv_switch_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			Switch(Object &parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_switch_create(((Object)parent).GetObj());
				} else {
					_obj = lv_switch_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			Switch(lv_obj_t *parent, bool isNew) {
				_obj = parent;
				_childs = NULL;
				_child = NULL;
			}
			Switch(Object *parent, bool isNew) {
				_obj = parent->GetObj();
				_childs = parent->GetChilds();
				_child = NULL;
			}
			Switch(Object &parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
				_childs = ((Object)parent).GetChilds();
				_child = NULL;
			}

			~Switch() {

			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

		};
	} /* namespace widget */
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_SWITCH_H_ */
