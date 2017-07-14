#include "GameEvent_Audio.h"

GameEvent_Audio::GameEvent_Audio(std::string src, AudioState a)
{
    event_type = EVENT_AUDIO;
    source = src;
    audio_state = a;
}

GameEvent_Audio::~GameEvent_Audio()
{
    //dtor
}
