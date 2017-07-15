#include "engine/core/Engine.h"

int main(int argc, char **argv)
{
    Engine engine = Engine();

    engine.init();
    engine.game_loop();
    engine.close();
    return engine.m_return_value;
}
