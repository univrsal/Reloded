#include "Button.h"

Button::Button(int id, int type, int x, int y, const char *texure, const char *tooltip, Screen *parent)
{
    m_type = type;
    m_bg = new Texture(texure, parent->m_renderer->m_sdl_renderer, parent->m_layout->get_scale_factor());
    m_pressed = false;
    m_tooltip_shown = false;
    m_hover_start = 0;
    SDL_Rect temp_rect;
    m_tooltip = tooltip;

    switch (type) {
        case BTN_MEDIUM:
        case BTN_MEDIUM_ACCEPT:
        case BTN_MEDIUM_CANCEL:
            temp_rect = SDL_Rect{x, y, 40, 40};
            break;
        case BTN_SMALL:
            temp_rect = SDL_Rect{x, y, 32, 32};
            break;
        case BTN_TINY:
            temp_rect = SDL_Rect{x, y, 22, 20};
            break;
        case BTN_MICRO:
            temp_rect = SDL_Rect {x, y, 15, 15};
            break;
        case BTN_BIG:
        default:
            temp_rect = SDL_Rect{x, y, 70, 67};
            break;
    }
    init(parent, temp_rect, id);
}

Button::~Button()
{
	close();
	delete m_bg;
}

void Button::draw_background(void)
{
    if (m_bg) {
        SDL_Rect cutout;

        if (m_pressed) {
            cutout = SDL_Rect{0, get_dimensions()->h, get_dimensions()->w, get_dimensions()->h};
        } else {
            cutout = SDL_Rect{0, 0, get_dimensions()->w, get_dimensions()->h};
        }
        m_bg->draw(get_parent_screen()->m_renderer->m_sdl_renderer, get_scaled_dimensions(), &cutout);

        if (!m_tooltip.empty() && m_hover_start != 0 && SDL_GetTicks() - m_hover_start > 1000) {
            if (!m_tooltip_shown) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                m_parent_screen->set_active_tooltip(&m_tooltip, x + 15, y);
                m_tooltip_shown = true;
            }
        }
    }
}


void Button::draw_foreground(void)
{

}

void Button::handle_events(SDL_Event *event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            if (is_mouse_over(event->button.x, event->button.y)) {
                if (!m_pressed)
                    get_parent_screen()->get_sfx_for_element(m_type)->play();
                m_pressed = true;
            }
        }
    } else if (event->type == SDL_MOUSEBUTTONUP) {
        if (event->button.button == SDL_BUTTON_LEFT) {

            if (m_pressed && is_mouse_over(event->button.x, event->button.y)) {
                get_parent_screen()->action_performed(m_element_id);
            }
            m_pressed = false;
        }
    } else if (event->type == SDL_MOUSEMOTION) {
        if (event->motion.state & SDL_BUTTON_LMASK) {
            if (is_mouse_over(event->button.x, event->button.y)) {
                if (!m_pressed)
                    get_parent_screen()->get_sfx_for_element(m_type)->play();
                m_pressed = true;
            }
        } else {
            m_pressed = false;
        }
    }

    if (!m_tooltip.empty() && is_mouse_over(event->button.x, event->button.y) == 1) {
        if (m_hover_start == 0) {
            m_hover_start = SDL_GetTicks();
        }
    } else {
        if (m_hover_start != 0) {
            m_hover_start = 0;
            m_parent_screen->set_active_tooltip(NULL, 0, 0);
            m_tooltip_shown = false;
        }
    }
}

void Button::close(void)
{
	m_tooltip.clear();
	m_text.clear();
	m_type = 0;
	m_hover_start = 0;
}
