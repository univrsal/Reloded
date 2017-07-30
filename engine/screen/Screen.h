/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "SDL.h"
#include <string>

class Tooltip;

class Resources;

class Sfx;

class Screen
{
public:

	virtual void init(Resources* r) = 0;

    virtual void draw_background(void) = 0;

    virtual void draw_foreground(void) = 0;

    virtual void close(void) = 0;

	virtual void handle_events(void) = 0;

    virtual void action_performed(int action_id) = 0;

    virtual void set_active_tooltip(std::string *text, int x, int y) = 0;

    virtual Sfx *get_sfx_for_element(int element_type) = 0;

	Resources* m_resources;
	
	Tooltip* m_tooltip;
};

#endif