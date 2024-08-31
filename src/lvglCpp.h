/*
 * lvglCpp.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_LVGLCPP_H_
#define LVGLCPP_SRC_LVGLCPP_H_

#include <lvgl.h>
#if(LVGL_VERSION_MAJOR != 8 || LVGL_VERSION_MINOR != 4 || LVGL_VERSION_PATCH != 0)
#error "LVGL Version must be 8.4.0"
#endif

#include "draw/Arc.h"
#include "draw/Label.h"
#include "draw/Line.h"
#include "draw/Rectangle.h"

#include "widgets/Arc.h"
#include "widgets/Bar.h"
#include "widgets/Button.h"
#include "widgets/ButtonMatrix.h"
#include "widgets/Canvas.h"
#include "widgets/CheckBox.h"
#include "widgets/DropDown.h"
#include "widgets/Image.h"
#include "widgets/Label.h"
#include "widgets/Line.h"
#include "widgets/List.h"
#include "widgets/MsgBox.h"
#include "widgets/Object.h"
#include "widgets/Roller.h"
#include "widgets/Slider.h"
#include "widgets/Style.h"
#include "widgets/Switch.h"
#include "widgets/Table.h"
#include "widgets/TabView.h"
#include "widgets/TextArea.h"



#endif /* LVGLCPP_SRC_LVGLCPP_H_ */
