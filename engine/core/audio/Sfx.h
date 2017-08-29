/**
 * Created by universallp on 14.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

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
	Sfx(uint8_t type, Audio *audio, std::string path);

    ~Sfx();

	void set_channel(uint8_t c);

    void close(void);

    void play(void);

private:
    Mix_Music *m_music;
    Mix_Chunk *m_effect;
	Audio *m_audio;
	uint8_t m_channel, m_type;
};


#endif //RELODED_SFX_H
