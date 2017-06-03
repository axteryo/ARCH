#include "AIBasicInputComponent.h"

AIBasicInputComponent::AIBasicInputComponent()
{
    isAlert = false;
    isAggro = false;
    target = nullptr;
    accelerate = false;
    //ctor
}

AIBasicInputComponent::~AIBasicInputComponent()
{
    //dtor
}
void AIBasicInputComponent::setTarget(entity* t)
{
    target = t;
}
void AIBasicInputComponent::setAlert()
{
    isAlert = true;
}
void AIBasicInputComponent::setAggro()
{
    isAggro = true;
}

std::string AIBasicInputComponent::steerDirection(b2Vec2 targPos, b2Vec2 selfPos,float selfRotation)
{
     b2Vec2 displacement = targPos - selfPos;
     ///Get the angle based on the vector direction toTarg
     float desiredAngle = atan2(displacement.y,displacement.x);

    float totalRotation = desiredAngle - selfRotation;

    while(totalRotation<=-3.141592){totalRotation+=2*3.141592;}//+=2*3.141592;}
    while(totalRotation>=3.141592){totalRotation-=2*3.141592;}

            if(totalRotation<-1||totalRotation>1)
            {
                accelerate = false;
            }

    if(totalRotation>.05){return "right";}
    else if(totalRotation<-.05){return "left";}
    else {return "";}

}

void AIBasicInputComponent::processInput(ActorEntity* a)
{
    if(a->isAlive())
    {
        ActionComponent* ac = a->getActions();
        std::string aim = "";
        accelerate = true;

        if(isAlert&&target!=nullptr)
        {
            aim = steerDirection(target->getPosition(),a->getPosition(),a->getRotation());
            if(accelerate){ac->performAction("accelerate",a);}
        }
        if(aim.compare("left")==0){ac->performAction("rotateLeft",a);}
        if(aim.compare("right")==0){ac->performAction("rotateRight",a);}

    }else{a->getPhysics()->getBody()->SetFixedRotation(false); a->getPhysics()->getBody()->SetAngularVelocity(4);}

}
void AIBasicInputComponent::onNotifyEntityNearby(entity* e)
{
    if(target==nullptr&&e->getID().compare("entity_player")==0)
    {
        //std::cout<<"player is nearby"<<std::endl;
        setTarget(e);
        setAlert();
    }


}
void AIBasicInputComponent::onNotifyEntityWithinRadius(entity* e)
{
    if(target==nullptr&&e->getID().compare("entity_player")==0)
    {
        setTarget(e);
        setAggro();
    }
}
void AIBasicInputComponent::onNotifyBodyCollision(entity* e)
{

}

