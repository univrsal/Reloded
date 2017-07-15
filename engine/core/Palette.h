//
// Created by universal on 13.07.17.
//

#ifndef RELODED_PALETTE_H
#define RELODED_PALETTE_H

#include "SDL.h"

class Palette
{
public:
    Palette();

    ~Palette();

    SDL_Color *get_bg(void);

    SDL_Color *get_fg(void);

    SDL_Color *get_accent(void);

    SDL_Color *get_tooltip_body(void);

    SDL_Color *white(void);

    SDL_Color *black(void);

private:
    SDL_Color m_background;
    SDL_Color m_foreground;
    SDL_Color m_accent;

    SDL_Color m_white;
    SDL_Color m_black;

    SDL_Color m_tooltip_body;
};


#endif //RELODED_PALETTE_H
