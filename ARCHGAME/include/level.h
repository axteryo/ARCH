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
#include "ObjectEntity.h"

class EntitySpawner;
class SpriteBatcher;
class GameMap;




extern camera gameCamera;

struct spawnPoint
    {
        std::string spawnID;
        std::string entityType;
        b2Vec2 location;
        float rotation;
    };



class level// : public sf::Drawable, public sf::Transformable
{
    public:
        level();
        virtual ~level();


        /**
        void loadFromSave();

        void close();
        int getQuadrant();
        void draw();
        **/
        void setup();
        void load(std::string mapFile);
        void getSpawnPoints();
        void update(float dt);
        void physicsUpdate(float dt, float a);
        void physicsSmooth(float alpha);
        void render(sf::RenderWindow* window,double alpha);

        std::vector<spawnPoint> spawnList;
        std::vector<entity*> entityList;
        std::vector<ObjectEntity*> wallList;


        EntitySpawner* spawner;
        SpriteBatcher* batcher;
        GameMap* _map;




    protected:
    private:
};

#endif // LEVEL_H
