#include "ActionComponent.h"

ActionComponent::ActionComponent()
{
    //ctor
}

ActionComponent::~ActionComponent()
{
    if(!actionList.empty())
    {
         for(int i = 0;i<actionList.size();i++)
        {
            delete actionList[i];
            actionList[i] = nullptr;
        }
    }
    actionList.clear();


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
void ActionComponent::cancelAction(std::string action)
{
    for(int i = 0;i<actionList.size();i++)
    {
        if(actionList[i]->getType().compare(action)==0)
        {
            actionList[i]->cancel();
            break;

        }
    }
}
void ActionComponent::addAction(Action* a)
{
    actionList.push_back(a);
}
