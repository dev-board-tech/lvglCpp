/*
 * Arc.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_DRAW_SRC_ARC_H_
#define LVGLCPP_DRAW_SRC_ARC_H_

#include <lvgl.h>
#include <stdlib.h>

namespace lvgl {
	namespace draw {
		class Arc {
		public:
			Arc() {
				lv_draw_arc_dsc_init(&arc);
			}
			Arc(Arc *arc) {
				if(arc) {
					memcpy(&arc->arc, &arc, sizeof(lv_draw_arc_dsc_t));
				}
			}
			
			inline lv_draw_arc_dsc_t *Get() {
				return &arc;
			}

			inline void clone(Arc *arc) {
				if(arc) {
					memcpy(&arc->arc, &arc, sizeof(lv_draw_arc_dsc_t));
				}
			}

			inline Arc *SetColor(lv_color_t color) {
				arc.color = color;
				return this;
			}
			inline lv_color_t GetColor() {
				return arc.color;
			}

			inline Arc *SetWidth(lv_coord_t width) {
				arc.width = width;
				return this;
			}
			inline lv_coord_t GetWidth() {
				return arc.width;
			}

			inline Arc *SetStartAngle(uint16_t start_angle) {
				arc.start_angle = start_angle;
				return this;
			}
			inline uint16_t GetStartAngle() {
				return arc.start_angle;
			}

			inline Arc *SetEndAngle(uint16_t end_angle) {
				arc.end_angle = end_angle;
				return this;
			}
			inline uint16_t GetEndAngle() {
				return arc.end_angle;
			}

			inline Arc *SetImageSource(const void * img_src) {
				arc.img_src = img_src;
				return this;
			}
			inline const void * GetImageSource() {
				return arc.img_src;
			}

			inline Arc *SetOpacity(lv_opa_t opa) {
				arc.opa = opa;
				return this;
			}
			inline lv_opa_t GetOpacity() {
				return arc.opa;
			}

			inline Arc *SetBlendMode(lv_blend_mode_t blend_mode) {
				arc.blend_mode = blend_mode;
				return this;
			}
			inline lv_blend_mode_t GetBlendMode() {
				return arc.blend_mode;
			}

			inline Arc *SetRounded(uint8_t rounded) {
				arc.rounded = rounded;
				return this;
			}
			inline uint8_t GetRounded() {
				return arc.rounded;
			}

/**
 * Draw an arc. (Can draw pie too with great thickness.)
 * @param center_x      the x coordinate of the center of the arc
 * @param center_y      the y coordinate of the center of the arc
 * @param radius        the radius of the arc
 * @param mask          the arc will be drawn only in this mask
 * @param start_angle   the start angle of the arc (0 deg on the bottom, 90 deg on the right)
 * @param end_angle     the end angle of the arc
 * @param clip_area     the arc will be drawn only in this area
 * @param dsc           pointer to an initialized `lv_draw_line_dsc_t` variable
 */
			static inline void drawArc(struct _lv_draw_ctx_t * draw_ctx, const lv_draw_arc_dsc_t * dsc, const lv_point_t * center,
								 uint16_t radius,  uint16_t start_angle, uint16_t end_angle) {
				lv_draw_arc(draw_ctx, dsc, center, radius, start_angle, end_angle);
			}

			static inline void drawArc(struct _lv_draw_ctx_t * draw_ctx, lvgl::draw::Arc * dsc, const lv_point_t * center,
								 uint16_t radius,  uint16_t start_angle, uint16_t end_angle) {
				lv_draw_arc(draw_ctx, dsc->Get(), center, radius, start_angle, end_angle);
			}

/**
 * Get an area the should be invalidated when the arcs angle changed between start_angle and end_ange
 * @param x             the x coordinate of the center of the arc
 * @param y             the y coordinate of the center of the arc
 * @param radius        the radius of the arc
 * @param start_angle   the start angle of the arc (0 deg on the bottom, 90 deg on the right)
 * @param end_angle     the end angle of the arc
 * @param w             width of the arc
 * @param rounded       true: the arc is rounded
 * @param area          store the area to invalidate here
 */
			static inline void drawArcGetArea(lv_coord_t x, lv_coord_t y, uint16_t radius,  uint16_t start_angle, uint16_t end_angle,
				                  lv_coord_t w, bool rounded, lv_area_t * area) {
				lv_draw_arc_get_area(x, y, radius, start_angle, end_angle, w, rounded, area);
			}

		private:
			lv_draw_arc_dsc_t arc;
		};
	}
}

#endif
