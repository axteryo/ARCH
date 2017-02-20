#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>


namespace States
{
   struct positionState
   {
       b2Vec2 postion;
       b2Vec2 velocity;
       b2Vec2 acceleration;
       float rotation;
   };
}

class level
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


    protected:
    private:
};

#endif // LEVEL_H
