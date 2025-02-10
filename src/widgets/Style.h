/*
 * Style.h
 *
 *      Author: Iulian Gheorghiu
 */
#ifndef LVGLCPP_SRC_H_
#define LVGLCPP_SRC_H_

#include <lvgl.h>

namespace lvgl {
	namespace style {
		class Prop {
		public:
			Prop() {
				memset(prop, LV_STYLE_PROP_INV, sizeof(prop));
			}
			Prop *Add(lv_style_prop_t p) {
				int i = 0;
				for(; i < sizeof(prop) - 1; i++) {
					if(prop[i] == p) {
						return this;
					}
					if(prop[i] == LV_STYLE_PROP_INV) {
						prop[i] = p;
						prop[i + 1] = LV_STYLE_PROP_INV;
						return this;
					}
				}
				return this;
			}
			Prop *Remove(lv_style_prop_t p) {
				int i = 0;
				bool found = false;
				for(; i < sizeof(prop) - 1; i++) {
					if(prop[i] == p || found == true) {
						found = true;
						prop[i] = prop[i + 1];
					}
					if(prop[i] == LV_STYLE_PROP_INV) {
						break;
					}
				}
				return this;
			}
			Prop *Remove(int idx) {
				int i = 0;
				bool found = false;
				for(; i < sizeof(prop) - 1; i++) {
					if(i >= idx) {
						found = true;
						prop[i] = prop[i + 1];
					}
					if(prop[i] == LV_STYLE_PROP_INV) {
						break;
					}
				}
				return this;
			}
			const lv_style_prop_t *Get() {
				return prop;
			}
		private:
			lv_style_prop_t prop[17];
		};
//------------------------------------------
		class Transition {
		public:
			Transition(Prop *prop, lv_anim_path_cb_t path_cb, uint32_t time = 250, uint32_t delay = 0, void * user_data = NULL) {
				lv_style_transition_dsc_init(&transitionDef, prop->Get(), path_cb, time, delay, user_data);
			}
			Transition(Prop prop, lv_anim_path_cb_t path_cb, uint32_t time = 250, uint32_t delay = 0, void * user_data = NULL) {
				lv_style_transition_dsc_init(&transitionDef, prop.Get(), path_cb, time, delay, user_data);
			}
			Transition(const lv_style_prop_t *prop, lv_anim_path_cb_t path_cb, uint32_t time = 250, uint32_t delay = 0, void * user_data = NULL) {
				lv_style_transition_dsc_init(&transitionDef, prop, path_cb, time, delay, user_data);
			}
			Transition *SetCb(lv_anim_path_cb_t path_cb) {
				pathCb = path_cb;
				return this;
			}
			lv_anim_path_cb_t GetCb() {
				return pathCb;
			}
			Transition *SetTime(uint32_t time) {
				this->time = time;
				return this;
			}
			uint32_t getTime() {
				return time;
			}
			Transition *SetDelay(uint32_t delay) {
				this->delay = delay;
				return this;
			}
			uint32_t getDelay() {
				return delay;
			}
			Transition *SetUserData(void * userData) {
				this->userData = userData;
				return this;
			}
			void *GetUserData() {
				return userData;
			}
			Transition *SetTransitionDef(lv_style_transition_dsc_t transitionDef) {
				this->transitionDef = transitionDef;
				return this;
			}
			lv_style_transition_dsc_t *Get() {
				return &transitionDef;
			}
		private:
			lv_style_transition_dsc_t transitionDef;
			lv_anim_path_cb_t pathCb;
			uint32_t time;
			uint32_t delay;
			void * userData;
		};
	} /* namespace style */
//------------------------------------------
	class Style {
	public:
		Style() {
			lv_style_init(&style);
		}
		lv_style_t *Get() {
			return &style;
		}
		
		
		Style *SetWidth(lv_coord_t value) {
			lv_style_set_width(&style, value);
			return this;
		}
		Style *SetMinWidth(lv_coord_t value) {
			lv_style_set_min_width(&style, value);
			return this;
		}
		Style *SetMaxWidth(lv_coord_t value) {
			lv_style_set_max_width(&style, value);
			return this;
		}
		Style *SetHeight(lv_coord_t value) {
			lv_style_set_height(&style, value);
			return this;
		}
		Style *SetMinHeight(lv_coord_t value) {
			lv_style_set_min_height(&style, value);
			return this;
		}
		Style *SetMaxHeight(lv_coord_t value) {
			lv_style_set_max_height(&style, value);
			return this;
		}
		Style *SetX(lv_coord_t value) {
			lv_style_set_x(&style, value);
			return this;
		}
		Style *SetY(lv_coord_t value) {
			lv_style_set_y(&style, value);
			return this;
		}
		Style *SetAlign(lv_align_t value) {
			lv_style_set_align(&style, value);
			return this;
		}
		Style *SetTransformWidth(lv_coord_t value) {
			lv_style_set_transform_width(&style, value);
			return this;
		}
		Style *SetTransformHeight(lv_coord_t value) {
			lv_style_set_transform_height(&style, value);
			return this;
		}
		Style *SetTranslateX(lv_coord_t value) {
			lv_style_set_translate_x(&style, value);
			return this;
		}
		Style *SetTranslateY(lv_coord_t value) {
			lv_style_set_translate_y(&style, value);
			return this;
		}
		Style *SetTransformZoom(lv_coord_t value) {
			lv_style_set_transform_zoom(&style, value);
			return this;
		}
		Style *SetTransformAngle(lv_coord_t value) {
			lv_style_set_transform_angle(&style, value);
			return this;
		}
		Style *SetTransformPivotX(lv_coord_t value) {
			lv_style_set_transform_pivot_x(&style, value);
			return this;
		}
		Style *SetTransformPivotY(lv_coord_t value) {
			lv_style_set_transform_pivot_y(&style, value);
			return this;
		}
		Style *SetPadTop(lv_coord_t value) {
			lv_style_set_pad_top(&style, value);
			return this;
		}
		Style *SetPadBottom(lv_coord_t value) {
			lv_style_set_pad_bottom(&style, value);
			return this;
		}
		Style *SetPadLeft(lv_coord_t value) {
			lv_style_set_pad_left(&style, value);
			return this;
		}
		Style *SetPadRight(lv_coord_t value) {
			lv_style_set_pad_right(&style, value);
			return this;
		}
		Style *SetPadRow(lv_coord_t value) {
			lv_style_set_pad_row(&style, value);
			return this;
		}
		Style *SetPadColumn(lv_coord_t value) {
			lv_style_set_pad_column(&style, value);
			return this;
		}
		Style *SetBgColor(lv_color_t value) {
			lv_style_set_bg_color(&style, value);
			return this;
		}
		Style *SetBgOpacity(lv_opa_t value) {
			lv_style_set_bg_opa(&style, value);
			return this;
		}
		Style *SetBgGradientColor(lv_color_t value) {
			lv_style_set_bg_grad_color(&style, value);
			return this;
		}
		Style *SetBgGradientDirection(lv_grad_dir_t value) {
			lv_style_set_bg_grad_dir(&style, value);
			return this;
		}
		Style *SetBgMainStop(lv_coord_t value) {
			lv_style_set_bg_main_stop(&style, value);
			return this;
		}
		Style *SetBgGradientStop(lv_coord_t value) {
			lv_style_set_bg_grad_stop(&style, value);
			return this;
		}
		Style *SetBgGradient(const lv_grad_dsc_t * value) {
			lv_style_set_bg_grad(&style,value);
			return this;
		}
		Style *SetBgDitherMode(lv_dither_mode_t value) {
			lv_style_set_bg_dither_mode(&style, value);
			return this;
		}
		Style *SetBgImageSource(const Style ** value) {
			lv_style_set_bg_img_src(&style, value);
			return this;
		}
		Style *SetBgImageOpacity(lv_opa_t value) {
			lv_style_set_bg_img_opa(&style, value);
			return this;
		}
		Style *SetBgImageReColor(lv_color_t value) {
			lv_style_set_bg_img_recolor(&style, value);
			return this;
		}
		Style *SetImageBgReColorOpacity(lv_opa_t value) {
			lv_style_set_bg_img_recolor_opa(&style, value);
			return this;
		}
		Style *SetBgImageTiled(bool value) {
			lv_style_set_bg_img_tiled(&style, value);
			return this;
		}
		Style *SetBorderColor(lv_color_t value) {
			lv_style_set_border_color(&style, value);
			return this;
		}
		Style *SetBorderOpacity(lv_opa_t value) {
			lv_style_set_border_opa(&style, value);
			return this;
		}
		Style *SetBorderWidth(lv_coord_t value) {
			lv_style_set_border_width(&style, value);
			return this;
		}
		Style *SetBorderSide(lv_border_side_t value) {
			lv_style_set_border_side(&style, value);
			return this;
		}
		Style *SetBorderPost(bool value) {
			lv_style_set_border_post(&style, value);
			return this;
		}
		Style *SetOutlineWidth(lv_coord_t value) {
			lv_style_set_outline_width(&style, value);
			return this;
		}
		Style *SetOutlineColor(lv_color_t value) {
			lv_style_set_outline_color(&style, value);
			return this;
		}
		Style *SetOutlineOpacity(lv_opa_t value) {
			lv_style_set_outline_opa(&style, value);
			return this;
		}
		Style *SetOutlinePad(lv_coord_t value) {
			lv_style_set_outline_pad(&style, value);
			return this;
		}
		Style *SetShadowWidth(lv_coord_t value) {
			lv_style_set_shadow_width(&style, value);
			return this;
		}
		Style *SetShadowOffsetX(lv_coord_t value) {
			lv_style_set_shadow_ofs_x(&style, value);
			return this;
		}
		Style *SetShadowOffsetY(lv_coord_t value) {
			lv_style_set_shadow_ofs_y(&style, value);
			return this;
		}
		Style *SetShadowSpread(lv_coord_t value) {
			lv_style_set_shadow_spread(&style, value);
			return this;
		}
		Style *SetShadowColor(lv_color_t value) {
			lv_style_set_shadow_color(&style, value);
			return this;
		}
		Style *SetShadowOpacity(lv_opa_t value) {
			lv_style_set_shadow_opa(&style, value);
			return this;
		}
		Style *SetImageOpacity(lv_opa_t value) {
			lv_style_set_img_opa(&style, value);
			return this;
		}
		Style *SetImageReColor(lv_color_t value) {
			lv_style_set_img_recolor(&style, value);
			return this;
		}
		Style *SetImageReColorOpacity(lv_opa_t value) {
			lv_style_set_img_recolor_opa(&style, value);
			return this;
		}
		Style *SetLineWidth(lv_coord_t value) {
			lv_style_set_line_width(&style, value);
			return this;
		}
		Style *SetLineDashWidth(lv_coord_t value) {
			lv_style_set_line_dash_width(&style, value);
			return this;
		}
		Style *SetLineDashGap(lv_coord_t value) {
			lv_style_set_line_dash_gap(&style, value);
			return this;
		}
		Style *SetLineRounded(bool value) {
			lv_style_set_line_rounded(&style, value);
			return this;
		}
		Style *SetLineColor(lv_color_t value) {
			lv_style_set_line_color(&style, value);
			return this;
		}
		Style *SetLineOpacity(lv_opa_t value) {
			lv_style_set_line_opa(&style, value);
			return this;
		}
		Style *SetArcWidth(lv_coord_t value) {
			lv_style_set_arc_width(&style, value);
			return this;
		}
		Style *SetArcRounded(bool value) {
			lv_style_set_arc_rounded(&style, value);
			return this;
		}
		Style *SetArcColor(lv_color_t value) {
			lv_style_set_arc_color(&style, value);
			return this;
		}
		Style *SetArcOpacity(lv_opa_t value) {
			lv_style_set_arc_opa(&style, value);
			return this;
		}
		Style *SetArcImageSource(const Style ** value) {
			lv_style_set_arc_img_src(&style, value);
			return this;
		}
		Style *SetTextColor(lv_color_t value) {
			lv_style_set_text_color(&style, value);
			return this;
		}
		Style *SetTextOpacity(lv_opa_t value) {
			lv_style_set_text_opa(&style, value);
			return this;
		}
		Style *SetTextFont(const lv_font_t * value) {
			lv_style_set_text_font(&style, value);
			return this;
		}
		Style *SetTextLetterSpace(lv_coord_t value) {
			lv_style_set_text_letter_space(&style, value);
			return this;
		}
		Style *SetTextLineSpace(lv_coord_t value) {
			lv_style_set_text_line_space(&style, value);
			return this;
		}
		Style *SetTextDecor(lv_text_decor_t value) {
			lv_style_set_text_decor(&style, value);
			return this;
		}
		Style *SetTextAlign(lv_coord_t value) {
			lv_style_set_text_align(&style, value);
			return this;
		}
		Style *SetRadius(lv_coord_t value) {
			lv_style_set_radius(&style, value);
			return this;
		}
		Style *SetClipCorner(bool value) {
			lv_style_set_clip_corner(&style, value);
			return this;
		}
		Style *SetOpacity(lv_opa_t value) {
			lv_style_set_opa(&style, value);
			return this;
		}
		Style *SetOpacityLayered(lv_opa_t value) {
			lv_style_set_opa_layered(&style, value);
			return this;
		}
		Style *SetColorFilterDsc(const lv_color_filter_dsc_t * value) {
			lv_style_set_color_filter_dsc(&style, value);
			return this;
		}
		Style *SetColorFilterOpacity(lv_opa_t value) {
			lv_style_set_color_filter_opa(&style, value);
			return this;
		}
		Style *SetAnimation(const lv_anim_t * value) {
			lv_style_set_anim(&style, value);
			return this;
		}
		Style *SetAnimationTime(uint32_t value) {
			lv_style_set_anim_time(&style, value);
			return this;
		}
		Style *SetAnimationSpeed(uint32_t value) {
			lv_style_set_anim_speed(&style, value);
			return this;
		}
		Style *SetTransition(const lv_style_transition_dsc_t *value) {
			lv_style_set_transition(&style, value);
			return this;
		}
		Style *SetTransition(lvgl::style::Transition *value) {
			lv_style_set_transition(&style, value->Get());
			return this;
		}
		Style *SetTransition(lvgl::style::Transition value) {
			lv_style_set_transition(&style, value.Get());
			return this;
		}
		Style *SetBlendMode(lv_blend_mode_t value) {
			lv_style_set_blend_mode(&style, value);
			return this;
		}
		Style *SetLayout(uint16_t value) {
			lv_style_set_layout(&style, value);
			return this;
		}
		Style *SetBaseDirection(lv_base_dir_t value) {
			lv_style_set_base_dir(&style, value);
			return this;
		}
		
