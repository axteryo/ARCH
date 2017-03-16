#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H



#include "player.h"



class playerInputComponent
{
    public:
        playerInputComponent();
        virtual ~playerInputComponent();
        void processInput(player* p);
    protected:
    private:
};

#endif // PLAYERINPUTCOMPONENT_H
