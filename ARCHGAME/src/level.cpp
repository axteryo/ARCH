#include "level.h"
#include "EntitySpawner.h"
#include "SpriteBatcher.h"
#include "GameMap.h"
#include "SequenceEntity.h"





camera gameCamera;
CollisionSystem* collisionSystem = new CollisionSystem();
EntitySpawner* spawner = new EntitySpawner();
SpriteBatcher* batcher = new SpriteBatcher;
GameMap* _map = new GameMap;



level::level()
{
    ///Creates A spawner object for creating entites and a batcher object for assembling sprites in a vertex array
    spawner = new EntitySpawner;
    batcher = new SpriteBatcher;
    _map = new GameMap;
    entityList= {};
}

level::~level()
{
    delete spawner;
    delete batcher;
    delete _map;
}
void level::close()
{

    if(!entityList.empty())
    {
        for(int i = 0;i<entityList.size();i++)
        {
            delete entityList[i];
        }
        entityList.clear();
    }
    if(!wallList.empty())
    {
        for(int i = 0;i<wallList.size();i++)
        {
            delete wallList[i];
        }
        wallList.clear();
    }
    spawnList.clear();
    _map->close();
}
void level::setup()
{
    batcher->loadEntityTextures();
    batcher->loadAnimations();
    spawner->loadEntityData();
    spawner->loadEntityShapes();
    spawner->loadActionData();
}

/**
This function loads a specified level and retrieves and stores data
**/
void level::load(std::string levelFile)
{
    currentLevelFile.open(levelFile);
    bool parsedSuccess = levelReader.parse(currentLevelFile,baseLevelRoot,false);
    if(!parsedSuccess)
    {
        std::cout<<"failed to parse JSON"<< std::endl
        <<levelReader.getFormattedErrorMessages()
        <<std::endl;
    }
    else
    {
         std::cout<<"Level file has been parsed"<< std::endl;
        _map->loadFile("data/"+ baseLevelRoot["map"].asString());
        spawnList = _map->getSpawnSpoints();
        triggerList = _map->getTriggers();
        for(int i = 0;i<baseLevelRoot["sequences"].size();++i)
        {
            std::string sType = baseLevelRoot["sequences"][i]["type"].asString();
            std::string tTag = baseLevelRoot["sequences"][i]["trigger_tag"].asString();
            std::string sTag = baseLevelRoot["sequences"][i]["name"].asString();
            std::string preSequence = baseLevelRoot["sequences"][i]["contingentSequence"].asString();
            SequenceEntity* seq = new SequenceEntity("entity_sequence",sTag,tTag,sType,preSequence);
            if(sType.compare("combat_sequence")==0)
            {
                for(int k = 0;k<baseLevelRoot["sequences"][i]["waveList"].size();++k)
                {

                    spawnWave wave;
                    wave.delay = baseLevelRoot["sequences"][i]["waveList"][k]["waveDelay"].asInt();
                    std::vector<spawnPoint> spawn;
                    for(int l = 0;l<baseLevelRoot["sequences"][i]["waveList"][k]["spawnList"].size();++l)
                    {
                        spawnPoint sp;
                        sp.spawnID =baseLevelRoot["sequences"][i]["waveList"][k]["spawnList"][l]["entityID"].asString();
                        sp.entityType =baseLevelRoot["sequences"][i]["waveList"][k]["spawnList"][l]["entityType"].asString();
                        sp.location.x =baseLevelRoot["sequences"][i]["waveList"][k]["spawnList"][l]["x"].asFloat()/30;
                        sp.location.y =baseLevelRoot["sequences"][i]["waveList"][k]["spawnList"][l]["y"].asFloat()/30;
                        sp.rotation =baseLevelRoot["sequences"][i]["waveList"][k]["spawnList"][l]["rotation"].asFloat();
                        spawn.push_back(sp);
                    }
                    wave.spawn = spawn;
                    seq->addWave(wave);
                }
            }


            for(int m = 0; m <triggerList.size();++m)
            {
                if(triggerList[m]->getTag().compare(tTag)==0)
                {

                    sequenceList.push_back(seq);
                    triggerList[m]->addSequence(seq);
                }
            }
        }
        std::cout<<"num of sequences: "<<sequenceList.size()<<std::endl;
        wallList = _map->walls;
        std::cout<<"num of Spawn: "<<spawnList.size()<<std::endl;
    }
}
/**
This function implements the level
**/
void level::initiate()
{
     _map->create();
     for(int i = 0; i<spawnList.size();++i)
    {
        entityList.push_back(spawner->spawnEntity(spawnList[i]));
        if(entityList[i]->getID().compare("entity_player")==0)
        {
            gameCamera.setTarget(entityList[i]);
        }
    }
}


