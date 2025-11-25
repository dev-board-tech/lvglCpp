/*
 * SpinBox.h
 *
 *      Author: Iulian Gheorghiu
 */
#ifndef LVGLCPP_SRC_SPINBOX_H_
#define LVGLCPP_SRC_SPINBOX_H_

#include "Object.h"

namespace lvgl {
	namespace widget {
		class SpinBox : public Object {
		public:
			SpinBox(lv_obj_t * parent) {
				_obj = lv_spinbox_create(parent);
			}
			SpinBox() {
				_obj = lv_spinbox_create(NULL);
			}
			SpinBox(Object *parent) {
				_obj = lv_spinbox_create(NULL);
			}
			SpinBox(Object parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_spinbox_create(((Object)parent).GetObj());
				} else {
					_obj = lv_spinbox_create(NULL);
				}
			}

			SpinBox(lv_obj_t *object, bool isNew) {
				_obj = object;
				_childs = NULL;
				_child = NULL;
			}
			SpinBox(Object *object, bool isNew) {
				_obj = object->GetObj();
				_childs = object->GetChilds();
				_child = NULL;
			}
			SpinBox(Object object, bool isNew) {
				_obj = ((Object)object).GetObj();
				_childs = ((Object)object).GetChilds();
				_child = NULL;
			}

			~SpinBox() {

			}

			/**
			 * Set the object pointer when used as a child.
			 */
			inline SpinBox *SetObj(lv_obj_t *obj) {
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
			/**
			 * Set spinbox value
			 * @param obj pointer to spinbox
			 * @param i value to be set
			 */
			SpinBox *SetValue(int32_t i) {
				lv_spinbox_set_value(_obj, i);
				return this;
			}

			/**
			 * Set spinbox rollover function
			 * @param obj pointer to spinbox
			 * @param b true or false to enable or disable (default)
			 */
			SpinBox *SetRolover(bool b) {
				lv_spinbox_set_rollover(_obj, b);
				return this;
			}

			/**
			 * Set spinbox digit format (digit count and decimal format)
			 * @param obj pointer to spinbox
			 * @param digit_count number of digit excluding the decimal separator and the sign
			 * @param separator_position number of digit before the decimal point. If 0, decimal point is not
			 * shown
			 */
			SpinBox *SetDigitFormat(uint8_t digit_count, uint8_t separator_position) {
				lv_spinbox_set_digit_format(_obj, digit_count, separator_position);
				return this;
			}

			/**
			 * Set spinbox step
			 * @param obj pointer to spinbox
			 * @param step steps on increment/decrement. Can be 1, 10, 100, 1000, etc the digit that will change.
			 */
			SpinBox *SetStep(uint32_t step) {
				lv_spinbox_set_step(_obj, step);
				return this;
			}

			/**
			 * Set spinbox value range
			 * @param obj pointer to spinbox
			 * @param range_min maximum value, inclusive
			 * @param range_max minimum value, inclusive
			 */
			SpinBox *SetRange(int32_t range_min, int32_t range_max) {
				lv_spinbox_set_range(_obj, range_min, range_max);
				return this;
			}

			/**
			 * Set cursor position to a specific digit for edition
			 * @param obj pointer to spinbox
			 * @param pos selected position in spinbox
			 */
			SpinBox *SetCursorPos(uint8_t pos) {
				lv_spinbox_set_cursor_pos(_obj, pos);
				return this;
			}

			/*SpinBox *SetPos(uint8_t pos) {
				lv_spinbox_set_cursor_pos(_obj, pos);
				return this;
			}*/

			/**
			 * Set direction of digit step when clicking an encoder button while in editing mode
			 * @param obj pointer to spinbox
			 * @param direction the direction (LV_DIR_RIGHT or LV_DIR_LEFT)
			 */
			SpinBox *SetDigitStepDirection(lv_dir_t direction) {
				lv_spinbox_set_digit_step_direction(_obj, direction);
				return this;
			}

			/*=====================
			 * Getter functions
			 *====================*/

			/**
			 * Get spinbox rollover function status
			 * @param obj pointer to spinbox
			 */
			bool GetRolover() {
				return lv_spinbox_get_rollover(_obj);
			}

			/**
			 * Get the spinbox numeral value (user has to convert to float according to its digit format)
			 * @param obj pointer to spinbox
			 * @return value integer value of the spinbox
			 */
			int32_t GetValue() {
				return lv_spinbox_get_value(_obj);
			}

			/**
			 * Get the spinbox step value (user has to convert to float according to its digit format)
			 * @param obj pointer to spinbox
			 * @return value integer step value of the spinbox
			 */
			int32_t GetStep() {
				return lv_spinbox_get_step(_obj);
			}

			/*=====================
			 * Other functions
			 *====================*/

			/**
			 * Select next lower digit for edition by dividing the step by 10
			 * @param obj pointer to spinbox
			 */
			SpinBox *StepNext() {
				lv_spinbox_step_next(_obj);
				return this;
			}

			/**
			 * Select next higher digit for edition by multiplying the step by 10
			 * @param obj pointer to spinbox
			 */
			SpinBox *StepPrev() {
				lv_spinbox_step_prev(_obj);
				return this;
			}

			/**
			 * Increment spinbox value by one step
			 * @param obj pointer to spinbox
			 */
			SpinBox *Increment() {
				lv_spinbox_increment(_obj);
				return this;
			}

			/**
			 * Decrement spinbox value by one step
			 * @param obj pointer to spinbox
			 */
			SpinBox *Decrement() {
				lv_spinbox_decrement(_obj);
				return this;
			}

		};
	}
}

#endif

//Added by Sloeber 
#pragma once