		Style *SetFlexFlow(lv_flex_flow_t value) {
			lv_style_set_flex_flow(&style, value);
			return this;
		}
		Style *SetFlexMainPlace(lv_flex_align_t value) {
			lv_style_set_flex_main_place(&style, value);
			return this;
		}
		Style *SetFlexCrossPlace(lv_flex_align_t value) {
			lv_style_set_flex_cross_place(&style, value);
			return this;
		}
		Style *SetFlexTrackPlace(lv_flex_align_t value) {
			lv_style_set_flex_track_place(&style, value);
			return this;
		}
		Style *SetFlexGrow(uint8_t value) {
			lv_style_set_flex_grow(&style, value);
			return this;
		}
		
		
		
		/**
		 * Clear all properties from a style and free all allocated memories.
		 * @param style pointer to a style
		 */
		inline Style * Reset() {
			lv_style_reset(&style);
			return this;
		}

		/**
		 * Register a new style property for custom usage
		 * @return a new property ID, or LV_STYLE_PROP_INV if there are no more available.
		 * @example
		 * lv_style_prop_t MY_PROP;
		 * static inline void lv_style_set_my_prop(lv_style_t * style, lv_color_t value) {
		 * lv_style_value_t v = {.color = value}; lv_style_set_prop(style, MY_PROP, v); }
		 *
		 * ...
		 * MY_PROP = lv_style_register_prop();
		 * ...
		 * lv_style_set_my_prop(&style1, lv_palette_main(LV_PALETTE_RED));
		 */
		inline static lv_style_prop_t RegisterProp(uint8_t flag) {
			return lv_style_register_prop(flag);
		}

