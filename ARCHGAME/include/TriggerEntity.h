#ifndef TRIGGERENTITY_H
#define TRIGGERENTITY_H

#include <entity.h>
#include "SequenceEntity.h"


class TriggerEntity : public entity
{
    public:
        TriggerEntity(std::string e_ID, std::string e_tag,PhysicsComponent* p);
        virtual ~TriggerEntity();
        void update();
        void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData);
        void initiateSequences();
        void addSequence(SequenceEntity* s);
    protected:
    private:
        PhysicsComponent* physics_component;
        std::vector<SequenceEntity*> sequenceList;
};

#endif // TRIGGERENTITY_H
