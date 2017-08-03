#include "ListBox.h"
/**
 * Created by universallp on 02.08.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

ListBox::ListBox(int id, int x, int y, int w, int max_items, Screen* parent)
{
	std::string line = "test";
	m_item_height = parent->m_resources->renderer()->util_text_default_dim(&line).h + 2;
	m_max_items = max_items;
	
	SDL_Rect temp = { x, y, w, m_item_height * max_items + 4};
	init(parent, temp, id);
	
	m_scroll_bar = new Scrollbar(id, x + w - 12, y + 2, temp.h - 4, get_max_scroll(), parent);
	m_scroll_bar->set_bar_height(get_coverage());
	m_item_width = w - 17;
	m_mouse_over_item = -1;
	m_selected_item = 0;
}

ListBox::~ListBox()
{
	close();
}

void ListBox::draw_background(void)
{
	m_scroll_bar->draw_background();
	get_resources()->renderer()->util_draw_rect(get_dimensions(), get_resources()->palette()->dark_gray());
}

void ListBox::draw_foreground(void)
{
	m_scroll_bar->draw_foreground();
	Renderer* r = get_resources()->renderer();

	// Draw file list
	std::string temp_line;
	int list_line = 0;
	SDL_Rect item_dim;
	
	for (int i = m_scroll_bar->get_offset(); i < m_list_items.size(); i++)
	{
		temp_line = m_list_items[i];
		item_dim = get_dim_for_item(list_line);

		if (i == m_selected_item)
			r->util_fill_rect(&item_dim);

		get_resources()->util_cut_string(temp_line, m_item_width - 15);

		if (list_line == m_mouse_over_item)
			r->util_draw_rect(&item_dim, get_resources()->palette()->dark_gray());

		r->util_text_default(&temp_line, item_dim.x + 2, item_dim.y, get_resources()->palette()->black());

		list_line++;
		if (list_line >= m_max_items)
			break;
	}
}

void ListBox::handle_events(SDL_Event * e)
{
	m_scroll_bar->handle_events(e);
	if (e->type == SDL_MOUSEMOTION)
	{
		if (is_mouse_over(e->button.x, e->button.y))
		{
			m_mouse_over_item = SDL_min((e->button.y - get_dimensions()->y) / m_item_height, m_max_items);
		}
		else
		{
			m_mouse_over_item = -1;
		}
	}
	else if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (m_mouse_over_item >= 0)
		{
			if (m_selected_item == m_mouse_over_item + m_scroll_bar->get_progress())
			{
				m_parent_screen->action_performed(ACTION_LIST_ITEM_CLICKED);
			}
			else
			{
				m_selected_item = SDL_min(m_mouse_over_item + m_scroll_bar->get_progress(), m_list_items.size() - 1);
			}
		}
	}
}

void ListBox::close(void)
{
	delete m_scroll_bar;
	m_scroll_bar = NULL;
}

std::vector<std::string> ListBox::get_items(void)
{
	return m_list_items;
}

void ListBox::set_list(std::vector<std::string> items)
{
	m_list_items = items;
	m_scroll_bar->set_max(get_max_scroll());
	m_scroll_bar->set_bar_height(get_coverage());
}

void ListBox::set_pos(const int & x, const int & y)
{
	GuiElement::set_pos(x, y);
	m_scroll_bar->set_pos(x + get_dimensions()->w - 12, y + 2);
}

bool ListBox::is_empty(void)
{
	return m_list_items.empty();
}

std::string ListBox::get_selected(void)
{
	return m_list_items[get_index()];
}

uint16_t ListBox::get_index(void)
{
	return SDL_max(0, SDL_min(m_list_items.size() - 1, m_selected_item));
}

SDL_Rect ListBox::get_dim_for_item(int i)
{
	return SDL_Rect{ get_dimensions()->x + 3, get_dimensions()->y + 2 + (m_item_height * i), m_item_width, m_item_height };
}

uint16_t ListBox::get_max_scroll(void)
{
	return SDL_max(m_list_items.size() - m_max_items, 0);
}

float ListBox::get_coverage(void)
{
	return is_empty() ? 1.f : (((float) m_max_items) / m_list_items.size());
}
