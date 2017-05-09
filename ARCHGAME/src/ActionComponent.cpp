#include "ActionComponent.h"

ActionComponent::ActionComponent()
{
    //ctor
}

ActionComponent::~ActionComponent()
{
    //dtor
}

void ActionComponent::update(ActorEntity* a)
{
    for(int i = 0;i<actionList.size();i++)
    {
        if(actionList[i]->getActive())
        {
            actionList[i]->update(a);
        }
    }
}
void ActionComponent::performAction(std::string action, ActorEntity* a)
{
    for(int i = 0;i<actionList.size();i++)
    {
        if(actionList[i]->getType().compare(action)==0)
        {
            actionList[i]->execute(a);
            break;

        }
    }
}
void ActionComponent::addAction(Action* a)
{
    actionList.push_back(a);
}
