/*
 * Arc.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_CHART_H_
#define LVGLCPP_SRC_CHART_H_

#include "Object.h"

namespace lvgl {
	namespace widget {
		class Chart : public Object {
		public:
			Chart(lv_obj_t *parent = NULL) {
				_obj = lv_chart_create(parent);
			}
			Chart(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_chart_create(parent->GetObj());
				} else {
					_obj = lv_chart_create(NULL);
				}
			}
			Chart(Object parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_chart_create(((Object)parent).GetObj());
				} else {
					_obj = lv_chart_create(NULL);
				}
			}
			Chart(lv_obj_t *parent, bool isNew) {
				_obj = parent;
			}
			Chart(Object *parent, bool isNew) {
				_obj = parent->GetObj();
			}
			Chart(Object parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
			}

			~Chart() {

			}

			/**
			 * Set the object pointer when used as a child.
			 */
			inline Chart *SetObj(lv_obj_t *obj) {
				_obj = obj;
				return this;
			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

			/*======================
			 * Add/remove functions
			 *=====================*/

			/*=====================
			 * Setter functions
			 *====================*/
			/**
			 * Set a new type for a chart
			 * @param obj       pointer to a chart object
			 * @param type      new type of the chart (from 'lv_chart_type_t' enum)
			 */
			Chart *SetType(lv_chart_type_t type) {
				lv_chart_set_type(_obj, type);
				return this;
			}
			/**
			 * Set the number of points on a data line on a chart
			 * @param obj       pointer to a chart object
			 * @param cnt       new number of points on the data lines
			 */
			Chart *SetPointCount(uint16_t cnt) {
				lv_chart_set_point_count(_obj, cnt);
				return this;
			}

			/**
			 * Set the minimal and maximal y values on an axis
			 * @param obj       pointer to a chart object
			 * @param axis      `LV_CHART_AXIS_PRIMARY_Y` or `LV_CHART_AXIS_SECONDARY_Y`
			 * @param min       minimum value of the y axis
			 * @param max       maximum value of the y axis
			 */
			Chart *SetRange(lv_chart_axis_t axis, lv_coord_t min, lv_coord_t max) {
				lv_chart_set_range(_obj, axis, min, max);
				return this;
			}

			/**
			 * Set update mode of the chart object. Affects
			 * @param obj       pointer to a chart object
			 * @param mode      the update mode
			 */
			Chart *SetUpdateMode(lv_chart_update_mode_t update_mode) {
				lv_chart_set_update_mode(_obj, update_mode);
				return this;
			}

			/**
			 * Set the number of horizontal and vertical division lines
			 * @param obj       pointer to a chart object
			 * @param hdiv      number of horizontal division lines
			 * @param vdiv      number of vertical division lines
			 */
			Chart *SetDivLineCount(uint8_t hdiv, uint8_t vdiv) {
				lv_chart_set_div_line_count(_obj, hdiv, vdiv);
				return this;
			}

			/**
			 * Zoom into the chart in X direction
			 * @param obj       pointer to a chart object
			 * @param zoom_x    zoom in x direction. LV_ZOOM_NONE or 256 for no zoom, 512 double zoom
			 */
			Chart *SetZoomX(uint16_t zoom_x) {
				lv_chart_set_zoom_x(_obj, zoom_x);
				return this;
			}

			/**
			 * Zoom into the chart in Y direction
			 * @param obj       pointer to a chart object
			 * @param zoom_y    zoom in y direction. LV_ZOOM_NONE or 256 for no zoom, 512 double zoom
			 */
			Chart *SetZoomY(uint16_t zoom_y) {
				lv_chart_set_zoom_y(_obj, zoom_y);
				return this;
			}

			/**
			 * Get X zoom of a chart
			 * @param obj       pointer to a chart object
			 * @return          the X zoom value
			 */
			uint16_t GetZoomX() {
				return lv_chart_get_zoom_x(_obj);
			}

			/**
			 * Get Y zoom of a chart
			 * @param obj       pointer to a chart object
			 * @return          the Y zoom value
			 */
			uint16_t GetZoomY() {
				return lv_chart_get_zoom_y(_obj);
			}

			/**
			 * Set the number of tick lines on an axis
			 * @param obj           pointer to a chart object
			 * @param axis          an axis which ticks count should be set
			 * @param major_len     length of major ticks
			 * @param minor_len     length of minor ticks
			 * @param major_cnt     number of major ticks on the axis
			 * @param minor_cnt     number of minor ticks between two major ticks
			 * @param label_en      true: enable label drawing on major ticks
			 * @param draw_size     extra size required to draw the tick and labels
			 *                      (start with 20 px and increase if the ticks/labels are clipped)
			 */
			Chart *SetAxisTick(lv_chart_axis_t axis, lv_coord_t major_len, lv_coord_t minor_len,
						                lv_coord_t major_cnt, lv_coord_t minor_cnt, bool label_en, lv_coord_t draw_size) {
				lv_chart_set_axis_tick(_obj, axis, major_len, minor_len, major_cnt, minor_cnt, label_en, draw_size);
				return this;
			}

			/**
			 * Get the type of a chart
			 * @param obj       pointer to chart object
			 * @return          type of the chart (from 'lv_chart_t' enum)
			 */
			lv_chart_type_t GetType() {
				return lv_chart_get_type(_obj);
			}

			/**
			 * Get the data point number per data line on chart
			 * @param chart     pointer to chart object
			 * @return          point number on each data line
			 */
			uint16_t GetPointCount() {
				return lv_chart_get_point_count(_obj);
			}

			/**
			 * Get the current index of the x-axis start point in the data array
			 * @param chart     pointer to a chart object
			 * @param ser       pointer to a data series on 'chart'
			 * @return          the index of the current x start point in the data array
			 */
			uint16_t GetXStartPoint(lv_chart_series_t * ser) {
				return lv_chart_get_x_start_point(_obj, ser);
			}

			/**
			 * Get the position of a point to the chart.
			 * @param chart     pointer to a chart object
			 * @param ser       pointer to series
			 * @param id        the index.
			 * @param p_out     store the result position here
			 */
			Chart *GetPintPosById(lv_chart_series_t * ser, uint16_t id, lv_point_t * p_out) {
				lv_chart_get_point_pos_by_id(_obj, ser, id, p_out);
				return this;
			}

			/**
			 * Refresh a chart if its data line has changed
			 * @param   chart pointer to chart object
			 */
			Chart *Refresh() {
				lv_chart_refresh(_obj);
				return this;
			}

			/*======================
			 * Series
			 *=====================*/

			/**
			 * Allocate and add a data series to the chart
			 * @param obj       pointer to a chart object
			 * @param color     color of the data series
			 * @param axis      the y axis to which the series should be attached (::LV_CHART_AXIS_PRIMARY_Y or ::LV_CHART_AXIS_SECONDARY_Y)
			 * @return          pointer to the allocated data series
			 */
			lv_chart_series_t * AddSeries(lv_color_t color, lv_chart_axis_t axis) {
				return lv_chart_add_series(_obj, color, axis);
			}

			/**
			 * Deallocate and remove a data series from a chart
			 * @param chart     pointer to a chart object
			 * @param series    pointer to a data series on 'chart'
			 */
			Chart *RemoveSeries(lv_chart_series_t * series) {
				lv_chart_remove_series(_obj, series);
				return this;
			}

			/**
			 * Hide/Unhide a single series of a chart.
			 * @param obj       pointer to a chart object.
			 * @param series    pointer to a series object
			 * @param hide      true: hide the series
			 */
			static void HideSeries(lv_obj_t * chart, lv_chart_series_t * series, bool hide) {
				lv_chart_hide_series(chart, series, hide);
			}
			Chart *HideSeries(lv_chart_series_t * series, bool hide) {
				lv_chart_hide_series(_obj, series, hide);
				return this;
			}

			/**
			 * Change the color of a series
			 * @param obj       pointer to a chart object.
			 * @param series    pointer to a series object
			 * @param color     the new color of the series
			 */
			static void SetSeriesColor(lv_obj_t * chart, lv_chart_series_t * series, lv_color_t color) {
				lv_chart_set_series_color(chart, series, color);
			}
			Chart *SetSeriesColor(lv_chart_series_t * series, lv_color_t color) {
				lv_chart_set_series_color(_obj, series, color);
				return this;
			}

			/**
			 * Set the index of the x-axis start point in the data array.
			 * This point will be considers the first (left) point and the other points will be drawn after it.
			 * @param obj       pointer to a chart object
			 * @param ser       pointer to a data series on 'chart'
			 * @param id        the index of the x point in the data array
			 */
			Chart *SetXStartPoint(lv_chart_series_t * ser, uint16_t id) {
				lv_chart_set_x_start_point(_obj, ser, id);
				return this;
			}

			/**
			 * Get the next series.
			 * @param chart     pointer to a chart
			 * @param ser      the previous series or NULL to get the first
			 * @return          the next series or NULL if there is no more.
			 */
			static lv_chart_series_t * GetSeriesNext(const lv_obj_t * chart, const lv_chart_series_t * ser) {
				return lv_chart_get_series_next(chart, ser);
			}
			lv_chart_series_t * GetSeriesNext(const lv_chart_series_t * ser) {
				return lv_chart_get_series_next(_obj, ser);
			}

			/*=====================
			 * Cursor
			 *====================*/

			/**
			 * Add a cursor with a given color
			 * @param obj       pointer to chart object
			 * @param color     color of the cursor
			 * @param dir       direction of the cursor. `LV_DIR_RIGHT/LEFT/TOP/DOWN/HOR/VER/ALL`. OR-ed values are possible
			 * @return          pointer to the created cursor
			 */
			lv_chart_cursor_t  * AddCursor(lv_color_t color, lv_dir_t dir) {
				return lv_chart_add_cursor(_obj, color, dir);
			}

			/**
			 * Set the coordinate of the cursor with respect to the paddings
			 * @param obj       pointer to a chart object
			 * @param cursor    pointer to the cursor
			 * @param pos       the new coordinate of cursor relative to the chart
			 */
			static void SetCursorPos(lv_obj_t * chart, lv_chart_cursor_t * cursor, lv_point_t * pos) {
				lv_chart_set_cursor_pos(chart, cursor, pos);
			}
			Chart *SetCursorPos(lv_chart_cursor_t * cursor, lv_point_t * pos) {
				lv_chart_set_cursor_pos(_obj, cursor, pos);
				return this;
			}

			/**
			 * Stick the cursor to a point
			 * @param obj       pointer to a chart object
			 * @param cursor    pointer to the cursor
			 * @param ser       pointer to a series
			 * @param point_id  the point's index or `LV_CHART_POINT_NONE` to not assign to any points.
			 */
			static void SetCursorPoint(lv_obj_t * chart, lv_chart_cursor_t * cursor, lv_chart_series_t * ser, uint16_t point_id) {
				lv_chart_set_cursor_point(chart, cursor, ser, point_id);
			}
			Chart *SetCursorPoint(lv_chart_cursor_t * cursor, lv_chart_series_t * ser, uint16_t point_id) {
				lv_chart_set_cursor_point(_obj, cursor, ser, point_id);
				return this;
			}

			/**
			 * Get the coordinate of the cursor with respect to the paddings
			 * @param obj       pointer to a chart object
			 * @param cursor    pointer to cursor
			 * @return          coordinate of the cursor as lv_point_t
			 */
			static lv_point_t GetCursorPoint(lv_obj_t * chart, lv_chart_cursor_t * cursor) {
				return lv_chart_get_cursor_point(chart, cursor);
			}
			lv_point_t GetCursorPoint(lv_chart_cursor_t * cursor) {
				return lv_chart_get_cursor_point(_obj, cursor);
			}

			/*=====================
			 * Set/Get value(s)
			 *====================*/

			/**
			 * Initialize all data points of a series with a value
			 * @param obj       pointer to chart object
			 * @param ser       pointer to a data series on 'chart'
			 * @param value     the new value for all points. `LV_CHART_POINT_NONE` can be used to hide the points.
			 */
			Chart *SetAllValues(lv_chart_series_t * ser, lv_coord_t value) {
				lv_chart_set_all_value(_obj, ser, value);
				return this;
			}

			/**
			 * Set the next point's Y value according to the update mode policy.
			 * @param obj       pointer to chart object
			 * @param ser       pointer to a data series on 'chart'
			 * @param value     the new value of the next data
			 */
			Chart *SetNextValue(lv_chart_series_t * ser, lv_coord_t value) {
				lv_chart_set_next_value(_obj, ser, value);
				return this;
			}

			/**
			 * Set the next point's X and Y value according to the update mode policy.
			 * @param obj       pointer to chart object
			 * @param ser       pointer to a data series on 'chart'
			 * @param x_value   the new X value of the next data
			 * @param y_value   the new Y value of the next data
			 */
			Chart *SetNextValue(lv_chart_series_t * ser, lv_coord_t x_value, lv_coord_t y_value) {
				lv_chart_set_next_value2(_obj, ser, x_value, y_value);
				return this;
			}

			/**
			 * Set an individual point's y value of a chart's series directly based on its index
			 * @param obj     pointer to a chart object
			 * @param ser     pointer to a data series on 'chart'
			 * @param id      the index of the x point in the array
			 * @param value   value to assign to array point
			 */
			Chart *SetValueById(lv_chart_series_t * ser, uint16_t id, lv_coord_t value) {
				lv_chart_set_value_by_id(_obj, ser, id, value);
				return this;
			}

			/**
			 * Set an individual point's x and y value of a chart's series directly based on its index
			 * Can be used only with `LV_CHART_TYPE_SCATTER`.
			 * @param obj       pointer to chart object
			 * @param ser       pointer to a data series on 'chart'
			 * @param id        the index of the x point in the array
			 * @param x_value   the new X value of the next data
			 * @param y_value   the new Y value of the next data
			 */
			Chart *SetValueById(lv_chart_series_t * ser, uint16_t id, lv_coord_t x_value, lv_coord_t y_value) {
				lv_chart_set_value_by_id2(_obj, ser, id, x_value, y_value);
				return this;
			}

			/**
			 * Set an external array for the y data points to use for the chart
			 * NOTE: It is the users responsibility to make sure the `point_cnt` matches the external array size.
			 * @param obj       pointer to a chart object
			 * @param ser       pointer to a data series on 'chart'
			 * @param array     external array of points for chart
			 */
			Chart *SetExtYArray(lv_chart_series_t * ser, lv_coord_t array[]) {
				lv_chart_set_ext_y_array(_obj, ser, array);
				return this;
			}

			/**
			 * Set an external array for the x data points to use for the chart
			 * NOTE: It is the users responsibility to make sure the `point_cnt` matches the external array size.
			 * @param obj       pointer to a chart object
			 * @param ser       pointer to a data series on 'chart'
			 * @param array     external array of points for chart
			 */
			Chart *SetExtXArray(lv_chart_series_t * ser, lv_coord_t array[]) {
				lv_chart_set_ext_x_array(_obj, ser, array);
				return this;
			}

			/**
			 * Get the array of y values of a series
			 * @param obj   pointer to a chart object
			 * @param ser   pointer to a data series on 'chart'
			 * @return      the array of values with 'point_count' elements
			 */
			lv_coord_t * GetYArray(lv_chart_series_t * ser) {
				return lv_chart_get_y_array(_obj, ser);
			}

			/**
			 * Get the array of x values of a series
			 * @param obj   pointer to a chart object
			 * @param ser   pointer to a data series on 'chart'
			 * @return      the array of values with 'point_count' elements
			 */
			lv_coord_t * GetXArray(lv_chart_series_t * ser) {
				return lv_chart_get_x_array(_obj, ser);
			}

			/**
			 * Get the index of the currently pressed point. It's the same for every series.
			 * @param obj       pointer to a chart object
			 * @return          the index of the point [0 .. point count] or LV_CHART_POINT_ID_NONE if no point is being pressed
			 */
			uint32_t GetPressedPoint() {
				return lv_chart_get_pressed_point(_obj);
			}
			
			typedef lv_chart_series_t Series;
		};
	}
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_CHART_H_ */
