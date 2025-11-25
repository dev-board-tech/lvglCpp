/*
 * Keyboard.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_KEYBOARD_H_
#define LVGLCPP_SRC_KEYBOARD_H_

#include <stdio.h>
#include <stdarg.h>

#include "Object.h"


namespace lvgl {
	namespace widget {
		class Keyboard : public Object {
		public:
			Keyboard(lv_obj_t *parent) {
				_obj = lv_keyboard_create(parent);
			}

			Keyboard(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_keyboard_create(parent->GetObj());
				} else {
					_obj = lv_keyboard_create(NULL);
				}
			}

			Keyboard(Object parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_keyboard_create(((Object)parent).GetObj());
				} else {
					_obj = lv_keyboard_create(NULL);
				}
			}

			Keyboard(lv_obj_t *object, bool isNew) {
				_obj = object;
			}
			Keyboard(Object *object, bool isNew) {
				_obj = object->GetObj();
			}

			Keyboard(Object object, bool isNew) {
				_obj = ((Object)object).GetObj();
			}

			~Keyboard() {

			}

			/**
			 * Set the object pointer when used as a child.
			 */
			inline Keyboard *SetObj(lv_obj_t *obj) {
				_obj = obj;
				return this;
			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

			/**
			 * Assign a Text Area to the Keyboard. The pressed characters will be put there.
			 * @param kb pointer to a Keyboard object
			 * @param ta pointer to a Text Area object to write there
			 */
			inline Keyboard *SetTextArea(lv_obj_t * ta) {
				lv_keyboard_set_textarea(_obj, ta);
				return this;
			}

			/**
			 * Set a new a mode (text or number map)
			 * @param kb pointer to a Keyboard object
			 * @param mode the mode from 'lv_keyboard_mode_t'
			 */
			inline Keyboard *SetMode(lv_keyboard_mode_t mode) {
				lv_keyboard_set_mode(_obj, mode);
				return this;
			}

			/**
			 * Show the button title in a popover when pressed.
			 * @param kb pointer to a Keyboard object
			 * @param en whether "popovers" mode is enabled
			 */
			inline Keyboard *SetPopOvers(bool en) {
				lv_keyboard_set_popovers(_obj, en);
				return this;
			}

			/**
			 * Set a new map for the keyboard
			 * @param kb pointer to a Keyboard object
			 * @param mode keyboard map to alter 'lv_keyboard_mode_t'
			 * @param map pointer to a string array to describe the map.
			 *            See 'lv_btnmatrix_set_map()' for more info.
			 */
			inline Keyboard *SetMap(lv_keyboard_mode_t mode, const char * map[], const lv_btnmatrix_ctrl_t ctrl_map[]) {
				lv_keyboard_set_map(_obj, mode, map, ctrl_map);
				return this;
			}

			/*=====================
			 * Getter functions
			 *====================*/

			/**
			 * Assign a Text Area to the Keyboard. The pressed characters will be put there.
			 * @param kb pointer to a Keyboard object
			 * @return pointer to the assigned Text Area object
			 */
			lv_obj_t * GetTextArea() {
				return lv_keyboard_get_textarea(_obj);
			}

			/**
			 * Set a new a mode (text or number map)
			 * @param kb pointer to a Keyboard object
			 * @return the current mode from 'lv_keyboard_mode_t'
			 */
			lv_keyboard_mode_t GetMode() {
				return lv_keyboard_get_mode(_obj);
			}

			/**
			 * Tell whether "popovers" mode is enabled or not.
			 * @param kb pointer to a Keyboard object
			 * @return true: "popovers" mode is enabled; false: disabled
			 */
			bool GetPopOvers() {
				return lv_btnmatrix_get_popovers(_obj);
			}

			/**
			 * Get the current map of a keyboard
			 * @param kb pointer to a keyboard object
			 * @return the current map
			 */
			static inline const char ** GetMapArray(const lv_obj_t * obj) {
				return lv_btnmatrix_get_map(obj);
			}

			/**
			 * Get the index of the lastly "activated" button by the user (pressed, released, focused etc)
			 * Useful in the `event_cb` to get the text of the button, check if hidden etc.
			 * @param obj       pointer to button matrix object
			 * @return          index of the last released button (LV_BTNMATRIX_BTN_NONE: if unset)
			 */
			static inline uint16_t GetSelectedBtn(const lv_obj_t * obj) {
				return lv_keyboard_get_selected_btn(obj);
			}

			/**
			 * Get the button's text
			 * @param obj       pointer to button matrix object
			 * @param btn_id    the index a button not counting new line characters.
			 * @return          text of btn_index` button
			 */
			static inline const char * GetBtnText(const lv_obj_t * obj, uint16_t btn_id) {
				return lv_keyboard_get_btn_text(obj, btn_id);
			}

			/*=====================
			 * Other functions
			 *====================*/

			/**
			 * Default keyboard event to add characters to the Text area and change the map.
			 * If a custom `event_cb` is added to the keyboard this function can be called from it to handle the
			 * button clicks
			 * @param kb pointer to a keyboard
			 * @param event the triggering event
			 */
			void DefEventCb(lv_event_t * e) {
				lv_keyboard_def_event_cb(e);
			}

		};
	}
}
#endif

//Added by Sloeber 
#pragma once
