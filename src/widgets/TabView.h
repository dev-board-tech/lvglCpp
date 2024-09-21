/*
 * TabView.h
 *
 *      Author: Iulian Gheorghiu
 */

#ifndef LVGLCPP_SRC_TABVIEW_H_
#define LVGLCPP_SRC_TABVIEW_H_

#include "ButtonMatrix.h"
#include "Object.h"

namespace lvgl {
	namespace widget {
		class TabView : public Object {
		public:
			TabView(lv_obj_t *parent, lv_dir_t tabPos = LV_DIR_TOP, lv_coord_t tabSize = 40) {
				_obj = lv_tabview_create(parent, tabPos, tabSize);
			}

			TabView(Object *parent, lv_dir_t tabPos = LV_DIR_TOP, lv_coord_t tabSize = 40) {
				if(parent && parent->GetObj()) {
					_obj = lv_tabview_create(parent->GetObj(), tabPos, tabSize);
				} else {
					_obj = lv_tabview_create(NULL, tabPos, tabSize);
				}
			}
			
			TabView(Object parent, lv_dir_t tabPos = LV_DIR_TOP, lv_coord_t tabSize = 40) {
				if(((Object)parent).GetObj()) {
					_obj = lv_tabview_create(((Object)parent).GetObj(), tabPos, tabSize);
				} else {
					_obj = lv_tabview_create(NULL, tabPos, tabSize);
				}
			}
			
			TabView(lv_obj_t *parent, bool isNew) {
				_obj = parent;
			}
			TabView(Object *parent, bool isNew) {
				_obj = parent->GetObj();
			}
			TabView(Object parent, bool isNew) {
				_obj = ((Object)parent).GetObj();
			}

			~TabView() {
				// TODO Auto-generated destructor stub
			}

			inline lv_obj_t *GetObj() {
				return _obj;
			}

			inline Object *AddTab(const char *name) {
				Object *tab = new Object(lv_tabview_add_tab(_obj, name), false);
				return tab;
			}

			/*inline Object *GetTabObj(const char *name) {
				int i = 0;
				for(; _childs[i] != NULL; i++);
				for(int j = 0; j < i; j++) {
					const char *txt = lv_btnmatrix_get_btn_text(lv_tabview_get_tab_btns(_obj), j);
					if(!strcmp(txt, name))
						return _childs[j];
				}
				return NULL;
			}*/



			inline TabView *RenameTab(uint32_t tab_id, const char * new_name) {
				lv_tabview_rename_tab(_obj, tab_id, new_name);
				return this;
			}
			inline Object GetContent() {
				return Object(lv_tabview_get_content(_obj), false);
			}
			inline ButtonMatrix GetTabBtns() {
				return ButtonMatrix(lv_tabview_get_tab_btns(_obj), false);
			}
			inline TabView *SetActiveTab(uint32_t id, lv_anim_enable_t anim_en) {
				lv_tabview_set_act(_obj, id, anim_en);
				return this;
			}
			inline uint16_t GetActiveTab() {
				return lv_tabview_get_tab_act(_obj);
			}
		};
	} /* namespace widget */
} /* namespace lvgl */

#endif /* LVGLCPP_SRC_TABVIEW_H_ */