		/**
		 * Get the number of custom properties that have been registered thus far.
		 */
		inline static lv_style_prop_t GetNumCustomProps(void) {
			return lv_style_get_num_custom_props();
		}

		/**
		 * Remove a property from a style
		 * @param style pointer to a style
		 * @param prop  a style property ORed with a state.
		 * @return true: the property was found and removed; false: the property wasn't found
		 */
		inline bool RemoveProp(lv_style_prop_t prop) {
			return lv_style_remove_prop(&style, prop);
		}

		/**
		 * Set the value of property in a style.
		 * This function shouldn't be used directly by the user.
		 * Instead use `lv_style_set_<prop_name>()`. E.g. `lv_style_set_bg_color()`
		 * @param style pointer to style
		 * @param prop the ID of a property (e.g. `LV_STYLE_BG_COLOR`)
		 * @param value `lv_style_value_t` variable in which a field is set according to the type of `prop`
		 */
		inline Style * SetProp(lv_style_prop_t prop, lv_style_value_t value) {
			lv_style_set_prop(&style, prop, value);
			return this;
		}

		/**
		 * Set a special meta state for a property in a style.
		 * This function shouldn't be used directly by the user.
		 * @param style pointer to style
		 * @param prop the ID of a property (e.g. `LV_STYLE_BG_COLOR`)
		 * @param meta the meta value to attach to the property in the style
		 */
		inline Style * SetPropMeta(lv_style_prop_t prop, uint16_t meta) {
			lv_style_set_prop_meta(&style, prop, meta);
			return this;
		}

