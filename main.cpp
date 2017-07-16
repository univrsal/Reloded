#include "engine/core/Engine.h"

Engine engine;

void channel_finished(int channel)
{
	engine.m_audio.channel_finished(channel);
}

int main(int argc, char **argv)
{
    engine = Engine();
	Mix_ChannelFinished(channel_finished);
    engine.init();
    engine.game_loop();
    engine.close();
    return engine.m_return_value;
}
