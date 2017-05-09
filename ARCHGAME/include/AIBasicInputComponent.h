#ifndef AIBASICINPUTCOMPONENT_H
#define AIBASICINPUTCOMPONENT_H

#include <InputComponent.h>


class AIBasicInputComponent : public InputComponent
{
    public:
        AIBasicInputComponent();
        virtual ~AIBasicInputComponent();
        void processInput(ActorEntity* a);
    protected:
    private:
};

#endif // AIBASICINPUTCOMPONENT_H
