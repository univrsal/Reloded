#include "Tooltip.h"


Tooltip::Tooltip(Screen *parent_screen)
{
    m_parent_screen = parent_screen;
    m_bg_color = parent_screen->m_renderer->m_palette->get_tooltip_body();
    m_is_visible = false;
    m_line_height = 0;
}


Tooltip::~Tooltip()
{
    close();
    m_formatted_text.clear();
    m_bg_color = NULL;
    m_parent_screen = NULL;
    m_dimensions = {0, 0, 0, 0};
}

void Tooltip::draw(void)
{
    if (m_is_visible) {
        m_parent_screen->m_renderer->util_fill_rect_shadow(&m_dimensions, m_bg_color);
        int i = 0;
        for (std::vector<std::string *>::iterator it = m_formatted_text.begin(); it != m_formatted_text.end(); ++it) {
            m_parent_screen->m_renderer->util_text_default(*it, m_dimensions.x + TOOLTIP_BORDER,
                                                                m_dimensions.y + TOOLTIP_BORDER +
                                                                ((TOOLTIP_LINE_SPACE + m_line_height) * i));
            i++;
        }
    }
}

void Tooltip::set_pos(int x, int y)
{
    m_dimensions.x = x;
    m_dimensions.y = y;

    int window_w, window_h;
    SDL_GetWindowSize(m_parent_screen->m_renderer->m_sdl_window, &window_w, &window_h);

    if (m_dimensions.x + m_dimensions.w > window_w)
        m_dimensions.x = m_dimensions.x - m_dimensions.w - TOOLTIP_BORDER * 4;

    if (m_dimensions.y < 0)
        m_dimensions.y = 0;

    if (m_dimensions.y + m_dimensions.h > window_h)
        m_dimensions.y = window_h - m_dimensions.h - TOOLTIP_BORDER;
}

void Tooltip::set_text(std::string *text)
{
    if (text == NULL) {
        m_is_visible = false;
        return;
    }
    m_formatted_text.clear();

    SDL_Rect dim = {0, 0, 0, 0};
    int width = 0;
    int lines = 1;

    auto start = 0U;
    auto end = text->find(m_delmiter);
    std::string token;

    while (end != std::string::npos) {
        token = text->substr(start, end - start);
        m_formatted_text.push_back(new std::string(token));
        start = end + m_delmiter.length();
        end = text->find(m_delmiter, start);

        if (!token.empty())
            dim = m_parent_screen->m_renderer->util_text_default_dim(&token);

        if (dim.w > width)
            width = dim.w;
        lines++;
    }
    token = text->substr(start, end);
    m_formatted_text.push_back(new std::string(token));

    if (!token.empty())
        dim = m_parent_screen->m_renderer->util_text_default_dim(&token);

    if (dim.w > width)
        width = dim.w;

    m_line_height = dim.h;
    m_dimensions.h = ((dim.h + TOOLTIP_LINE_SPACE) * lines + TOOLTIP_BORDER * 2) -
                     TOOLTIP_LINE_SPACE; // Last line space doesn't count
    m_dimensions.w = width + TOOLTIP_BORDER * 2;

    m_is_visible = true;
}

void Tooltip::close(void)
{
    m_formatted_text.clear();
    m_line_height = 0;
    m_dimensions = {0, 0, 0, 0};
}
