#include "EntitySpawner.h"

EntitySpawner::EntitySpawner()
{
    //ctor
}

EntitySpawner::~EntitySpawner()
{
    //dtor
}

entity* EntitySpawner::spawnEntity(level::spawnPoint s)
{
    if(s.spawnID.empty())
    {
        std::cout<<"Invalid spawnPoint provided"<<std::endl;
        return nullptr;
    }
    else
    {
        if(s.spawnID.compare("entity_player")==0)
        {

            player* p;
            PhysicsComponent* pC = new PhysicsComponent;
            b2Fixture* f;
            pC->createFixtureRectangle(f,b2Vec2(1,1),b2Vec2(0,0),"Nothing");
            p = new player(new GraphicsComponent,pC);

            p->setPosition(s.location);
            p->setRotation(s.rotation);


            return p;
        }
    }
}
