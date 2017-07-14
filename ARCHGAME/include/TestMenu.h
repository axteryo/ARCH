#ifndef TESTMENU_H
#define TESTMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <TGUI/TGUI.hpp>

class TestMenu
{
    public:
        TestMenu(sf::RenderWindow* w);
        virtual ~TestMenu();

        tgui::Gui testGui;
    protected:
    private:
};

#endif // TESTMENU_H
