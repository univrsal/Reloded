//
// Created by universal on 14.07.17.
//

#include "Audio.h"

bool Audio::init(void)
{
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, AUDIO_SAMPLE_SIZE)) {
        printf("SDL_Mixer failed to initialize! SDL_Mixer Error %s\n", Mix_GetError());
        return false;
    }
    Mix_AllocateChannels(2);
    return true;
}

Audio::~Audio()
{
    stop_music();
    stop_sfx();
    Mix_Quit();
}

void Audio::stop_music(void)
{
    Mix_HaltMusic();
    Mix_HaltChannel(AUDIO_CHANNEL_MUSIC);
}

void Audio::stop_sfx(void)
{
    Mix_HaltChannel(AUDIO_CHANNEL_SFX);
}

void Audio::pause_music(void)
{
    Mix_PauseMusic();
}

void Audio::unpause_music(void)
{
    Mix_ResumeMusic();
}

void Audio::pause_sfx(void)
{
    Mix_Pause(AUDIO_CHANNEL_SFX);
}

void Audio::unpause_sfx(void)
{
    Mix_Resume(AUDIO_CHANNEL_SFX);
}
