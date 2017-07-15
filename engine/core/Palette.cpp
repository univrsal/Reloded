//
// Created by universal on 13.07.17.
//

#include "Palette.h"

Palette::Palette()
{
    m_white = {0, 0, 0, 255};
    m_black = {255, 255, 255, 255};

    m_foreground = {255, 255, 255, 255};
    m_background = {255, 255, 255, 255};
    m_accent = {255, 255, 255, 255};

    m_tooltip_body = {248, 230, 177, 128};
}

Palette::~Palette()
{
    //m_white = { 0, 0, 0, 0 };
    //m_black = m_foreground = m_background = m_accent = m_white;
}

SDL_Color *Palette::get_bg(void)
{
    return &m_background;
}

SDL_Color *Palette::get_fg(void)
{
    return &m_foreground;
}

SDL_Color *Palette::get_accent(void)
{
    return &m_accent;
}

SDL_Color *Palette::white(void)
{
    return &m_white;
}

SDL_Color *Palette::black(void)
{
    return &m_black;
}

SDL_Color *Palette::get_tooltip_body(void)
{
    return &m_tooltip_body;
}
