#include "Input.h"

Input::Input()
{
    m_unfocused = false;
}


Input::~Input()
{
}

void Input::handle_input(bool *run_flag, Resources* r)
{
    while (SDL_PollEvent(&m_event) != 0) {
        if (m_event.type == SDL_KEYDOWN) {
            if (m_event.key.keysym.sym == SDLK_q) {
                *run_flag = false;
            } else if (m_event.key.keysym.sym == SDLK_F11) {
                bool is_fullscreen = SDL_GetWindowFlags(r->window()) & SDL_WINDOW_FULLSCREEN;
                SDL_SetWindowFullscreen(r->window(), is_fullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
            } else if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                r->active_screen()->action_performed(ACTION_CANCEL);
            } else if (m_event.key.keysym.sym == SDLK_0) {
				r->gui_mgr()->queue_screen(GUI_GAME);
            } else if (m_event.key.keysym.sym == SDLK_1) {
                r->gui_mgr()->queue_screen(GUI_SP);
            }

        } else if (m_event.type == SDL_QUIT) {
            *run_flag = false;
        } else if (m_event.type == SDL_WINDOWEVENT) {
            switch (m_event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    r->gui_mgr()->m_layout->resize();
					r->gui_mgr()->get_active_screen()->action_performed(ACTION_RESIZE);
                    m_unfocused = true;
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    m_unfocused = true;
                    break;
            }
        }

        if (r->gui_mgr()->m_current_screen != NULL)
			r->gui_mgr()->m_current_screen->handle_events();
    }
}
