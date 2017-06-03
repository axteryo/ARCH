#include "SequenceEntity.h"

SequenceEntity::SequenceEntity(std::string e_ID, std::string e_tag,std::string t_tag,std::string sequenceType)
{
    entityType = "sequence";
    entity_ID = e_ID;
    entityTag = e_tag;
    trigger_tag = t_tag;
    if(sequenceType.compare("combat_sequence")==0)
    {
        seqType = SEQ_COMBAT;
    }
    else if(sequenceType.compare("narrative_sequence")==0)
    {
        seqType = SEQ_NARRATIVE;
    }
    deathFlag = 0;

}

SequenceEntity::~SequenceEntity()
{
     delete physics_component;
}

/**UPDATE FUNCTION**/
void SequenceEntity::update()
{

}

void SequenceEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{

}


