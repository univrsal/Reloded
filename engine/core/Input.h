/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"
#include "../screen/GuiManager.h"
#include "../core/Resources.h"

class Resources;

class GuiManager;

class Input
{
public:
	Input();

    ~Input();

	void init(bool *flag, Resources *r);
    void handle_input(void);

    SDL_Event m_event;
	bool m_unfocused;

private:
	Resources *m_resources;
	bool *m_run_flag;
};

#endif