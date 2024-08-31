/*
 * Slider.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_SLIDER_H_
#define LVGLCPP_SRC_SLIDER_H_

#include "Object.h"

namespace lvgl {
	namespace widget {
		class Slider : public Object {
		public:
			Slider(lv_obj_t *parent = NULL) {
				if(parent) {
					_obj = lv_slider_create(parent);
				} else {
					_obj = lv_slider_create(lv_scr_act());
				}
				_child = NULL;
				_childs = NULL;
			}
			~Slider() {

			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

			/*=====================
			 * Setter functions
			 *====================*/

			/**
			 * Set a new value on the slider
			 * @param obj       pointer to a slider object
			 * @param value     the new value
			 * @param anim      LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
			 */
			inline Slider *SetValue(int32_t value, lv_anim_enable_t anim) {
				lv_bar_set_value(_obj, value, anim);
				return this;
			}

			/**
			 * Set a new value for the left knob of a slider
			 * @param obj       pointer to a slider object
			 * @param value     new value
			 * @param anim      LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
			 */
			inline Slider *SetLeftValue(int32_t value, lv_anim_enable_t anim) {
				lv_bar_set_start_value(_obj, value, anim);
				return this;
			}

			/**
			 * Set minimum and the maximum values of a bar
			 * @param obj       pointer to the slider object
			 * @param min       minimum value
			 * @param max       maximum value
			 */
			inline Slider *SetRange(int32_t min, int32_t max) {
				lv_bar_set_range(_obj, min, max);
				return this;
			}

			/**
			 * Set the mode of slider.
			 * @param obj       pointer to a slider object
			 * @param mode      the mode of the slider. See ::lv_slider_mode_t
			 */
			inline Slider *SetMode(lv_slider_mode_t mode) {
				lv_bar_set_mode(_obj, (lv_bar_mode_t)mode);
				return this;
			}

			/*=====================
			 * Getter functions
			 *====================*/

			/**
			 * Get the value of the main knob of a slider
			 * @param obj       pointer to a slider object
			 * @return          the value of the main knob of the slider
			 */
			inline int32_t GetValue() {
				return lv_bar_get_value((const lv_obj_t *)_obj);
			}

			/**
			 * Get the value of the left knob of a slider
			 * @param obj       pointer to a slider object
			 * @return          the value of the left knob of the slider
			 */
			inline int32_t GetLeftValue() {
				return lv_bar_get_start_value((const lv_obj_t *)_obj);
			}

			/**
			 * Get the minimum value of a slider
			 * @param obj       pointer to a slider object
			 * @return          the minimum value of the slider
			 */
			inline int32_t GetMinValue() {
				return lv_bar_get_min_value((const lv_obj_t *)_obj);
			}

			/**
			 * Get the maximum value of a slider
			 * @param obj       pointer to a slider object
			 * @return          the maximum value of the slider
			 */
			inline int32_t GetMaxValue(const lv_obj_t * obj) {
				return lv_bar_get_max_value((const lv_obj_t *)_obj);
			}

			/**
			 * Give the slider is being dragged or not
			 * @param obj       pointer to a slider object
			 * @return          true: drag in progress false: not dragged
			 */
			inline bool IsDragged() {
				return lv_slider_is_dragged((const lv_obj_t *)_obj);
			}

			/**
			 * Get the mode of the slider.
			 * @param obj       pointer to a bar object
			 * @return          see ::lv_slider_mode_t
			 */
			inline lv_slider_mode_t GetMode() {
				lv_bar_mode_t mode = lv_bar_get_mode(_obj);
				if(mode == LV_BAR_MODE_SYMMETRICAL) return LV_SLIDER_MODE_SYMMETRICAL;
				else if(mode == LV_BAR_MODE_RANGE) return LV_SLIDER_MODE_RANGE;
				else return LV_SLIDER_MODE_NORMAL;
			}

		};
	} /* namespace widget */
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_SLIDER_H_ */
