/**
 * Created by universallp on 26.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#include "Label.h"

Label::Label(int8_t id, int x, int y, uint8_t type, const char *text, Screen *parent)
{
    m_dimensions = SDL_Rect {x, y, 0, 0};
    m_text = std::string(text);
    m_parent_screen = parent;
    m_element_id = id;
	m_shadow = false;
    switch (type) {
        default:
        case LABEL_GOLD:
            m_color = parent->m_resources->palette()->get_accent();
            break;
        case LABEL_TITLE:
            m_color = parent->m_resources->palette()->black();
            break;
		case LABEL_DEFAULT:
		case LABEL_WHITE_SHADOW:
			m_shadow = true;
        case LABEL_WHITE:
            m_color = parent->m_resources->palette()->white();
            break;
    }

	m_type = type;
}

Label::~Label()
{
    close();
    m_text.clear();
}

void Label::close(void)
{
}

void Label::draw_background(void)
{
	SDL_Point *o = get_parent_screen()->m_resources->origin();
    int scale = *get_parent_screen()->m_resources->scalef();

	if (!m_text.empty())
	{
		if (m_type == LABEL_DEFAULT)
		{
			get_resources()->renderer()->util_text_default(&m_text, o->x + m_dimensions.x * scale,
														   o->y + m_dimensions.y  * scale, m_color);
		}
		else
		{
			if (!m_shadow)
			{
				get_resources()->renderer()->util_text_lode(&m_text, o->x + m_dimensions.x * scale,
															o->y + m_dimensions.y * scale,
															m_color);
			}
			else
			{
				get_resources()->renderer()->util_text_lode_shadow(&m_text, o->x + m_dimensions.x * scale,
																   o->y + m_dimensions.y * scale,
																   m_color);
			}
		}
	}
}

void Label::handle_events(SDL_Event *event)
{

}

void Label::draw_foreground(void)
{

}

void Label::set_text(std::string text)
{
    m_text = text;
}
