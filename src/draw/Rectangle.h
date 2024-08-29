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
			
			inline lv_draw_rect_dsc_t *get() {
				return &rectangle;
			}

			inline void clone(Rectangle *rec) {
				if(rec) {
					memcpy(&rec->rectangle, &rectangle, sizeof(lv_draw_rect_dsc_t));
				}
			}

			inline Rectangle *setRadius(lv_coord_t radius) {
				rectangle.radius = radius;
				return this;
			}
			inline lv_coord_t getRadius() {
				return rectangle.radius;
			}

			inline Rectangle *setBlendMode(lv_blend_mode_t blend_mode) {
				rectangle.blend_mode = blend_mode;
				return this;
			}
			inline lv_blend_mode_t getBlendMode() {
				return rectangle.blend_mode;
			}

			/*Background*/
			inline Rectangle *setOpacity(lv_opa_t bg_opa) {
				rectangle.bg_opa = bg_opa;
				return this;
			}
			inline lv_opa_t getOpacity() {
				return rectangle.bg_opa;
			}

			/**< First element of a gradient is a color, so it maps well here*/
			inline Rectangle *setColor(lv_color_t bg_color) {
				rectangle.bg_color = bg_color;
				return this;
			}
			inline lv_color_t getColor() {
				return rectangle.bg_color;
			}

			inline Rectangle *setGradientDirection(lv_grad_dir_t bg_grad_dir) {
				rectangle.bg_grad.dir = bg_grad_dir;
				return this;
			}
			inline lv_grad_dir_t getGradientDirection() {
				return rectangle.bg_grad.dir;
			}

			inline Rectangle *setGradientStopsCount(uint8_t stops_count) {
				rectangle.bg_grad.stops_count = stops_count;
				return this;
			}
			inline uint8_t getGradientStopsCount() {
				return rectangle.bg_grad.stops_count;
			}

			inline Rectangle *setGradientStopsColor(uint8_t idx, lv_color_t color) {
				rectangle.bg_grad.stops[idx].color = color;
				return this;
			}
			inline lv_color_t getGradientStopsColor(uint8_t idx) {
				return rectangle.bg_grad.stops[idx].color;
			}

			inline Rectangle *setGradientStopsFraction(uint8_t idx, uint8_t fraction) {
				rectangle.bg_grad.stops[idx].frac = fraction;
				return this;
			}
			inline uint8_t getGradientStopsFraction(uint8_t idx) {
				return rectangle.bg_grad.stops[idx].frac;
			}

			inline Rectangle *setGradientDither(lv_dither_mode_t dither) {
				rectangle.bg_grad.dither = dither;
				return this;
			}
			inline lv_dither_mode_t getGradientDither() {
				return rectangle.bg_grad.dither;
			}

			/*Background img*/
			inline Rectangle *setImageSource(const void * bg_img_src) {
				rectangle.bg_img_src = bg_img_src;
				return this;
			}
			inline const void * getImageSource() {
				return rectangle.bg_img_src;
			}

			inline Rectangle *setImageSymbolFont(const void * bg_img_symbol_font) {
				rectangle.bg_img_symbol_font = bg_img_symbol_font;
				return this;
			}
			inline const void * getImageSymbolFont() {
				return rectangle.bg_img_symbol_font;
			}

			inline Rectangle *setImageReColor(lv_color_t bg_img_recolor) {
				rectangle.bg_img_recolor = bg_img_recolor;
				return this;
			}
			inline lv_color_t getImageReColor() {
				return rectangle.bg_img_recolor;
			}

			inline Rectangle *setImageOpacity(lv_opa_t bg_img_opa) {
				rectangle.bg_img_opa = bg_img_opa;
				return this;
			}
			inline lv_opa_t getImageOpacity() {
				return rectangle.bg_img_opa;
			}

			inline Rectangle *setImageReColorOpacity(lv_opa_t bg_img_recolor_opa) {
				rectangle.bg_img_recolor_opa = bg_img_recolor_opa;
				return this;
			}
			inline lv_opa_t getImageReColorOpacity() {
				return rectangle.bg_img_recolor_opa;
			}

			inline Rectangle *setImageTiled(uint8_t bg_img_tiled) {
				rectangle.bg_img_tiled = bg_img_tiled;
				return this;
			}
			inline uint8_t getImageTiled() {
				return rectangle.bg_img_tiled;
			}

			/*Border*/
			inline Rectangle *setBorderColor(lv_color_t border_color) {
				rectangle.border_color = border_color;
				return this;
			}
			inline lv_color_t getBorderColor() {
				return rectangle.border_color;
			}

			inline Rectangle *setBorderWidth(lv_coord_t border_width) {
				rectangle.border_width = border_width;
				return this;
			}
			inline lv_coord_t getBorderWidth() {
				return rectangle.border_width;
			}

			inline Rectangle *setBorderOpacity(lv_opa_t border_opa) {
				rectangle.border_opa = border_opa;
				return this;
			}
			inline lv_opa_t getBorderOpacity() {
				return rectangle.border_opa;
			}
			inline Rectangle *setBorderOpacityPercent(uint8_t border_opa) {
				rectangle.border_opa = map(border_opa, 0, 100, 0, 255);
				return this;
			}
			inline lv_opa_t getBorderOpacityPercent() {
				return map(rectangle.border_opa, 0, 255, 0, 100);
			}

			/*There is a border it will be drawn later.*/
			inline Rectangle *setBorderPost(uint8_t border_post) {
				rectangle.border_post = border_post;
				return this;
			}
			inline uint8_t getBorderPost() {
				return rectangle.border_post;
			}

			inline Rectangle *setBorderSide(lv_border_side_t border_side) {
				rectangle.border_side = border_side;
				return this;
			}
			inline lv_border_side_t getBorderSide() {
				return rectangle.border_side;
			}

			/*Outline*/
			inline Rectangle *setOutlineColor(lv_color_t outline_color) {
				rectangle.outline_color = outline_color;
				return this;
			}
			inline lv_color_t getOutlineColor() {
				return rectangle.outline_color;
			}

			inline Rectangle *setOutlineWidth(lv_coord_t outline_width) {
				rectangle.outline_width = outline_width;
				return this;
			}
			inline lv_coord_t getOutlineWidth() {
				return rectangle.outline_width;
			}

			inline Rectangle *setOutlinePad(lv_coord_t outline_pad) {
				rectangle.outline_pad = outline_pad;
				return this;
			}
			inline lv_coord_t getOutlinePad() {
				return rectangle.outline_pad;
			}

			inline Rectangle *setOutlineOpacity(lv_opa_t outline_opa) {
				rectangle.outline_opa = outline_opa;
				return this;
			}
			inline lv_opa_t getOutlineOpacity() {
				return rectangle.outline_opa;
			}

			/*Shadow*/
			inline Rectangle *setShadowColor(lv_color_t shadow_color) {
				rectangle.shadow_color = shadow_color;
				return this;
			}
			inline lv_color_t getShadowColor() {
				return rectangle.shadow_color;
			}

			inline Rectangle *setShadowWidth(lv_coord_t shadow_width) {
				rectangle.shadow_width = shadow_width;
				return this;
			}
			inline lv_coord_t getShadowWidth() {
				return rectangle.shadow_width;
			}

			inline Rectangle *setShadowOffsetX(lv_coord_t shadow_ofs_x) {
				rectangle.shadow_ofs_x = shadow_ofs_x;
				return this;
			}
			inline lv_coord_t getShadowOffsetX() {
				return rectangle.shadow_ofs_x;
			}

			inline Rectangle *setShadowOffsetY(lv_coord_t shadow_ofs_y) {
				rectangle.shadow_ofs_y = shadow_ofs_y;
				return this;
			}
			inline lv_coord_t getShadowOffsetY() {
				return rectangle.shadow_ofs_y;
			}

			inline Rectangle *setShadowSpread(lv_coord_t shadow_spread) {
				rectangle.shadow_spread = shadow_spread;
				return this;
			}
			inline lv_coord_t getShadowSpread() {
				return rectangle.shadow_spread;
			}

			inline Rectangle *setShadowOpacity(lv_opa_t shadow_opa) {
				rectangle.shadow_opa = shadow_opa;
				return this;
			}
			inline lv_opa_t getShadowOpacity() {
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

			private:
				lv_draw_rect_dsc_t rectangle;
		};
	}
}

#endif
