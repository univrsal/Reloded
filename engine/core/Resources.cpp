#include "Resources.h"

Resources::Resources()
{
	m_renderer = NULL;
	m_audio = NULL;
	m_input = NULL;
	m_layout = NULL;
	m_engine = NULL;
}

Resources::~Resources()
{
	m_engine = NULL;
	m_audio = NULL;
	m_input = NULL;
	m_renderer = NULL;
	m_layout = NULL;
}

void Resources::init(Renderer * r, Audio * a, Input * i, Layout * l, Engine* e)
{
	m_renderer = r;
	m_audio = a;
	m_input = i;
	m_layout = l;
	m_engine = e;
}

Renderer * Resources::renderer(void)
{
	return m_renderer;
}

SDL_Point * Resources::origin(void)
{
	return m_layout->get_content_origin();
}

SDL_Renderer * Resources::sdl_renderer(void)
{
	return m_renderer->m_sdl_renderer;
}

SDL_Window * Resources::window(void)
{
	return m_renderer->m_sdl_window;
}

Audio * Resources::audio(void)
{
	return m_audio;
}

Input * Resources::input(void)
{
	return m_input;
}

Layout * Resources::layout(void)
{
	return m_layout;
}

SDL_Event * Resources::input_event(void)
{
	return &m_input->m_event;
}

int * Resources::scalef(void)
{
	return m_layout->get_scale_factor();
}

Screen * Resources::active_screen(void)
{
	return m_renderer->m_gui_mgr->get_active_screen();
}

GuiManager * Resources::gui_mgr(void)
{
	return m_renderer->m_gui_mgr;
}

Palette * Resources::palette(void)
{
	return m_renderer->m_palette;
}

void Resources::set_layout(Layout * l)
{
	m_layout = l;
}
