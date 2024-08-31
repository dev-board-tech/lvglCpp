/*
 * Rectangle.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVCPP_DRAW_LVRECTANGLE_H_
#define LVCPP_DRAW_LVRECTANGLE_H_

#include <lvgl.h>
#include <stdlib.h>
#include <Arduino.h>

namespace lvgl {
	namespace draw {
		class Rectangle {
		public:
			Rectangle() {
				lv_draw_rect_dsc_init(&rectangle);
			}
			Rectangle(Rectangle *rec) {
				if(rec) {
					memcpy(&rec->rectangle, &rectangle, sizeof(lv_draw_rect_dsc_t));
				}
			}
			
			inline lv_draw_rect_dsc_t *Get() {
				return &rectangle;
			}

			inline void Clone(Rectangle *rec) {
				if(rec) {
					memcpy(&rec->rectangle, &rectangle, sizeof(lv_draw_rect_dsc_t));
				}
			}

			inline Rectangle *SetRadius(lv_coord_t radius) {
				rectangle.radius = radius;
				return this;
			}
			inline lv_coord_t GetRadius() {
				return rectangle.radius;
			}

			inline Rectangle *SetBlendMode(lv_blend_mode_t blend_mode) {
				rectangle.blend_mode = blend_mode;
				return this;
			}
			inline lv_blend_mode_t GetBlendMode() {
				return rectangle.blend_mode;
			}

			/*Background*/
			inline Rectangle *SetOpacity(lv_opa_t bg_opa) {
				rectangle.bg_opa = bg_opa;
				return this;
			}
			inline lv_opa_t GetOpacity() {
				return rectangle.bg_opa;
			}

			/**< First element of a gradient is a color, so it maps well here*/
			inline Rectangle *SetColor(lv_color_t bg_color) {
				rectangle.bg_color = bg_color;
				return this;
			}
			inline lv_color_t GetColor() {
				return rectangle.bg_color;
			}

			inline Rectangle *SetGradientDirection(lv_grad_dir_t bg_grad_dir) {
				rectangle.bg_grad.dir = bg_grad_dir;
				return this;
			}
			inline lv_grad_dir_t GetGradientDirection() {
				return rectangle.bg_grad.dir;
			}

			inline Rectangle *SetGradientStopsCount(uint8_t stops_count) {
				rectangle.bg_grad.stops_count = stops_count;
				return this;
			}
			inline uint8_t GetGradientStopsCount() {
				return rectangle.bg_grad.stops_count;
			}

			inline Rectangle *SetGradientStopsColor(uint8_t idx, lv_color_t color) {
				rectangle.bg_grad.stops[idx].color = color;
				return this;
			}
			inline lv_color_t GetGradientStopsColor(uint8_t idx) {
				return rectangle.bg_grad.stops[idx].color;
			}

			inline Rectangle *SetGradientStopsFraction(uint8_t idx, uint8_t fraction) {
				rectangle.bg_grad.stops[idx].frac = fraction;
				return this;
			}
			inline uint8_t GetGradientStopsFraction(uint8_t idx) {
				return rectangle.bg_grad.stops[idx].frac;
			}

			inline Rectangle *SetGradientDither(lv_dither_mode_t dither) {
				rectangle.bg_grad.dither = dither;
				return this;
			}
			inline lv_dither_mode_t GetGradientDither() {
				return rectangle.bg_grad.dither;
			}

			/*Background img*/
			inline Rectangle *SetImageSource(const void * bg_img_src) {
				rectangle.bg_img_src = bg_img_src;
				return this;
			}
			inline const void * GetImageSource() {
				return rectangle.bg_img_src;
			}

			inline Rectangle *SetImageSymbolFont(const void * bg_img_symbol_font) {
				rectangle.bg_img_symbol_font = bg_img_symbol_font;
				return this;
			}
			inline const void * GetImageSymbolFont() {
				return rectangle.bg_img_symbol_font;
			}

			inline Rectangle *SetImageReColor(lv_color_t bg_img_recolor) {
				rectangle.bg_img_recolor = bg_img_recolor;
				return this;
			}
			inline lv_color_t GetImageReColor() {
				return rectangle.bg_img_recolor;
			}

			inline Rectangle *SetImageOpacity(lv_opa_t bg_img_opa) {
				rectangle.bg_img_opa = bg_img_opa;
				return this;
			}
			inline lv_opa_t GetImageOpacity() {
				return rectangle.bg_img_opa;
			}

			inline Rectangle *SetImageReColorOpacity(lv_opa_t bg_img_recolor_opa) {
				rectangle.bg_img_recolor_opa = bg_img_recolor_opa;
				return this;
			}
			inline lv_opa_t GetImageReColorOpacity() {
				return rectangle.bg_img_recolor_opa;
			}

			inline Rectangle *SetImaGetiled(uint8_t bg_img_tiled) {
				rectangle.bg_img_tiled = bg_img_tiled;
				return this;
			}
			inline uint8_t GetImaGetiled() {
				return rectangle.bg_img_tiled;
			}

			/*Border*/
			inline Rectangle *SetBorderColor(lv_color_t border_color) {
				rectangle.border_color = border_color;
				return this;
			}
			inline lv_color_t GetBorderColor() {
				return rectangle.border_color;
			}

			inline Rectangle *SetBorderWidth(lv_coord_t border_width) {
				rectangle.border_width = border_width;
				return this;
			}
			inline lv_coord_t GetBorderWidth() {
				return rectangle.border_width;
			}

			inline Rectangle *SetBorderOpacity(lv_opa_t border_opa) {
				rectangle.border_opa = border_opa;
				return this;
			}
			inline lv_opa_t GetBorderOpacity() {
				return rectangle.border_opa;
			}
			inline Rectangle *SetBorderOpacityPercent(uint8_t border_opa) {
				rectangle.border_opa = map(border_opa, 0, 100, 0, 255);
				return this;
			}
			inline lv_opa_t GetBorderOpacityPercent() {
				return map(rectangle.border_opa, 0, 255, 0, 100);
			}

			/*There is a border it will be drawn later.*/
			inline Rectangle *SetBorderPost(uint8_t border_post) {
				rectangle.border_post = border_post;
				return this;
			}
			inline uint8_t GetBorderPost() {
				return rectangle.border_post;
			}

			inline Rectangle *SetBorderSide(lv_border_side_t border_side) {
				rectangle.border_side = border_side;
				return this;
			}
			inline lv_border_side_t GetBorderSide() {
				return rectangle.border_side;
			}

			/*Outline*/
			inline Rectangle *SetOutlineColor(lv_color_t outline_color) {
				rectangle.outline_color = outline_color;
				return this;
			}
			inline lv_color_t GetOutlineColor() {
				return rectangle.outline_color;
			}

			inline Rectangle *SetOutlineWidth(lv_coord_t outline_width) {
				rectangle.outline_width = outline_width;
				return this;
			}
			inline lv_coord_t GetOutlineWidth() {
				return rectangle.outline_width;
			}

			inline Rectangle *SetOutlinePad(lv_coord_t outline_pad) {
				rectangle.outline_pad = outline_pad;
				return this;
			}
			inline lv_coord_t GetOutlinePad() {
				return rectangle.outline_pad;
			}

			inline Rectangle *SetOutlineOpacity(lv_opa_t outline_opa) {
				rectangle.outline_opa = outline_opa;
				return this;
			}
			inline lv_opa_t GetOutlineOpacity() {
				return rectangle.outline_opa;
			}

			/*Shadow*/
			inline Rectangle *SetShadowColor(lv_color_t shadow_color) {
				rectangle.shadow_color = shadow_color;
				return this;
			}
			inline lv_color_t GetShadowColor() {
				return rectangle.shadow_color;
			}

			inline Rectangle *SetShadowWidth(lv_coord_t shadow_width) {
				rectangle.shadow_width = shadow_width;
				return this;
			}
			inline lv_coord_t GetShadowWidth() {
				return rectangle.shadow_width;
			}

			inline Rectangle *SetShadowOffsetX(lv_coord_t shadow_ofs_x) {
				rectangle.shadow_ofs_x = shadow_ofs_x;
				return this;
			}
			inline lv_coord_t GetShadowOffsetX() {
				return rectangle.shadow_ofs_x;
			}

			inline Rectangle *SetShadowOffsetY(lv_coord_t shadow_ofs_y) {
				rectangle.shadow_ofs_y = shadow_ofs_y;
				return this;
			}
			inline lv_coord_t GetShadowOffsetY() {
				return rectangle.shadow_ofs_y;
			}

			inline Rectangle *SetShadowSpread(lv_coord_t shadow_spread) {
				rectangle.shadow_spread = shadow_spread;
				return this;
			}
			inline lv_coord_t GetShadowSpread() {
				return rectangle.shadow_spread;
			}

			inline Rectangle *SetShadowOpacity(lv_opa_t shadow_opa) {
				rectangle.shadow_opa = shadow_opa;
				return this;
			}
			inline lv_opa_t GetShadowOpacity() {
				return rectangle.shadow_opa;
			}
/**
 * Draw a rectangle
 * @param coords the coordinates of the rectangle
 * @param clip the rectangle will be drawn only in this area
 * @param dsc pointer to an initialized `lv_draw_rect_dsc_t` variable
 */
			static inline void drawRectangle(struct _lv_draw_ctx_t * draw_ctx, const lv_draw_rect_dsc_t * dsc, const lv_area_t * coords) {
				lv_draw_rect(draw_ctx, dsc, coords);
			}

			static inline void drawRectangle(struct _lv_draw_ctx_t * draw_ctx, lvgl::draw::Rectangle * dsc, const lv_area_t * coords) {
				lv_draw_rect(draw_ctx, dsc->Get(), coords);
			}

			private:
				lv_draw_rect_dsc_t rectangle;
		};
	}
}

#endif
