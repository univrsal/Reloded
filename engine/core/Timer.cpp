//
// Created by universal on 13.07.17.
//

#include "Timer.h"

Timer::Timer()
{

}

void Timer::start()
{
    m_started = true;
    m_paused = false;

    m_start_ticks = SDL_GetTicks();
}

void Timer::stop()
{
    m_started = false;
    m_paused = false;
    m_start_ticks = 0;
    m_paused_ticks = 0;
}

void Timer::pause()
{
    if (m_started && !m_paused) {
        m_paused = true;
        m_paused_ticks = SDL_GetTicks() - m_start_ticks;
    }
}

void Timer::unpause()
{
    if (m_started && m_paused) {
        m_paused = false;
        m_start_ticks = SDL_GetTicks() - m_paused_ticks;
        m_paused_ticks = 0;
    }
}

uint32_t Timer::get_ticks()
{
	uint32_t time = 0;

    if (m_started) {

        if (m_paused) {
            time = m_paused_ticks;
        } else {
            time = SDL_GetTicks() - m_start_ticks;
        }
    }

    return time;
}

bool Timer::is_started()
{
    return m_started;
}

bool Timer::is_paused()
{
    return m_paused && m_started;
}

Timer::~Timer()
{
    m_paused_ticks = 0;
    m_start_ticks = 0;
}
