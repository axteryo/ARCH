#include "GameEvent_Sequence.h"
#include "SequenceEntity.h"

GameEvent_Sequence::GameEvent_Sequence(SequenceEntity* e,std::string seqState)
{
    event_type = EVENT_SEQUENCE;
    sequence = e;
    if(seqState.compare("BEGIN")==0)
    {
        sequenceState = SEQUENCE_BEGIN;
    }
    else if(seqState.compare("END")==0)
    {
        sequenceState = SEQUENCE_END;
    }
}

GameEvent_Sequence::~GameEvent_Sequence()
{
    //dtor
}
