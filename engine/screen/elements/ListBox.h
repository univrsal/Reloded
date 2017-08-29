/**
 * Created by universallp on 02.08.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef LISTBOX_H
#define LISTBOX_H

#include "SDL.h"
#include "GuiElement.h"
#include "Scrollbar.h"
#include "../Screen.h"
#include <vector>
#include <string>

class Scrollbar;

class Screen;

class ListBox : public GuiElement
{
public:
	ListBox(uint8_t id, int x, int y, int w, int max_items, Screen *parent);

	~ListBox();

	void draw_background(void);

	void draw_foreground(void);

	void handle_events(SDL_Event *e);

	void close(void);

	void clear(void);

	void add(std::string item);

	std::vector<std::string> *get_list(void);

	void set_list(std::vector<std::string> items);

	void set_pos(const int &x, const int &y);

	bool is_empty(void);

	std::string get_selected(void);

	uint16_t get_index(void);

	uint16_t get_item_count(void);
private:
	void select_item(uint16_t i);

	SDL_Rect get_dim_for_item(uint16_t i);

	uint16_t get_max_scroll(void);

	float get_coverage(void);

	Scrollbar *m_scroll_bar;
	std::vector<std::string> m_list_items;

	uint8_t m_item_height;
	uint16_t m_max_items;
	uint16_t m_selected_item;
	uint16_t m_mouse_over_item;
	uint16_t m_item_width;
};

#endif // !LISTBOX_H
