#include "SequenceEntity.h"


SequenceEntity::SequenceEntity(std::string e_ID, std::string e_tag,std::string t_tag,std::string sequenceType,std::string preSeq)
{
    entityType = "sequence";
    isActive = false;
    entity_ID = e_ID;
    entityTag = e_tag;
    trigger_tag = t_tag;
    contingentSequence = preSeq;
    if(sequenceType.compare("combat_sequence")==0)
    {
        seqType = SEQ_COMBAT;
    }
    else if(sequenceType.compare("narrative_sequence")==0)
    {
        seqType = SEQ_NARRATIVE;
    }
    deathFlag = 0;
    waveDelayCounter = 0;

}
bool SequenceEntity::getIsActive()
{
    return isActive;
}
void SequenceEntity::onSequenceBegin()
{
    if(contingentSequence.compare("")==0)
    {
        isActive = true;
        std::cout<<entityTag<<" SEQUENCE INITIATED"<<std::endl;
    }
}
void SequenceEntity::sequenceEnd()
{
    isActive = false;
    std::cout<<entityTag<<" SEQUENCE HAS ENDED"<<std::endl;
}
void SequenceEntity::addWave(spawnWave wave)
{
    spawnWaveQueue.push(wave);
}

SequenceEntity::~SequenceEntity()
{
     delete physics_component;
}

/**UPDATE FUNCTION**/
void SequenceEntity::update()
{

    switch(seqType)
    {
        case SEQ_COMBAT:
        {
           if(waveDelayCounter <=0)
           {
                int deathCount = 0;
                for(int i = 0; i<activeSpawn.size();++i)
                {
                    if(activeSpawn[i]!=nullptr)
                    {
                        activeSpawn[i]->update();
                        if(!activeSpawn[i]->isAlive())
                        {
                            activeSpawn[i]=nullptr;
                            deathCount++;
                        }
                    }
                    else
                    {
                        deathCount++;
                    }
                }
                if(deathCount>=activeSpawn.size())
                {
                    activeSpawn.clear();
                    if(!spawnWaveQueue.empty())
                    {
                        currentWave = spawnWaveQueue.front();
                        waveDelayCounter = currentWave.delay;
                        for(int i = 0;i<currentWave.spawn.size();++i)
                        {

                            if(currentWave.spawn[i].entityType.compare("actor")==0)
                            {
                                activeSpawn.push_back(static_cast<ActorEntity*>(spawner->spawnEntity(currentWave.spawn[i])));
                            }
                        }
                            spawnWaveQueue.pop();
                    }
                    else
                    {
                        sequenceEnd();
                    }
                }
                break;
            }
            else
            {
                waveDelayCounter--;
            }
        }
        case SEQ_NARRATIVE:
        break;
    }
}

void SequenceEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{

}


