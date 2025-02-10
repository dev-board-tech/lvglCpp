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

			lv_obj_t * lv_tabview_insert_tab(lv_obj_t * obj, const char * name, int idx, Object *_page = NULL)
			{
				LV_ASSERT_OBJ(obj, MY_CLASS);
				lv_tabview_t * tabview = (lv_tabview_t *)obj;
				lv_obj_t * cont = lv_tabview_get_content(obj);

				lv_obj_t * page;
				if(!_page) {
					page = lv_obj_create(cont);
				} else {
					page = _page->GetObj();
					cont->spec_attr->child_cnt++;
				}
				lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
				lv_obj_clear_flag(page, LV_OBJ_FLAG_CLICK_FOCUSABLE);
				uint32_t tab_id = lv_obj_get_child_cnt(cont);

				lv_obj_t * btns = lv_tabview_get_tab_btns(obj);

				const char ** old_map = (const char **)tabview->map;
				const char ** new_map;

				/*top or bottom dir*/
				if(tabview->tab_pos & LV_DIR_VER) {
					new_map = (const char**)lv_mem_alloc((tab_id + 1) * sizeof(const char *));
					lv_memcpy_small(new_map, old_map, sizeof(const char *) * (tab_id - 1));
					if(tabview->tab_cnt == 0) {
						new_map[tab_id - 1] = (const char*)lv_mem_alloc(strlen(name) + 1);
						strcpy((char *)new_map[tab_id - 1], name);
						new_map[tab_id] = "";
						if(_page) {
							cont->spec_attr->children[tab_id - 1] = page;
							lv_event_send(cont, LV_EVENT_CHILD_DELETED, page);
						}
					} else {
						int i = tab_id;
						//lv_obj_t * child = lv_obj_get_child(cont, i - 1);
						for(; i > idx + 1; i--) {
							new_map[i - 1] = new_map[i - 2];
							cont->spec_attr->children[i - 1] = cont->spec_attr->children[i - 2];
							lv_event_send(cont, LV_EVENT_CHILD_DELETED, cont->spec_attr->children[i - 1]);
						}
						cont->spec_attr->children[idx] = page;
						lv_event_send(cont, LV_EVENT_CHILD_DELETED, page);
						new_map[idx] = (const char*)lv_mem_alloc(strlen(name) + 1);
						strcpy((char *)new_map[idx], name);
						new_map[tab_id] = "";
						Serial.println(name);
					}
				}
				/*left or right dir*/
				else {
					new_map = (const char**)lv_mem_alloc((tab_id * 2) * sizeof(const char *));
					lv_memcpy_small(new_map, old_map, sizeof(const char *) * (tab_id - 1) * 2);
					if(tabview->tab_cnt == 0) {
						new_map[0] = (const char*)lv_mem_alloc(strlen(name) + 1);
						strcpy((char *)new_map[0], name);
						new_map[1] = "";
					} else {
						// Move from idx to end to the right
						int i = tab_id;
						for(; i > idx; i--) {
						new_map[i * 2 + 1] = new_map[(i - 1) * 2 + 1];
						new_map[i * 2 + 0] = new_map[(i - 1) * 2 + 0];
					}
					new_map[i * 2 + 1] = "\n";
					new_map[i * 2 + 0] = (const char*)lv_mem_alloc(strlen(name) + 1);
					strcpy((char *)new_map[(i * 2) + 1], name);
					}
				}
				tabview->map = new_map;
				lv_btnmatrix_set_map(btns, (const char **)new_map);
				lv_mem_free(old_map);

				lv_btnmatrix_set_btn_ctrl_all(btns, LV_BTNMATRIX_CTRL_CHECKABLE | LV_BTNMATRIX_CTRL_CLICK_TRIG |
				LV_BTNMATRIX_CTRL_NO_REPEAT);

				tabview->tab_cnt++;
				if(tabview->tab_cnt == 1) {
					lv_tabview_set_act(obj, 0, LV_ANIM_OFF);
				}
				lv_btnmatrix_set_btn_ctrl(btns, tabview->tab_cur, LV_BTNMATRIX_CTRL_CHECKED);
				return page;
			}


			inline Object *AddTab(const char *name, int idx = -1, Object *_page = NULL) {
				//LV_ASSERT_OBJ(_obj, MY_CLASS);
				lv_obj_t * cont = lv_tabview_get_content(_obj);
				uint32_t tab_id = lv_obj_get_child_cnt(cont);
				if(idx < 0 || idx > tab_id || (idx == tab_id && _page == NULL) || tab_id == 0) {
					Object *tab = new Object(lv_tabview_add_tab(_obj, name), false);
					return tab;
				}
				if(idx < 0 || idx > tab_id) {
					idx = tab_id;
				}
				Object *tab = new Object(lv_tabview_insert_tab(_obj, name, idx, _page), false);
				return tab;
			} 

			lv_obj_t * lv_tabview_remove_tab(lv_obj_t * obj, int idx) {
				LV_ASSERT_OBJ(obj, MY_CLASS);
				lv_tabview_t * tabview = (lv_tabview_t *)obj;
				lv_obj_t * cont = lv_tabview_get_content(obj);

				lv_obj_t * page;
				uint32_t tab_id = lv_obj_get_child_cnt(cont);

				lv_obj_t * btns = lv_tabview_get_tab_btns(obj);

				const char ** old_map = (const char **)tabview->map;
				const char ** new_map;

				/*top or bottom dir*/
				if(tabview->tab_pos & LV_DIR_VER) {
					page = cont->spec_attr->children[idx];
					new_map = (const char**)lv_mem_alloc((tab_id) * sizeof(const char *));
					lv_memcpy_small(new_map, old_map, sizeof(const char *) * (tab_id));
					int i = idx;
					for(; i < tab_id - 1; i++) {
						new_map[i] = new_map[i + 1];
						lv_event_send(cont, LV_EVENT_CHILD_DELETED, cont->spec_attr->children[i]);
						cont->spec_attr->children[i] = cont->spec_attr->children[i + 1];
					}
					lv_event_send(cont, LV_EVENT_CHILD_DELETED, cont->spec_attr->children[i]);
					new_map[i] = "";
				}
				/*left or right dir*/
				else {
					page = cont->spec_attr->children[idx * 2];
					new_map = (const char**)lv_mem_alloc((tab_id * 2) * sizeof(const char *));
					lv_memcpy_small(new_map, old_map, sizeof(const char *) * (tab_id) * 2);
					// Move from idx to end to the right
					int i = idx;
					for(; i < tab_id - 1; i++) {
						lv_event_send(cont, LV_EVENT_CHILD_DELETED, cont->spec_attr->children[i * 2]);
						new_map[i * 2] = new_map[(i + 1) * 2];
					}
					lv_event_send(cont, LV_EVENT_CHILD_DELETED, cont->spec_attr->children[i * 2]);
					new_map[i * 2 + 1] = "";
				}
				tabview->map = new_map;
				lv_btnmatrix_set_map(btns, (const char **)new_map);
				lv_mem_free(old_map);

				lv_btnmatrix_set_btn_ctrl_all(btns, LV_BTNMATRIX_CTRL_CHECKABLE | LV_BTNMATRIX_CTRL_CLICK_TRIG |
				LV_BTNMATRIX_CTRL_NO_REPEAT);

				tabview->tab_cnt--;
				cont->spec_attr->child_cnt--;
				if(tabview->tab_cnt == 1) {
					lv_tabview_set_act(obj, 0, LV_ANIM_OFF);
				}

				lv_btnmatrix_set_btn_ctrl(btns, tabview->tab_cur, LV_BTNMATRIX_CTRL_CHECKED);

				return page;
			}
			
			inline Object *RemoveTab(int idx) {
				Object *tab = new Object(lv_tabview_remove_tab(_obj, idx), false);
				return tab;
			}

			void lv_tabview_swap_tabs(lv_obj_t * obj, int idx1, int idx2) {
				LV_ASSERT_OBJ(obj, MY_CLASS);
				lv_tabview_t * tabview = (lv_tabview_t *)obj;
				lv_obj_t * cont = lv_tabview_get_content(obj);

				uint32_t tab_id = lv_obj_get_child_cnt(cont);

				lv_obj_t * btns = lv_tabview_get_tab_btns(obj);

				const char ** map = (const char **)tabview->map;

				if(tabview->tab_pos & LV_DIR_VER) {
					const char *s = map[idx1];
					map[idx1] = map[idx2];
					map[idx2] = s;
					lv_obj_t * page = cont->spec_attr->children[idx1];
					cont->spec_attr->children[idx1] = cont->spec_attr->children[idx2];
					cont->spec_attr->children[idx2] = page;
					lv_event_send(cont, LV_EVENT_CHILD_DELETED, cont->spec_attr->children[idx1]);
					lv_event_send(cont, LV_EVENT_CHILD_DELETED, cont->spec_attr->children[idx2]);
				} else {
					const char *s = map[idx1 * 2];
					map[idx1 * 2] = map[idx2 * 2];
					map[idx2 * 2] = s;
					lv_obj_t * page = cont->spec_attr->children[idx1];
					cont->spec_attr->children[idx1] = cont->spec_attr->children[idx2];
					cont->spec_attr->children[idx2] = page;
					lv_event_send(cont, LV_EVENT_CHILD_DELETED, cont->spec_attr->children[idx1]);
					lv_event_send(cont, LV_EVENT_CHILD_DELETED, cont->spec_attr->children[idx2]);
				}
			}

			inline Object *SwapTabs(int idx1, int idx2) {
				lv_tabview_swap_tabs(_obj, idx1, idx2);
				return this;
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



			inline Object *AddFlag(lv_obj_flag_t f) {
				lv_obj_add_flag(lv_tabview_get_content(_obj), f);
				return this;
			}

			inline Object *ClearFlag(lv_obj_flag_t f) {
				lv_obj_clear_flag(lv_tabview_get_content(_obj), f);
				return this;
			}

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
