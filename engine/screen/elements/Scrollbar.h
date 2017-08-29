/**
 * Created by universallp on 02.08.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#define SCROLL_UP 0
#define SCROLL_DOWN 1

#define SCROLL_TYPE_DIALOG 0
#define SCROLL_TYPE_INGAME 1
#include "GuiElement.h"
#include "../../screen/Screen.h"
#include "../../core/Resources.h"
#include "../../core/render/Texture.h"
#include "../../util/Textures.h"

class Texture;

class Screen;

class Scrollbar : public GuiElement
{
public:
    Scrollbar(int8_t id, int x, int y, int h, int max, uint8_t type, Screen *parent);

	~Scrollbar();

	// % of height vs the total height
	void set_bar_height(float f);

	void draw_background(void);

	void draw_foreground(void);

	void handle_events(SDL_Event *e);

	void scroll(bool dir);

	void set_max(int max);

	void start_pos(void);

	void end_pos(void);

	void set_pos(const int& x, const int& y);

    void resize(void);

    void set_progress(float f);

	float get_progress(void);

	void close(void);
	
	uint16_t get_offset(void);

    SDL_Rect *get_handle_dim(void);

    SDL_Rect *get_body_dim(void);
private:
    bool m_scroll_handle_used;
    uint8_t m_type;
    uint16_t m_scroll_handle_offset;

	SDL_Rect m_scroll_button_dim;
    SDL_Rect m_scroll_button_dim_scaled;
	uint16_t m_progress;
	uint16_t m_max_scroll;

    Texture *m_scroll_btn;
    Texture *m_scroll_body;
};

#endif