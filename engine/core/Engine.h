#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "Renderer.h"
#include "Input.h"
#include "../screen/GuiManager.h"
#include "audio/Audio.h"

class Renderer;

class Engine
{

public:
    Engine();

    ~Engine();

    void init(void);

    void close(void);

    void game_loop(void);

    Renderer m_renderer;
    Input m_input;
    Audio m_audio;
    GuiManager m_gui_manager;
    int m_return_value;
    bool m_run_flag;
private:
    Timer m_frame_timer;
    Timer m_frame_cap_timer;
};

#endif