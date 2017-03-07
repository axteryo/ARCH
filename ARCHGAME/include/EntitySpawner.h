#ifndef ENTITYSPAWNER_H
#define ENTITYSPAWNER_H

#include "entity.h"
#include "level.h"



class EntitySpawner
{
    public:
        EntitySpawner();
        virtual ~EntitySpawner();

        void loadEntityShapes();
        entity* spawnEntity(level::spawnPoint s);

    protected:
    private:
};

#endif // ENTITYSPAWNER_H
