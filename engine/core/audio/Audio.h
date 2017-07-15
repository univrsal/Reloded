//
// Created by universal on 14.07.17.
//

#ifndef RELODED_AUDIO_H
#define RELODED_AUDIO_H

#include "SDL_mixer.h"

#define AUDIO_SAMPLE_SIZE 2048

#define AUDIO_CHANNEL_SFX 1
#define AUDIO_CHANNEL_MUSIC 2

class Audio
{
public:
    ~Audio();

    bool init(void);

    void stop_music(void);

    void stop_sfx(void);

    void pause_music(void);

    void unpause_music(void);

    void pause_sfx(void);

    void unpause_sfx(void);
};


#endif //RELODED_AUDIO_H
