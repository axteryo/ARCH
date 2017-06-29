#include "EntitySpawner.h"
#include "level.h"

EntitySpawner::EntitySpawner()
{
    //ctor
}

EntitySpawner::~EntitySpawner()
{
    //dtor
}
void EntitySpawner::loadEntityShapes()
{
    shapeFile.open("data/shapes.json");
    bool parsedSuccess = shapeReader.parse(shapeFile,shapeRoot,false);
    if(!parsedSuccess)
    {
         std::cout<<"failed to parse JSON"<< std::endl
            <<shapeReader.getFormattedErrorMessages()<<std::endl;

    }
    shapeFile.close();

}
void EntitySpawner::loadEntityData()
{
    dataFile.open("data/entityData.json");
    bool parsedSuccess = dataReader.parse(dataFile,dataRoot,false);
    if(!parsedSuccess)
    {
         std::cout<<"failed to parse JSON"<< std::endl
            <<dataReader.getFormattedErrorMessages()<<std::endl;

    }
    dataFile.close();
}

void EntitySpawner::loadActionData()
{
    actionDataFile.open("data/attackData.json");
    bool parsedSuccess = dataReader.parse(actionDataFile,actionDataRoot,false);
    if(!parsedSuccess)
    {
         std::cout<<"failed to parse JSON"<< std::endl
            <<dataReader.getFormattedErrorMessages()<<std::endl;
    }
    actionDataFile.close();
}


