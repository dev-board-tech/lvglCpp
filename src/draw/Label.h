/*
 * Label.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_DRAW_SRC_LABEL_H_
#define LVGLCPP_DRAW_SRC_LABEL_H_

#include <lvgl.h>
#include <stdlib.h>

namespace lvgl {
	namespace draw {
		class Label {
		public:
			Label() {
				lv_draw_label_dsc_init(&label);
			}
			Label(Label *label) {
				if(label) {
					memcpy(&label->label, &label, sizeof(lv_draw_label_dsc_t));
				}
			}
			
			inline lv_draw_label_dsc_t *Get() {
				return &label;
			}

			inline void clone(Label *label) {
				if(label) {
					memcpy(&label->label, &label, sizeof(lv_draw_label_dsc_t));
				}
			}

			inline Label *SetFont(const lv_font_t *font) {
				label.font = font;
				return this;
			}
			inline const lv_font_t *GetFont() {
				return label.font;
			}

			inline Label *SetSelectStart(uint32_t sel_start) {
				label.sel_start = sel_start;
				return this;
			}
			inline uint32_t GetSelectStart() {
				return label.sel_start;
			}

			inline Label *SetSelectEnd(uint32_t sel_end) {
				label.sel_end = sel_end;
				return this;
			}
			inline uint32_t GetSelectEnd() {
				return label.sel_end;
			}

			inline Label *SetColor(lv_color_t color) {
				label.color = color;
				return this;
			}
			inline lv_color_t GetColor() {
				return label.color;
			}

			inline Label *SetSelectColor(lv_color_t sel_color) {
				label.sel_color = sel_color;
				return this;
			}
			inline lv_color_t GetSelectColor() {
				return label.sel_color;
			}

			inline Label *SetBgColor(lv_color_t sel_bg_color) {
				label.sel_bg_color = sel_bg_color;
				return this;
			}
			inline lv_color_t GetBgColor() {
				return label.sel_bg_color;
			}

			inline Label *SetLineSpace(lv_coord_t line_space) {
				label.line_space = line_space;
				return this;
			}
			inline lv_coord_t GetLineSpace() {
				return label.line_space;
			}

			inline Label *SetLetterSpace(lv_coord_t letter_space) {
				label.letter_space = letter_space;
				return this;
			}
			inline lv_coord_t GetLetterSpace() {
				return label.letter_space;
			}

			inline Label *SetOffsetX(lv_coord_t ofs_x) {
				label.ofs_x = ofs_x;
				return this;
			}
			inline lv_coord_t GetOffsetX() {
				return label.ofs_x;
			}

			inline Label *SetOffsetY(lv_coord_t ofs_y) {
				label.ofs_y = ofs_y;
				return this;
			}
			inline lv_coord_t GetOffsetY() {
				return label.ofs_y;
			}

			inline Label *SetOpacity(lv_opa_t opa) {
				label.opa = opa;
				return this;
			}
			inline lv_opa_t GetOpacity() {
				return label.opa;
			}

			inline Label *SetBidiDirection(lv_base_dir_t bidi_dir) {
				label.bidi_dir = bidi_dir;
				return this;
			}
			inline lv_base_dir_t GetBidiDirection() {
				return label.bidi_dir;
			}

			inline Label *SetAlign(lv_text_align_t align) {
				label.align = align;
				return this;
			}
			inline lv_text_align_t GetAlign() {
				return label.align;
			}

			inline Label *SetFlag(lv_text_flag_t flag) {
				label.flag = flag;
				return this;
			}
			inline lv_text_flag_t GetFlag() {
				return label.flag;
			}

			inline Label *SetDecoration(lv_text_decor_t decor) {
				label.decor = decor;
				return this;
			}
			inline lv_text_decor_t GetDecoration() {
				return label.decor;
			}

			inline Label *SetBlendMode(lv_blend_mode_t blend_mode) {
				label.blend_mode = blend_mode;
				return this;
			}
			inline lv_blend_mode_t GetBlendMode() {
				return label.blend_mode;
			}

/**
 * Write a text
 * @param coords coordinates of the label
 * @param mask the label will be drawn only in this area
 * @param dsc pointer to draw descriptor
 * @param txt `\0` terminated text to write
 * @param hint pointer to a `lv_draw_label_hint_t` variable.
 * It is managed by the draw to speed up the drawing of very long texts (thousands of lines).
 */
 			static inline void drawLabel(struct _lv_draw_ctx_t * draw_ctx, const lv_draw_label_dsc_t * dsc,
                                               const lv_area_t * coords, const char * txt, lv_draw_label_hint_t * hint) {
				lv_draw_label(draw_ctx, dsc, coords, txt, hint);
			}

 			static inline void drawLabel(struct _lv_draw_ctx_t * draw_ctx, lvgl::draw::Label *dsc,
                                               const lv_area_t * coords, const char * txt, lv_draw_label_hint_t * hint) {
				lv_draw_label(draw_ctx, dsc->Get(), coords, txt, hint);
			}

			static inline void drawLetter(struct _lv_draw_ctx_t * draw_ctx, const lv_draw_label_dsc_t * dsc,  const lv_point_t * pos_p, uint32_t letter) {
				lv_draw_letter(draw_ctx, dsc, pos_p, letter);
			}

			static inline void drawLetter(struct _lv_draw_ctx_t * draw_ctx, lvgl::draw::Label *dsc,  const lv_point_t * pos_p, uint32_t letter) {
				lv_draw_letter(draw_ctx, dsc->Get(), pos_p, letter);
			}
		private:
			lv_draw_label_dsc_t label;
		};
	}
}

#endif
