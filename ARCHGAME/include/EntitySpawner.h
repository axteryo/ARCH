#ifndef ENTITYSPAWNER_H
#define ENTITYSPAWNER_H

#include "entity.h"
#include "ActorEntity.h"
#include "level.h"
#include "SpriteBatcher.h"



class EntitySpawner
{
    public:
        EntitySpawner();
        virtual ~EntitySpawner();

        void loadEntityShapes();
        void loadEntityData();
        void loadActionData();

        entity* spawnEntity(spawnPoint s);

    protected:
    private:
        Json::Value dataRoot;
        Json::Reader dataReader;
        std::ifstream dataFile;

        Json::Value shapeRoot;
        Json::Reader shapeReader;
        std::ifstream shapeFile;

        Json::Value actionDataRoot;
        Json::Reader actionDataReader;
        std::ifstream actionDataFile;
};

#endif // ENTITYSPAWNER_H
