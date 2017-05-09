#include "EntitySpawner.h"

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
    shapeFile.open("assets/shapes.json");
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
    dataFile.open("assets/entityData.json");
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
    actionDataFile.open("assets/attackData.json");
    bool parsedSuccess = dataReader.parse(actionDataFile,actionDataRoot,false);
    if(!parsedSuccess)
    {
         std::cout<<"failed to parse JSON"<< std::endl
            <<dataReader.getFormattedErrorMessages()<<std::endl;
    }
    actionDataFile.close();
}


entity* EntitySpawner::spawnEntity(spawnPoint s,SpriteBatcher* b)
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
                    else if(s.spawnID.compare("entity_d1")==0)
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
                    states->setMovementAttributeState(m);

                    /*statusAttributeState stats = states->getStatusAttributeState();
                    stats.maxHealth = dataRoot["actor"][i]["StatusAttributes"]["maxHealth"].asFloat();
                    stats.minHealth = dataRoot["actor"][i]["StatusAttributes"]["minHealth"].asFloat();
                    stats.curHealth = dataRoot["actor"][i]["StatusAttributes"]["curHealth"].asFloat();
                    states->setStatusAttributeState(stats);*/

                    ///Setup the physics component
                    b2Fixture* f;

                    std::string shape = dataRoot["actor"][i]["shape"].asString();

                    ///Setup graphics Component
                    b->setFrameTexture(g,dataRoot["actor"][i]["texture"].asString());


                    ///in order to properly align physics to sprite we must
                    ///get the height and width of sprite and apply to physics points
                    b2Vec2 position= b2Vec2(g->getTextureCoord().width,g->getTextureCoord().height);
                    fixtureUserData* fixtureData = new fixtureUserData;
                    fixtureData->type = "BODY";
                    fixtureData->data = s.spawnID+"Body";



                    ///MAKE SURE THAT THE "SHAPE" IN THE "ENTITY DATA" FILE
                    /// CORRESPONDS WITH THE "SHAPE" IN THE "SHAPE DATA" FILE
                    for(int i =0; i<shapeRoot[shape].size();++i)
                    {
                        int ss = shapeRoot[shape][i]["shape"].size();

                        std::vector<float> points;
                        for(int ii = 0;ii<ss;++ii)
                        {
                            //points[ii]= shapeRoot[shape][i]["shape"][ii].asInt();
                            points.push_back(shapeRoot[shape][i]["shape"][ii].asInt());
                        }
                        ///NOTE TO SELF:IMPLEMENT BODY AND FIXTUREDATA
                        p->createFixturePolygon(points,position,fixtureData,false);

                    }


                    ///SetUp Action Component
                    ActionComponent* ac = new ActionComponent;

                    for(int k = 0;k<dataRoot["actor"][i]["movementActions"].size();k++)
                    {

                        MovementAction* ma;

                        if(dataRoot["actor"][i]["movementActions"][k].asString().compare("rotateLeft")==0)
                        {
                            std::cout<<"Made it here"<<std::endl;
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

                        ac->addAction(ma);

                    }
                    for(int j = 0;j<dataRoot["actor"][i]["attackActions"].size();j++)
                    {
                        attackData aData;
                        AttackAction* aa;
                        std::cout<<"we got here"<<std::endl;
                        for(int ii = 0;ii<actionDataRoot["attacks"].size();ii++)
                        {
                            if(actionDataRoot["attacks"][ii]["name"].asString().compare(dataRoot["actor"][i]["attackActions"][j]["name"].asString())==0)
                            {
                                if(dataRoot["actor"][i]["attackActions"][j]["type"].asString().compare("beamAttack")==0)
                                {
                                    aa = new BeamAttackAction;

                                }
                                aData.name = actionDataRoot["attacks"][ii]["name"].asString();
                                aData.attackType=actionDataRoot["attacks"][ii]["attackType"].asString();
                                aData.duration=actionDataRoot["attacks"][ii]["duration"].asInt();
                                aData.coolDown=actionDataRoot["attacks"][ii]["cooldown"].asInt();
                                aData.rotationRate=actionDataRoot["attacks"][i]["rotationRate"].asFloat();

                                for(int k = 0;k<actionDataRoot["attacks"][ii]["shape"].size();k++)
                                {
                                    aData.shape.push_back(actionDataRoot["attacks"][ii]["shape"][k].asFloat());
                                }

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
                    a = new ActorEntity(s.spawnID,g,p,ic,states,ac);
                    a->setPosition(s.location);
                    a->setRotation(s.rotation);

                   /* States::attributeState attributes = a->getAttributes();


                    a->setAttributes(attributes);*/

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
