//
// Created by universal on 13.07.17.
//

#ifndef RELODED_TIMER_H
#define RELODED_TIMER_H


#include <cstdint>
#include "SDL.h"

class Timer
{
public:
    ~Timer();

    void start();

    void stop();

    void pause();

    void unpause();

    uint32_t get_ticks();

    bool is_started();

    bool is_paused();


    Timer();

private:
    uint32_t m_start_ticks;
    uint32_t m_paused_ticks;

    bool m_paused;
    bool m_started;
};


#endif //RELODED_TIMER_H
