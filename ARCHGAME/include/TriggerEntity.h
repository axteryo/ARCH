#ifndef TRIGGERENTITY_H
#define TRIGGERENTITY_H

#include <entity.h>

class SequenceEntity;


class TriggerEntity : public entity
{
    public:
        TriggerEntity(std::string e_ID, std::string e_tag,PhysicsComponent* p);
        virtual ~TriggerEntity();
        void update();
        void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData);
        void sequenceBegin();
        void addSequence(SequenceEntity* s);
    protected:
    private:
        PhysicsComponent* physics_component;
        std::vector<SequenceEntity*> sequenceList;
};

#endif // TRIGGERENTITY_H
