/**
 * Created by universal on 19.07.17.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#define FONT_SOLID 0
#define FONT_SHADED 1
#define FONT_BLENDED 2

#define FONT_SMALL 10
#define FONT_DEFAULT 15
#define FONT_LARGE 25

#define FONT_ROBOTO 0
#define FONT_LODE 1

#ifndef RELODED_FONT_H
#define RELODED_FONT_H

#include "SDL_ttf.h"
#include "Renderer.h"
#include <string>

class Renderer;

class FontHelper
{
public:
    FontHelper(Renderer *renderer);

    ~FontHelper();

    void set_mode(int m);

    void draw(std::string *text, int x, int y, TTF_Font *font, SDL_Color *fg, SDL_Color *bg, int scale = 1);

    void draw(std::string *text, int x, int y, TTF_Font *font, SDL_Color *fg, int scale = 1);

    void draw(std::string *text, int x, int y, TTF_Font *font, int scale = 1);

    SDL_Rect get_text_dimension(TTF_Font *font, std::string *text, int scale = 1);

private:
    Renderer *m_renderer;
    int m_mode;
};


#endif //RELODED_FONT_H
