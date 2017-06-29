#include "SequenceEntity.h"
#include "level.h"


SequenceEntity::SequenceEntity(std::string e_ID, std::string e_tag,std::string t_tag,std::string sequenceType,std::string preSeq,GameEventListener* e)
{

    entityType = "sequence";
    isActive = false;
    entity_ID = e_ID;
    entityTag = e_tag;
    trigger_tag = t_tag;
    contingentSequence = preSeq;
    if(sequenceType.compare("COMBAT")==0)
    {
        seqType = SEQ_COMBAT;
    }
    else if(sequenceType.compare("NARRATIVE")==0)
    {
        seqType = SEQ_NARRATIVE;
    }
    deathFlag = 0;
    waveDelayCounter = 0;
    _listener = e;
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
        GameEvent_Sequence* s = new GameEvent_Sequence(this,"BEGIN");
        _listener->notifyEvent(s);
    }
}
void SequenceEntity::sequenceEnd()
{
    isActive = false;
    std::cout<<entityTag<<" SEQUENCE HAS ENDED"<<std::endl;
    GameEvent_Sequence* s = new GameEvent_Sequence(this,"END");
    _listener->notifyEvent(s);
}
void SequenceEntity::onNotifySequenceEnd(std::string tag)
{
        if(tag.compare(contingentSequence)==0)
        {
            contingentSequence = "";
            onSequenceBegin();
        }
}
void SequenceEntity::addWave(spawnWave wave)
{
    spawnWaveQueue.push(wave);

}

SequenceEntity::~SequenceEntity()
{
     delete physics_component;
     delete _listener;
}

/**UPDATE FUNCTION**/
void SequenceEntity::update()
{

    switch(seqType)
    {
        case SEQ_COMBAT:
        {
            //std::cout<<"GOT HEREEEE"<<std::endl;
           if(waveDelayCounter >=0)
           {
               waveDelayCounter--;
           }
           else
            {
                int deathCount = 0;
                for(int i = 0; i<activeSpawn.size();++i)
                {

                    if(activeSpawn[i]!=nullptr)
                    {   activeSpawn[i]->update();
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
            }
                break;
            }

        case SEQ_NARRATIVE:
            {
                sequenceEnd();
            }

        break;
    }
}

void SequenceEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{

}