		/**
		 * Get the value of a property
		 * @param style pointer to a style
		 * @param prop  the ID of a property
		 * @param value pointer to a `lv_style_value_t` variable to store the value
		 * @return LV_RES_INV: the property wasn't found in the style (`value` is unchanged)
		 *         LV_RES_OK: the property was fond, and `value` is set accordingly
		 * @note For performance reasons there are no sanity check on `style`
		 */
		inline lv_style_res_t GetProp(lv_style_prop_t prop, lv_style_value_t * value) {
			return lv_style_get_prop(&style, prop, value);
		}

		/**
		 * Initialize a transition descriptor.
		 * @param tr        pointer to a transition descriptor to initialize
		 * @param props     an array with the properties to transition. The last element must be zero.
		 * @param path_cb   an animation path (ease) callback. If `NULL` liner path will be used.
		 * @param time      duration of the transition in [ms]
		 * @param delay     delay before the transition in [ms]
		 * @param user_data any custom data that will be saved in the transition animation and will be available when `path_cb` is called
		 * @example
		 * const static lv_style_prop_t trans_props[] = { LV_STYLE_BG_OPA, LV_STYLE_BG_COLOR, 0 };
		 *  static lv_style_transition_dsc_t trans1;
		 *  lv_style_transition_dsc_init(&trans1, trans_props, NULL, 300, 0, NULL);
		 */
		inline static void TransitionDscInit(lv_style_transition_dsc_t * tr, const lv_style_prop_t props[],
				                          lv_anim_path_cb_t path_cb, uint32_t time, uint32_t delay, void * user_data) {
			lv_style_transition_dsc_init(tr, props, path_cb, time, delay, user_data);
		}

