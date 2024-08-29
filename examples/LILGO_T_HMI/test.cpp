/*
 * test1.h
 *
 *  Created on: Nov 27, 2023
 *      Author: morgoth
 */

#include <lvgl.h>
#if __IN_ECLIPSE__
#include "../../src/lvglCpp.h"
#else
#include <lvglCpp.h>
#endif
#include "dbg.h"

void uiInit() {
	static lvgl::widget::TabView tView = lvgl::widget::TabView(lv_scr_act());
	tView.addTab("Tab 1");
	tView.addTab("Tab");
	tView.addTab("Tab 3");
	tView.addTab("Tab 4");
	tView.renameTab(1, "Tab 2");

	lv_obj_t *tab2 = tView.getTabObj("Tab 2");
	lv_obj_t *tab1 = tView.getTabObj("Tab 1");
	lv_obj_t *tab3 = tView.getTabObj("Tab 3");
	lv_obj_t *tab4 = tView.getTabObj("Tab 4");
	static lvgl::widget::ButtonMatrix bMatrix = lvgl::widget::ButtonMatrix(tab2);
	static const char *btnm_map[] = {
			"1", "2", "3", "4", "5", "\n",
			"6", "7", "8", "9", "0", "\n",
			"Action1", "Action2", ""
			};
	bMatrix.setMap(btnm_map);
	bMatrix.setPos(0, 0);
	bMatrix.setVisible(false);
	if(bMatrix.getVisible())
		DBG_println("Visible");
	else
		DBG_println("Hidden");
	bMatrix.setVisible(true);
	if(bMatrix.getVisible())
		DBG_println("Visible");
	else
		DBG_println("Hidden");

	static lvgl::widget::Button button = lvgl::widget::Button(tab1, "Button %u", 1);

	static lvgl::widget::Label label = lvgl::widget::Label(tab1, "Label %u", 1);
	label.setPos(100, 0);

	static lvgl::widget::Arc arc = lvgl::widget::Arc(tab1);
	arc.setPos(210, 0);
	arc.setSize(80, 80);
	arc.setBgAngles(0, 180);
	arc.setRange(0, 360);
	arc.setValue(180);

	static lvgl::widget::Bar bar = lvgl::widget::Bar(tab1);
	bar.setPos(0, 40);
	bar.setSize(80, 20);
	bar.setRange(0, 50);
	bar.setValue(25, LV_ANIM_ON);

	static lvgl::widget::CheckBox checkBox = lvgl::widget::CheckBox(tab1);
	checkBox.setPos(100, 40);
	checkBox.setSize(110, 40);
	checkBox.setChecked(true);

	static lvgl::widget::DropDown dropDown = lvgl::widget::DropDown(tab1);
	dropDown.setPos(0, 80);
	dropDown.setSize(160, 40);
	dropDown.setOptions(""
			"Apple\n"
			"Banana\n"
			"Orange\n"
			"Cherry\n"
			"Grape\n"
			"Raspberry\n"
			"Melon\n"
			"Orange\n"
			"Lemon\n"
			"Nuts");

	LV_IMG_DECLARE(fan30);
	static lvgl::widget::Image image = lvgl::widget::Image(tab1);
	image.setPos(0, 120);
	image.setSize(30, 30);
	image.setSource(&fan30);

	static lvgl::widget::Line line = lvgl::widget::Line(tab1);
	line.setPos(40, 120);
	line.setSize(80, 40);
	line.setYInvert(true);
	static const lv_point_t points[] = {
	  {0, 20},
	  {10, 0},
	  {30, 30}
	};
	line.setPoints(points, 3);

	static lvgl::widget::Roller roller = lvgl::widget::Roller(tab1);
	roller.setPos(170, 100);
	roller.setSize(100, 85);
	roller.setOptionsInfinite(
			"January\n"
			"February\n"
			"March\n"
			"April\n"
			"May\n"
			"June\n"
			"July\n"
			"August\n"
			"September\n"
			"October\n"
			"November\n"
			"December");

  static lvgl::draw::Rectangle rect_dsc = lvgl::draw::Rectangle();
  rect_dsc.setRadius(10);
  rect_dsc.setOpacity(LV_OPA_COVER);
  rect_dsc.setGradientDirection(LV_GRAD_DIR_HOR);
  rect_dsc.setGradientStopsColor(0, lv_palette_main(LV_PALETTE_RED));
  rect_dsc.setGradientStopsColor(1, lv_palette_main(LV_PALETTE_BLUE));
  rect_dsc.setBorderWidth(2);
  rect_dsc.setBorderOpacityPercent(90);
  rect_dsc.setBorderColor(lv_color_white());
  rect_dsc.setShadowWidth(5);
  rect_dsc.setShadowOffsetX(5);
  rect_dsc.setShadowOffsetY(5);

	static uint8_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(200, 150)];
	static lvgl::widget::Canvas canvas = lvgl::widget::Canvas(tab3);
	canvas.setBuffer(cbuf, 200, 150, LV_IMG_CF_TRUE_COLOR);
	canvas.drawRectangle(70, 60, 100, 70, &rect_dsc);

	static lvgl::widget::Switch sw = lvgl::widget::Switch(tab4);
	sw.setPos(0, 0);
	sw.setSize(80, 40);
	sw.setChecked(true);

	static lvgl::widget::Table table = lvgl::widget::Table(tab4);
	table.setPos(0, 50);
	table.setSize(270, 130);
	table.setColCount(2);
	table.setRowCount(2);
	table.setCellValue(0, 0, "Row 1");
	table.setCellValue(0, 1, "Val %u", 1);
	table.setCellValue(1, 0, "Row 2");
	table.setCellValue(1, 1, "Val %u", 2);
	table.setCellValue(2, 0, "Row 3");
	table.setCellValue(2, 1, "Val %u", 3);
}
