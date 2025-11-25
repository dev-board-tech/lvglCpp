/*
 * ButtonMatrix.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef __LVGLCPP_SRC_WINDOW_H__
#define __LVGLCPP_SRC_WINDOW_H__


#include <lvgl.h>
#include "Label.h"
#include "Object.h"

namespace lvgl {
	namespace widget {
		class Window : public Object {
		public:
			/**
			 * Create a button matrix object
			 * @param parent    pointer to an object, it will be the parent of the new button matrix
			 * @return          pointer to the created button matrix
			 */
			Window(lv_obj_t *parent = NULL, lv_coord_t header_height = 40) {
				_obj = lv_win_create(parent, header_height);
				_child = NULL;
				_childs = NULL;
			}
			
			Window(Object *parent, lv_coord_t header_height = 40) {
				if(parent && parent->GetObj()) {
					_obj = lv_win_create(parent->GetObj(), header_height);
				} else {
					_obj = lv_win_create(NULL,header_height);
				}
				_child = NULL;
				_childs = NULL;
			}
			
			Window(Object &parent, lv_coord_t header_height) {
				if(((Object)parent).GetObj()) {
					_obj = lv_win_create(((Object)parent).GetObj(), header_height);
				} else {
					_obj = lv_win_create(NULL, header_height);
				}
				_child = NULL;
				_childs = NULL;
			}

			Window(lv_obj_t *object, bool isNew) {
				_obj = object;
				_child = NULL;
				_childs = NULL;
			}

			Window(Object *object, bool isNew) {
				_obj = object->GetObj();
				_child = NULL;
				_childs = NULL;
			}

			Window(Object &object, bool isNew) {
				_obj = ((Object)object).GetObj();
				_child = NULL;
				_childs = NULL;
			}

			~Window() {
				// TODO Auto-generated destructor stub
			}

			/**
			 * Set the object pointer when used as a child.
			 */
			Window *SetObj(lv_obj_t *obj) {
				_obj = obj;
				return this;
			}

			lv_obj_t *GetObj() {
				return _obj;
			}

			lv_obj_t *AddTitle(const char * txt) {
				_child = lv_win_add_title(_obj, txt);
				return _child;
			}
			
			Object GetTitle() {
				return Object(_child, false);
			}

			Window *RenameTitle(const char * txt) {
				lv_label_set_text(_child, txt);
				return this;
			}

			lv_obj_t *AddButton(const void * icon, lv_coord_t btn_w) {
				return lv_win_add_btn(_obj, icon, btn_w);
			}

			lv_obj_t *GetHeader() {
				return lv_win_get_header(_obj);
			}
			
			Object GetContent() {
				return Object(lv_win_get_content(_obj), false);
			}

		};
	} /* namespace widget */
} /* namespace lvgl */

#endif

//Added by Sloeber 
#pragma once