///Updates game entities by a dt variable
void level::update(float dt)
{

    for(int i = 0;i<triggerList.size();++i)
    {

        if(triggerList[i]!=nullptr)
        {
            triggerList[i]->update();
            if(triggerList[i]->getDeathFlag()>0)
            {
                triggerList[i]=nullptr;
            }
        }
    }
    if(!entityList.empty())
    {
        //std::cout<<"GOT HERE"<<std::endl;
        for(int i = 0; i<entityList.size();++i)
        {
            if(entityList[i]!=nullptr)
            {
                entityList[i]->update();
                if(entityList[i]->getDeathFlag()>0)
                {
                    entityList[i]=nullptr;
                }

            }

            //std::cout<<entityList[i]->getPosition().x/30<<","<<entityList[i]->getPosition().y<<std::endl;
        }
        gameCamera.update();
    }
    if(!sequenceList.empty())
    {
        for(int i = 0; i<sequenceList.size();++i)
        {
            if(sequenceList[i]->getIsActive())
            {
                sequenceList[i]->update();
            }
        }

    }

}

///Draws Entites along with the map
void level::render(sf::RenderWindow* window,double alpha)
{
    if(!entityList.empty())
    {
        for(int i = 0; i<entityList.size();++i)
        {
            if(entityList[i]!=nullptr)
            {

                batcher->addToBatch(entityList[i],alpha);
            }
        }
    }
    if(!sequenceList.empty())
    {
        for(int i = 0; i<sequenceList.size();++i)
        {
            //if(sequenceList[i]->getIsActive())
            //{
                for(int ii = 0; ii<sequenceList[i]->activeSpawn.size();++ii)
                {
                    if(sequenceList[i]->activeSpawn[ii]!=nullptr)
                    {
                        batcher->addToBatch(sequenceList[i]->activeSpawn[ii],alpha);
                    }

                }

            //}
        }

    }

    batcher->batchSprites();

    //window->draw(_map->getFirstLayer());
    //window->draw(_map->getSecondLayer());
    window->draw(_map->layer1);
    window->draw(_map->layer2);

    window->draw(batcher->b);



}



void level::physicsUpdate(float dt, float a)
{
    double maxStep = 0.017;
    double progress = 0.0;
    while(progress<dt)
    {
        float step = std::min((dt-progress),maxStep);
        world->Step(step,6,3);
        progress+=step;
    }

    /*
    const int maxSteps = 5;
    float32 timeStep = 1.f/60.f;
    //a = 0.0f;
    a+=dt;
    int numSteps = static_cast<int>(std::floor(a/timeStep));
    if(numSteps>0)
    {
        a -=(numSteps*timeStep);
    }
    assert (
		"Accumulator must have a value lesser than the fixed time step" &&
		a < timeStep + FLT_EPSILON
	);
    int clampedNumSteps = std::min(numSteps,maxSteps);
    //std::cout<<clampedNumSteps<<std::endl;


    for(int i = 0;i<clampedNumSteps;++i)
    {
        world->Step(timeStep,6,2);
    }
    world->ClearForces();

    PhysicsComponent* ph;
    player* p;
    GraphicsComponent* g;
    float alpha = a/timeStep;
    //update(.01f);
    if(!entityList.empty())
    {
        //std::cout<<"GOT HERE"<<std::endl;
       // for(int i = 0; i<entityList.size();++i)
        //{
            if(entityList[0]->getID().compare("entity_player")==0)
            {

                p = static_cast<player*>(entityList[0]);
                ph = p->getPhysics();
                //ph->update(.01f);
                States::positionState state = States::lerpPositionState(ph->getPreviousState(),ph->getCurrentState(),alpha);
                ph->setPosition(state.position);
                ph->setRotation(state.rotation);

            }
            //entityList[i]->update(dt);
            //std::cout<<entityList[i]->getPosition().x/30<<","<<entityList[i]->getPosition().y<<std::endl;

    }

*/
}

void level::physicsSmooth(float alpha)
{/*
    PhysicsComponent* ph;
    player* p;
    if(!entityList.empty())
    {


        //std::cout<<"GOT HERE"<<std::endl;
       for(int i = 0; i<entityList.size();++i)
        {
            if(entityList[i]->getID().compare("entity_player")==0)
            {

                p = static_cast<player*>(entityList[i]);

                ph = p->getPhysics();
                b2Vec2 cur = p->getPosition();
                b2Vec2 pre = ph->getBody()->GetPosition();
                //std::cout<<cur.x<<","<<pre.x<<std::endl;
                float curAngle = p->getRotation();
                float preAngle = ph->getBody()->GetAngle();
                cur.x = (pre.x*alpha+cur.x*(1.0f-alpha));
                cur.y = (pre.y*alpha+cur.y*(1.0f-alpha));
                curAngle = (curAngle*alpha+preAngle*(1.0f-alpha));
                p->setPosition(cur);
                p->setRotation(curAngle);

                //States::positionState state = //States::lerpPositionState(ph->getPreviousState(),ph->getCurrentState(),a);

                /////>update(.01);
            }
            //entityList[i]->update(dt);
            //std::cout<<entityList[i]->getPosition().x/30<<","<<entityList[i]->getPosition().y<<std::endl;
        }
    }*/
}


