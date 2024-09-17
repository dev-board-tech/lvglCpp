/*
 * Image.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_IMAGE_H_
#define LVGLCPP_SRC_IMAGE_H_

#include "Object.h"

namespace lvgl {
	namespace widget {
		class Image : public Object {
		public:
			Image(lv_obj_t *parent) {
				_obj = lv_img_create(parent);
				_child = NULL;
				_childs = NULL;
			}
			Image(Object *parent) {
				if(parent && parent->GetObj()) {
					_obj = lv_img_create(parent->GetObj());
				} else {
					_obj = lv_img_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			Image(Object &parent) {
				if(((Object)parent).GetObj()) {
					_obj = lv_img_create(((Object)parent).GetObj());
				} else {
					_obj = lv_img_create(NULL);
				}
				_child = NULL;
				_childs = NULL;
			}
			Image(lv_obj_t *parent, bool isNew) {
				_obj = parent;
				_childs = NULL;
				_child = NULL;
			}
			Image(Object *parent, bool isNew) {
				_obj = parent->GetObj();
				_childs = parent->GetChilds();
				_child = NULL;
			}
			Image(Object &parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
				_childs = ((Object)parent).GetChilds();
				_child = NULL;
			}

			~Image() {

			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

			/*=====================
			 * Setter functions
			 *====================*/

			/**
			 * Set the image data to display on the object
			 * @param obj       pointer to an image object
			 * @param src_img   1) pointer to an ::lv_img_dsc_t descriptor (converted by LVGL's image converter) (e.g. &my_img) or
			 *                  2) path to an image file (e.g. "S:/dir/img.bin")or
			 *                  3) a SYMBOL (e.g. LV_SYMBOL_OK)
			 */
			inline Image *SetImageSource(const void *src) {
				lv_img_set_src(_obj, src);
				return this;
			}

			/**
			 * Set an offset for the source of an image so the image will be displayed from the new origin.
			 * @param obj       pointer to an image
			 * @param x         the new offset along x axis.
			 */
			inline Image *SetOffset(lv_coord_t x, lv_coord_t y) {
				lv_img_set_offset_x(_obj, x);
				lv_img_set_offset_y(_obj, y);
				return this;
			}

			/**
			 * Set an offset for the source of an image so the image will be displayed from the new origin.
			 * @param obj       pointer to an image
			 * @param x         the new offset along x axis.
			 */
			inline Image *SetOffsetX(lv_coord_t x) {
				lv_img_set_offset_x(_obj, x);
				return this;
			}

			/**
			 * Set an offset for the source of an image.
			 * so the image will be displayed from the new origin.
			 * @param obj       pointer to an image
			 * @param y         the new offset along y axis.
			 */
			inline Image *SetOffsetY(lv_coord_t y) {
				lv_img_set_offset_y(_obj, y);
				return this;
			}


			/**
			 * Set the rotation angle of the image.
			 * The image will be rotated around the set pivot set by `lv_img_set_pivot()`
			 * Note that indexed and alpha only images can't be transformed.
			 * @param obj       pointer to an image object
			 * @param angle     rotation angle in degree with 0.1 degree resolution (0..3600: clock wise)
			 */
			inline Image *SetAngle(int16_t angle) {
				lv_img_set_angle(_obj, angle);
				return this;
			}

			/**
			 * Set the rotation center of the image.
			 * The image will be rotated around this point.
			 * @param obj       pointer to an image object
			 * @param x         rotation center x of the image
			 * @param y         rotation center y of the image
			 */
			inline Image *SetPivot(lv_coord_t x, lv_coord_t y) {
				lv_img_set_pivot(_obj, x, y);
				return this;
			}


			/**
			 * Set the zoom factor of the image.
			 * Note that indexed and alpha only images can't be transformed.
			 * @param img       pointer to an image object
			 * @param zoom      the zoom factor.
			 * @example 256 or LV_ZOOM_IMG_NONE for no zoom
			 * @example <256: scale down
			 * @example >256 scale up
			 * @example 128 half size
			 * @example 512 double size
			 */
			inline Image *SetZoom(uint16_t zoom) {
				lv_img_set_zoom(_obj, zoom);
				return this;
			}

			/**
			 * Enable/disable anti-aliasing for the transformations (rotate, zoom) or not.
			 * The quality is better with anti-aliasing looks better but slower.
			 * @param obj       pointer to an image object
			 * @param antialias true: anti-aliased; false: not anti-aliased
			 */
			inline Image *SetAntiAlias(bool antialias) {
				lv_img_set_antialias(_obj, antialias);
				return this;
			}

			/**
			 * Set the image object size mode.
			 *
			 * @param obj       pointer to an image object
			 * @param mode      the new size mode.
			 */
			inline Image *SetSizeMode(lv_img_size_mode_t mode) {
				lv_img_set_size_mode(_obj, mode);
				return this;
			}
			/*=====================
			 * Getter functions
			 *====================*/

			/**
			 * Get the source of the image
			 * @param obj       pointer to an image object
			 * @return          the image source (symbol, file name or ::lv-img_dsc_t for C arrays)
			 */
			inline const void *GetSource() {
				return lv_img_get_src(_obj);
			}

			/**
			 * Get the offset's x attribute of the image object.
			 * @param img       pointer to an image
			 * @return          offset X value.
			 */
			inline lv_coord_t GetOffsetX() {
				return lv_img_get_offset_x(_obj);
			}

			/**
			 * Get the offset's y attribute of the image object.
			 * @param obj       pointer to an image
			 * @return          offset Y value.
			 */
			inline lv_coord_t GetOffsetY() {
				return lv_img_get_offset_y(_obj);
			}

			/**
			 * Get the rotation angle of the image.
			 * @param obj       pointer to an image object
			 * @return      rotation angle in 0.1 degrees (0..3600)
			 */
			inline uint16_t GetAngle() {
				return lv_img_get_angle(_obj);
			}

			/**
			 * Get the pivot (rotation center) of the image.
			 * @param img       pointer to an image object
			 * @param pivot     store the rotation center here
			 */
			inline lv_point_t GetPivot() {
				lv_point_t pivot;
				lv_img_get_pivot(_obj, &pivot);
				return pivot;
			}

			/**
			 * Get the zoom factor of the image.
			 * @param obj       pointer to an image object
			 * @return          zoom factor (256: no zoom)
			 */
			inline uint16_t GetZoom() {
				return lv_img_get_zoom(_obj);
			}

			/**
			 * Get whether the transformations (rotate, zoom) are anti-aliased or not
			 * @param obj       pointer to an image object
			 * @return          true: anti-aliased; false: not anti-aliased
			 */
			inline bool GetAntialias() {
				return lv_img_get_antialias(_obj);
			}

			/**
			 * Get the size mode of the image
			 * @param obj       pointer to an image object
			 * @return          element of @ref lv_img_size_mode_t
			 */
			inline lv_img_size_mode_t GetSizeMode() {
				return lv_img_get_size_mode(_obj);
			}

		};
	} /* namespace widget */
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_IMAGE_H_ */
