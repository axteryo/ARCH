#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <UI_Element.h>


class UI_Button : public UI_Element
{
    public:
        UI_Button(std::string i);
        virtual ~UI_Button();
        void update();
        void onControlOver();
        void onControlOverNot();
        void onControlPress();
        void onControlRelease();
    protected:
    private:
};

#endif // UI_BUTTON_H
