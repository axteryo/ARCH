#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

#include "player.h"
//#include "entity.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"

class EntitySpawner;
class SpriteBatcher;




class level// : public sf::Drawable, public sf::Transformable
{
    public:
        level();
        virtual ~level();

        struct spawnPoint
        {
            std::string spawnID;
            b2Vec2 location;
            float rotation;
        };
        /**
        void loadFromSave();

        void close();
        int getQuadrant();
        void draw();
        **/
        void load();
        void getSpawnPoints();
        void update(float dt);
        void render(sf::RenderWindow* window);

        std::vector<spawnPoint> spawnList;
        std::vector<entity*> entityList;


        EntitySpawner* spawner;
        SpriteBatcher* batcher;




    protected:
    private:
};

#endif // LEVEL_H
