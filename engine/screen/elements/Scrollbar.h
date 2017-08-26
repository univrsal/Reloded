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

#include "GuiElement.h"
#include "../../core/Resources.h"

class Scrollbar : public GuiElement
{
public:
	Scrollbar(int8_t id, int x, int y, int h, int max, Screen *parent);

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

	float get_progress(void);

	void close(void);
	
	uint16_t get_offset(void);

private:
	SDL_Rect m_scroll_button_dim;
	uint16_t m_progress;
	uint16_t m_max_scroll;
};

#endif