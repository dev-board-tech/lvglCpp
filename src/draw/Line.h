/*
 * line.h
 *
 *  Created on: Nov 27, 2023
 *      Author: morgoth
 */

#ifndef LVGLCPP_DRAW_SRC_LINE_H_
#define LVGLCPP_DRAW_SRC_LINE_H_

#include <lvgl.h>
#include <stdlib.h>

namespace lvgl {
	namespace draw {
		class Line {
		public:
			Line() {
				lv_draw_line_dsc_init(&line);
			}
			Line(Line *line) {
				if(line) {
					memcpy(&line->line, &line, sizeof(lv_draw_line_dsc_t));
				}
			}
			
			inline lv_draw_line_dsc_t *get() {
				return &line;
			}

			inline void clone(Line *line) {
				if(line) {
					memcpy(&line->line, &line, sizeof(lv_draw_line_dsc_t));
				}
			}

			inline Line *setColor(lv_color_t color) {
				line.color = color;
				return this;
			}
			inline lv_color_t getColor() {
				return line.color;
			}

			inline Line *setWidth(lv_coord_t width) {
				line.width = width;
				return this;
			}
			inline lv_coord_t getWidth() {
				return line.width;
			}

			inline Line *setDashWidth(lv_coord_t dash_width) {
				line.dash_width = dash_width;
				return this;
			}
			inline lv_coord_t getDashWidth() {
				return line.dash_width;
			}

			inline Line *setDashGap(lv_coord_t dash_gap) {
				line.dash_gap = dash_gap;
				return this;
			}
			inline lv_coord_t getDashGap() {
				return line.dash_gap;
			}

			inline Line *setOpacity(lv_opa_t opa) {
				line.opa = opa;
				return this;
			}
			inline lv_opa_t getOpacity() {
				return line.opa;
			}

			inline Line *setBlendMode(lv_blend_mode_t blend_mode) {
				line.blend_mode = blend_mode;
				return this;
			}
			inline lv_blend_mode_t getBlendMode() {
				return line.blend_mode;
			}

			inline Line *setRoundStart(uint8_t round_start) {
				line.round_start = round_start;
				return this;
			}
			inline uint8_t getRoundStart() {
				return line.round_start;
			}

			inline Line *setRoundEnd(uint8_t round_end) {
				line.round_end = round_end;
				return this;
			}
			inline uint8_t getRoundEnd() {
				return line.round_end;
			}
			/*Do not bother with perpendicular line ending if it's not visible for any reason*/
			inline Line *setRawEnd(uint8_t raw_end) {
				line.raw_end = raw_end;
				return this;
			}
			inline uint8_t getRawEnd() {
				return line.raw_end;
			}

/**
 * Draw a line
 * @param point1 first point of the line
 * @param point2 second point of the line
 * @param clip the line will be drawn only in this area
 * @param dsc pointer to an initialized `lv_draw_line_dsc_t` variable
 */
			static inline void drawLine(struct _lv_draw_ctx_t * draw_ctx, const lv_draw_line_dsc_t * dsc,
                                              const lv_point_t * point1, const lv_point_t * point2) {
				lv_draw_line(draw_ctx, dsc, point1, point2);
			}

			private:
				lv_draw_line_dsc_t line;
		};
	}
}

#endif
