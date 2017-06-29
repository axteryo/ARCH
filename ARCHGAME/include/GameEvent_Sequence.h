#ifndef GAMEEVENT_SEQUENCE_H
#define GAMEEVENT_SEQUENCE_H

#include <GameEvent.h>
#include "string"

class SequenceEntity;

class GameEvent_Sequence : public GameEvent
{
    public:
        GameEvent_Sequence(SequenceEntity* e,std::string seqState);
        virtual ~GameEvent_Sequence();

        SequenceEntity* sequence;

        enum SequenceState
        {
        SEQUENCE_BEGIN,
        SEQUENCE_END
        }sequenceState;

    protected:
    private:
};

#endif // GAMEEVENT_SEQUENCE_H
