/*
 * lv.h
 *
 *  Created on: Nov 26, 2023
 *      Author: morgoth
 */

#ifndef LVGLCPP_SRC_LVGLCPP_H_
#define LVGLCPP_SRC_LVGLCPP_H_

#include <lvgl.h>
#if(LVGL_VERSION_MAJOR != 8 && LVGL_VERSION_MINOR != 2 && LVGL_VERSION_PATCH != 10)
#error "LVGL Version must be 8.3.10"
#endif

#include "Arc.h"
#include "Bar.h"
#include "Button.h"
#include "ButtonMatrix.h"
#include "Canvas.h"
#include "CheckBox.h"
#include "DropDown.h"
#include "Image.h"
#include "Label.h"
#include "Line.h"
#include "Object.h"
#include "Roller.h"
#include "Slider.h"
#include "Switch.h"
#include "Table.h"
#include "TabView.h"
#include "TextArea.h"



#endif /* LVGLCPP_SRC_LVGLCPP_H_ */
