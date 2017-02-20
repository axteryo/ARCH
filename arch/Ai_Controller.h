#ifndef AI_CONTROLLER_H
#define AI_CONTROLLER_H

#include "Enemy_D1.h"
#include "Observer.h"
#include "Subject.h"


class Ai_Controller : Observer
{
    public:
        Ai_Controller();
        virtual ~Ai_Controller();
        void onNotify(GameEvent e,const GameObject& gObj);
        void initiateRoutine(Enemy_D1* e);

        enum Routine
        {
            IDLE,
            DESTROY_TARGET,
            LOOK_FOR_TARGET,
            RUN_AWAY

        }Ai_Routine;
    protected:
    private:
};

#endif // AI_CONTROLLER_H
