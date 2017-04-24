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
                    GraphicsComponent* g = new GraphicsComponent;
                    PhysicsComponent* p = new PhysicsComponent(b2_dynamicBody);
                    playerInputComponent* ic = new playerInputComponent;
                    b2Fixture* f;
                    b->setFrameTexture(g,dataRoot["actor"][i]["texture"].asString());
                    std::string shape = dataRoot["actor"][i]["shape"].asString();

                    ///in order to properly align physics to sprite we must
                    ///get the height and width of sprite and apply to physics points
                    b2Vec2 position= b2Vec2(g->getTextureCoord().width,g->getTextureCoord().height);


                    ///MAKE SURE THAT THE "SHAPE" IN THE "ENTITY DATA" FILE
                    /// CORRESPONDS WITH THE "SHAPE" IN THE "SHAPE DATA" FILE
                    for(int i =0; i<shapeRoot[shape].size();++i)
                    {
                        int ss = shapeRoot[shape][i]["shape"].size();

                        float points[ss];
                        for(int ii = 0;ii<ss;++ii)
                        {
                            points[ii]= shapeRoot[shape][i]["shape"][ii].asInt();
                        }
                        ///NOTE TO SELF:IMPLEMENT BODY AND FIXTUREDATA
                        p->createFixturePolygon(f,points,ss,position,new fixtureUserData);

                    }
                    //p->createFixtureRectangle(f,b2Vec2(1,1),b2Vec2(0,0),"Nothing");



                    a = new ActorEntity(s.spawnID,g,p,ic);

                    a->setPosition(s.location);
                    a->setRotation(s.rotation);
                    States::attributeState attributes = a->getAttributes();

                    attributes.accelRate = dataRoot["actor"][i]["accelRate"].asFloat();
                    attributes.accelRateLimit= dataRoot["actor"][i]["accelRateLimit"].asFloat();
                    attributes.velLimit= dataRoot["actor"][i]["velLimit"].asFloat();
                    attributes.brakeLimit = dataRoot["actor"][i]["brakeLimit"].asFloat();
                    attributes.rotationRate= dataRoot["actor"][i]["rotationRate"].asFloat();
                    attributes.accel_rotationRate = dataRoot["actor"][i]["accel_rotationRate"].asFloat();
                    a->setAttributes(attributes);

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