entity* EntitySpawner::spawnEntity(spawnPoint s)
{
    if(s.spawnID.empty())
    {
        std::cout<<"Invalid spawnPoint provided"<<std::endl;
        return nullptr;
    }
    else
    {
        if(s.entityType.compare("actor")==0)
        {
            for(int i = 0;i<dataRoot["actor"].size();++i)
            {
                if(dataRoot["actor"][i]["entity_ID"].asString().compare(s.spawnID)==0)
                {
                    ActorEntity* a;
                    InputComponent* ic;
                    StateComponent* states = new StateComponent;
                    PhysicsComponent* p = new PhysicsComponent(b2_dynamicBody);
                    GraphicsComponent* g = new GraphicsComponent;

                    ///Setup the input component
                    if(s.spawnID.compare("entity_player")==0)
                    {
                        ic = new playerInputComponent;
                    }
                    else
                    {
                        ic = new AIBasicInputComponent;
                    }

                    ///Setup the state component
                    movementAttributeState m = states->getMovementAttributeState();
                    m.accelRate = dataRoot["actor"][i]["MovementAttributes"]["accelRate"].asFloat();
                    m.accelRateLimit= dataRoot["actor"][i]["MovementAttributes"]["accelRateLimit"].asFloat();
                    m.velLimit= dataRoot["actor"][i]["MovementAttributes"]["velLimit"].asFloat();
                    m.brakeLimit = dataRoot["actor"][i]["MovementAttributes"]["brakeLimit"].asFloat();
                    m.rotationRate= dataRoot["actor"][i]["MovementAttributes"]["rotationRate"].asFloat();
                    m.accel_rotationRate = dataRoot["actor"][i]["MovementAttributes"]["accel_rotationRate"].asFloat();
                    m.accel = 0;
                    m.isRotating = false;
                    m.isAccelerating = false;
                    m.isBoosting = false;
                    m.isBraking = false;
                    m.inGridMode = false;
                    states->setMovementAttributeState(m);

                    p->setTopSpeed(m.velLimit);

                    statusAttributeState stats = states->getStatusAttributeState();
                    stats.maxHealth = dataRoot["actor"][i]["StatusAttributes"]["maxHealth"].asInt();
                    stats.minHealth = dataRoot["actor"][i]["StatusAttributes"]["minHealth"].asInt();
                    stats.curHealth = dataRoot["actor"][i]["StatusAttributes"]["curHealth"].asInt();
                    stats.isAlive = true;
                    states->setStatusAttributeState(stats);

                    ///Setup the physics component
                    b2Fixture* f;

                    std::string shape = dataRoot["actor"][i]["shape"].asString();

                    ///Setup graphics Component
                    batcher->setFrameTexture(g,dataRoot["actor"][i]["texture"].asString());

                    ///Setup Animations
                    for(int j = 0; j< dataRoot["actor"][i]["animations"].size();j++)
                    {
                        Animation anim = batcher->setAnimation(dataRoot["actor"][i]["animations"][j]["name"].asString());
                        anim.tag = dataRoot["actor"][i]["animations"][j]["tag"].asString();

                        anim.currentFrame = 0;
                        g->addAnimation(anim);
                    }

                    ///in order to properly align physics to sprite we must
                    ///get the height and width of sprite and apply to physics points
                    b2Vec2 position= b2Vec2(g->getTextureCoord().width,g->getTextureCoord().height);
                    fixtureUserData* fixtureData = new fixtureUserData;
                    fixtureData->type = "bodyFixture";
                    fixtureData->data = s.spawnID+"Body";


                    ///MAKE SURE THAT THE "SHAPE" IN THE "ENTITY DATA" FILE
                    /// CORRESPONDS WITH THE "SHAPE" IN THE "SHAPE DATA" FILE
                    for(int k =0; k<shapeRoot[shape].size();++k)
                    {
                        int ss = shapeRoot[shape][k]["shape"].size();

                        std::vector<float> points;
                        for(int ii = 0;ii<ss;++ii)
                        {
                            //points[ii]= shapeRoot[shape][i]["shape"][ii].asInt();
                            points.push_back(shapeRoot[shape][k]["shape"][ii].asInt());
                        }
                        ///NOTE TO SELF:IMPLEMENT BODY AND FIXTUREDATA
                        p->createFixturePolygon(points,position,fixtureData,false);

                    }

                    ///Create Field Sensors for actors
                    fixtureUserData* sensorData = new fixtureUserData;
                    sensorData->type = dataRoot["actor"][i]["sensorField"]["fixtureType"].asString();
                    sensorData->data = dataRoot["actor"][i]["sensorField"]["fixtureData"].asString();
                    float sensorRadius = dataRoot["actor"][i]["sensorField"]["radius"][0].asFloat();
                    bool isSensor = dataRoot["actor"][i]["sensorField"]["isSensor"].asBool();
                    p->createFixtureCircle(sensorRadius,b2Vec2(0,0),sensorData,isSensor);


                    ///SetUp Action Component
                    ActionComponent* ac = new ActionComponent;

                    for(int k = 0;k<dataRoot["actor"][i]["movementActions"].size();k++)
                    {

                        MovementAction* ma;

                        if(dataRoot["actor"][i]["movementActions"][k].asString().compare("rotateLeft")==0)
                        {
                            ma = new RotateLeftAction;
                        }
                        else if(dataRoot["actor"][i]["movementActions"][k].asString().compare("rotateRight")==0)
                        {
                            ma = new RotateRightAction;
                        }
                        else if(dataRoot["actor"][i]["movementActions"][k].asString().compare("accelerate")==0)
                        {
                            ma = new AccelerateAction;
                        }
                        else if(dataRoot["actor"][i]["movementActions"][k].asString().compare("deccelerate")==0)
                        {
                             ma = new DeccelerateAction;
                        }
                        else if(dataRoot["actor"][i]["movementActions"][k].asString().compare("brake")==0)
                        {
                             ma = new BrakeAction;
                        }
                        else if(dataRoot["actor"][i]["movementActions"][k].asString().compare("boost")==0)
                        {
                             ma = new BoostAction;
                        }


                        ac->addAction(ma);

                    }
                    for(int j = 0;j<dataRoot["actor"][i]["attackActions"].size();j++)
                    {

                        attackData aData;
                        AttackAction* aa;
                        for(int ii = 0;ii<actionDataRoot["attacks"].size();ii++)
                        {
                            if(actionDataRoot["attacks"][ii]["name"].asString().compare(dataRoot["actor"][i]["attackActions"][j]["name"].asString())==0)
                            {
                                if(dataRoot["actor"][i]["attackActions"][j]["type"].asString().compare("beamAttack")==0)
                                {
                                    aa = new BeamAttackAction;
                                }
                                else if(dataRoot["actor"][i]["attackActions"][j]["type"].asString().compare("radiusAttack")==0)
                                {
                                    aa = new RadiusAttackAction;
                                }
                                else if(dataRoot["actor"][i]["attackActions"][j]["type"].asString().compare("modeAttack")==0)
                                {
                                    aa = new GridModeAttack;
                                }
                                aData.name = actionDataRoot["attacks"][ii]["name"].asString();
                                aData.attackType=actionDataRoot["attacks"][ii]["attackType"].asString();
                                aData.attackRate=actionDataRoot["attacks"][ii]["attackRate"].asInt();
                                aData.duration=actionDataRoot["attacks"][ii]["duration"].asInt();
                                aData.coolDown=actionDataRoot["attacks"][ii]["cooldown"].asInt();
                                aData.rotationRate=dataRoot["actor"][i]["attackActions"][j]["rotationRate"].asFloat();

                                for(int k = 0;k<actionDataRoot["attacks"][ii]["shape"].size();k++)
                                {
                                    aData.shape.push_back(actionDataRoot["attacks"][ii]["shape"][k].asFloat());
                                }
                                aData.relPosition.x = dataRoot["actor"][i]["attackActions"][j]["relativePosition"][0].asFloat();
                                aData.relPosition.y = dataRoot["actor"][i]["attackActions"][j]["relativePosition"][1].asFloat();

                                aData.damage= dataRoot["actor"][i]["attackActions"][j]["damage"].asInt();
                                aData.force = dataRoot["actor"][i]["attackActions"][j]["force"].asFloat();

                                aData.impactDuration = actionDataRoot["attacks"][ii]["impactDuration"].asInt();
                                aData.impactType =actionDataRoot["attacks"][ii]["impactType"].asString();
                                aData.fixtureType =actionDataRoot["attacks"][ii]["fixtureType"].asString();
                                aData.fixtureData =actionDataRoot["attacks"][ii]["fixtureData"].asString();
                                aData.isSensor =actionDataRoot["attacks"][ii]["isSensor"].asBool();
                                aData.graphic =actionDataRoot["attacks"][ii]["graphic"].asString();
                                aa->setData(aData);
                                break;
                            }

                        }
                        ac->addAction(aa);
                    }
                    ///Create Actor
                    a = new ActorEntity(s.spawnID,g,p,ic,states,ac,new GameEventListener());
                    a->setPosition(s.location);
                    a->setRotation(s.rotation);

                    return a;

                }
            }

        }
         if(s.entityType.compare("object")==0)
        {
            ///SPAWN OBJECT ENTITIES



        }

    }
}
