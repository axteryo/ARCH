#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>

#include "player.h"
//#include "entity.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"


class level// : public sf::Drawable, public sf::Transformable
{
    public:
        level();
        virtual ~level();
        /**
        void loadFromSave();
        void load();
        void close();
        int getQuadrant();
        void draw();
        **/
        void spawn();
        void render(sf::RenderWindow* window);
        void update(float dt);
        std::vector<entity*> spawnList;


    protected:
    private:
};

#endif // LEVEL_H
