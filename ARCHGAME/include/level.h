#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <iostream>


//#include "entity.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "player.h"
#include "camera.h"

class EntitySpawner;
class SpriteBatcher;
class GameMap;




extern camera gameCamera;





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
        void load(std::string mapFile);
        void getSpawnPoints();
        void update(float dt);
        void physicsUpdate(float dt, float a);
        void physicsSmooth(float alpha);
        void render(sf::RenderWindow* window,double alpha);

        std::vector<spawnPoint> spawnList;
        std::vector<entity*> entityList;


        EntitySpawner* spawner;
        SpriteBatcher* batcher;
        GameMap* _map;




    protected:
    private:
};

#endif // LEVEL_H
