#include "Subject.h"

Subject::Subject()
{

}

Subject::~Subject()
{
    //dtor
}
/*
void Subject::addObserver(Observer* o)
{
    observerList.push_back(o);
}
void Subject::removeObserver(Observer* o)
{

}
void Subject::notify(Observer::GameEvent e,const GameObject& gObj)
{
    if(!observerList.empty())
    {
        for(int i = 0;i<observerList.size();i++)
        {
            observerList[i]->onNotify(e,gObj);
        }
    }
}
*/
