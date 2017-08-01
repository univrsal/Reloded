#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include "SDL.h"

#define BTN_BIG 0
#define BTN_MEDIUM 1
#define BTN_MEDIUM_ACCEPT 2
#define BTN_MEDIUM_CANCEL 3
#define BTN_SMALL 4
#define BTN_SMALL_ACCEPT 5
#define BTN_SMALL_CANCEL 6
#define BTN_TINY 7
#define BTN_MICRO 8

class Resources;

class Screen;

class GuiElement
{
public:
	virtual ~GuiElement();

	virtual void draw_background(void) = 0;

    virtual void draw_foreground(void) = 0;

	virtual void close(void);

	virtual void handle_events(SDL_Event *event) = 0;

    void resize(void);

    Screen *get_parent_screen(void);

	Resources* get_resources();

    SDL_Rect *get_scaled_dimensions(void);

    SDL_Rect *get_dimensions(void);

    int get_id(void);

    void init(Screen *parent, SDL_Rect dim, int id);

    bool is_mouse_over(const int &x, const int &y);

    void set_pos(int x, int y);

protected:
    Screen *m_parent_screen;
    SDL_Rect m_dimensions;
    SDL_Rect m_scaled_dimensions;
    int m_element_id;
};

#endif