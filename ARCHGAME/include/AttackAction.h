#ifndef ATTACKACTION_H
#define ATTACKACTION_H

#include <Action.h>
#include "StateComponent.h"
#include "ProjectileEntity.h"




struct attackData
{
    std::string name;
    std::string attackType;
    int duration;
    int coolDown;
    float rotationRate;
    std::vector<float> shape;
    b2Vec2 relPosition;
    int attackRate;
    int damage;
    float force;
    std::string impactType;
    int impactDuration;
    std::string fixtureType;
    std::string fixtureData;
    bool isSensor;
    std::string graphic;
};
class AttackAction : public Action
{
    public:
        AttackAction();
        virtual ~AttackAction();
        virtual void execute(ActorEntity* a)=0;


        virtual void setData(attackData aData);
        virtual void update(ActorEntity* a);


    protected:
        b2Fixture* attackFixture;
        attackData data;
        attackAttributeState attackState;
        bool inCoolDown;
        int rate;
        std::vector<ProjectileEntity*> projectileList;

    private:

};

#endif // ATTACKACTION_H
