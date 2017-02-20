#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"



class Subject
{
    public:
        Subject();
        virtual ~Subject();
        /*void addObserver(Observer* o);
        void removeObserver(Observer* o);
        void notify(Observer::GameEvent e,const GameObject& gObj);*/
        //std::vector<Observer*> observerList;

    protected:
    private:
};

#endif // SUBJECT_H
