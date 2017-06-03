#ifndef ACTIONCOMPONENT_H
#define ACTIONCOMPONENT_H

#include "ActorEntity.h"
#include "AccelerateAction.h"
#include "BrakeAction.h"
#include "RotateLeftAction.h"
#include "RotateRightAction.h"
#include "BoostAction.h"
#include "DeccelerateAction.h"
#include "BeamAttackAction.h"
#include "RadiusAttackAction.h"
#include "GridModeAttack.h"




class ActionComponent
{
    public:
        ActionComponent();
        virtual ~ActionComponent();
        void update(ActorEntity* a);
        void performAction(std::string action,ActorEntity* a);
        void cancelAction(std::string action);
        void addAction(Action* a);
        void removeAction(std::string action);
    protected:
    private:
        std::vector<Action*> actionList;


};

#endif // ACTIONCOMPONENT_H
