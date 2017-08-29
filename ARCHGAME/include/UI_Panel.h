#ifndef UI_PANEL_H
#define UI_PANEL_H

#include <UI_Element.h>



class UI_Panel : public UI_Element
{
    public:
        UI_Panel(std::string i);
        virtual ~UI_Panel();

        void arrangeElementsHorizontally();
        void addChildElement(UI_Element* c);
    protected:

        std::vector<UI_Element*> childElementsList;
    private:
};

#endif // UI_PANEL_H
