#ifndef TRIGGERENTITY_H
#define TRIGGERENTITY_H

#include <entity.h>


class TriggerEntity : public entity
{
    public:
        TriggerEntity(std::string e_ID, std::string e_tag,PhysicsComponent* p);

        virtual ~TriggerEntity();
        void setPosition(b2Vec2 p);
        void setRotation(float a);
        b2Vec2 getPosition();
        float getRotation();

        void update();
        std::string getID();
        std::string getType();
        std::string getTag();

        positionState getCurrentState();
        positionState getPreviousState();

        void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData);
    protected:
    private:
        PhysicsComponent* physics_component;
};

#endif // TRIGGERENTITY_H
