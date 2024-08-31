/*
 * Object.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVCPP_LVOBJ_H_
#define LVCPP_LVOBJ_H_

#include <lvgl.h>
#include <stdlib.h>
#include "Style.h"


namespace lvgl {
	namespace widget {
		class Object {
		protected:
			lv_obj_t *_obj;
			lv_obj_t *_child;
			lv_obj_t **_childs;
		public:

			/**
			 * Set the object pointer when used as a child.
			 */
			Object(lv_obj_t *obj = NULL) {
				_obj = lv_obj_create(obj);
			}

			/**
			 * Set the object pointer when used as a child.
			 */
			Object(Object *obj) {
				_obj = lv_obj_create(obj->GetObj());
			}

			/**
			 * Set the object pointer when used as a child.
			 */
			/*Object(const Object& obj) {
				_obj = lv_obj_create(obj.GetObj());
			}*/

			/**
			 * Set the object pointer when used as a child.
			 */
			inline Object *SetObj(lv_obj_t *obj) {
				_obj = obj;
				return this;
			}

			/**
			 * Set the object pointer when used as a child.
			 */
			inline Object *SetObj(Object *obj) {
				_obj = obj->GetObj();
				return this;
			}

			/**
			 * Set the object pointer when used as a child.
			 */
			inline Object *SetObj(Object obj) {
				_obj = obj.GetObj();
				return this;
			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

			void SetEnabled(bool enable) {
				if (enable) {
					lv_obj_clear_state(_obj, LV_STATE_DISABLED);
				}
				else {
					lv_obj_add_state(_obj, LV_STATE_DISABLED);
				}
			}

			inline bool GetEnabled() {
				return lv_obj_has_state(_obj, LV_STATE_DISABLED);
			}

			void SetChecked(bool checked) {
				if (checked) {
					lv_obj_add_state(_obj, LV_STATE_CHECKED);
				}
				else {
					lv_obj_clear_state(_obj, LV_STATE_CHECKED);
				}
			}

			inline bool GetChecked() {
				return lv_obj_has_state(_obj, LV_STATE_CHECKED);
			}

			void SetVisible(bool visible) {
				if (visible) {
					lv_obj_clear_flag(_obj, LV_OBJ_FLAG_HIDDEN);
				}
				else {
					lv_obj_add_flag(_obj, LV_OBJ_FLAG_HIDDEN);
				}
			}

			inline bool GetVisible() {
				return _obj->flags & LV_STATE_CHECKED ? false : true;
			}
			
			inline Object *AddFlag(lv_obj_flag_t f) {
				lv_obj_add_flag(_obj, f);
				return this;
			}

			inline Object *ClearFlag(lv_obj_flag_t f) {
				lv_obj_clear_flag(_obj, f);
				return this;
			}

			/**
			 * Set the position of an object relative to the set alignment.
			 * @param Object       pointer to an object
			 * @param x         new x coordinate
			 * @param y         new y coordinate
			 * @note            With default alignment it's the distance from the top left corner
			 * @note            E.g. LV_ALIGN_CENTER alignment it's the offset from the center of the parent
			 * @note            The position is interpreted on the content area of the parent
			 * @note            The values can be set in pixel or in percentage of parent size with `lv_pct(v)`
			 */
			inline Object *SetPos(lv_coord_t x, lv_coord_t y) {
				lv_obj_set_pos(_obj, x, y);
			return this;
			}

			/**
			 * Set the x coordinate of an object
			 * @param Object       pointer to an object
			 * @param x         new x coordinate
			 * @note            With default alignment it's the distance from the top left corner
			 * @note            E.g. LV_ALIGN_CENTER alignment it's the offset from the center of the parent
			 * @note            The position is interpreted on the content area of the parent
			 * @note            The values can be set in pixel or in percentage of parent size with `lv_pct(v)`
			 */

			inline Object *SetPosX(lv_coord_t x) {
				lv_obj_set_x(_obj, x);
			return this;
			}

			/**
			 * Set the y coordinate of an object
			 * @param Object       pointer to an object
			 * @param y         new y coordinate
			 * @note            With default alignment it's the distance from the top left corner
			 * @note            E.g. LV_ALIGN_CENTER alignment it's the offset from the center of the parent
			 * @note            The position is interpreted on the content area of the parent
			 * @note            The values can be set in pixel or in percentage of parent size with `lv_pct(v)`
			 */
			inline Object *SetPosY(lv_coord_t y) {
				lv_obj_set_y(_obj, y);
			return this;
			}

			/**
			 * Set the size of an object.
			 * @param Object       pointer to an object
			 * @param w         the new width
			 * @param h         the new height
			 * @note            possible values are:
			 *                  pixel               simple set the size accordingly
			 *                  LV_SIZE_CONTENT     set the size to involve all children in the given direction
			 *                  LV_SIZE_PCT(x)     to set size in percentage of the parent's content area size (the size without paddings).
			 *                                      x should be in [0..1000]% range
			 */
			inline Object *SetSize(lv_coord_t w, lv_coord_t h) {
				lv_obj_set_size(_obj, w, h);
			return this;
			}


			/**
			 * Recalculate the size of the object
			 * @param Object       pointer to an object
			 * @return          true: the size has been changed
			 */
			inline Object *SetRefrSize() {
				lv_obj_refr_size(_obj);
			return this;
			}


			/**
			 * Set the width of an object
			 * @param Object       pointer to an object
			 * @param w         the new width
			 * @note            possible values are:
			 *                  pixel               simple set the size accordingly
			 *                  LV_SIZE_CONTENT     set the size to involve all children in the given direction
			 *                  lv_pct(x)           to set size in percentage of the parent's content area size (the size without paddings).
			 *                                      x should be in [0..1000]% range
			 */
			inline Object *SetWidth(lv_coord_t w) {
				lv_obj_set_width(_obj, w);
			return this;
			}


			/**
			 * Set the height of an object
			 * @param Object       pointer to an object
			 * @param h         the new height
			 * @note            possible values are:
			 *                  pixel               simple set the size accordingly
			 *                  LV_SIZE_CONTENT     set the size to involve all children in the given direction
			 *                  lv_pct(x)           to set size in percentage of the parent's content area size (the size without paddings).
			 *                                      x should be in [0..1000]% range
			 */
			inline Object *SetHeight(lv_coord_t h) {
				lv_obj_set_height(_obj, h);
			return this;
			}


			/**
			 * Set the width reduced by the left and right padding and the border width.
			 * @param Object       pointer to an object
			 * @param w         the width without paddings in pixels
			 */
			inline Object *SetContentWidth(lv_coord_t w) {
				lv_obj_set_content_width(_obj, w);
			return this;
			}


			/**
			 * Set the height reduced by the top and bottom padding and the border width.
			 * @param Object       pointer to an object
			 * @param h         the height without paddings in pixels
			 */
			inline Object *SetContentHeight(lv_coord_t h) {
				lv_obj_set_content_height(_obj, h);
			return this;
			}


			/**
			 * Set a layout for an object
			 * @param Object       pointer to an object
			 * @param layout    pointer to a layout descriptor to set
			 */
			inline Object *SetLayout(uint32_t layout) {
				lv_obj_set_layout(_obj, layout);
				return this;
			}

			/**
			 * Test whether the and object is positioned by a layout or not
			 * @param Object       pointer to an object to test
			 * @return true:    positioned by a layout; false: not positioned by a layout
			 */
			inline bool IsLayoutPositioned() {
				return lv_obj_is_layout_positioned(_obj);
			}

			/**
			 * Mark the object for layout update.
			 * @param Object      pointer to an object whose children needs to be updated
			 */
			inline Object *MarkLayoutAsDirty() {
				lv_obj_mark_layout_as_dirty(_obj);
				return this;
			}

			/**
			 * Update the layout of an object.
			 * @param Object      pointer to an object whose children needs to be updated
			 */
			inline Object *UpdateLayout() {
				lv_obj_update_layout(_obj);
				return this;
			}

			/**
			 * Register a new layout
			 * @param cb        the layout update callback
			 * @param user_data custom data that will be passed to `cb`
			 * @return          the ID of the new layout
			 */
			inline uint32_t LayoutRegister(lv_layout_update_cb_t cb, void * user_data) {
				return lv_layout_register(cb, user_data);
			}

			/**
			 * Change the alignment of an object.
			 * @param Object       pointer to an object to align
			 * @param align     type of alignment (see 'lv_align_t' enum) `LV_ALIGN_OUT_...` can't be used.
			 */
			inline Object *SetAlign(lv_align_t align) {
				lv_obj_set_align(_obj,  align);
				return this;
			}

			/**
			 * Change the alignment of an object and set new coordinates.
			 * Equivalent to:
			 * lv_obj_set_align(Object, align);
			 * lv_obj_set_pos(Object, x_ofs, y_ofs);
			 * @param Object       pointer to an object to align
			 * @param align     type of alignment (see 'lv_align_t' enum) `LV_ALIGN_OUT_...` can't be used.
			 * @param x_ofs     x coordinate offset after alignment
			 * @param y_ofs     y coordinate offset after alignment
			 */
			inline Object *SetAlign(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) {
				lv_obj_align(_obj,  align,  x_ofs,  y_ofs);
				return this;
			}

			/**
			 * Align an object to an other object.
			 * @param Object       pointer to an object to align
			 * @param base      pointer to an other object (if NULL `Object`s parent is used). 'Object' will be aligned to it.
			 * @param align     type of alignment (see 'lv_align_t' enum)
			 * @param x_ofs     x coordinate offset after alignment
			 * @param y_ofs     y coordinate offset after alignment
			 * @note            if the position or size of `base` changes `Object` needs to be aligned manually again
			 */
			inline Object *SetAlignTo(const lv_obj_t * _base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) {
				lv_obj_align_to(_obj, _base, align, x_ofs, y_ofs);
				return this;
			}


			/**
			 * Align an object to the center on its parent.
			 * @param Object       pointer to an object to align
			 * @note            if the parent size changes `Object` needs to be aligned manually again
			 */
			inline void SetCenter() {
				lv_obj_center(_obj);
			}


			/**
			 * Copy the coordinates of an object to an area
			 * @param Object       pointer to an object
			 * @param coords    pointer to an area to store the coordinates
			 */
			inline Object *GetCoords(lv_area_t * coords) {
				lv_obj_get_coords(_obj, coords);
				return this;
			}

			/**
			 * Get the x coordinate of object.
			 * @param Object       pointer to an object
			 * @return          distance of `Object` from the left side of its parent plus the parent's left padding
			 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
			 *                  call `lv_obj_update_layout(Object)`.
			 * @note            Zero return value means the object is on the left padding of the parent, and not on the left edge.
			 * @note            Scrolling of the parent doesn't change the returned value.
			 * @note            The returned value is always the distance from the parent even if `Object` is positioned by a layout.
			 */
			inline lv_coord_t GetX() {
				return lv_obj_get_x(_obj);
			}

			/**
			 * Get the x2 coordinate of object.
			 * @param Object       pointer to an object
			 * @return          distance of `Object` from the right side of its parent plus the parent's right padding
			 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
			 *                  call `lv_obj_update_layout(Object)`.
			 * @note            Zero return value means the object is on the right padding of the parent, and not on the right edge.
			 * @note            Scrolling of the parent doesn't change the returned value.
			 * @note            The returned value is always the distance from the parent even if `Object` is positioned by a layout.
			 */
			inline lv_coord_t GetX2() {
				return lv_obj_get_x2(_obj);
			}

			/**
			 * Get the y coordinate of object.
			 * @param Object       pointer to an object
			 * @return          distance of `Object` from the top side of its parent plus the parent's top padding
			 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
			 *                  call `lv_obj_update_layout(Object)`.
			 * @note            Zero return value means the object is on the top padding of the parent, and not on the top edge.
			 * @note            Scrolling of the parent doesn't change the returned value.
			 * @note            The returned value is always the distance from the parent even if `Object` is positioned by a layout.
			 */
			inline lv_coord_t GetY() {
				return lv_obj_get_y(_obj);
			}

			/**
			 * Get the y2 coordinate of object.
			 * @param Object       pointer to an object
			 * @return          distance of `Object` from the bottom side of its parent plus the parent's bottom padding
			 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
			 *                  call `lv_obj_update_layout(Object)`.
			 * @note            Zero return value means the object is on the bottom padding of the parent, and not on the bottom edge.
			 * @note            Scrolling of the parent doesn't change the returned value.
			 * @note            The returned value is always the distance from the parent even if `Object` is positioned by a layout.
			 */
			inline lv_coord_t GetY2() {
				return lv_obj_get_y2(_obj);
			}

			/**
			 * Get the actually set x coordinate of object, i.e. the offset form the set alignment
			 * @param Object       pointer to an object
			 * @return          the set x coordinate
			 */
			inline lv_coord_t GetXAligned() {
				return lv_obj_get_x_aligned(_obj);
			}

			/**
			 * Get the actually set y coordinate of object, i.e. the offset form the set alignment
			 * @param Object       pointer to an object
			 * @return          the set y coordinate
			 */
			inline lv_coord_t GetYAligned() {
				return lv_obj_get_y_aligned(_obj);
			}

			/**
			 * Get the width of an object
			 * @param Object       pointer to an object
			 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
			 *                  call `lv_obj_update_layout(Object)`.
			 * @return          the width in pixels
			 */
			inline lv_coord_t GetWidth() {
				return lv_obj_get_width(_obj);
			}

			/**
			 * Get the height of an object
			 * @param Object       pointer to an object
			 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
			 *                  call `lv_obj_update_layout(Object)`.
			 * @return          the height in pixels
			 */
			inline lv_coord_t GetHeight() {
				return lv_obj_get_height(_obj);
			}

			/**
			 * Get the width reduced by the left and right padding and the border width.
			 * @param Object       pointer to an object
			 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
			 *                  call `lv_obj_update_layout(Object)`.
			 * @return          the width which still fits into its parent without causing overflow (making the parent scrollable)
			 */
			inline lv_coord_t GetConstantWidth() {
				return lv_obj_get_content_width(_obj);
			}

			/**
			 * Get the height reduced by the top and bottom padding and the border width.
			 * @param Object       pointer to an object
			 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
			 *                  call `lv_obj_update_layout(Object)`.
			 * @return          the height which still fits into the parent without causing overflow (making the parent scrollable)
			 */
			inline lv_coord_t GetConstantHeight() {
				return lv_obj_get_content_height(_obj);
			}

			/**
			 * Get the area reduced by the paddings and the border width.
			 * @param Object       pointer to an object
			 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
			 *                  call `lv_obj_update_layout(Object)`.
			 * @param area      the area which still fits into the parent without causing overflow (making the parent scrollable)
			 */
			inline Object *GetContentCoords(lv_area_t * area) {
				lv_obj_get_content_coords(_obj, area);
				return this;
			}

			/**
			 * Get the width occupied by the "parts" of the widget. E.g. the width of all columns of a table.
			 * @param Object       pointer to an objects
			 * @return          the width of the virtually drawn content
			 * @note            This size independent from the real size of the widget.
			 *                  It just tells how large the internal ("virtual") content is.
			 */
			inline lv_coord_t GetSelfWidth() {
				return lv_obj_get_self_width(_obj);
			}

			/**
			 * Get the height occupied by the "parts" of the widget. E.g. the height of all rows of a table.
			 * @param Object       pointer to an objects
			 * @return          the width of the virtually drawn content
			 * @note            This size independent from the real size of the widget.
			 *                  It just tells how large the internal ("virtual") content is.
			 */
			inline lv_coord_t GetSelfHeight() {
				return lv_obj_get_self_height(_obj);
			}

			/**
			 * Handle if the size of the internal ("virtual") content of an object has changed.
			 * @param Object       pointer to an object
			 * @return          false: nothing happened; true: refresh happened
			 */
			inline bool RefreshSelfSize() {
				return lv_obj_refresh_self_size(_obj);
			}

			inline Object *RefreshPos() {
				lv_obj_refr_pos(_obj);
				return this;
			}

			inline Object *MoveTo(lv_coord_t x, lv_coord_t y) {
				lv_obj_move_to(_obj, x, y);
				return this;
			}


			inline Object *MoveChildrenBy(lv_coord_t x_diff, lv_coord_t y_diff, bool ignore_floating) {
				lv_obj_move_children_by(_obj, x_diff, y_diff, ignore_floating);
				return this;
			}

			inline Object *Clean() {
				lv_obj_clean(_obj);
				return this;
			}

			/**
			 * Transform a point using the angle and zoom style properties of an object
			 * @param Object           pointer to an object whose style properties should be used
			 * @param p             a point to transform, the result will be written back here too
			 * @param recursive     consider the transformation properties of the parents too
			 * @param inv           do the inverse of the transformation (-angle and 1/zoom)
			 */
			inline Object *TransformPoint(lv_point_t * p, bool recursive, bool inv) {
				lv_obj_transform_point(_obj, p, recursive, inv);
				return this;
			}

			/**
			 * Transform an area using the angle and zoom style properties of an object
			 * @param Object           pointer to an object whose style properties should be used
			 * @param area          an area to transform, the result will be written back here too
			 * @param recursive     consider the transformation properties of the parents too
			 * @param inv           do the inverse of the transformation (-angle and 1/zoom)
			 */
			inline Object *GetTransformedArea(lv_area_t * area, bool recursive, bool inv) {
				lv_obj_get_transformed_area(_obj, area, recursive, inv);
				return this;
			}

			/**
			 * Mark an area of an object as invalid.
			 * The area will be truncated to the object's area and marked for redraw.
			 * @param Object       pointer to an object
			 * @param           area the area to redraw
			 */
			inline Object *InvalidateArea(const lv_area_t * area) {
				lv_obj_invalidate_area(_obj, area);
				return this;
			}

			/**
			 * Mark the object as invalid to redrawn its area
			 * @param Object       pointer to an object
			 */
			inline Object *Invalidate() {
				lv_obj_invalidate(_obj);
				return this;
			}

			/**
			 * Tell whether an area of an object is visible (even partially) now or not
			 * @param Object       pointer to an object
			 * @param area      the are to check. The visible part of the area will be written back here.
			 * @return true     visible; false not visible (hidden, out of parent, on other screen, etc)
			 */
			inline bool AreaIsVisible(lv_area_t * area) {
				return lv_obj_area_is_visible(_obj, area);
			}

			/**
			 * Tell whether an object is visible (even partially) now or not
			 * @param Object       pointer to an object
			 * @return      true: visible; false not visible (hidden, out of parent, on other screen, etc)
			 */
			inline bool IsVisible() {
				return lv_obj_is_visible(_obj);
			}

			/**
			 * Set the size of an extended clickable area
			 * @param Object       pointer to an object
			 * @param size      extended clickable area in all 4 directions [px]
			 */
			inline Object *SetExtClickArea(lv_coord_t size) {
				lv_obj_set_ext_click_area(_obj, size);
				return this;
			}

			/**
			 * Get the an area where to object can be clicked.
			 * It's the object's normal area plus the extended click area.
			 * @param Object       pointer to an object
			 * @param area      store the result area here
			 */
			inline Object *GetClickArea(lv_area_t * area) {
				lv_obj_get_click_area(_obj, area);
				return this;
			}

			/**
			 * Hit-test an object given a particular point in screen space.
			 * @param Object       object to hit-test
			 * @param point     screen-space point (absolute coordinate)
			 * @return          true: if the object is considered under the point
			 */
			inline bool HitTest(const lv_point_t * point) {
				return lv_obj_hit_test(_obj, point);
			}

			/**
			 * Clamp a width between min and max width. If the min/max width is in percentage value use the ref_width
			 * @param width         width to clamp
			 * @param min_width     the minimal width
			 * @param max_width     the maximal width
			 * @param ref_width     the reference width used when min/max width is in percentage
			 * @return              the clamped width
			 */
			inline lv_coord_t ClampWidth(lv_coord_t width, lv_coord_t min_width, lv_coord_t max_width, lv_coord_t ref_width) {
				return lv_clamp_width(width, min_width, max_width, ref_width);
			}

			/**
			 * Clamp a height between min and max height. If the min/max height is in percentage value use the ref_height
			 * @param height         height to clamp
			 * @param min_height     the minimal height
			 * @param max_height     the maximal height
			 * @param ref_height     the reference height used when min/max height is in percentage
			 * @return              the clamped height
			 */
			inline lv_coord_t ChampHeight(lv_coord_t height, lv_coord_t min_height, lv_coord_t max_height, lv_coord_t ref_height) {
				return lv_clamp_height(height, min_height, max_height, ref_height);
			}




			inline Object *sSetStyleWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleMinWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_min_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleMaxWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_max_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleHeight(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_height(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleMinHeight(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_min_height(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleMaxHeight(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_max_height(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleX(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_x(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleY(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_y(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleAlign(lv_align_t value, lv_style_selector_t selector) {
				lv_obj_set_style_align(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_transform_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformHeight(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_transform_height(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformX(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_translate_x(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformY(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_translate_y(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformZoom(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_transform_zoom(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTranbsformAngle(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_transform_angle(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformPivotX(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_transform_pivot_x(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformPivotY(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_transform_pivot_y(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformPadTop(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_top(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformPadBottom(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_bottom(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformPadLeft(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_left(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransformPadRight(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_right(_obj, value, selector);
				return this;
			}
			inline Object *SetStylePadRow(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_row(_obj, value, selector);
				return this;
			}
			inline Object *SetStylePadCollumn(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_column(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgColor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_color(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgGradColor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_grad_color(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgGradDir(lv_grad_dir_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_grad_dir(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgMainStop(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_main_stop(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgGradStop(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_grad_stop(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgGrad(const lv_grad_dsc_t * value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_grad(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgDitherMode(lv_dither_mode_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_dither_mode(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgImgSrc(const void * value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_img_src(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgImgOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_img_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgImgRecolor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_img_recolor(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgImgRecolorOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_img_recolor_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBgImgTiled(bool value, lv_style_selector_t selector) {
				lv_obj_set_style_bg_img_tiled(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBorderColor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_border_color(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBorderOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_border_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBorderWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_border_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBorderSide(lv_border_side_t value, lv_style_selector_t selector) {
				lv_obj_set_style_border_side(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBorderPost(bool value, lv_style_selector_t selector) {
				lv_obj_set_style_border_post(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleOutlineWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_outline_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleOutlineColor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_outline_color(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleOutlineOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_outline_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleOutlinePad(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_outline_pad(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleShadowWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_shadow_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleShadowOfsX(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_shadow_ofs_x(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleShadowOfsY(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_shadow_ofs_y(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleShadowSpread(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_shadow_spread(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleShadowColor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_shadow_color(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleShadowOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_shadow_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleImgOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_img_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleImgRecolor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_img_recolor(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleImgRecolorOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_img_recolor_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleLineWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_line_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleLineDashWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_line_dash_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleLineDashGap(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_line_dash_gap(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleLineRounded(bool value, lv_style_selector_t selector) {
				lv_obj_set_style_line_rounded(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleLineColor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_line_color(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleLineOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_line_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleArcWidth(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_arc_width(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleArcRounded(bool value, lv_style_selector_t selector) {
				lv_obj_set_style_arc_rounded(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleArcColor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_arc_color(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleArcOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_arc_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleArcImgSrc(const void * value, lv_style_selector_t selector) {
				lv_obj_set_style_arc_img_src(_obj,value, selector);
				return this;
			}
			inline Object *SetStyleTextColor(lv_color_t value, lv_style_selector_t selector) {
				lv_obj_set_style_text_color(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTextOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_text_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTextFont(const lv_font_t * value, lv_style_selector_t selector) {
				lv_obj_set_style_text_font(_obj,value, selector);
				return this;
			}
			inline Object *SetStyleTextLetterSpace(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_text_letter_space(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTextLineSpace(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_text_line_space(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTextDecor(lv_text_decor_t value, lv_style_selector_t selector) {
				lv_obj_set_style_text_decor(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTextAlign(lv_text_align_t value, lv_style_selector_t selector) {
				lv_obj_set_style_text_align(_obj, value, selector);
				return this;
			}
			inline Object *SetStylePadAll(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_all(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleRadius(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_radius(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleClipCorner(bool value, lv_style_selector_t selector) {
				lv_obj_set_style_clip_corner(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleOpaLayered(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_opa_layered(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleColorFilterDsc(const lv_color_filter_dsc_t * value, lv_style_selector_t selector) {
				lv_obj_set_style_color_filter_dsc(_obj,value, selector);
				return this;
			}
			inline Object *SetStyleColorFilterOpa(lv_opa_t value, lv_style_selector_t selector) {
				lv_obj_set_style_color_filter_opa(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleAnim(const lv_anim_t * value, lv_style_selector_t selector) {
				lv_obj_set_style_anim(_obj,value, selector);
				return this;
			}
			inline Object *SetStyleAnimTime(uint32_t value, lv_style_selector_t selector) {
				lv_obj_set_style_anim_time(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleAnimSpeed(uint32_t value, lv_style_selector_t selector) {
				lv_obj_set_style_anim_speed(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleTransition(const lv_style_transition_dsc_t * value, lv_style_selector_t selector) {
				lv_obj_set_style_transition(_obj,value, selector);
				return this;
			}
			inline Object *SetStyleBlendMode(lv_blend_mode_t value, lv_style_selector_t selector) {
				lv_obj_set_style_blend_mode(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleLayout(uint16_t value, lv_style_selector_t selector) {
				lv_obj_set_style_layout(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleBaseDir(lv_base_dir_t value, lv_style_selector_t selector) {
				lv_obj_set_style_base_dir(_obj, value, selector);
				return this;
			}
			inline Object *AddEventCbValueChanged(lv_event_cb_t event_cb, void * user_data = NULL) {
				lv_obj_add_event_cb(_obj, event_cb, LV_EVENT_VALUE_CHANGED, user_data);
				return this;
			}
			inline Object *AddEventCbClicked(lv_event_cb_t event_cb, void * user_data = NULL) {
				lv_obj_add_event_cb(_obj, event_cb, LV_EVENT_CLICKED, user_data);
				return this;
			}
			
			inline Object *AddStyle(lv_style_t * style, lv_style_selector_t selector) {
				lv_obj_add_style(_obj, style, selector);
				return this;
			}
			
			inline Object *AddStyle(lvgl::Style * style, lv_style_selector_t selector) {
				lv_obj_add_style(_obj, style->Get(), selector);
				return this;
			}
			
			/*inline Object *AddStyle(lvgl::Style style, lv_style_selector_t selector) {
				lv_obj_add_style(_obj, style.Get(), selector);
				return this;
			}*/
			
			inline Object *RemoveStyle(lv_style_t * style, lv_style_selector_t selector) {
				lv_obj_remove_style(_obj, style, selector);
				return this;
			}
			
			inline Object *RemoveStyleAll() {
				lv_obj_remove_style(_obj, NULL, (lv_style_selector_t)LV_PART_ANY | (lv_style_selector_t)LV_STATE_ANY);
				return this;
			}
			
			inline Object *ReportStyleChanged(lv_style_t * style) {
				lv_obj_report_style_change(style);
				return this;
			}
			
			inline Object *RefreshStyle(lv_part_t part, lv_style_prop_t prop) {
				lv_obj_refresh_style(_obj, part, prop);
				return this;
			}
			
			inline Object *EnableStyleRefresh(bool en) {
				lv_obj_enable_style_refresh(en);
				return this;
			}
			
			inline lv_style_value_t GetStyleProp(lv_part_t part, lv_style_prop_t prop) {
				return lv_obj_get_style_prop(_obj, part, prop);
			}
			
			inline Object *SetLocalStyleProp(lv_style_prop_t prop, lv_style_value_t value, lv_style_selector_t selector) {
				lv_obj_set_local_style_prop(_obj, prop, value, selector);
				return this;
			}
			
			inline Object *SetLocalStylePropMeta(lv_style_prop_t prop, uint16_t meta, lv_style_selector_t selector) {
				lv_obj_set_local_style_prop_meta(_obj, prop, meta, selector);
				return this;
			}
			
			inline lv_style_res_t GetLocalStyleProp(lv_style_prop_t prop, lv_style_value_t * value, lv_style_selector_t selector) {
				return lv_obj_get_local_style_prop(_obj, prop, value, selector);
			}
			
			inline bool RemoveLocalStyleProp(lv_style_prop_t prop, lv_style_selector_t selector) {
				return lv_obj_remove_local_style_prop(_obj, prop, selector);
			}
			
			inline lv_style_value_t StyleApplyColorFilter(uint32_t part, lv_style_value_t v) {
				return _lv_obj_style_apply_color_filter(_obj, part, v);
			}
			
			inline Object *StyleCreateTransition(lv_part_t part, lv_state_t prev_state, lv_state_t new_state, const _lv_obj_style_transition_dsc_t * tr) {
				_lv_obj_style_create_transition(_obj, part, prev_state, new_state, tr);
				return this;
			}
			
			inline _lv_style_state_cmp_t StyleStateCompare(lv_state_t state1, lv_state_t state2) {
				return _lv_obj_style_state_compare(_obj, state1, state2);
			}
			
			inline Object *FadeIn(uint32_t time, uint32_t delay) {
				lv_obj_fade_in(_obj, time, delay);
				return this;
			}
			
			inline Object *FadeOut(uint32_t time, uint32_t delay) {
				lv_obj_fade_out(_obj, time, delay);
				return this;
			}
			
			inline lv_state_t StyleGetSelectorState(lv_style_selector_t selector) {
				return lv_obj_style_get_selector_state(selector);
			}
			
			inline lv_part_t StyleGetSelectorPart(lv_style_selector_t selector) {
				return lv_obj_style_get_selector_part(selector);
			}
			
			inline Object *SetStylePadHor(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_hor(_obj, value, selector);
				return this;
			}
			
			inline Object *SetStylePadVer(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_ver(_obj, value, selector);
				return this;
			}
			
			inline Object *SetStylePadGap(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_pad_gap(_obj, value, selector);
				return this;
			}
			
			inline Object *SetStyleSize(lv_coord_t value, lv_style_selector_t selector) {
				lv_obj_set_style_size(_obj, value, selector);
				return this;
			}
			
			inline lv_text_align_t CalculateTextAlign(lv_part_t part, const char * txt) {
				return lv_obj_calculate_style_text_align(_obj, part, txt);
			}
			
			inline lv_text_align_t GetStyleTransformZoomSafe(uint32_t part) {
				return lv_obj_get_style_transform_zoom_safe(_obj, part);
			}
			
			inline lv_opa_t GetStyleOpaRecursive(lv_part_t part) {
				return lv_obj_get_style_opa_recursive(_obj, part);
			}
			
			
			
			
			/**
		 * Set how the scrollbars should behave.
		 * @param obj       pointer to an object
		 * @param mode      LV_SCROLL_MODE_ON/OFF/AUTO/ACTIVE
		 */
			inline Object *SetScrollbarMode(lv_scrollbar_mode_t mode) {
				lv_obj_set_scrollbar_mode(_obj, mode);
				return this;
			}

		/**
		 * Set the object in which directions can be scrolled
		 * @param obj       pointer to an object
		 * @param dir       the allow scroll directions. An element or OR-ed values of `lv_dir_t`
		 */
			inline Object *SetScrollDirection(lv_dir_t dir) {
				lv_obj_set_scroll_dir(_obj, dir);
				return this;
			}

		/**
		 * Set where to snap the children when scrolling ends horizontally
		 * @param obj       pointer to an object
		 * @param align     the snap align to set from `lv_scroll_snap_t`
		 */
			inline Object *SetScrollSnapX(lv_scroll_snap_t align) {
				lv_obj_set_scroll_snap_x(_obj, align);
				return this;
			}

		/**
		 * Set where to snap the children when scrolling ends vertically
		 * @param obj       pointer to an object
		 * @param align     the snap align to set from `lv_scroll_snap_t`
		 */
			inline Object *SetScrollSnapY(lv_scroll_snap_t align) {
				lv_obj_set_scroll_snap_y(_obj, align);
				return this;
			}

		/*=====================
		 * Getter functions
		 *====================*/

		/**
		 * Get the current scroll mode (when to hide the scrollbars)
		 * @param obj       pointer to an object
		 * @return          the current scroll mode from `lv_scrollbar_mode_t`
		 */
			lv_scrollbar_mode_t GetScrollbarMode() {
				return lv_obj_get_scrollbar_mode(_obj);
			}

		/**
		 * Get the object in which directions can be scrolled
		 * @param obj       pointer to an object
		 * @param dir       the allow scroll directions. An element or OR-ed values of `lv_dir_t`
		 */
			lv_dir_t GetScrollDirection() {
				return lv_obj_get_scroll_dir(_obj);
			}

		/**
		 * Get where to snap the children when scrolling ends horizontally
		 * @param obj       pointer to an object
		 * @return          the current snap align from `lv_scroll_snap_t`
		 */
			lv_scroll_snap_t GetScrollSnapX() {
				return lv_obj_get_scroll_snap_x(_obj);
			}

		/**
		 * Get where to snap the children when scrolling ends vertically
		 * @param  obj      pointer to an object
		 * @return          the current snap align from `lv_scroll_snap_t`
		 */
			lv_scroll_snap_t GetScrollSnapY() {
				return lv_obj_get_scroll_snap_y(_obj);
			}

		/**
		 * Get current X scroll position.
		 * @param obj       pointer to an object
		 * @return          the current scroll position from the left edge.
		 *                  If the object is not scrolled return 0
		 *                  If scrolled return > 0
		 *                  If scrolled in (elastic scroll) return < 0
		 */
			lv_coord_t GetScrollX() {
				return lv_obj_get_scroll_x(_obj);
			}

		/**
		 * Get current Y scroll position.
		 * @param obj       pointer to an object
		 * @return          the current scroll position from the top edge.
		 *                  If the object is not scrolled return 0
		 *                  If scrolled return > 0
		 *                  If scrolled inside return < 0
		 */
			lv_coord_t GetScrollY() {
				return lv_obj_get_scroll_y(_obj);
			}

		/**
		 * Return the height of the area above the object.
		 * That is the number of pixels the object can be scrolled down.
		 * Normally positive but can be negative when scrolled inside.
		 * @param obj       pointer to an object
		 * @return          the scrollable area above the object in pixels
		 */
			lv_coord_t GetScrollTop() {
				return lv_obj_get_scroll_top(_obj);
			}

		/**
		 * Return the height of the area below the object.
		 * That is the number of pixels the object can be scrolled down.
		 * Normally positive but can be negative when scrolled inside.
		 * @param obj       pointer to an object
		 * @return          the scrollable area below the object in pixels
		 */
			lv_coord_t GetScrollBottom() {
				return lv_obj_get_scroll_bottom(_obj);
			}

		/**
		 * Return the width of the area on the left the object.
		 * That is the number of pixels the object can be scrolled down.
		 * Normally positive but can be negative when scrolled inside.
		 * @param obj       pointer to an object
		 * @return          the scrollable area on the left the object in pixels
		 */
			lv_coord_t GetScrollLeft() {
				return lv_obj_get_scroll_left(_obj);
			}

		/**
		 * Return the width of the area on the right the object.
		 * That is the number of pixels the object can be scrolled down.
		 * Normally positive but can be negative when scrolled inside.
		 * @param obj       pointer to an object
		 * @return          the scrollable area on the right the object in pixels
		 */
			lv_coord_t GetScrollRight() {
				return lv_obj_get_scroll_right(_obj);
			}

		/**
		 * Get the X and Y coordinates where the scrolling will end for this object if a scrolling animation is in progress.
		 * If no scrolling animation, give the current `x` or `y` scroll position.
		 * @param obj       pointer to an object
		 * @param end       pointer to store the result
		 */
			inline Object *GetScrollEnd(lv_point_t * end) {
				lv_obj_get_scroll_end(_obj, end);
				return this;
			}

		/*=====================
		 * Other functions
		 *====================*/

		/**
		 * Scroll by a given amount of pixels
		 * @param obj       pointer to an object to scroll
		 * @param dx         pixels to scroll horizontally
		 * @param dy         pixels to scroll vertically
		 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
		 * @note            > 0 value means scroll right/bottom (show the more content on the right/bottom)
		 * @note            e.g. dy = -20 means scroll down 20 px
		 */
			inline Object *ScrollBy(lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en) {
				lv_obj_scroll_by(_obj, x, y, anim_en);
				return this;
			}

		/**
		 * Scroll by a given amount of pixels.
		 * `dx` and `dy` will be limited internally to allow scrolling only on the content area.
		 * @param obj       pointer to an object to scroll
		 * @param dx        pixels to scroll horizontally
		 * @param dy        pixels to scroll vertically
		 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
		 * @note            e.g. dy = -20 means scroll down 20 px
		 */
			inline Object *ScrollByBounded(lv_coord_t dx, lv_coord_t dy, lv_anim_enable_t anim_en) {
				lv_obj_scroll_by_bounded(_obj, dx, dy, anim_en);
				return this;
			}

		/**
		 * Scroll to a given coordinate on an object.
		 * `x` and `y` will be limited internally to allow scrolling only on the content area.
		 * @param obj       pointer to an object to scroll
		 * @param x         pixels to scroll horizontally
		 * @param y         pixels to scroll vertically
		 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
		 */
			inline Object *ScrollTo(lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en) {
				lv_obj_scroll_to(_obj, x, y, anim_en);
				return this;
			}

		/**
		 * Scroll to a given X coordinate on an object.
		 * `x` will be limited internally to allow scrolling only on the content area.
		 * @param obj       pointer to an object to scroll
		 * @param x         pixels to scroll horizontally
		 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
		 */
			inline Object *ScrollToX(lv_coord_t x, lv_anim_enable_t anim_en) {
				lv_obj_scroll_to_x(_obj, x, anim_en);
				return this;
			}

		/**
		 * Scroll to a given Y coordinate on an object
		 * `y` will be limited internally to allow scrolling only on the content area.
		 * @param obj       pointer to an object to scroll
		 * @param y         pixels to scroll vertically
		 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
		 */
			inline Object *ScrollToY(lv_coord_t y, lv_anim_enable_t anim_en) {
				lv_obj_scroll_to_y(_obj, y, anim_en);
				return this;
			}

		/**
		 * Scroll to an object until it becomes visible on its parent
		 * @param obj       pointer to an object to scroll into view
		 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
		 */
			inline Object *ScrollToView(lv_anim_enable_t anim_en) {
				lv_obj_scroll_to_view(_obj, anim_en);
				return this;
			}

		/**
		 * Scroll to an object until it becomes visible on its parent.
		 * Do the same on the parent's parent, and so on.
		 * Therefore the object will be scrolled into view even it has nested scrollable parents
		 * @param obj       pointer to an object to scroll into view
		 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
		 */
			inline Object *ScrollToViewRecursive(lv_anim_enable_t anim_en) {
				lv_obj_scroll_to_view_recursive(_obj, anim_en);
				return this;
			}

		/**
		 * Low level function to scroll by given x and y coordinates.
		 * `LV_EVENT_SCROLL` is sent.
		 * @param obj       pointer to an object to scroll
		 * @param x         pixels to scroll horizontally
		 * @param y         pixels to scroll vertically
		 * @return          `LV_RES_INV`: to object was deleted in `LV_EVENT_SCROLL`;
		 *                  `LV_RES_OK`: if the object is still valid
		 */
			lv_res_t ScrollByRaw(lv_coord_t x, lv_coord_t y) {
				_lv_obj_scroll_by_raw(_obj, x, y);
			}

		/**
		 * Tell whether an object is being scrolled or not at this moment
		 * @param obj   pointer to an object
		 * @return      true: `obj` is being scrolled
		 */
			bool IsScrolling() {
				return lv_obj_is_scrolling(_obj);
			}

		/**
		 * Check the children of `obj` and scroll `obj` to fulfill the scroll_snap settings
		 * @param obj       an object whose children needs to checked and snapped
		 * @param anim_en   LV_ANIM_ON/OFF
		 */
			inline Object *UpdateSnap(lv_anim_enable_t anim_en) {
				lv_obj_update_snap(_obj, anim_en);
				return this;
			}

		/**
		 * Get the area of the scrollbars
		 * @param obj   pointer to an object
		 * @param hor   pointer to store the area of the horizontal scrollbar
		 * @param ver   pointer to store the area of the vertical  scrollbar
		 */
			inline Object *GetScrollbarArea(lv_area_t * hor, lv_area_t * ver) {
				lv_obj_get_scrollbar_area(_obj, hor, ver);
				return this;
			}

		/**
		 * Invalidate the area of the scrollbars
		 * @param obj       pointer to an object
		 */
			inline Object *ScrollbarInvalidate() {
				lv_obj_scrollbar_invalidate(_obj);
				return this;
			}

		/**
		 * Checks if the content is scrolled "in" and adjusts it to a normal position.
		 * @param obj       pointer to an object
		 * @param anim_en   LV_ANIM_ON/OFF
		 */
			inline Object *ReadjustScroll(lv_anim_enable_t anim_en) {
				lv_obj_readjust_scroll(_obj, anim_en);
				return this;
			}
			
			
			
			
			
			
		/**
		 * Set hot the item should flow
		 * @param flex pointer to a flex layout descriptor
		 * @param flow an element of `lv_flex_flow_t`.
		 */
			inline Object *SetFlexFlow(lv_flex_flow_t flow) {
				lv_obj_set_flex_flow(_obj, flow);
				return this;
			}

		/**
		 * Set how to place (where to align) the items and tracks
		 * @param flex pointer: to a flex layout descriptor
		 * @param main_place where to place the items on main axis (in their track). Any value of `lv_flex_align_t`.
		 * @param cross_place where to place the item in their track on the cross axis. `LV_FLEX_ALIGN_START/END/CENTER`
		 * @param track_place where to place the tracks in the cross direction. Any value of `lv_flex_align_t`.
		 */
			inline Object *SetFlexAlign(lv_flex_align_t main_place, lv_flex_align_t cross_place,
						               lv_flex_align_t track_cross_place) {
				lv_obj_set_flex_align(_obj, main_place, cross_place, track_cross_place);
				return this;
			}

		/**
		 * Sets the width or height (on main axis) to grow the object in order fill the free space
		 * @param obj pointer to an object. The parent must have flex layout else nothing will happen.
		 * @param grow a value to set how much free space to take proportionally to other growing items.
		 */
			inline Object *SetFlexGrow(uint8_t grow) {
				lv_obj_set_flex_grow(_obj, grow);
				return this;
			}

			inline Object *SetStyleFlexFlow(lv_flex_flow_t value, lv_style_selector_t selector) {
				lv_obj_set_style_flex_flow(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleFlexMainPlace(lv_flex_align_t value, lv_style_selector_t selector) {
				lv_obj_set_style_flex_main_place(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleFlexCrossPlace(lv_flex_align_t value, lv_style_selector_t selector) {
				lv_obj_set_style_flex_cross_place(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleFlexTrackPlace(lv_flex_align_t value, lv_style_selector_t selector) {
				lv_obj_set_style_flex_track_place(_obj, value, selector);
				return this;
			}
			inline Object *SetStyleFlexGrow(uint8_t value, lv_style_selector_t selector) {
				lv_obj_set_style_flex_grow(_obj, value, selector);
				return this;
			}
			
			
			
			
			
			
		/**
		 * Send an event to the object
		 * @param obj           pointer to an object
		 * @param event_code    the type of the event from `lv_event_t`
		 * @param param         arbitrary data depending on the widget type and the event. (Usually `NULL`)
		 * @return LV_RES_OK: `obj` was not deleted in the event; LV_RES_INV: `obj` was deleted in the event_code
		 */
			lv_res_t EventSend(lv_event_code_t event_code, void * param) {
				return lv_event_send(_obj, event_code, param);
			}

		/**
		 * Used by the widgets internally to call the ancestor widget types's event handler
		 * @param class_p   pointer to the class of the widget (NOT the ancestor class)
		 * @param e         pointer to the event descriptor
		 * @return          LV_RES_OK: the target object was not deleted in the event; LV_RES_INV: it was deleted in the event_code
		 */
			static lv_res_t EventBase(const lv_obj_class_t *class_p, lv_event_t *e) {
				lv_obj_event_base(class_p, e);
			}

		/**
		 * Get the object originally targeted by the event. It's the same even if the event is bubbled.
		 * @param e     pointer to the event descriptor
		 * @return      the target of the event_code
		 */
			static struct _lv_obj_t *EventGetTarget(lv_event_t *e) {
				return lv_event_get_target(e);
			}

		/**
		 * Get the current target of the event. It's the object which event handler being called.
		 * If the event is not bubbled it's the same as "normal" target.
		 * @param e     pointer to the event descriptor
		 * @return      pointer to the current target of the event_code
		 */
			static struct _lv_obj_t *EventGetCurrentTarget(lv_event_t *e) {
				return lv_event_get_current_target(e);
			}

		/**
		 * Get the event code of an event
		 * @param e     pointer to the event descriptor
		 * @return      the event code. (E.g. `LV_EVENT_CLICKED`, `LV_EVENT_FOCUSED`, etc)
		 */
			static lv_event_code_t EventGetCode(lv_event_t *e) {
				return lv_event_get_code(e);
			}

		/**
		 * Get the parameter passed when the event was sent
		 * @param e     pointer to the event descriptor
		 * @return      pointer to the parameter
		 */
			static void *EventGetParam(lv_event_t *e) {
				return lv_event_get_param(e);
			}

		/**
		 * Get the user_data passed when the event was registered on the object
		 * @param e     pointer to the event descriptor
		 * @return      pointer to the user_data
		 */
			static void *EventGetUserData(lv_event_t *e) {
				return lv_event_get_user_data(e);
			}

		/**
		 * Stop the event from bubbling.
		 * This is only valid when called in the middle of an event processing chain.
		 * @param e     pointer to the event descriptor
		 */
			static void EventStopBubbling(lv_event_t *e) {
				lv_event_stop_bubbling(e);
			}

		/**
		 * Stop processing this event.
		 * This is only valid when called in the middle of an event processing chain.
		 * @param e     pointer to the event descriptor
		 */
			static void EventStopProcessing(lv_event_t *e) {
				lv_event_stop_processing(e);
			}

		/**
		 * Register a new, custom event ID.
		 * It can be used the same way as e.g. `LV_EVENT_CLICKED` to send custom events
		 * @return      the new event id
		 * @example
		 * uint32_t LV_EVENT_MINE = 0;
		 * ...
		 * e = lv_event_register_id();
		 * ...
		 * lv_event_send(obj, LV_EVENT_MINE, &some_data);
		 */
			static uint32_t EventRegisterId() {
				return lv_event_register_id();
			}

		/**
		 * Nested events can be called and one of them might belong to an object that is being deleted.
		 * Mark this object's `event_temp_data` deleted to know that its `lv_event_send` should return `LV_RES_INV`
		 * @param obj pointer to an object to mark as deleted
		 */
			void EventMarkDeleted() {
				_lv_event_mark_deleted(_obj);
			}

		/**
		 * Add an event handler function for an object.
		 * Used by the user to react on event which happens with the object.
		 * An object can have multiple event handler. They will be called in the same order as they were added.
		 * @param obj       pointer to an object
		 * @param filter    and event code (e.g. `LV_EVENT_CLICKED`) on which the event should be called. `LV_EVENT_ALL` can be sued the receive all the events.
		 * @param event_cb  the new event function
		 * @param           user_data custom data data will be available in `event_cb`
		 * @return          a pointer the event descriptor. Can be used in ::lv_obj_remove_event_dsc
		 */
			struct _lv_event_dsc_t * AddEventCb(lv_event_cb_t event_cb, lv_event_code_t filter,
						                                 void * user_data) {
				return lv_obj_add_event_cb(_obj, event_cb, filter, user_data);
			}

		/**
		 * Remove an event handler function for an object.
		 * @param obj       pointer to an object
		 * @param event_cb  the event function to remove, or `NULL` to remove the firstly added event callback
		 * @return          true if any event handlers were removed
		 */
			bool RemoveEventCb(lv_event_cb_t event_cb) {
				return lv_obj_remove_event_cb(_obj, event_cb);
			}

		/**
		 * Remove an event handler function with a specific user_data from an object.
		 * @param obj               pointer to an object
		 * @param event_cb          the event function to remove, or `NULL` only `user_data` matters.
		 * @param event_user_data   the user_data specified in ::lv_obj_add_event_cb
		 * @return                  true if any event handlers were removed
		 */
			bool RemoveEventCbWithUserData(lv_event_cb_t event_cb, const void * event_user_data) {
				return lv_obj_remove_event_cb_with_user_data(_obj, event_cb, event_user_data);
			}

		/**
		 * DEPRECATED because doesn't work if multiple event handlers are added to an object.
		 * Remove an event handler function for an object.
		 * @param obj       pointer to an object
		 * @param event_dsc pointer to an event descriptor to remove (returned by ::lv_obj_add_event_cb)
		 * @return          true if any event handlers were removed
		 */
			bool RemoveEventDsc(struct _lv_event_dsc_t * event_dsc) {
				return lv_obj_remove_event_dsc(_obj, event_dsc);
			}

		/**
		 * The user data of an event object event callback. Always the first match with `event_cb` will be returned.
		 * @param obj               pointer to an object
		 * @param event_cb          the event function
		 * @return                  the user_data
		 */
			void *GetEventUserData(lv_event_cb_t event_cb) {
				return lv_obj_get_event_user_data(_obj, event_cb);
			}

		/**
		 * Get the input device passed as parameter to indev related events.
		 * @param e     pointer to an event
		 * @return      the indev that triggered the event or NULL if called on a not indev related event
		 */
			static lv_indev_t * EventGetIndev(lv_event_t *e) {
				return lv_event_get_indev(e);
			}

		/**
		 * Get the part draw descriptor passed as parameter to `LV_EVENT_DRAW_PART_BEGIN/END`.
		 * @param e     pointer to an event
		 * @return      the part draw descriptor to hook the drawing or NULL if called on an unrelated event
		 */
			static lv_obj_draw_part_dsc_t *EventGetDrawPartRescriptor(lv_event_t *e) {
				return lv_event_get_draw_part_dsc(e);
			}

		/**
		 * Get the draw context which should be the first parameter of the draw functions.
		 * Namely: `LV_EVENT_DRAW_MAIN/POST`, `LV_EVENT_DRAW_MAIN/POST_BEGIN`, `LV_EVENT_DRAW_MAIN/POST_END`
		 * @param e     pointer to an event
		 * @return      pointer to a draw context or NULL if called on an unrelated event
		 */
			static lv_draw_ctx_t *EventGetDrawContext(lv_event_t *e) {
				return lv_event_get_draw_ctx(e);
			}

		/**
		 * Get the old area of the object before its size was changed. Can be used in `LV_EVENT_SIZE_CHANGED`
		 * @param e     pointer to an event
		 * @return      the old absolute area of the object or NULL if called on an unrelated event
		 */
			static const lv_area_t *EventGetOldSize(lv_event_t *e) {
				return lv_event_get_old_size(e);
			}

		/**
		 * Get the key passed as parameter to an event. Can be used in `LV_EVENT_KEY`
		 * @param e     pointer to an event
		 * @return      the triggering key or NULL if called on an unrelated event
		 */
			static uint32_t EventGetKey(lv_event_t *e) {
				return lv_event_get_key(e);
			}

		/**
		 * Get the animation descriptor of a scrolling. Can be used in `LV_EVENT_SCROLL_BEGIN`
		 * @param e     pointer to an event
		 * @return      the animation that will scroll the object. (can be modified as required)
		 */
			static lv_anim_t *EventGetScrollAnim(lv_event_t *e) {
				return lv_event_get_scroll_anim(e);
			}

		/**
		 * Set the new extra draw size. Can be used in `LV_EVENT_REFR_EXT_DRAW_SIZE`
		 * @param e     pointer to an event
		 * @param size  The new extra draw size
		 */
			static void EventSetExtraDrawSize(lv_event_t *e, lv_coord_t size) {
				lv_event_set_ext_draw_size(e, size);
			}

		/**
		 * Get a pointer to an `lv_point_t` variable in which the self size should be saved (width in `point->x` and height `point->y`).
		 * Can be used in `LV_EVENT_GET_SELF_SIZE`
		 * @param e     pointer to an event
		 * @return      pointer to `lv_point_t` or NULL if called on an unrelated event
		 */
			static lv_point_t *EventGetSelfSizeInfo(lv_event_t *e) {
				return lv_event_get_self_size_info(e);
			}

		/**
		 * Get a pointer to an `lv_hit_test_info_t` variable in which the hit test result should be saved. Can be used in `LV_EVENT_HIT_TEST`
		 * @param e     pointer to an event
		 * @return      pointer to `lv_hit_test_info_t` or NULL if called on an unrelated event
		 */
			static lv_hit_test_info_t *EventGetHitTestInfo(lv_event_t *e) {
				return lv_event_get_hit_test_info(e);
			}

		/**
		 * Get a pointer to an area which should be examined whether the object fully covers it or not.
		 * Can be used in `LV_EVENT_HIT_TEST`
		 * @param e     pointer to an event
		 * @return      an area with absolute coordinates to check
		 */
			static const lv_area_t *EventGetCoverArea(lv_event_t *e) {
				return lv_event_get_cover_area(e);
			}

		/**
		 * Set the result of cover checking. Can be used in `LV_EVENT_COVER_CHECK`
		 * @param e     pointer to an event
		 * @param res   an element of ::lv_cover_check_info_t
		 */
			static void EventSetCoverRes(lv_event_t *e, lv_cover_res_t res) {
				lv_event_set_cover_res(e, res);
			}


		};
	} /* namespace widget */
} /* namespace lvgl */

#endif /* LVCPP_LVOBJ_H_ */
