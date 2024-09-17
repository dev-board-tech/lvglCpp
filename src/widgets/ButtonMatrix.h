/*
 * ButtonMatrix.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_BUTTONMATRIX_H_
#define LVGLCPP_SRC_BUTTONMATRIX_H_


#include "Object.h"

namespace lvgl {
	namespace widget {
		class ButtonMatrix : public Object {
		public:
			/**
			 * Create a button matrix object
			 * @param parent    pointer to an object, it will be the parent of the new button matrix
			 * @return          pointer to the created button matrix
			 */
			ButtonMatrix(lv_obj_t *parent) {
				_obj = lv_btnmatrix_create(parent);
				_child = NULL;
				_childs = NULL;
			}
			ButtonMatrix(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_btnmatrix_create(parent->GetObj());
				} else {
					_obj = lv_btnmatrix_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			ButtonMatrix(Object &parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_btnmatrix_create(((Object)parent).GetObj());
				} else {
					_obj = lv_btnmatrix_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			/**
			 * Create an empty btnMatrix object, this is useful when used as a child.
			 */
			ButtonMatrix() {
				_obj = NULL;
				_child = NULL;
				_childs = NULL;
			}
			
			ButtonMatrix(lv_obj_t *parent, bool isNew) {
				_obj = parent;
				_child = NULL;
				_childs = NULL;
			}

			ButtonMatrix(Object *parent, bool isNew) {
				_obj = parent->GetObj();
				_child = NULL;
				_childs = NULL;
			}
			ButtonMatrix(Object &parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
				_child = NULL;
				_childs = NULL;
			}

			~ButtonMatrix() {
				// TODO Auto-generated destructor stub
			}

			/**
			 * Set the object pointer when used as a child.
			 */
			ButtonMatrix *SetObj(lv_obj_t *obj) {
				_obj = obj;
				return this;
			}

			lv_obj_t *GetObj() {
				return _obj;
			}

			/*=====================
			 * Setter functions
			 *====================*/

			/**
			 * Set a new map. Buttons will be created/deleted according to the map. The
			 * button matrix keeps a reference to the map and so the string array must not
			 * be deallocated during the life of the matrix.
			 * @param map       pointer a string array. The last string has to be: "". Use "\n" to make a line break.
			 * @return          object pointer
			 */
			inline ButtonMatrix *SetMap(const char * map[]) {
				lv_btnmatrix_set_map(_obj, map);
				return this;
			}

			/**
			 * Set the button control map (hidden, disabled etc.) for a button matrix.
			 * The control map array will be copied and so may be deallocated after this
			 * function returns.
			 * @param ctrl_map  pointer to an array of `lv_btn_ctrl_t` control bytes. The
			 *                  length of the array and position of the elements must match
			 *                  the number and order of the individual buttons (i.e. excludes
			 *                  newline entries).
			 *                  An element of the map should look like e.g.:
			 *                 `ctrl_map[0] = width | LV_BTNMATRIX_CTRL_NO_REPEAT |  LV_BTNMATRIX_CTRL_TGL_ENABLE`
			 * @return          object pointer
			 */
			inline ButtonMatrix *SetCtrlMap(const lv_btnmatrix_ctrl_t ctrl_map[]) {
				lv_btnmatrix_set_ctrl_map(_obj, ctrl_map);
				return this;
			}
			/**
			 * Set the selected buttons
			 * @param btn_id         0 based index of the button to modify. (Not counting new lines)
			 * @return          object pointer
			 */
			inline ButtonMatrix *SetSelectedBtn(uint16_t btn_id) {
				lv_btnmatrix_set_selected_btn(_obj, btn_id);
				return this;
			}
			/**
			 * Set the attributes of a button of the button matrix
			 * @param btn_id    0 based index of the button to modify. (Not counting new lines)
			 * @param ctrl      OR-ed attributs. E.g. `LV_BTNMATRIX_CTRL_NO_REPEAT | LV_BTNMATRIX_CTRL_CHECKABLE`
			 * @return          object pointer
			 */
			inline ButtonMatrix *SetBtnCtrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) {
				lv_btnmatrix_set_btn_ctrl(_obj, btn_id, ctrl);
				return this;
			}
			/**
			 * Clear the attributes of a button of the button matrix
			 * @param btn_id    0 based index of the button to modify. (Not counting new lines)
			 * @param ctrl      OR-ed attributs. E.g. `LV_BTNMATRIX_CTRL_NO_REPEAT | LV_BTNMATRIX_CTRL_CHECKABLE`
			 * @return          object pointer
			 */
			inline ButtonMatrix *clearBtn(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) {
				lv_btnmatrix_clear_btn_ctrl(_obj,  btn_id, ctrl);
				return this;
			}
			/**
			 * Set attributes of all buttons of a button matrix
			 * @param ctrl      attribute(s) to set from `lv_btnmatrix_ctrl_t`. Values can be ORed.
			 * @return          object pointer
			 */
			inline ButtonMatrix *SetBtnCtrlAll(lv_btnmatrix_ctrl_t ctrl) {
				lv_btnmatrix_set_btn_ctrl_all(_obj, ctrl);
				return this;
			}
			/**
			 * Clear the attributes of all buttons of a button matrix
			 * @param ctrl      attribute(s) to set from `lv_btnmatrix_ctrl_t`. Values can be ORed.
			 * @param en        true: set the attributes; false: clear the attributes
			 * @return          object pointer
			 */
			inline ButtonMatrix *clearBtnCtrlAll(lv_btnmatrix_ctrl_t ctrl) {
				lv_btnmatrix_clear_btn_ctrl_all(_obj, ctrl);
				return this;
			}
			/**
			 * Set a single button's relative width.
			 * This method will cause the matrix be regenerated and is a relatively
			 * expensive operation. It is recommended that initial width be specified using
			 * `lv_btnmatrix_set_ctrl_map` and this method only be used for dynamic changes.
			 * @param btn_id    0 based index of the button to modify.
			 * @param width     relative width compared to the buttons in the same row. [1..7]
			 * @return          object pointer
			 */
			inline ButtonMatrix *SetBtnWidth(uint16_t btn_id, uint8_t width) {
				lv_btnmatrix_set_btn_width(_obj, btn_id, width);
				return this;
			}
			/**
			 * Make the button matrix like a selector widget (only one button may be checked at a time).
			 * `LV_BTNMATRIX_CTRL_CHECKABLE` must be enabled on the buttons to be selected using
			 * `lv_btnmatrix_set_ctrl()` or `lv_btnmatrix_set_btn_ctrl_all()`.
			 * @param en        whether "one check" mode is enabled
			 * @return          object pointer
			 */
			inline ButtonMatrix *SetOneChildren(bool en) {
				lv_btnmatrix_set_one_checked(_obj, en);
				return this;
			}
			/*=====================
			 * Getter functions
			 *====================*/

			/**
			 * Get the current map of a button matrix
			 * @return          the current map
			 */
			inline const char ** GetMap() {
				return lv_btnmatrix_get_map(_obj);
			}

			/**
			 * Get the index of the lastly "activated" button by the user (pressed, released, focused etc)
			 * Useful in the `event_cb` to get the text of the button, check if hidden etc.
			 * @return          index of the last released button (LV_BTNMATRIX_BTN_NONE: if unset)
			 */
			inline uint16_t GetSelectedBtn() {
				return lv_btnmatrix_get_selected_btn(_obj);
			}

			/**
			 * Get the button's text
			 * @param btn_id    the index a button not counting new line characters.
			 * @return          text of btn_index` button
			 */
			inline const char *GetBtnText(uint16_t btn_id) {
				if(!_obj) {
					return "";
				}
				return lv_btnmatrix_get_btn_text(_obj, btn_id);
			}

			/**
			 * Get the whether a control value is enabled or disabled for button of a button matrix
			 * @param btn_id    the index of a button not counting new line characters.
			 * @param ctrl      control values to check (ORed value can be used)
			 * @return          true: the control attribute is enabled false: disabled
			 */
			inline bool HasBtnCtrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) {
				return lv_btnmatrix_has_btn_ctrl(_obj, btn_id, ctrl);
			}

			/**
			 * Tell whether "one check" mode is enabled or not.
			 * @return          true: "one check" mode is enabled; false: disabled
			 */
			inline bool GetOneChecked() {
				return lv_btnmatrix_get_one_checked(_obj);
			}

		};
	}
} /* namespace lvgl */


#endif /* LVGLCPP_SRC_BUTTONMATRIX_H_ */
