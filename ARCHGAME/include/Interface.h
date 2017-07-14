#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


class Interface
{
    public:
        Interface();
        virtual ~Interface();
        //void run(GameState* gameState);
        void processInput(sf::RenderWindow* window);
    protected:
    private:
};

#endif // INTERFACE_H
