#include "Engine.h"

Engine::Engine()
{
    m_renderer = Renderer();
    m_input = Input();
    m_return_value = 0;
    m_run_flag = true;
    m_gui_manager = GuiManager();
    m_audio = Audio();

    m_frame_timer = Timer();
    m_frame_cap_timer = Timer();
}


Engine::~Engine()
{
    m_frame_timer.~Timer();
    m_renderer.~Renderer();
    m_gui_manager.~GuiManager();

}

void Engine::init(void)
{
    m_renderer.init(&m_gui_manager);

    if (!m_renderer.m_init_success) {
        m_return_value = -1;
    } else {
        if (!m_audio.init()) {
            m_return_value = -1;
        } else {
            m_gui_manager.init(&m_input, &m_renderer);
            m_gui_manager.set_screen(GUI_GAME);
            m_frame_timer.start();
        }
    }
}

void Engine::game_loop(void)
{
    int counted_frames = 0;
    float fps = 0.0;
    char window_text[100];

    while (m_run_flag) {
        m_frame_cap_timer.start();

        m_input.handle_input(&m_run_flag, &m_gui_manager);

        if (!m_input.m_unfocused) {
            m_renderer.clear();

            m_gui_manager.draw_gui();

            m_renderer.repaint();
        } else {
            m_input.m_unfocused = false;
        }

        { // Calculate fps
            fps = counted_frames / (m_frame_timer.get_ticks() / 1000.f);
            if (fps > 200000)
                fps = 0;
            snprintf(window_text, sizeof(window_text), "%s | %.2f FPS", CONST_WINDOW_TITLE, fps);
            SDL_SetWindowTitle(m_renderer.m_sdl_window, window_text);
            counted_frames++;
        }

        if (m_frame_cap_timer.get_ticks() < CONST_TICKS_PER_FRAME) {
            SDL_Delay(CONST_TICKS_PER_FRAME - m_frame_cap_timer.get_ticks());
        }
    }
}

void Engine::close(void)
{
    m_renderer.~Renderer();
    m_gui_manager.~GuiManager();
    m_input.~Input();
}