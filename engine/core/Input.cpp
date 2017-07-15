#include "Input.h"

Input::Input()
{
    m_unfocused = false;
}


Input::~Input()
{
}

void Input::handle_input(bool *run_flag, GuiManager *gui_mgr)
{
    while (SDL_PollEvent(&m_event) != 0) {
        if (m_event.type == SDL_KEYDOWN) {
            if (m_event.key.keysym.sym == SDLK_q) {
                *run_flag = false;
            } else if (m_event.key.keysym.sym == SDLK_F11) {
                bool is_fullscreen = SDL_GetWindowFlags(gui_mgr->m_renderer->m_sdl_window) & SDL_WINDOW_FULLSCREEN;
                SDL_SetWindowFullscreen(gui_mgr->m_renderer->m_sdl_window, is_fullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
            } else if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                gui_mgr->get_active_screen()->action_performed(ACTION_CANCEL);
            } else if (m_event.key.keysym.sym == SDLK_0) {
                gui_mgr->set_screen(GUI_GAME);
            } else if (m_event.key.keysym.sym == SDLK_1) {
                gui_mgr->set_screen(GUI_SP);
            }

        } else if (m_event.type == SDL_QUIT) {
            *run_flag = false;
        } else if (m_event.type == SDL_WINDOWEVENT) {
            switch (m_event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    gui_mgr->m_layout->resize();
                    gui_mgr->get_active_screen()->action_performed(ACTION_RESIZE);
                    m_unfocused = true;
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    m_unfocused = true;
                    break;
            }
        }
    }
}
