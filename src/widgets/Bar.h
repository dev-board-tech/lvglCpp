/*
 * Bar.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_BAR_H_
#define LVGLCPP_SRC_BAR_H_

#include "Object.h"

namespace lvgl {
	namespace widget {
		class Bar : public Object {
		public:
			Bar(lv_obj_t *parent) {
				_obj = lv_bar_create(parent);
			}
			Bar(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_bar_create(parent->GetObj());
				} else {
					_obj = lv_bar_create(NULL);
				}
			}
			Bar(Object parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_bar_create(((Object)parent).GetObj());
				} else {
					_obj = lv_bar_create(NULL);
				}
			}
			Bar(lv_obj_t *parent, bool isNew) {
				_obj = parent;
			}
			Bar(Object *parent, bool isNew) {
				_obj = parent->GetObj();
			}
			Bar(Object parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
			}

			~Bar() {

			}

			/**
			 * Set the object pointer when used as a child.
			 */
			inline Bar *setObj(lv_obj_t *obj) {
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
			 * Set a new value on the bar
			 * @param bar       pointer to a bar object
			 * @param value     new value
			 * @param anim      LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
			 */
			inline Bar *SetValue(int32_t value, lv_anim_enable_t anim) {
				lv_bar_set_value(_obj, value, anim);
				return this;
			}

			/**
			 * Set a new start value on the bar
			 * @param obj       pointer to a bar object
			 * @param value     new start value
			 * @param anim      LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
			 */
			inline Bar *SetStartValue(int32_t start_value, lv_anim_enable_t anim) {
				lv_bar_set_start_value(_obj, start_value,  anim);
				return this;
			}

			/**
			 * Set minimum and the maximum values of a bar
			 * @param obj       pointer to the bar object
			 * @param min       minimum value
			 * @param max       maximum value
			 */
			inline Bar *SetRange(int32_t min, int32_t max) {
				lv_bar_set_range(_obj, min, max);
				return this;
			}

			/**
			 * Set the type of bar.
			 * @param obj       pointer to bar object
			 * @param mode      bar type from ::lv_bar_mode_t
			 */
			inline Bar *SetMode(lv_bar_mode_t mode) {
				lv_bar_set_mode(_obj,  mode);
				return this;
			}

			/*=====================
			 * Getter functions
			 *====================*/

			/**
			 * Get the value of a bar
			 * @param obj       pointer to a bar object
			 * @return          the value of the bar
			 */
			inline int32_t GetValue() {
				return lv_bar_get_value((const lv_obj_t *)_obj);
			}

			/**
			 * Get the start value of a bar
			 * @param obj       pointer to a bar object
			 * @return          the start value of the bar
			 */
			inline int32_t GetStartValue() {
				return lv_bar_get_start_value((const lv_obj_t *)_obj);
			}

			/**
			 * Get the minimum value of a bar
			 * @param obj       pointer to a bar object
			 * @return          the minimum value of the bar
			 */
			inline int32_t GetMinValue() {
				return lv_bar_get_min_value((const lv_obj_t *)_obj);
			}

			/**
			 * Get the maximum value of a bar
			 * @param obj       pointer to a bar object
			 * @return          the maximum value of the bar
			 */
			inline int32_t GetMaxValue() {
				return lv_bar_get_max_value((const lv_obj_t *)_obj);
			}

			/**
			 * Get the type of bar.
			 * @param obj       pointer to bar object
			 * @return          bar type from ::lv_bar_mode_t
			 */
			inline lv_bar_mode_t GetMode() {
				return lv_bar_get_mode(_obj);
			}

		};
	}
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_BAR_H_ */