		/**
		 * Get the default value of a property
		 * @param prop the ID of a property
		 * @return the default value
		 */
		inline static lv_style_value_t PropGetDefault(lv_style_prop_t prop) {
			return lv_style_prop_get_default(prop);
		}

		/**
		 * Get the value of a property
		 * @param style pointer to a style
		 * @param prop  the ID of a property
		 * @param value pointer to a `lv_style_value_t` variable to store the value
		 * @return LV_RES_INV: the property wasn't found in the style (`value` is unchanged)
		 *         LV_RES_OK: the property was fond, and `value` is set accordingly
		 * @note For performance reasons there are no sanity check on `style`
		 * @note This function is the same as ::lv_style_get_prop but inlined. Use it only on performance critical places
		 */
		inline lv_style_res_t GetPropInlined(lv_style_prop_t prop, lv_style_value_t * value) {
			return lv_style_get_prop_inlined(&style, prop, value);
		}

		/**
		 * Checks if a style is empty (has no properties)
		 * @param style pointer to a style
		 * @return true if the style is empty
		 */
		inline bool IsEmpty() {
			return lv_style_is_empty(&style);
		}

		/**
		 * Tell the group of a property. If the a property from a group is set in a style the (1 << group) bit of style->has_group is set.
		 * It allows early skipping the style if the property is not exists in the style at all.
		 * @param prop a style property
		 * @return the group [0..7] 7 means all the custom properties with index > 112
		 */
		inline uint8_t GetPropGroup(lv_style_prop_t prop) {
			return _lv_style_get_prop_group(prop);
		}

		/**
		 * Get the flags of a built-in or custom property.
		 *
		 * @param prop a style property
		 * @return the flags of the property
		 */
		inline static uint8_t PropLockupFlags(lv_style_prop_t prop) {
			return _lv_style_prop_lookup_flags(prop);
		}


		inline Style * SetSize(lv_coord_t value) {
			lv_style_set_size(&style, value);
			return this;
		}

		inline Style * SetPadAll(lv_coord_t value) {
			lv_style_set_pad_all(&style, value);
			return this;
		}

		inline Style * SetPadHorisontal(lv_coord_t value) {
			lv_style_set_pad_hor(&style, value);
			return this;
		}

		inline Style * SetPadVer(lv_coord_t value) {
			lv_style_set_pad_ver(&style, value);
			return this;
		}

		inline Style * SetPadGap(lv_coord_t value) {
			lv_style_set_pad_gap(&style, value);
			return this;
		}

		/**
		 * @brief Check if the style property has a specified behavioral flag.
		 *
		 * Do not pass multiple flags to this function as backwards-compatibility is not guaranteed
		 * for that.
		 *
		 * @param prop Property ID
		 * @param flag Flag
		 * @return true if the flag is set for this property
		 */
		static inline bool PropHasFlag(lv_style_prop_t prop, uint8_t flag) {
			return lv_style_prop_has_flag(prop, flag);
		}


		private:
			lv_style_t style;
	};
} /* namespace lvgl */

#endif
