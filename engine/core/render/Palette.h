/**
 * Created by universallp on 13.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

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

    SDL_Color *gray(void);

    SDL_Color *dark_gray(void);

    SDL_Color *blue(void);

private:
    SDL_Color m_background;
    SDL_Color m_foreground;
    SDL_Color m_accent;

    SDL_Color m_white;
    SDL_Color m_black;
    SDL_Color m_gray;
    SDL_Color m_dark_gray;
    SDL_Color m_blue;

    SDL_Color m_tooltip_body;
};


#endif //RELODED_PALETTE_H
