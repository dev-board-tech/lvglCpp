/*
 * Line.h
 *
 *      Author: Iulian Gheorghiu
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
			
			inline lv_draw_line_dsc_t *Get() {
				return &line;
			}

			inline void clone(Line *line) {
				if(line) {
					memcpy(&line->line, &line, sizeof(lv_draw_line_dsc_t));
				}
			}

			inline Line *SetColor(lv_color_t color) {
				line.color = color;
				return this;
			}
			inline lv_color_t GetColor() {
				return line.color;
			}

			inline Line *SetWidth(lv_coord_t width) {
				line.width = width;
				return this;
			}
			inline lv_coord_t GetWidth() {
				return line.width;
			}

			inline Line *SetDashWidth(lv_coord_t dash_width) {
				line.dash_width = dash_width;
				return this;
			}
			inline lv_coord_t GetDashWidth() {
				return line.dash_width;
			}

			inline Line *SetDashGap(lv_coord_t dash_gap) {
				line.dash_gap = dash_gap;
				return this;
			}
			inline lv_coord_t GetDashGap() {
				return line.dash_gap;
			}

			inline Line *SetOpacity(lv_opa_t opa) {
				line.opa = opa;
				return this;
			}
			inline lv_opa_t GetOpacity() {
				return line.opa;
			}

			inline Line *SetBlendMode(lv_blend_mode_t blend_mode) {
				line.blend_mode = blend_mode;
				return this;
			}
			inline lv_blend_mode_t GetBlendMode() {
				return line.blend_mode;
			}

			inline Line *SetRoundStart(uint8_t round_start) {
				line.round_start = round_start;
				return this;
			}
			inline uint8_t GetRoundStart() {
				return line.round_start;
			}

			inline Line *SetRoundEnd(uint8_t round_end) {
				line.round_end = round_end;
				return this;
			}
			inline uint8_t GetRoundEnd() {
				return line.round_end;
			}
			/*Do not bother with perpendicular line ending if it's not visible for any reason*/
			inline Line *SetRawEnd(uint8_t raw_end) {
				line.raw_end = raw_end;
				return this;
			}
			inline uint8_t GetRawEnd() {
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

			static inline void drawLine(struct _lv_draw_ctx_t * draw_ctx, lvgl::draw::Line * dsc,
                                              const lv_point_t * point1, const lv_point_t * point2) {
				lv_draw_line(draw_ctx, dsc->Get(), point1, point2);
			}

			private:
				lv_draw_line_dsc_t line;
		};
	}
}

#endif
