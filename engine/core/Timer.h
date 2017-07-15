/**
 * Created by universallp on 13.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

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
