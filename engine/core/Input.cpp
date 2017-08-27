#include "Input.h"

Input::Input()
{
	m_unfocused = false;
	m_run_flag = NULL;
}

Input::~Input()
{
	m_run_flag = NULL;
}

void Input::init(bool* flag, Resources* r)
{
	m_run_flag = flag;
	m_resources = r;
}

void Input::handle_input(void)
{
    while (SDL_PollEvent(&m_event) != 0) {
        if (m_event.type == SDL_KEYDOWN) {
            if (m_event.key.keysym.sym == SDLK_q) {
				*m_run_flag = false;
            } else if (m_event.key.keysym.sym == SDLK_F11) {
				bool is_fullscreen = (bool) SDL_GetWindowFlags(m_resources->window()) & SDL_WINDOW_FULLSCREEN;
				SDL_SetWindowFullscreen(m_resources->window(), is_fullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
            } else if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                m_resources->active_screen()->action_performed(ACTION_CANCEL);
            } else if (m_event.key.keysym.sym == SDLK_0) {
				m_resources->gui_mgr()->queue_screen(GUI_GAME);
            } else if (m_event.key.keysym.sym == SDLK_1) {
				m_resources->gui_mgr()->queue_screen(GUI_SP);
            }

        } else if (m_event.type == SDL_QUIT) {
			*m_run_flag = false;
        } else if (m_event.type == SDL_WINDOWEVENT) {
            switch (m_event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    if (m_resources->gui_mgr()->m_layout != NULL)
					    m_resources->gui_mgr()->m_layout->resize();
                    if (m_resources->gui_mgr()->get_active_screen() != NULL)
					    m_resources->gui_mgr()->get_active_screen()->action_performed(ACTION_RESIZE);
                    m_unfocused = true;
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    m_unfocused = true;
                    break;
            }
        }

		if (m_resources->gui_mgr()->m_current_screen != NULL)
			m_resources->gui_mgr()->m_current_screen->handle_events();
    }
}
