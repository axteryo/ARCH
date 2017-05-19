#include "AIBasicInputComponent.h"

AIBasicInputComponent::AIBasicInputComponent()
{
    isAlert = false;
    isAggro = false;
    target = nullptr;
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

void AIBasicInputComponent::processInput(ActorEntity* a)
{
        ActionComponent* ac = a->getActions();
        bool accelerate = true;
        if(isAlert&&target!=nullptr)
        {

            b2Vec2 targetPos = target->getPosition();
            b2Vec2 displacement = targetPos - a->getPosition();

            ///Get the angle based on the vector direction toTarg
            float desiredAngle = atan2(displacement.y,displacement.x);

            float totalRotation = desiredAngle - a->getRotation();



            while(totalRotation<=-3.141592){totalRotation+=2*3.141592;}//+=2*3.141592;}
            while(totalRotation>=3.141592){totalRotation-=2*3.141592;}//totalRotation-=2*3.141592;}
            if(totalRotation>.1){ac->performAction("rotateRight",a);}
            else if(totalRotation<-.1){ac->performAction("rotateLeft",a);}
            else {a->setRotation(desiredAngle);}

            if(totalRotation<-1||totalRotation>1)
            {
                accelerate = false;
            }

        }
        if(accelerate){ac->performAction("accelerate",a);}


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
