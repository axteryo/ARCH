#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H




class ActorEntity;
class AccelerateAction;


class InputComponent
{
    public:
        InputComponent();
        virtual ~InputComponent();
        virtual void processInput(ActorEntity* a)=0;
    protected:
    private:
};

#endif // INPUTCOMPONENT_H
