#ifndef GAMEEVENT_AUDIO_H
#define GAMEEVENT_AUDIO_H

#include <string>
#include <GameEvent.h>

enum AudioState
{
    AUDIO_START,
    AUDIO_END
};

class GameEvent_Audio : public GameEvent
{
    public:
        GameEvent_Audio(std::string src, AudioState a);
        virtual ~GameEvent_Audio();
        std::string source;
        AudioState audio_state;
    protected:
    private:
};

#endif // GAMEEVENT_AUDIO_H
