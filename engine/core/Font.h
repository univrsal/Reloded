#ifndef FONT_H
#define FONT_H

#include "SDL_ttf.h"
#include "SDL.h"
#include "Renderer.h"
#include <iostream>
#include <string>

#define FONT_SOLID 0
#define FONT_SHADED 1
#define FONT_BLENDED 2

#define FONT_SMALL 10
#define FONT_DEFAULT 15
#define FONT_LARGE 25

class Renderer;

class Font
{
public:
    Font(const char *path);

    ~Font();

    void set_size(int pt);

    void close(void);

    void render_text(Renderer *render, std::string *text, int x, int y);

    void render_text(Renderer *render, std::string *text, SDL_Rect *dest);

    void render_text_blended(Renderer *renderer, std::string *text, int x, int y);

    void render_text_blended(Renderer *renderer, std::string *text, int x, int y, int size);

    SDL_Rect get_text_dimension(Renderer *render, std::string *text, int siz = -1);

    void init();

    int m_size;
    int m_mode;
    bool m_was_init;
    const char *m_font_path;
    TTF_Font *m_font_instance;
    SDL_Color m_text_color;
};

#endif