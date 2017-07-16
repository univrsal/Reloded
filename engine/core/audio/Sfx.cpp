//
// Created by universal on 14.07.17.
//

#include "Sfx.h"


Sfx::Sfx(int type, Audio* audio, std::string path)
{
    m_music = NULL;
    m_effect = NULL;
	m_audio = audio;
    m_type = type;
    switch (type) {
        default:
        case SFX_EFFECT:
            m_effect = Mix_LoadWAV(path.c_str());
            m_channel = AUDIO_CHANNEL_SFX;
            break;
        case SFX_MUSIC:
            m_channel = AUDIO_CHANNEL_MUSIC;
            m_music = Mix_LoadMUS(path.c_str());
    }
}


Sfx::~Sfx()
{
    close();
    m_music = NULL;
    m_effect = NULL;
}

void Sfx::set_channel(int c)
{
    m_channel = c;
}

void Sfx::play(void)
{
    switch (m_type) {
        default:
        case SFX_EFFECT:
            Mix_PlayChannel(m_channel, m_effect, 0);
			m_audio->m_channel_sfx_finished = false;
            break;
        case SFX_MUSIC:
            Mix_PlayMusic(m_music, 0);
			break;
    }
}

void Sfx::close(void)
{
    if (m_music) {
        Mix_FreeMusic(m_music);

    } else if (m_effect) {
        Mix_FreeChunk(m_effect);
    }
    m_type = 0;
    m_channel = 0;
}
