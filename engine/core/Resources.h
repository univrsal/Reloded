/**
* Created by universallp on 28.07.2017.
* This file is part of reloded which is licenced
* under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
* github.com/univrsal/reloded
*/

#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL.h"
#include "render\Renderer.h"
#include "Input.h"

class Screen;

class Engine;

class GuiManager;

class Renderer;

class Audio;

class Input;

class Layout;

class Palette;

class Resources
{
public:
	Resources();
	~Resources();
	
	void init(Renderer* r, Audio* a, Input* i, Layout* l, Engine* e);
	void set_layout(Layout* l);

	SDL_Point* origin(void);
	SDL_Renderer* sdl_renderer(void);
	SDL_Window* window(void);
	SDL_Event* input_event(void);
	int* scalef(void);

	Renderer* renderer(void);
	Audio* audio(void);
	Input* input(void);
	Layout* layout(void);
	Screen* active_screen(void);
	GuiManager* gui_mgr(void);
	Palette* palette(void);

private:
	Engine* m_engine;
	Renderer* m_renderer;
	Audio* m_audio;
	Input* m_input;
	Layout* m_layout;
};

#endif