#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <iostream>


//#include "entity.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "camera.h"
#include "ObjectEntity.h"
#include "TriggerEntity.h"
#include "CollisionSystem.h"
#include "SequenceEntity.h"

class EntitySpawner;
class SpriteBatcher;
class GameMap;




extern camera gameCamera;
extern CollisionSystem* collisionSystem;


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
        int getQuadrant();
        **/
        void setup();
        void load(std::string levelFile);
        void initiate();
        void close();
        void getSpawnPoints();
        void update(float dt);
        void physicsUpdate(float dt, float a);
        void physicsSmooth(float alpha);
        void render(sf::RenderWindow* window,double alpha);

        std::vector<spawnPoint> spawnList;
        std::vector<entity*> entityList;
        std::vector<TriggerEntity*> triggerList;
        std::vector<SequenceEntity*> sequenceList;
        std::vector<ObjectEntity*> wallList;


        EntitySpawner* spawner;
        SpriteBatcher* batcher;
        GameMap* _map;




    protected:
    private:

        Json::Value baseLevelRoot;
        Json::Reader levelReader;
        std::ifstream currentLevelFile;
};

#endif // LEVEL_H
