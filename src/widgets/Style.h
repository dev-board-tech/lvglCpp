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
			lvgl::style::Prop *add(lv_style_prop_t p) {
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
			lvgl::style::Prop *remove(lv_style_prop_t p) {
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
			lvgl::style::Prop *remove(int idx) {
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
			const lv_style_prop_t *get() {
				return prop;
			}
		private:
			lv_style_prop_t prop[17];
		};
//------------------------------------------
		class Transition {
		public:
			Transition(lvgl::style::Prop *prop, lv_anim_path_cb_t path_cb, uint32_t time = 250, uint32_t delay = 0, void * user_data = NULL) {
				lv_style_transition_dsc_init(&transitionDef, prop->get(), path_cb, time, delay, user_data);
			}
			Transition(lvgl::style::Prop prop, lv_anim_path_cb_t path_cb, uint32_t time = 250, uint32_t delay = 0, void * user_data = NULL) {
				lv_style_transition_dsc_init(&transitionDef, prop.get(), path_cb, time, delay, user_data);
			}
			Transition(const lv_style_prop_t *prop, lv_anim_path_cb_t path_cb, uint32_t time = 250, uint32_t delay = 0, void * user_data = NULL) {
				lv_style_transition_dsc_init(&transitionDef, prop, path_cb, time, delay, user_data);
			}
			lvgl::style::Transition *setCb(lv_anim_path_cb_t path_cb) {
				pathCb = path_cb;
				return this;
			}
			lv_anim_path_cb_t getCb() {
				return pathCb;
			}
			lvgl::style::Transition *setTime(uint32_t time) {
				this->time = time;
				return this;
			}
			uint32_t getTime() {
				return time;
			}
			lvgl::style::Transition *setDelay(uint32_t delay) {
				this->delay = delay;
				return this;
			}
			uint32_t getDelay() {
				return delay;
			}
			lvgl::style::Transition *setUserData(void * userData) {
				this->userData = userData;
				return this;
			}
			void *getUserData() {
				return userData;
			}
			lvgl::style::Transition *setTransitionDef(lv_style_transition_dsc_t transitionDef) {
				this->transitionDef = transitionDef;
				return this;
			}
			lv_style_transition_dsc_t *get() {
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
		lv_style_t *get() {
			return &style;
		}
		
		
		lvgl::Style *setWidth(lv_coord_t value) {
			lv_style_set_width(&style, value);
			return this;
		}
		lvgl::Style *setMinWidth(lv_coord_t value) {
			lv_style_set_min_width(&style, value);
			return this;
		}
		lvgl::Style *setMaxWidth(lv_coord_t value) {
			lv_style_set_max_width(&style, value);
			return this;
		}
		lvgl::Style *setHeight(lv_coord_t value) {
			lv_style_set_height(&style, value);
			return this;
		}
		lvgl::Style *setMinHeight(lv_coord_t value) {
			lv_style_set_min_height(&style, value);
			return this;
		}
		lvgl::Style *setMaxHeight(lv_coord_t value) {
			lv_style_set_max_height(&style, value);
			return this;
		}
		lvgl::Style *setX(lv_coord_t value) {
			lv_style_set_x(&style, value);
			return this;
		}
		lvgl::Style *setY(lv_coord_t value) {
			lv_style_set_y(&style, value);
			return this;
		}
		lvgl::Style *setAlign(lv_align_t value) {
			lv_style_set_align(&style, value);
			return this;
		}
		lvgl::Style *setTransformWidth(lv_coord_t value) {
			lv_style_set_transform_width(&style, value);
			return this;
		}
		lvgl::Style *setTransformHeight(lv_coord_t value) {
			lv_style_set_transform_height(&style, value);
			return this;
		}
		lvgl::Style *setTranslateX(lv_coord_t value) {
			lv_style_set_translate_x(&style, value);
			return this;
		}
		lvgl::Style *setTranslateY(lv_coord_t value) {
			lv_style_set_translate_y(&style, value);
			return this;
		}
		lvgl::Style *setTransformZoom(lv_coord_t value) {
			lv_style_set_transform_zoom(&style, value);
			return this;
		}
		lvgl::Style *setTransformAngle(lv_coord_t value) {
			lv_style_set_transform_angle(&style, value);
			return this;
		}
		lvgl::Style *setTransformPivotX(lv_coord_t value) {
			lv_style_set_transform_pivot_x(&style, value);
			return this;
		}
		lvgl::Style *setTransformPivotY(lv_coord_t value) {
			lv_style_set_transform_pivot_y(&style, value);
			return this;
		}
		lvgl::Style *setPadTop(lv_coord_t value) {
			lv_style_set_pad_top(&style, value);
			return this;
		}
		lvgl::Style *setPadBottom(lv_coord_t value) {
			lv_style_set_pad_bottom(&style, value);
			return this;
		}
		lvgl::Style *setPadLeft(lv_coord_t value) {
			lv_style_set_pad_left(&style, value);
			return this;
		}
		lvgl::Style *setPadRight(lv_coord_t value) {
			lv_style_set_pad_right(&style, value);
			return this;
		}
		lvgl::Style *setPadRow(lv_coord_t value) {
			lv_style_set_pad_row(&style, value);
			return this;
		}
		lvgl::Style *setPadColumn(lv_coord_t value) {
			lv_style_set_pad_column(&style, value);
			return this;
		}
		lvgl::Style *setBgColor(lv_color_t value) {
			lv_style_set_bg_color(&style, value);
			return this;
		}
		lvgl::Style *setBgOpacity(lv_opa_t value) {
			lv_style_set_bg_opa(&style, value);
			return this;
		}
		lvgl::Style *setBgGradientColor(lv_color_t value) {
			lv_style_set_bg_grad_color(&style, value);
			return this;
		}
		lvgl::Style *setBgGradientDirection(lv_grad_dir_t value) {
			lv_style_set_bg_grad_dir(&style, value);
			return this;
		}
		lvgl::Style *setBgMainStop(lv_coord_t value) {
			lv_style_set_bg_main_stop(&style, value);
			return this;
		}
		lvgl::Style *setBgGradientStop(lv_coord_t value) {
			lv_style_set_bg_grad_stop(&style, value);
			return this;
		}
		lvgl::Style *setBgGradient(const lv_grad_dsc_t * value) {
			lv_style_set_bg_grad(&style,value);
			return this;
		}
		lvgl::Style *setBgDitherMode(lv_dither_mode_t value) {
			lv_style_set_bg_dither_mode(&style, value);
			return this;
		}
		lvgl::Style *setBgImageSource(const lvgl::Style ** value) {
			lv_style_set_bg_img_src(&style, value);
			return this;
		}
		lvgl::Style *setBgImageOpacity(lv_opa_t value) {
			lv_style_set_bg_img_opa(&style, value);
			return this;
		}
		lvgl::Style *setBgImageReColor(lv_color_t value) {
			lv_style_set_bg_img_recolor(&style, value);
			return this;
		}
		lvgl::Style *setImageBgReColorOpacity(lv_opa_t value) {
			lv_style_set_bg_img_recolor_opa(&style, value);
			return this;
		}
		lvgl::Style *setBgImageTiled(bool value) {
			lv_style_set_bg_img_tiled(&style, value);
			return this;
		}
		lvgl::Style *setBorderColor(lv_color_t value) {
			lv_style_set_border_color(&style, value);
			return this;
		}
		lvgl::Style *setBorderOpacity(lv_opa_t value) {
			lv_style_set_border_opa(&style, value);
			return this;
		}
		lvgl::Style *setBorderWidth(lv_coord_t value) {
			lv_style_set_border_width(&style, value);
			return this;
		}
		lvgl::Style *setBorderSide(lv_border_side_t value) {
			lv_style_set_border_side(&style, value);
			return this;
		}
		lvgl::Style *setBorderPost(bool value) {
			lv_style_set_border_post(&style, value);
			return this;
		}
		lvgl::Style *setOutlineWidth(lv_coord_t value) {
			lv_style_set_outline_width(&style, value);
			return this;
		}
		lvgl::Style *setOutlineColor(lv_color_t value) {
			lv_style_set_outline_color(&style, value);
			return this;
		}
		lvgl::Style *setOutlineOpacity(lv_opa_t value) {
			lv_style_set_outline_opa(&style, value);
			return this;
		}
		lvgl::Style *setOutlinePad(lv_coord_t value) {
			lv_style_set_outline_pad(&style, value);
			return this;
		}
		lvgl::Style *setShadowWidth(lv_coord_t value) {
			lv_style_set_shadow_width(&style, value);
			return this;
		}
		lvgl::Style *setShadowOffsetX(lv_coord_t value) {
			lv_style_set_shadow_ofs_x(&style, value);
			return this;
		}
		lvgl::Style *setShadowOffsetY(lv_coord_t value) {
			lv_style_set_shadow_ofs_y(&style, value);
			return this;
		}
		lvgl::Style *setShadowSpread(lv_coord_t value) {
			lv_style_set_shadow_spread(&style, value);
			return this;
		}
		lvgl::Style *setShadowColor(lv_color_t value) {
			lv_style_set_shadow_color(&style, value);
			return this;
		}
		lvgl::Style *setShadowOpacity(lv_opa_t value) {
			lv_style_set_shadow_opa(&style, value);
			return this;
		}
		lvgl::Style *setImageOpacity(lv_opa_t value) {
			lv_style_set_img_opa(&style, value);
			return this;
		}
		lvgl::Style *setImageReColor(lv_color_t value) {
			lv_style_set_img_recolor(&style, value);
			return this;
		}
		lvgl::Style *setImageReColorOpacity(lv_opa_t value) {
			lv_style_set_img_recolor_opa(&style, value);
			return this;
		}
		lvgl::Style *setLineWidth(lv_coord_t value) {
			lv_style_set_line_width(&style, value);
			return this;
		}
		lvgl::Style *setLineDashWidth(lv_coord_t value) {
			lv_style_set_line_dash_width(&style, value);
			return this;
		}
		lvgl::Style *setLineDashGap(lv_coord_t value) {
			lv_style_set_line_dash_gap(&style, value);
			return this;
		}
		lvgl::Style *setLineRounded(bool value) {
			lv_style_set_line_rounded(&style, value);
			return this;
		}
		lvgl::Style *setLineColor(lv_color_t value) {
			lv_style_set_line_color(&style, value);
			return this;
		}
		lvgl::Style *setLineOpacity(lv_opa_t value) {
			lv_style_set_line_opa(&style, value);
			return this;
		}
		lvgl::Style *setArcWidth(lv_coord_t value) {
			lv_style_set_arc_width(&style, value);
			return this;
		}
		lvgl::Style *setArcRounded(bool value) {
			lv_style_set_arc_rounded(&style, value);
			return this;
		}
		lvgl::Style *setArcColor(lv_color_t value) {
			lv_style_set_arc_color(&style, value);
			return this;
		}
		lvgl::Style *setArcOpacity(lv_opa_t value) {
			lv_style_set_arc_opa(&style, value);
			return this;
		}
		lvgl::Style *setArcImageSource(const lvgl::Style ** value) {
			lv_style_set_arc_img_src(&style, value);
			return this;
		}
		lvgl::Style *setTextColor(lv_color_t value) {
			lv_style_set_text_color(&style, value);
			return this;
		}
		lvgl::Style *setTextOpacity(lv_opa_t value) {
			lv_style_set_text_opa(&style, value);
			return this;
		}
		lvgl::Style *setTextFont(const lv_font_t * value) {
			lv_style_set_text_font(&style, value);
			return this;
		}
		lvgl::Style *setTextLetterSpace(lv_coord_t value) {
			lv_style_set_text_letter_space(&style, value);
			return this;
		}
		lvgl::Style *setTextLineSpace(lv_coord_t value) {
			lv_style_set_text_line_space(&style, value);
			return this;
		}
		lvgl::Style *setTextDecor(lv_text_decor_t value) {
			lv_style_set_text_decor(&style, value);
			return this;
		}
		lvgl::Style *setTextAlign(lv_coord_t value) {
			lv_style_set_text_align(&style, value);
			return this;
		}
		lvgl::Style *setRadius(lv_coord_t value) {
			lv_style_set_radius(&style, value);
			return this;
		}
		lvgl::Style *setClipCorner(bool value) {
			lv_style_set_clip_corner(&style, value);
			return this;
		}
		lvgl::Style *setOpacity(lv_opa_t value) {
			lv_style_set_opa(&style, value);
			return this;
		}
		lvgl::Style *setOpacityLayered(lv_opa_t value) {
			lv_style_set_opa_layered(&style, value);
			return this;
		}
		lvgl::Style *setColorFilterDsc(const lv_color_filter_dsc_t * value) {
			lv_style_set_color_filter_dsc(&style, value);
			return this;
		}
		lvgl::Style *setColorFilterOpacity(lv_opa_t value) {
			lv_style_set_color_filter_opa(&style, value);
			return this;
		}
		lvgl::Style *setAnimation(const lv_anim_t * value) {
			lv_style_set_anim(&style, value);
			return this;
		}
		lvgl::Style *setAnimationTime(uint32_t value) {
			lv_style_set_anim_time(&style, value);
			return this;
		}
		lvgl::Style *setAnimationSpeed(uint32_t value) {
			lv_style_set_anim_speed(&style, value);
			return this;
		}
		lvgl::Style *setTransition(const lv_style_transition_dsc_t * value) {
			lv_style_set_transition(&style, value);
			return this;
		}
		lvgl::Style *setTransition(lvgl::style::Transition *value) {
			lv_style_set_transition(&style, value->get());
			return this;
		}
		lvgl::Style *setTransition(lvgl::style::Transition value) {
			lv_style_set_transition(&style, value.get());
			return this;
		}
		lvgl::Style *setBlendMode(lv_blend_mode_t value) {
			lv_style_set_blend_mode(&style, value);
			return this;
		}
		lvgl::Style *setLayout(uint16_t value) {
			lv_style_set_layout(&style, value);
			return this;
		}
		lvgl::Style *setBaseDirection(lv_base_dir_t value) {
			lv_style_set_base_dir(&style, value);
			return this;
		}
		
		lvgl::Style *setFlexFlow(lv_flex_flow_t value) {
			lv_style_set_flex_flow(&style, value);
			return this;
		}
		lvgl::Style *setFlexMainPlace(lv_flex_align_t value) {
			lv_style_set_flex_main_place(&style, value);
			return this;
		}
		lvgl::Style *setFlexCrossPlace(lv_flex_align_t value) {
			lv_style_set_flex_cross_place(&style, value);
			return this;
		}
		lvgl::Style *setFlexTrackPlace(lv_flex_align_t value) {
			lv_style_set_flex_track_place(&style, value);
			return this;
		}
		lvgl::Style *setFlexGrow(uint8_t value) {
			lv_style_set_flex_grow(&style, value);
			return this;
		}


	private:
		lv_style_t style;
	};
} /* namespace lvgl */

#endif
