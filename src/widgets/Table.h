/*
 * Table.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_TABLE_H_
#define LVGLCPP_SRC_TABLE_H_

#include <stdio.h>
#include <stdarg.h>

#include "Object.h"

namespace lvgl {
	namespace widget {
		class Table : public Object {
		public:
			Table(lv_obj_t *parent) {
				_obj = lv_table_create(parent);
				_child = NULL;
				_childs = NULL;
			}
			Table(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_table_create(parent->GetObj());
				} else {
					_obj = lv_table_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			Table(Object &parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_table_create(((Object)parent).GetObj());
				} else {
					_obj = lv_table_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			Table(lv_obj_t *parent, bool isNew) {
				_obj = parent;
				_childs = NULL;
				_child = NULL;
			}
			Table(Object *parent, bool isNew) {
				_obj = parent->GetObj();
				_childs = parent->GetChilds();
				_child = NULL;
			}
			Table(Object &parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
				_childs = ((Object)parent).GetChilds();
				_child = NULL;
			}

			~Table() {

			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

			/*=====================
			 * Setter functions
			 *====================*/

			/**
			 * Set the value of a cell.
			 * @param obj           pointer to a Table object
			 * @param row           id of the row [0 .. row_cnt -1]
			 * @param col           id of the column [0 .. col_cnt -1]
			 * @param txt           text to display in the cell. It will be copied and saved so this variable is not required after this function call.
			 * @note                New roes/columns are added automatically if required
			 */
			Table *SetCellValue(uint16_t row, uint16_t col, const char * fmt, ...) {
				va_list args;
				va_start(args, fmt);
				int size = vsnprintf(NULL, 0, fmt, args);
				va_end(args);
				char buffer[size + 1];
				va_start(args, fmt);
				vsnprintf(buffer, size + 1, fmt, args);
				va_end(args);
				lv_table_set_cell_value(_obj, row, col, buffer);
				return this;
			}

			/**
			 * Set the number of rows
			 * @param obj           table pointer to a Table object
			 * @param row_cnt       number of rows
			 */
			inline Table *SetRowCount(uint16_t row_cnt) {
				lv_table_set_row_cnt(_obj, row_cnt);
				return this;
			}

			/**
			 * Set the number of columns
			 * @param obj       table pointer to a Table object
			 * @param col_cnt   number of columns.
			 */
			inline Table *SetColCount(uint16_t col_cnt) {
				lv_table_set_col_cnt(_obj, col_cnt);
				return this;
			}

			/**
			 * Set the width of a column
			 * @param obj       table pointer to a Table object
			 * @param col_id    id of the column [0 .. LV_TABLE_COL_MAX -1]
			 * @param w         width of the column
			 */
			inline Table *SetColWidth(uint16_t col_id, lv_coord_t w) {
				lv_table_set_col_width(_obj, col_id, w);
				return this;
			}

			/**
			 * Add control bits to the cell.
			 * @param obj       pointer to a Table object
			 * @param row       id of the row [0 .. row_cnt -1]
			 * @param col       id of the column [0 .. col_cnt -1]
			 * @param ctrl      OR-ed values from ::lv_table_cell_ctrl_t
			 */
			inline Table *AddCellCtrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl) {
				lv_table_add_cell_ctrl(_obj, row, col, ctrl);
				return this;
			}


			/**
			 * Clear control bits of the cell.
			 * @param obj       pointer to a Table object
			 * @param row       id of the row [0 .. row_cnt -1]
			 * @param col       id of the column [0 .. col_cnt -1]
			 * @param ctrl      OR-ed values from ::lv_table_cell_ctrl_t
			 */
			inline Table *ClearCellCtrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl) {
				lv_table_clear_cell_ctrl(_obj, row, col, ctrl);
				return this;
			}

			/*=====================
			 * Getter functions
			 *====================*/

			/**
			 * Get the value of a cell.
			 * @param obj       pointer to a Table object
			 * @param row       id of the row [0 .. row_cnt -1]
			 * @param col       id of the column [0 .. col_cnt -1]
			 * @return          text in the cell
			 */
			inline const char *GetCellValue(uint16_t row, uint16_t col) {
				return lv_table_get_cell_value(_obj, row, col);
			}

			/**
			 * Get the number of rows.
			 * @param obj       table pointer to a Table object
			 * @return          number of rows.
			 */
			inline uint16_t GetRowCount() {
				return lv_table_get_row_cnt(_obj);
			}

			/**
			 * Get the number of columns.
			 * @param obj       table pointer to a Table object
			 * @return          number of columns.
			 */
			inline uint16_t GetColCount() {
				return lv_table_get_col_cnt(_obj);
			}

			/**
			 * Get the width of a column
			 * @param obj       table pointer to a Table object
			 * @param col       id of the column [0 .. LV_TABLE_COL_MAX -1]
			 * @return          width of the column
			 */
			inline lv_coord_t GetColWidth(uint16_t col) {
				return lv_table_get_col_width(_obj, col);
			}

			/**
			 * Get whether a cell has the control bits
			 * @param obj       pointer to a Table object
			 * @param row       id of the row [0 .. row_cnt -1]
			 * @param col       id of the column [0 .. col_cnt -1]
			 * @param ctrl      OR-ed values from ::lv_table_cell_ctrl_t
			 * @return          true: all control bits are set; false: not all control bits are set
			 */
			inline bool HasCellCtrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl) {
				return lv_table_has_cell_ctrl(_obj, row, col, ctrl);
			}

			/**
			 * Get the selected cell (pressed and or focused)
			 * @param obj       pointer to a table object
			 * @param row       pointer to variable to store the selected row (LV_TABLE_CELL_NONE: if no cell selected)
			 * @param col       pointer to variable to store the selected column  (LV_TABLE_CELL_NONE: if no cell selected)
			 */
			inline Table *GetSelectedCell(uint16_t * row, uint16_t * col) {
				lv_table_get_selected_cell(_obj, row, col);
				return this;
			}
			
			inline Table *SecondRowGrewish(lv_obj_t *tableObj, uint8_t opa, uint8_t *colAlignTable, bool topHeader) {
				uint32_t *args = (uint32_t *)malloc(sizeof(uint32_t) * 3);
				args[0] = opa;
				args[1] = (uint32_t)colAlignTable;
				args[2] = topHeader;
				lv_obj_add_event_cb(tableObj, [](lv_event_t * e) {
					uint32_t *args = (uint32_t *)e->user_data;
					lv_obj_t * obj = lv_event_get_target(e);
					lv_obj_draw_part_dsc_t * dsc = (lv_obj_draw_part_dsc_t *)lv_event_get_param(e);
					/*If the cells are drawn...*/
					if(dsc->part == LV_PART_ITEMS) {
						uint32_t row = dsc->id /  lv_table_get_col_cnt(obj);
						uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);
						uint8_t *arr = (uint8_t *)args[1];
						dsc->label_dsc->align = arr[col];
						/*MAke every 2nd row grayish*/
						if((row != 0 && row % 2) == 0) {
							dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_GREY), dsc->rect_dsc->bg_color, (uint32_t)args[0]);
							dsc->rect_dsc->bg_opa = LV_OPA_COVER;
						}
						/*Make the texts in the first cell center aligned*/
						if(row == 0 && args[2]) {
							dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
							dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_BLUE), dsc->rect_dsc->bg_color, LV_OPA_20);
							dsc->rect_dsc->bg_opa = LV_OPA_COVER;
						}
					}
				}, LV_EVENT_DRAW_PART_BEGIN, (void *)args);
				return this;
			}
			inline Table *SecondRowGrewish(uint8_t opa, uint8_t *colAlignTable, bool topHeader) {
				return SecondRowGrewish(_obj, opa, colAlignTable, topHeader);
			}
		};
	} /* namespace widget */
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_TABLE_H_ */
