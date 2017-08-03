/**
 * Created by universallp on 02.08.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#include "Scrollbar.h"

Scrollbar::Scrollbar(int id, int x, int y, int h, int max, Screen *parent)
{
	SDL_Rect temp_rect = { x, y, 10, h };
	m_scroll_button_dim = { x, y, 10, 0 };
	init(parent, temp_rect, id);
	set_bar_height(0.5f);
	m_progress = 0;
	m_max_scroll = max;
}

Scrollbar::~Scrollbar()
{
	close();
}

void Scrollbar::set_bar_height(float f)
{
	m_scroll_button_dim.h = m_dimensions.h * f;
}

void Scrollbar::draw_background(void)
{
	get_resources()->renderer()->util_fill_rect(get_dimensions(), get_resources()->palette()->gray());
}

void Scrollbar::draw_foreground(void)
{
	get_resources()->renderer()->util_fill_rect(&m_scroll_button_dim, get_resources()->palette()->dark_gray());
}

void Scrollbar::handle_events(SDL_Event *e)
{
	if (e->type == SDL_MOUSEWHEEL)
	{
		if (e->wheel.y > 0)
		{
			scroll(SCROLL_UP);
		}
		else
		{
			scroll(SCROLL_DOWN);
		}
	}
}

void Scrollbar::scroll(bool dir)
{
	if (dir)
	{
		m_progress = SDL_min(m_max_scroll, m_progress + 1);
	}
	else
	{
		m_progress = SDL_max(0, m_progress - 1);
	}
	m_scroll_button_dim.y = get_dimensions()->y + (get_dimensions()->h - m_scroll_button_dim.h) * get_progress();
}

void Scrollbar::set_max(int max)
{
	m_max_scroll = max;
}

void Scrollbar::set_pos(const int & x, const int & y)
{
	GuiElement::set_pos(x, y);
	m_scroll_button_dim.x = x;
	m_scroll_button_dim.y = y + get_offset();
}

float Scrollbar::get_progress(void)
{
	return ((float) m_progress) / m_max_scroll;
}

void Scrollbar::close(void)
{
	m_scroll_button_dim = {};
}

int Scrollbar::get_offset(void)
{
	return m_progress;
}
