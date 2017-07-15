//
// Created by universal on 14.07.17.
//

#ifndef RELODED_SFX_H
#define RELODED_SFX_H

#define SFX_EFFECT 0
#define SFX_MUSIC 1

#include <string>
#include <SDL_mixer.h>
#include "Audio.h"

class Sfx
{
public:
    Sfx(int type, std::string path);

    ~Sfx();

    void set_channel(int c);

    void close(void);

    void play(void);

private:
    Mix_Music *m_music;
    Mix_Chunk *m_effect;
    int m_channel, m_type;
};


#endif //RELODED_SFX_H
