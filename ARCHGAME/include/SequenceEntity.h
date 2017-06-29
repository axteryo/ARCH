#ifndef SEQUENCEENTITY_H
#define SEQUENCEENTITY_H

#include <entity.h>
#include <queue>
#include "EntitySpawner.h"
#include "GameEvent_Sequence.h"
#include "GameEventListener.h"

struct spawnWave
{
    int delay;
    std::vector<spawnPoint> spawn;
};

//struct spawnPoint;


class SequenceEntity : public entity
{
    public:
        SequenceEntity(std::string e_ID, std::string e_tag,std::string t_tag,std::string sequenceType,std::string preSeq,GameEventListener* e);
        virtual ~SequenceEntity();
        void update();
        void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData);
        void onSequenceBegin();
        void sequenceEnd();
        void addWave(spawnWave wave);
        bool getIsActive();
        void onNotifySequenceEnd(std::string tag);

         enum sequence_type
        {
            SEQ_COMBAT,
            SEQ_NARRATIVE
        }seqType;

        spawnWave currentWave;
        std::vector<ActorEntity*> activeSpawn;
    protected:
        bool isActive;
        std::string trigger_tag;
        std::queue<spawnWave> spawnWaveQueue;
        int waveDelayCounter;
        std::string contingentSequence;
        GameEventListener* _listener;



    private:
};

#endif // SEQUENCEENTITY_H
