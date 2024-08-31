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
	tView.AddTab("Tab 1");
	tView.AddTab("Tab");
	tView.AddTab("Tab 3");
	tView.AddTab("Tab 4");
	tView.RenameTab(1, "Tab 2");

	lv_obj_t *tab2 = tView.GetTabObj("Tab 2");
	lv_obj_t *tab1 = tView.GetTabObj("Tab 1");
	lv_obj_t *tab3 = tView.GetTabObj("Tab 3");
	lv_obj_t *tab4 = tView.GetTabObj("Tab 4");
	static lvgl::widget::ButtonMatrix bMatrix = lvgl::widget::ButtonMatrix(tab2);
	static const char *btnm_map[] = {
			"1", "2", "3", "4", "5", "\n",
			"6", "7", "8", "9", "0", "\n",
			"Action1", "Action2", ""
			};
	bMatrix.SetMap(btnm_map);
	bMatrix.SetPos(0, 0);
	bMatrix.SetVisible(false);
	if(bMatrix.GetVisible())
		DBG_println("Visible");
	else
		DBG_println("Hidden");
	bMatrix.SetVisible(true);
	if(bMatrix.GetVisible())
		DBG_println("Visible");
	else
		DBG_println("Hidden");

	static lvgl::widget::Button button = lvgl::widget::Button(tab1, "Button %u", 1);

	static lvgl::widget::Label label = lvgl::widget::Label(tab1, "Label %u", 1);
	label.SetPos(100, 0);

	static lvgl::widget::Arc arc = lvgl::widget::Arc(tab1);
	arc.SetPos(210, 0);
	arc.SetSize(80, 80);
	arc.SetBgAngles(0, 180);
	arc.SetRange(0, 360);
	arc.SetValue(180);

	static lvgl::widget::Bar bar = lvgl::widget::Bar(tab1);
	bar.SetPos(0, 40);
	bar.SetSize(80, 20);
	bar.SetRange(0, 50);
	bar.SetValue(25, LV_ANIM_ON);

	static lvgl::widget::CheckBox checkBox = lvgl::widget::CheckBox(tab1);
	checkBox.SetPos(100, 40);
	checkBox.SetSize(110, 40);
	checkBox.SetChecked(true);

	static lvgl::widget::DropDown dropDown = lvgl::widget::DropDown(tab1);
	dropDown.SetPos(0, 80);
	dropDown.SetSize(160, 40);
	dropDown.SetOptions(""
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
	image.SetPos(0, 120);
	image.SetSize(30, 30);
	image.SetSource(&fan30);

	static lvgl::widget::Line line = lvgl::widget::Line(tab1);
	line.SetPos(40, 120);
	line.SetSize(80, 40);
	line.SetYInvert(true);
	static const lv_point_t points[] = {
	  {0, 20},
	  {10, 0},
	  {30, 30}
	};
	line.SetPoints(points, 3);

	static lvgl::widget::Roller roller = lvgl::widget::Roller(tab1);
	roller.SetPos(170, 100);
	roller.SetSize(100, 85);
	roller.SetOptionsInfinite(
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
  rect_dsc.SetRadius(10);
  rect_dsc.SetOpacity(LV_OPA_COVER);
  rect_dsc.SetGradientDirection(LV_GRAD_DIR_HOR);
  rect_dsc.SetGradientStopsColor(0, lv_palette_main(LV_PALETTE_RED));
  rect_dsc.SetGradientStopsColor(1, lv_palette_main(LV_PALETTE_BLUE));
  rect_dsc.SetBorderWidth(2);
  rect_dsc.SetBorderOpacityPercent(90);
  rect_dsc.SetBorderColor(lv_color_white());
  rect_dsc.SetShadowWidth(5);
  rect_dsc.SetShadowOffsetX(5);
  rect_dsc.SetShadowOffsetY(5);

	static uint8_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(200, 150)];
	static lvgl::widget::Canvas canvas = lvgl::widget::Canvas(tab3);
	canvas.SetBuffer(cbuf, 200, 150, LV_IMG_CF_TRUE_COLOR);
	canvas.DrawRectangle(70, 60, 100, 70, &rect_dsc);

	static lvgl::widget::Switch sw = lvgl::widget::Switch(tab4);
	sw.SetPos(0, 0);
	sw.SetSize(80, 40);
	sw.SetChecked(true);

	static lvgl::widget::Table table = lvgl::widget::Table(tab4);
	table.SetPos(0, 50);
	table.SetSize(270, 130);
	table.SetColCount(2);
	table.SetRowCount(2);
	table.SetCellValue(0, 0, "Row 1");
	table.SetCellValue(0, 1, "Val %u", 1);
	table.SetCellValue(1, 0, "Row 2");
	table.SetCellValue(1, 1, "Val %u", 2);
	table.SetCellValue(2, 0, "Row 3");
	table.SetCellValue(2, 1, "Val %u", 3);
}
