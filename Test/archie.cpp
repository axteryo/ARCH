#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <math.h>
#include "BoxWiz.h"

#include "dist/json/json-forwards.h"
#define _USE_MATH_DEFINES

using namespace sf;
using namespace std;



/** Creates walls for the map**/
void CreatePlane(b2World& world,  float X, float Y);
void createSegment(b2World& world,b2Body* bod);
void createObject(b2World& world, float X, float Y,std::string name, int id);

struct fixtureUserData
{
  std::string data;
  fixtureUserData()
  {
      data = "";
  }
};
int getSlope(float x1,float y1,float x2,float y2)
{
    return (y2-y1)/(x2-x1);
}
bool checkIntercept(float x,float y,float x1,float y1,float slope)
{

    std::cout<<y<<","<<(((slope*x)-(slope*x1))+y1)<<std::endl;
    if(abs(y - ((slope*(x-x1))+y1))<.00005 )
    {
        return true;
    }
    else
    {
        return false;
    }

}
bool checkBetween(float x1,float y1,float x2,float y2,float x,float y)
{
  if(x2<x&&x<x1 )

        {
            std::cout<<"in between"<<std::endl;
            return true;
        }
  else if (x2>x && x>x1)
        {
            std::cout<<"in between"<<std::endl;
            return true;
        }
   else if (y2>y && y>y1)
   {
        std::cout<<"in between"<<std::endl;
            return true;
   }
    else if (y2<y && y<y1)
    {
        std::cout<<"in between"<<std::endl;
            return true;
    }
    else
    {
        return false;
    }

}


float lerp(float g, float c, float t)
    {
       /* float diff = g - c;

        if (diff > t)
        {
            return c +t;
        }
        if (diff < -t)
        {
            return c - t;
        }*/

        return g+(t*(c-g));
    }

extern sf::Vector2f normalize(Vector2f source)
{
    float mag = sqrt((source.x * source.x) + (source.y * source.y));
    if (mag != 0)
        {
            source = Vector2f(source.x / mag, source.y / mag);
        //return source;
        }

        return source;
}
class DynamicCam
{
public:
    sf::View camView;
    sf::Vector2f position;
    sf::Vector2f focalPoint;
    sf::Vector2f camDim;
    DynamicCam(sf::Vector2f pos,sf::Vector2f cameraDimension)
    {
        position = pos;
        camDim = cameraDimension;
        focalPoint = sf::Vector2f(camDim.x/2,camDim.y/2);
        camView = sf::View(position,camDim);
        //camView.move(100,100);
        //camView.setViewport(sf::FloatRect(0,0,1.0f,1.0f));
       // camView = sf::View(position,camDim);


    }

    void update()
    {


    }
    void scroll(float dx,float dy)
    {
        camView.move(sf::Vector2f(dx,dy));
    }


    void follow(b2Body* subject)
    {

            sf::Vector2f direction = sf::Vector2f(subject->GetPosition().x*30 -focalPoint.x,
                                                  subject->GetPosition().y*30 -focalPoint.y);
            float camVel;

if (sqrt(((subject->GetPosition().x*30-focalPoint.x)*
          (subject->GetPosition().x*30-focalPoint.x))+
         ((subject->GetPosition().y*30-focalPoint.y)*
          ((subject->GetPosition().y*30-focalPoint.y)))) > 100);
   {

        camVel = sqrt(((subject->GetPosition().x*30-focalPoint.x)*
                       (subject->GetPosition().x*30-focalPoint.x))+
                      ((subject->GetPosition().y*30-focalPoint.y)*
                       ((subject->GetPosition().y*30-focalPoint.y))))/15;
            //std::cout<< camVel<<std::endl;


         camView.setCenter( focalPoint.x+=normalize(direction).x*camVel,focalPoint.y+=normalize(direction).y*camVel);
    }

            //camView.setCenter(lerp(subject->GetPosition().x*30,focalPoint.x,.0001),lerp(subject->GetPosition().y*30,focalPoint.y,.0001));


       //
        //{

        //}


    }
    sf::View GetView()
    {
        return camView;
    }


private:


};
class Commander
{
private:

public:
    enum cState
    {
        neutral,
        chase,
        offense,
        defensive,
        cautious
    }commanderState;
    fixtureUserData* fixtureData;
    std::string objectID;
    sf::CircleShape spriteBody;
    sf::CircleShape radius;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f position;
    b2BodyDef commanderBodyDef;
    b2Body* commanderBody;
    b2CircleShape commanderShape;
    b2FixtureDef commanderFixtureDef;

    b2BodyDef radiusBodyDef;
    b2Body* radiusBody;
    b2CircleShape radiusShape;
    b2FixtureDef radiusFixtureDef;
    float angle;
    int counter;


    int cCounter;
    Commander(sf::Vector2f pos,b2World& world)
    {
        fixtureData =  new fixtureUserData;
        fixtureData->data="radius";
        objectID = "enemy";
        velocity = sf::Vector2f(0,0);
        acceleration = sf::Vector2f(0,0);
        position = pos;
        spriteBody.setRotation(180);
        cCounter = 60;
        angle = 0;

        spriteBody.setRadius(15);
        spriteBody.setPointCount(3);
        radius.setRadius(300);
        radius.setPointCount(50);

        spriteBody.setFillColor(sf::Color::Red);
        spriteBody.setOrigin(15,15);
        commanderState = cautious;
        radius.setOrigin(300,300);
        radius.setOutlineColor(sf::Color::Red);
        radius.setFillColor(sf::Color::Transparent);
        radius.setOutlineThickness(2);

        commanderBodyDef.type = b2_dynamicBody;
        commanderBodyDef.position.Set(position.x/30,position.y/30);
        commanderBodyDef.fixedRotation = true;
        commanderBody = world.CreateBody(&commanderBodyDef);
        commanderBody->SetAngularVelocity(0);

        radiusBodyDef.type = b2_dynamicBody;
        radiusBodyDef.position.Set(position.x/30,position.y/30);
        radiusBodyDef.fixedRotation = true;
        radiusBody = world.CreateBody(&radiusBodyDef);
        radiusBody->SetAngularVelocity(0);


        commanderShape.m_p.Set(0,0);
        commanderShape.m_radius = (spriteBody.getGlobalBounds().width/2)/30;
        commanderFixtureDef.shape = &commanderShape;
        commanderFixtureDef.density = 0.1;
        commanderBody->CreateFixture(&commanderFixtureDef);
        commanderBody->SetUserData((void*)this);


        radiusShape.m_p.Set(0,0);
        radiusShape.m_radius = (radius.getGlobalBounds().width/2)/30;
        radiusFixtureDef.shape = &radiusShape;
        radiusFixtureDef.density = 0;
        radiusFixtureDef.isSensor = true;
        radiusFixtureDef.userData = ((void*)fixtureData);
        radiusBody->CreateFixture(&radiusFixtureDef);
        radiusBody->SetUserData((void*)this);
        radiusBody->SetActive(true);



        spriteBody.setPosition(commanderBody->GetPosition().x*30,commanderBody->GetPosition().y*30);
        radius.setPosition(radiusBody->GetPosition().x*30,radiusBody->GetPosition().y*30);




    }
    ~Commander()
    {
        world.DestroyBody(commanderBody);
        world.DestroyBody(radiusBody);
        delete fixtureData;
    }
void update(Vector2f player)
{


    //goToward(Vector2f(cos(body.getRotation()),sin(body.getRotation())));

    //position = spriteBody.getPosition();
    velocity = sf::Vector2f(commanderBody->GetLinearVelocity().x,commanderBody->GetLinearVelocity().y);
    switch(commanderState)
    {
    case neutral:
        break;
    case offense:
        goToward(player);
        angle = target(player);
        break;
    case chase:

        break;
    case defensive:
        break;
    case cautious:
angle = target(player);
        break;
    }

    /*sf::Vector2f direction =sf::Vector2f(cos(angle),sin(angle));
    float dmag = sqrt((direction.x*direction.x)+(direction.y*direction.y));
    if (dmag != 0)
    {
        direction.x/=dmag;
        direction.y/=dmag;

    }
    direction.x*=4;
    direction.y*=4;
    */
    //acceleration = direction;
    //angle = target(player);
    //float desiredAngle = atan2(commanderBody->GetPosition().x*30 - player.x, commanderBody->GetPosition().y*30-player.y);







    velocity+=acceleration;
    //angle = atan2((velocity.y),(velocity.x))-3.141592/2;


    if(sqrt((velocity.x*velocity.x)+(velocity.y*velocity.y))>14)
    {
        float mag = sqrt((velocity.x*velocity.x)+(velocity.y*velocity.y));
            if (mag != 0)
                {

                    velocity.x/=mag;
                    velocity.y/=mag;
                    velocity.x*=14;
                    velocity.y*=14;

                }
    }

    commanderBody->SetLinearVelocity(b2Vec2(velocity.x,velocity.y));
    commanderBody->SetTransform(commanderBody->GetPosition(),angle);
    radiusBody->SetTransform(commanderBody->GetPosition(),angle);
    radius.setPosition(radiusBody->GetPosition().x*30,radiusBody->GetPosition().y*30);
    spriteBody.setPosition(commanderBody->GetPosition().x*30,commanderBody->GetPosition().y*30);
    spriteBody.setRotation(180+(commanderBody->GetAngle()*(180/3.141592)));

    acceleration = sf::Vector2f(0,0);
   // std::cout<<"commanderLocation:"<<commanderBody->GetPosition().x<<","<<commanderBody->GetPosition().y<<std::endl;
    //std::cout<<"SpriteLocation:"<<spriteBody.getPosition().x/30<<","<<spriteBody.getPosition().y/30<<std::endl;


}

void setCautious()
{
    commanderState = cautious;
}
void setNeutral()
{
    commanderState = neutral;
}
void setOffense()
{
     commanderState = offense;

}
void startCount()
{
    counter+=1;
}
void wander()
{

}
void goToward(sf::Vector2f direction)
{
   direction =sf::Vector2f(direction-spriteBody.getPosition());
    float mag = sqrt((direction.x*direction.x)+(direction.y*direction.y));
    if (mag != 0)
    {
        direction.x/=mag;
        direction.y/=mag;

    }
        direction.x*=30;
        direction.y*=30;
    sf::Vector2f steer = direction -velocity;
    float smag = sqrt((steer.x*steer.x)+(steer.y*steer.y));
    if(smag>1)
       {
           steer.x/smag;
           steer.y/smag;
       }
    steer.x*=.025;
    steer.y*=.025;
    acceleration += steer;

}
void encircle(float angle)
{
    angle = angle*(3.141592/180);
    //Vector2f(cos(body.getRotation()*(3.141592/180)),sin((body.getRotation()*(3.141592/180))))
    acceleration = Vector2f(cos(angle),sin(angle));
}
float target(Vector2f targ)
{
    b2Vec2 target = b2Vec2(targ.x/30,targ.y/30);
    float rotation = commanderBody->GetAngle();
    b2Vec2 toTarg = target - commanderBody->GetPosition();
    float desiredAngle = atan2f(-toTarg.x,toTarg.y);
    float totalRotation = desiredAngle - rotation;
    float change = 3 * (3.141592/180); //allow 3 degree rotation per time step
    while ( totalRotation < -3.141592 ) totalRotation += 2*(3.141592);
    while ( totalRotation >  3.141592 ) totalRotation -= 2*(3.141592);
    float newAngle = rotation + std::min( change, std::max(-change, totalRotation));
    //std::cout<<totalRotation<<std::endl;
   // std::cout<<"enemy angle"<<rotation*(180/3.141592)<<std::endl;
    //std::cout<<"Necessary rotation angle"<<totalRotation*(180/3.141592)<<std::endl;

   /*  if(std::abs(totalRotation)<.05)
    {
        rotation = desiredAngle;
    }
    //angle =0- angle;

    if(desiredAngle> rotation)
    {
            if(totalRotation> 3.141592)
        {
                rotation-=change;
        }
        else
        {
                rotation+=change;
        }
    }
    else
    {

        if(totalRotation< -3.141592)
        {
            rotation+=change;
        }
        else
        {
            rotation-=change;
        }

    }



    /*float diff;
    diff = angle-rotation;
    if(rotation!=-angle)
    {
       /* if (diff > 3.141592) diff -= 3.141592 ;
        if (diff < -3.141592) diff += 3.141592 ;
        if(diff > 3.141592) rotation-=3.141592;
        if(diff < -3.141592) rotation+=3.141592;
        std::cout<<diff<<std::endl;
        if(angle> rotation)
        {
            //rotation+=.1;

            if(diff>1)
            {
                rotation-=.1;

                //std::cout<<"Problem Spot"<<std::endl;
            }
            else
            {
               rotation+=.1;
            }

        }
        else
        {
            //rotation-=.1;
            if(diff<-1)
            {
                rotation+=.1;
            }
            else
            {
               rotation-=.1;
            }

        }
         if(std::abs(diff)<.5)
        {

            rotation = angle;
        }

        /*if(diff>0)
        {
            rotation+=4;
        }
        else
        {
            rotation-=4;
        }
        if(std::abs(diff)<4)
        {
            rotation = angle;
        }*/


        //std::cout<<rotation<<","<<angle<<std::endl;
        //std::cout<<diff<<std::endl;

        // body.setRotation((angle*(-180/3.141592)+180)+(.0000000001*(rotation-(angle*(-180/3.141592)+180))));

    return newAngle;
}
void attack()
{

}
sf::CircleShape getBody()
{
    return spriteBody;
}
sf::CircleShape getRadius()
{
    return radius;
}
void setPosition(sf::Vector2f p)
{
    //spriteBody.setPosition(p);
    commanderBody->SetTransform(b2Vec2(p.x/30,p.y/30),commanderBody->GetAngle());
}
b2Vec2 getPosition()
{
    return commanderBody->GetPosition();
}



};

float getAngle(sf::Vector2f a, sf::Vector2f b, bool inDegrees = false) {
    if (inDegrees)
        return (atan2(b.y - a.y, b.x - a.x) * 180 / 3.141592);
    return (float)(atan2(b.y - a.y, b.x - a.x));
}

class point
{
public:
    float x, y;
    float angle;

    point(float X, float Y)
    {
        x = X;
        y = Y;
    }
};
class BodyLoader
{public:
    void attachFixture(b2Body* bod, sf::String name, b2FixtureDef &fd)
    {
        std::ifstream shapeFile;
        shapeFile.open(name+".json");

        Json::Reader  myReader;
        Json::Value shapeRoot;

        bool parsedSuccess = myReader.parse(shapeFile,shapeRoot,false);
        if(!parsedSuccess)
        {
            std::cout<<"failed to parse JSON"<< std::endl
            <<myReader.getFormattedErrorMessages()<<std::endl;

        }
        else
            std::cout<<"success"<<std::endl;


        b2PolygonShape polyShape;
        //for objects in the "sprite name array"
        for(int i = 0; i < shapeRoot[name].size(); i++)
        {
            b2Vec2 vertices[shapeRoot[name][i]["shape"].size()/2];
            int x = shapeRoot[name][i]["shape"].size()-2;
            int y = x+1;

	//FOr vertices in the "shapes array"
            for (int ii = 0; ii < shapeRoot[name][i]["shape"].size(); ++ii)
            {
                if(x>=0)
                {
                    vertices[ii].Set((shapeRoot[name][i]["shape"][x].asInt()-bod->GetPosition().x*30)/30,
                                     (shapeRoot[name][i]["shape"][y].asInt()-bod->GetPosition().y*30)/30);

                    x-=2;
                    y = x+1;
                }
            }
            //int counter = 4;
            polyShape.Set(vertices,shapeRoot[name][i]["shape"].size()/2);
            fd.shape = &polyShape;
            fd.friction = 0.0f;
            fd.density = 2.0f;
            //b2Fixture* myFixture = bod->CreateFixture(&fd);
            //std::cout<<"got here"<<std::endl;

            bod->CreateFixture(&fd);
        }
        //std::cout<<"got here"<<std::endl;


//get vertices and store them in an array

//clear array and go to next shape



    }
};

class MapLoader

{
public:

   // std::vector<
   /**Map dimensions(Tile Count)**/
   sf::Vector2f v2f_mapDimension;
   /**Tile dimensions in pixels**/
   sf::Vector2f v2f_tileDimension;
   /**A List for the maps layers **/
   std::vector<Json::Value> mapLayers;

   /**Map data list**/
   std::vector<int> level;
   sf::Image spriteSheet;
   sf::Texture texture;

    MapLoader()
    {

        v2f_mapDimension = sf::Vector2f(0,0);
        v2f_tileDimension = sf::Vector2f(0,0);



    }
    void loadMap( std::string mapFile)
    {
        Json::Value baseMapRoot;
        Json::Reader mapReader;
        std::ifstream currentMapFile;
        currentMapFile.open(mapFile);
        bool parsedSuccess = mapReader.parse(currentMapFile,baseMapRoot,false);
        if(!parsedSuccess)
        {
            std::cout<<"failed to parse JSON"<< std::endl
            <<mapReader.getFormattedErrorMessages()
            <<std::endl;
        }
        spriteSheet.loadFromFile(baseMapRoot["tilesets"][0]["image"].asString());
        for(int i = 0;i < baseMapRoot["layers"].size();++i)
        {
            mapLayers.push_back(baseMapRoot["layers"][i]);
        }

        //mapLayers.push_back();
        //std::cout<<mapLayers[0]["data"]<<std::endl;

    }
private:

};


class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact)
    {
        ///Check if fixture B is the enemy
        fixtureUserData* userData = static_cast<fixtureUserData*>(contact->GetFixtureB()->GetUserData());
                    if(userData)
                    {

                        if( userData->data== "radius")
                        {
                            Commander* userData1 = static_cast<Commander*>(contact->GetFixtureB()->GetBody()->GetUserData());
                             if(userData1->objectID == "enemy")
                             {
                                void* userData2 = contact->GetFixtureA()->GetBody()->GetUserData();
                                if((int)userData2 == 1)
                                {


                                    //std::cout<<"close2"<<std::endl;
                                    //userData1->startCount();
                                    userData1->setOffense();




                                 }
                                 //delete userData2;
                            }
                            //delete userData1;
                        }

                    }
                    //delete userData;


       // grounded = true;


    }/*
    void EndContact(b2Contact* contact)
    {
         void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
         if((std::string)static_cast<Commander*>(bodyUserData)->objectID == "enemy")
        {

            void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
            if((int)bodyUserData2 == 1)
            {
                std::cout<<"close2"<<std::endl;

                static_cast<Commander*>(bodyUserData)->setNeutral();
            }


        }
    }*/

};


int main()
{ /** The window we'll be using to display  stuff as well as its dimensional variables **/
    //sf::Vector2f mapSize(5000,3000);
//    sf::Vector2f mapOrigin(-2500,)
    sf::Vector2f wSize(1000,800);
    sf::RenderWindow window(sf::VideoMode(wSize.x,wSize.y,32),"Hello Box2d");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    sf::Event event;
    sf::Mouse mouse;
    float angle;

    /** Camera **/
    DynamicCam* mainCam = new DynamicCam(sf::Vector2f(0,0),wSize);

    sf::Vector2f cam(0,0);
    sf::Vector2f camTarg(wSize.x/2,wSize.y/2);
    sf::Vector2f camFocus(0,0);
    bool moved = false;


/** Prepares the box2d world**/
    b2Vec2 grav(0.0f,0.0f);
    b2World world(grav);
    MyContactListener mcl;
    world.SetContactListener(&mcl);


/**Player Stuff**/

///Sprite is setup
sf::CircleShape playerSprite;
playerSprite.setRadius(15.0f);
playerSprite.setPointCount(3);
playerSprite.setFillColor(sf::Color::Transparent);
playerSprite.setOutlineColor(sf::Color::Blue);
playerSprite.setOutlineThickness(2);
playerSprite.setOrigin(15.0f,15.0f);


///Physics body is setUp
b2BodyDef playerBodyDef;
playerBodyDef.type = b2_dynamicBody;
playerBodyDef.position.Set(wSize.x/2/30,wSize.y/2/30);
playerBodyDef.fixedRotation = true;
b2Body* playerBody = world.CreateBody(&playerBodyDef);
b2CircleShape playerShape;

playerShape.m_p.Set(0,0);
playerShape.m_radius = playerSprite.getGlobalBounds().width/2/30.0f;

b2FixtureDef playerFixtureDef;
playerFixtureDef.shape = &playerShape;
playerFixtureDef.density = 0.1;
playerBody->CreateFixture(&playerFixtureDef);
playerBody->SetUserData((void*) 1);
playerBody->SetTransform(playerBody->GetPosition(),0);

bool thrust = false;
bool rightBoost = false;
bool brake = false;
sf::Vector2f targ;
sf::Vector2f dir;
float thrustLevel = 0;
float boostLevel = 0;
float boostCounter = 20;
float tapCounter = 1;
bool singleTap = false;
bool doubleTap = false;
bool gridMode = false;
float gridDuration = 50;

float32 timeStep = 1.0f/60.0f;
int32 velocityIterations = 8;
int32 positionIterations = 3;





/**Surrounding arena**/

 int x,y;
    x = 0;
    y = 0;
int rowcount = 0;


    for(int i = 0; i< 100;++i)
    {

        CreatePlane(world,x,y);
        x+=192;
        ++rowcount;
        if (rowcount ==10)
        {
            x = 0;
            y +=192;
            rowcount = 0;
        }

    }
    /** Textures and junk**/
    sf::Texture pineTexture;
    pineTexture.loadFromFile("pine_sprite.png");
    sf::Sprite pineSprite;
    pineSprite.setTexture(pineTexture);
    pineSprite.setOrigin(0,0);
    pineSprite.setPosition(0,0);

    //createObject(world,100,100,"pine_sprite",10);
    //createObject(world,200,100,"wiz",9);


    sf::Texture boxTexture;
    boxTexture.loadFromFile("box.png");

    sf::Texture segmentTexture;
    segmentTexture.loadFromFile("segement.png");

    sf::Texture wizTexture;
    wizTexture.loadFromFile("wiz.png");
    std::vector<Commander*> cList;
    for(int i = 0; i <1; i++)
    {
        cList.push_back(new Commander(sf::Vector2f(wSize.x,wSize.y),world));
    }
    /*Commander queen1(sf::Vector2f(wSize.x/2,wSize.y/4),world);
    Commander queen2(sf::Vector2f(wSize.x/2,wSize.y/4),world);
    Commander queen3(sf::Vector2f(wSize.x/2,wSize.y/4),world);
    Commander queen4(sf::Vector2f(wSize.x/2,wSize.y/4),world);
    Commander queen5(sf::Vector2f(wSize.x/2,wSize.y/4),world);
    Commander queen6(sf::Vector2f(wSize.x/2,wSize.y/4),world);
    Commander queen7(sf::Vector2f(wSize.x/2,wSize.y/4),world);
/*    Commander queen2(sf::Vector2f(wSize.x,wSize.y/4));
    Commander queen3(sf::Vector2f(wSize.x/4,wSize.y/2));*/






    /** Laser Stuff **/

    sf::VertexArray beam(sf::Lines,2);
    beam[0].position = sf::Vector2f(0,0);
    beam[1].position = sf::Vector2f(0,0);
    beam[0].color =  sf::Color::Green;
    beam[1].color =  sf::Color::Green;
    sf::Vector2f beamDir = sf::Vector2f(0,0);

    bool firing = false;
    bool rRotate = false;
    bool lRotate = false;
    float maxlength = 1000;
    float topSpeed = 12;
    float turnRate = .075;
    b2Vec2 curPos;
    float pi = atan(1)*4;

    std::vector<point*> segPoints;
    sf::ConvexShape gridShape[1];

while(window.isOpen())
{

window.setView(mainCam->GetView());
mainCam->follow(playerBody);
///The players current velocity
    b2Vec2 vel = playerBody->GetLinearVelocity();
     //std::cout<<"proxycount:"<<world.GetProxyCount()<<std::endl;


    angle = playerBody->GetAngle();
    /**INPUT IS PROCESSED**/

    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            topSpeed+=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(!gridMode)
            {
                rRotate = true;
            }

            //angle+=.25;
            //std::cout<<"rotating right"<<std::endl;
        }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(!gridMode && !rightBoost)
            {
                lRotate = true;
            }

            //angle-=.25;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
           if(!gridMode)
            {
                if(!thrust && !firing)
                {
                    brake = true;
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if(!gridMode)
            {
                //if(!thrust&& !brake)
                //{
                    firing = true;
                //}
            }
        }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
           ///This Unlocks the the target direction
                if(!firing && !brake)
                {
                    thrust = true;
                    //std::cout<<"Thrust is occurring" <<std::endl;
                }


        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))

        {
            if(!thrust)
            {
                rightBoost = true;
                boostLevel = 2;
            }

        }

     if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::S)
            {


            //{if(!thrust)
            //{
                if(!gridMode)
                {
                    gridMode = true;
                }
                else
                {
                    gridMode = false;
                }
            //}



            }
             if(event.key.code == sf::Keyboard::Left)
                {
                    lRotate = false;
                    if(gridMode)
                    {
                        angle=angle - pi/2;
                    }
                }
            if(event.key.code == sf::Keyboard::Right)
                {
                    rRotate = false;
                    if(gridMode)
                    {
                        angle= angle + pi/2;
                    }
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    firing = false;
                }

                if(event.key.code == sf::Keyboard::Down)
                {
                     brake = false;
                }
                 if(event.key.code == sf::Keyboard::Up)
                {
                ///This locks the Target Direction causing the player to float continuously in the same direction
                thrust = false;
                //std::cout<<"Thrust disengaded"<<std::endl;
                //thrustLevel = 0.0;
                /**Registers a single tap has been made and whether a doubletap has been made **/
                if(singleTap)
                {
                    if(tapCounter>=0)
                    {
                    doubleTap = true;
                    }
                }
            //topSpeed = 14;
                singleTap = true;
                }
                if(event.key.code == sf::Keyboard::LAlt)
                {
                    rightBoost = false;
                    boostLevel = 0;
                }


            }




        if (event.type == sf::Event::MouseMoved)
        {
            //targ = sf::Vector2f(mouse.getPosition(window));
            targ = window.mapPixelToCoords((Vector2i(sf::Vector2f(mouse.getPosition(window)))));

        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            //std::cout <<window.mapPixelToCoords((Vector2i(sf::Vector2f(mouse.getPosition(window))))).x <<std::endl;
            //std::cout <<window.mapPixelToCoords((Vector2i)(sf::Vector2f(mouse.getPosition(window)))).y <<std::endl;


            //std::cout<<playerSprite.getRotation()<<std::endl;
        }

    }
    ///Sets a target location for the direction of the players thrust
         if(thrust)
            {
               //std::cout<<"THIS IS GETTING HERE"<<std::endl;

                //dir = sf::Vector2f(mouse.getPosition(window));

                dir =window.mapPixelToCoords((Vector2i(sf::Vector2f(mouse.getPosition(window)))));
            }


    /**UPDATES ARE PROCESSED**/






 /** Rotates the player based upon input **/
    if(lRotate)
    {
        angle-=turnRate;
        //std::cout<<"ITS A HIT"<<std::endl;
    }
    else if(rRotate)
    {
        angle+=turnRate;
    }

///This is for targeting enemies and changing the angle the player is looking towards

 //   b2Vec2 toDir = b2Vec2(,);
 float beamAngle;
 if(!firing)
 {



      beam[0].position = sf::Vector2f(0,0);
      beam[1].position = sf::Vector2f(0,0);

     beamDir=sf::Vector2f(cos(playerBody->GetAngle())*50,sin(playerBody->GetAngle())*50);
     beam[0].position = playerSprite.getPosition();
     beam[1].position = beam[0].position+ beamDir;

 }
 else
 {

    // targ = sf::Vector2f(playerSprite.getPosition().x,playerSprite.getPosition().y) + sf::Vector2f(cos(playerSprite.getRotation()),sin(playerSprite.getRotation()));

     //beamAngle = atan2(targ.x-playerSprite.getPosition().x,targ.y-playerSprite.getPosition().y);
     //std::cout<<<<std::endl;
     //beamDir= sf::Vector2f(cos(beamAngle),sin(beamAngle));
     beamDir=sf::Vector2f(cos(playerBody->GetAngle())*500,sin(playerBody->GetAngle())*500);
     beam[0].position = playerSprite.getPosition();
     beam[1].position = beam[0].position+ beamDir;


     /*beamDir+=sf::Vector2f(beamDir.x,beamDir.y);

     if(sqrt(((beam[1].position.x-beam[0].position.x) * (beam[1].position.x-beam[0].position.x))+
             ((beam[1].position.y-beam[0].position.y) * (beam[1].position.y-beam[0].position.y))) >=maxlength)
        {
            firing = false;
        }*/

    /*if(checkBetween(beam[0].position.x,beam[0].position.y,
                    beam[1].position.x,beam[1].position.y,
                    queen1.spriteBody.getPosition().x,queen1.spriteBody.getPosition().y))
    {

        std::cout<<"ITs a hit"<<std::endl;
    }
    /*if(queen1.getBody().getGlobalBounds().contains(beam[1].position))
    {

    }*/

 }


    //angle = angle *(180/3.14159);
    /// When the players Thrusts we take the direction that the mouse is in
/// And we make it a unit Vector. This gives us a direction as well as an initial accelaration
/// which we will apply to the players velocity
sf::Vector2f dest(0,0);
if (thrust)
{
    if(thrustLevel < 2)
    {
        thrustLevel += .005;
    }
    else{thrustLevel = 2;}
    //dest = sf::Vector2f(dir.x-(playerBody->GetPosition().x*30),dir.y-(playerBody->GetPosition().y*30));
    dest = sf::Vector2f(cos(angle),sin(angle));

}
    float dMag =sqrt( (dest.x*dest.x)+(dest.y*dest.y));
    if(dMag!=0)
    {

        dest.x/dMag;
        dest.y/dMag;



    }
sf::Vector2f rightDest(0,0);

  if(rightBoost)
            {

                rightDest=sf::Vector2f(cos(angle-(pi/2)),sin(angle-(pi/2)));
                //rightDest.x/=boostLevel;
                //rightDest.y/=boostLevel;
               // std::cout<<vel.y<<std::endl;


            }

/*** THIS REGISTERS WHETHER the player will BE BOOSTED **/

if(tapCounter<=0)
{
    singleTap = false;
    doubleTap = false;
    tapCounter = 1;
}

if(singleTap)
    {tapCounter-=1;




    }

 /*   if(doubleTap)
{

    //std::cout<<"RULE NUMBER ONE: DOUBLETAP"<<std::endl;
    singleTap = false;
    doubleTap = false;
    float impulse = playerBody->GetMass()*30;
    //playerBody->ApplyLinearImpulse(b2Vec2(impulse,impulse),playerBody->GetWorldCenter(),true);
    curPos = playerBody->GetPosition();

    //if(segPoints.size()<4)
    //{


    //}

    //topSpeed = 5;
/* playerBody->SetTransform(b2Vec2(lerp(playerBody->GetPosition().x+cos(playerBody->GetAngle())*4,playerBody->GetPosition().x,1.0),
                                    lerp(playerBody->GetPosition().y+sin(playerBody->GetAngle())*4,playerBody->GetPosition().y,1.0)),playerBody->GetAngle());*/
             //playerBody->SetTransform(b2Vec2(playerBody->GetPosition().x+cos(playerBody->GetAngle())*4,
               //                         playerBody->GetPosition().y+sin(playerBody->GetAngle())*4),playerBody->GetAngle());

    //g+(t*(c-g))




    //playerBody->ApplyLinearImpulse(b2Vec2(playerBody->GetMass()*(cos(playerBody->GetAngle())*32),playerBody->GetMass()*(sin(playerBody->GetAngle())*32)),playerBody->GetWorldCenter(),true);
    //tapCounter = 20;
  //  boostCounter = 20;

//}

boostCounter-=1;




///When the player is no longer thrusting The body will try to stablize itself to a minimum speed
    if(!thrust)
    {


        //std::cout<<thrustLevel<<std::endl;
       // if(thrustLevel>0)
        //{

           //thrustLevel-=.04;
          //thrustLevel -=.0275;

        //}
       // else
        //{
            thrustLevel = 0;
       // }
    //}
   // if(brake)
    //{
         if(sqrt((vel.x*vel.x)+(vel.y*vel.y)) > .5)
        {
          //std::cout<<"STABLIZING"<<std::endl;

             vel.x -=normalize(sf::Vector2f(vel.x,vel.y)).x/20;
             vel.y -=normalize(sf::Vector2f(vel.x,vel.y)).y/20;
        }
        else
        {
            //vel.x=0;
            //vel.y=0;
        }
    }

    dest.x*=thrustLevel;
    dest.y*=thrustLevel;
if(!gridMode)
        {
            window.setFramerateLimit(60);
            topSpeed = 13;
            if(!firing)
            {

                if(thrust)
                {
                    turnRate = .05;

                }
                else
                {
                    if(rightBoost)
                    {topSpeed = 16;
                      turnRate = .05;
                    }
                    else{ turnRate = .1;}

                }
                segPoints.clear();
            }
            else
            {
                turnRate = .04;
            }




        }
    else
        {
            window.setFramerateLimit(20);
            gridDuration-=1;
            //turnRate = 1.5;
            topSpeed = 100;
            if(singleTap)
            {
                //std::cout<<"herehereherehere"<<std::endl;

                dest.x=cos(playerBody->GetAngle())*20;
                dest.y=sin(playerBody->GetAngle())*20;
                vel.x*=0;
                vel.y*=0;

                segPoints.push_back(new point(playerBody->GetPosition().x,playerBody->GetPosition().y));

            }
            if(sqrt((vel.x*vel.x)+(vel.y*vel.y)) > 0)
            { if(segPoints.size()>0)
            {
                createSegment(world,playerBody);
            }

            }
            //std::cout<<gridDuration<<std::endl;

            if(gridDuration<=0)
            {
                //gridMode = false;
                gridDuration = 75;
            }
        }
if(segPoints.size()==4)
        {
            float m = getSlope(segPoints[0]->x,segPoints[0]->y,segPoints[1]->x,segPoints[1]->y);

        /*if(sqrt(((segPoints[0]->x-playerBody->GetPosition().x) * (segPoints[0]->x-playerBody->GetPosition().x))+
                        ((segPoints[0]->y-playerBody->GetPosition().y) * (segPoints[0]->y-playerBody->GetPosition().y))) <1
                        && checkIntercept(playerBody->GetPosition().x,playerBody->GetPosition().y,segPoints[0]->x,segPoints[0]->y,m)
                        ||sqrt(((segPoints[0]->x-playerBody->GetPosition().x) * (segPoints[0]->x-playerBody->GetPosition().x))+
                        ((segPoints[0]->y-playerBody->GetPosition().y) * (segPoints[0]->y-playerBody->GetPosition().y))) <1
                        ||checkIntercept(playerBody->GetPosition().x,playerBody->GetPosition().y,segPoints[1]->x,segPoints[1]->y,m))

                               )*/
                 if(checkIntercept(playerBody->GetPosition().x,playerBody->GetPosition().y,segPoints[0]->x,segPoints[0]->y,m))
            {
                if(checkBetween(segPoints[0]->x,segPoints[0]->y,segPoints[1]->x,segPoints[1]->y,playerBody->GetPosition().x,playerBody->GetPosition().y))
                 {
                /*    gridMode = false;
                    segPoints.clear();
                    std::cout<<"Segment Coordinates:"<<std::endl;
                    std::cout<<segPoints[0]->x<<","<<segPoints[0]->y<<std::endl;
                    std::cout<<segPoints[1]->x<<","<<segPoints[1]->y<<std::endl;
                    std::cout<<"player stuff:"<<std::endl;
                    std::cout<<playerBody->GetPosition().x<<","<<playerBody->GetPosition().y<<std::endl;
                    std::cout<<"player stuff end"<<std::endl;*/


                   }




            }

            //std::cout<<checkIntercept(playerBody->GetPosition().x,playerBody->GetPosition().y,segPoints[1]->x,segPoints[1]->y,m)<<std::endl;
            /*std::cout<<segPoints[0]->x<<","<<segPoints[0]->y<<std::endl;
            std::cout<<segPoints[1]->x<<","<<segPoints[1]->y<<std::endl;
            std::cout<<playerBody->GetPosition().x<<","<<playerBody->GetPosition().y<<std::endl;*/



        }


    vel.x+=dest.x;
    vel.y+=dest.y;
    vel.x+=rightDest.x;
    vel.y+=rightDest.y;
    float dx, dy;
    ///This limits the maximum velocity of the Player
     if(sqrt((vel.x*vel.x)+(vel.y*vel.y)) > topSpeed)
        {
            //std::cout<<
            //cout<< velocity.x*velocity.x<< endl;
            float mag = sqrt((vel.x*vel.x)+(vel.y*vel.y));
            if (mag != 0)
                {
                   // std::cout<<"here"<<std::endl;
                    vel.x/=mag;
                    vel.y/=mag;
                    vel.x*=topSpeed;
                    vel.y*=topSpeed;
                    //dx = playerBody->GetPosition().x*30-(wSize.x/2);
                    //dy = playerBody->GetPosition().y*30-(wSize.y/2);
                    //mainCam->scroll(dx,dy);


                }
        }
    //cam.x-=dest.x;
    //cam.y-=dest.y;


    playerBody->SetLinearVelocity( vel );
    playerBody->SetTransform( playerBody->GetPosition(),angle );
    playerBody->SetAngularVelocity(0);

    world.Step(timeStep,velocityIterations,positionIterations);
       // std::cout<<"got here"<<std::endl;




    ///This ensures that the sprite is always glued to the physics body
    playerSprite.setPosition(30.0*playerBody->GetPosition().x,30.0*playerBody->GetPosition().y);
    playerSprite.setRotation(90+playerBody->GetAngle()*((180/3.141592)));
    /*queen1.update(playerSprite.getPosition());
    queen2.update(playerSprite.getPosition());
    queen3.update(playerSprite.getPosition());
    queen4.update(playerSprite.getPosition());
    queen5.update(playerSprite.getPosition());
    queen6.update(playerSprite.getPosition());
    queen7.update(playerSprite.getPosition());
    /*queen2.update(playerSprite.getPosition());
    queen3.update(playerSprite.getPosition());*/
    for(int i = 0; i<cList.size(); i++)
    {
        cList[i]->update(playerSprite.getPosition());
    }

    /** SOME GRID LINE SSTUFFFF**/

    /*for(size_t i = 0; i <segPoints.size();i++)
    {
        segPoints[i]->angle =getAngle(segPoints[i]->position,segPoints[i]->position);
    }*/




   /* if(segPoints.size()==4)
    {
        gridShape[1] = {sf::ConvexShape(4)};
        for(int i = 0; i<segPoints.size();++i)
        {
            gridShape[1].setPoint(i,segPoints[i]->position);

        }

    }*/

    mainCam->update();



    /**IMAGES ARE REFRESHED AND DRAWN**/


    window.clear((sf::Color::White));

    int drawcount = 0;
    for(b2Body* bodyIter = world.GetBodyList(); bodyIter!=0; bodyIter = bodyIter->GetNext())
        {


            if((int)bodyIter->GetUserData() == 9)
            {



                sf::Sprite sprite;
                sprite.setTexture(wizTexture);
                //sprite.setOrigin(30*bodyIter->GetPosition().x,30*bodyIter->GetPosition().y);
                sprite.setPosition(30*bodyIter->GetTransform().p.x,30*bodyIter->GetTransform().p.y);

                sprite.setRotation((bodyIter->GetTransform().q.GetAngle()*(180-(180/3.14159))));
                window.draw(sprite);
            }
            if((int)bodyIter->GetUserData() == 10)
            {




                /*quads[0].position =
                quads[1].position =
                quads[2].position =;
                quads[3].position =;
                quads[0].color = sf::Color::Green;
                quads[1].color = sf::Color::Green;
                quads[2].color = sf::Color::Green;
                quads[3].color = sf::Color::Green;*/
               // std::cout<<colShape.getPoint(3).x<<","<<colShape.getPoint(3).y<<std::endl;
               // std::cout<<(bodyIter->GetPosition().x-polygonShape->GetVertex(0).x)*30//bodyIter->GetPosition().x)*30<<
               // /*","<<(polygonShape->GetVertex(0).y-bodyIter->GetPosition().y)*30*/<<std::endl;

               // std::cout<<quads[3].position.x <<","<<quads[3].position.y<<std::endl;
                sf::Sprite sprite;
                sprite.setTexture(pineTexture);
                //sprite.setOrigin(sprite.getScale().x/2, sprite.getScale().y/2);
                sprite.setPosition(30*bodyIter->GetPosition().x,30*bodyIter->GetPosition().y);
                //sprite.setOrigin(30*bodyIter->GetPosition().x,30*bodyIter->GetPosition().y);
                sprite.setRotation((bodyIter->GetAngle()*(180-(180/3.14159))));
                window.draw(sprite);

            }
            if((int)bodyIter->GetUserData() == 2)
            {
                b2Vec2 pos;
                pos = bodyIter->GetPosition();
                pos.x+=cam.x;
                pos.y+=cam.y;
                bodyIter->SetTransform(pos,bodyIter->GetAngle());

                sf::Sprite sprite;
                sprite.setTexture(boxTexture);
                sprite.setOrigin(16,16);
                sprite.setPosition(30*bodyIter->GetPosition().x,30*bodyIter->GetPosition().y);
                sprite.setRotation((bodyIter->GetAngle()*(180/3.14159)));
                window.draw(sprite);
                //std::cout<<playerSprite.getPosition().x<<std::endl;
                //std::cout<<playerSprite.getPosition().y<<std::endl;
            }
            if((int)bodyIter->GetUserData() == 3)
            {
                if(gridMode)
                {
                    b2Vec2 pos;
                pos = bodyIter->GetPosition();
                pos.x+=cam.x;
                pos.y+=cam.y;
                bodyIter->SetTransform(pos,bodyIter->GetAngle());

                sf::Sprite sprite;
                sprite.setTexture(segmentTexture);
                sprite.setOrigin(2.0f,2);
                sprite.setPosition(30*bodyIter->GetPosition().x,30*bodyIter->GetPosition().y);
                sprite.setRotation((bodyIter->GetAngle()*(180-(180/3.14159))));
                window.draw(sprite);
                }
                else
                {
                    world.DestroyBody(bodyIter); //https://peaceful-refuge-13515.herokuapp.com/
                }

            }
            b2PolygonShape* polygonShape;
                sf::ConvexShape colShape;


                for (b2Fixture* f = bodyIter->GetFixtureList(); f; f = f->GetNext())
                {
                    b2Shape::Type shapeType = f->GetType();
                    if(shapeType == b2Shape::e_polygon)
                    {
                        polygonShape = (b2PolygonShape*)f->GetShape();
                        colShape.setPointCount(polygonShape->GetVertexCount());
                        int i = 0;
                        for(int ii = polygonShape->GetVertexCount()-1; ii>=0 ; ii--)
                        {
                            colShape.setPoint(ii,sf::Vector2f((polygonShape->GetVertex(i).x)*30,(polygonShape->GetVertex(i).y)*30));
                            i++;
                        }

                        /*colShape.setPoint(3,sf::Vector2f((polygonShape->GetVertex(0).x)*30,(polygonShape->GetVertex(0).y)*30));
                        colShape.setPoint(2,sf::Vector2f((polygonShape->GetVertex(1).x)*30,(polygonShape->GetVertex(1).y)*30));
                        colShape.setPoint(1,sf::Vector2f((polygonShape->GetVertex(2).x)*30,(polygonShape->GetVertex(2).y)*30));
                        colShape.setPoint(0,sf::Vector2f((polygonShape->GetVertex(3).x)*30,(polygonShape->GetVertex(3).y)*30));*/
                        colShape.setFillColor(sf::Color::Transparent);
                        colShape.setOutlineColor(sf::Color::Red);
                        colShape.setOutlineThickness(1);
                        colShape.setPosition(bodyIter->GetPosition().x*30,bodyIter->GetPosition().y*30);
                        colShape.setRotation((bodyIter->GetTransform().q.GetAngle()*(180-(180/3.14159))));

                    }
                    window.draw(colShape);
                }
                drawcount+=1;


        }
        //std::cout<<drawcount<<std::endl;
    cam.x*=0;
    cam.y*=0;
    window.draw(beam);
    window.draw(playerSprite);
     for(int i = 0; i<cList.size(); i++)
    {
        window.draw(cList[i]->getBody());
        window.draw(cList[i]->getRadius());
    }
    //window.draw(pineSprite);
    /*window.draw(queen1.getBody());
    window.draw(queen2.getBody());
    window.draw(queen3.getBody());
    window.draw(queen4.getBody());
    window.draw(queen5.getBody());
    window.draw(queen6.getBody());
    window.draw(queen7.getBody());
    /*window.draw(queen2.getBody());
    window.draw(queen3.getBody());*/
    window.display();
}



    return 0;
}
void createObject(b2World& world, float X, float Y,std::string name,int id)
{   /** BodyLoader**/
    BodyLoader bl;

    b2BodyDef bodyDef;
    //bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(1.25,1.25);
    b2Body* body = world.CreateBody(&bodyDef);
    b2FixtureDef fd;
    bl.attachFixture(body,name,fd);
    body->SetTransform(b2Vec2(X/30,Y/30),body->GetAngle());


    body->SetUserData((void*) id);



}
void CreatePlane(b2World& world, float X, float Y)
{

        /**prepares the Box**/
    b2BodyDef bodyDef;
    bodyDef.angularDamping =50.0f;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(X/30,Y/30);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBody;
    dynamicBody.SetAsBox((32.0f/2)/30,(32.0f/2)/30);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBody;
    fixtureDef.density = 100.0f;
    fixtureDef.friction = 0.0f;
    body->CreateFixture(&fixtureDef);
    body->SetUserData((void* )2);
}
void createSegment(b2World& world,b2Body* bod)
{
    float angle;
    b2BodyDef segBodyDef;
    segBodyDef.angularDamping =50.0f;
    segBodyDef.type = b2_kinematicBody;
    segBodyDef.position.Set(bod->GetPosition().x-10 ,bod->GetPosition().y-10);
    b2Body* body = world.CreateBody(&segBodyDef);
    b2PolygonShape kinBody;
    kinBody.SetAsBox((4.0f/2)/30,(4.0f/2)/30);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &kinBody;
    fixtureDef.density = 100.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);
    body->SetUserData((void* )3);
    angle = atan2(bod->GetPosition().x-body->GetPosition().x,bod->GetPosition().y-body->GetPosition().y);

    body->SetTransform(b2Vec2(bod->GetPosition().x,bod->GetPosition().y),angle);






}


int main9()
{
    /** The window we'll be using to display  stuff as well as its dimensional variables **/
    sf::Vector2f mapSize(5000,3000);
//    sf::Vector2f mapOrigin(-2500,)r
    sf::Vector2f wSize(800,600);
    sf::Vector2f mPos(0,0);
    sf::RenderWindow window(sf::VideoMode(wSize.x,wSize.y,32),"Hello Box2d");
    window.setFramerateLimit(60);
    sf::Event event;
    sf::Mouse mouse;
    float angle = 0;


/** Prepares the box2d world**/
    b2Vec2 grav(0.0f,0.0f);
    b2World world(grav);
    float32 timeStep = 1.0f/60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    MyContactListener mcl;
    world.SetContactListener(&mcl);
    world.SetAllowSleeping(false);
    /**Surrounding arena**/

 int x,y;
    x = 200;
    y = 100;
int rowcount = 0;


    for(int i = 0; i< 30;++i)
    {

        CreatePlane(world,x,y);
        x+=192;
        ++rowcount;
        if (rowcount == 6)
        {
            x = 200;
            y +=192;
            rowcount = 0;
        }

    }
    /** Textures and junk**/
    sf::Texture boxTexture;
    boxTexture.loadFromFile("box.png");


    Commander queen(sf::Vector2f(wSize.x/4,wSize.y/4),world);
    MapLoader ml;
    ml.loadMap("practice_map.json");

    //ifstream myFile;
    //myFile.open("pine_sprite.json");

   /* std::string json_ex = "{\"Layer\":\
                            [\"item1\", \
                            \"item2\"], \
                            \"not an array\": \
                            \"asdf\" \
                            }";*/

/*
    Json::Value rootValue;
    Json::Reader myReader;
    bool parsedSuccess = myReader.parse(myFile,
                                        rootValue,
                                        false);

    if(!parsedSuccess)
    {
        std::cout<<"failed to parse JSON"<< std::endl
        <<myReader.getFormattedErrorMessages()
        <<std::endl;
        return 1;
    }*/

    //const Json::Value layerValues = rootValue["layers"];
     //cout<< rootValue["pine_sprite"][1]["shape"][0]<<endl;
    /*for(unsigned int index = 1; inde<test_array.size(); ++index)
    {
        std::cout<<"Element "
                << index
                << " in array:"
                <<test_array[index].
                <<std::endl;
    }
*/
   /* const Json::Value test_notArray =
                        rootValue["not an array"];
    if(test_notArray.isNull())*/

    while(window.isOpen())
    {

        while (window.pollEvent(event))
        {
             if (event.type == sf::Event::Closed)
             {
                  window.close();

             }
             if(event.type == sf::Event::MouseButtonPressed)
             {

                 //queen.goToward(static_cast<sf::Vector2f>(mouse.getPosition(window)));
                // std::cout<< mouse.getPosition(window).x<< ","<< mouse.getPosition(window).y<<std::endl;
                 //std::cout<< (180-angle*(180/3.141592))<<std::endl;
               // std::cout<< queen.commanderBody->GetAngle()<<std::endl;



             }
             if(event.type == sf::Event::MouseMoved)
             {
                mPos = static_cast<sf::Vector2f>(mouse.getPosition(window));
             }

        }
/*
        if(queen.getPosition().x*30<0)
        {
            queen.setPosition(sf::Vector2f(wSize.x,queen.getPosition().y*30));
        }
        if(queen.getPosition().x*30>wSize.x)
        {
            queen.setPosition(sf::Vector2f(0,queen.getPosition().y*30));
        }
        if(queen.getPosition().y*30<0)
        {
            queen.setPosition(sf::Vector2f(queen.getPosition().x*30,wSize.y));
        }
         if(queen.getPosition().y*30>wSize.y)
        {
            queen.setPosition(sf::Vector2f(queen.getPosition().x*30,0));
        }*/
        //angle = atan2f(mouse.getPosition(window).x-(queen.getBody().getPosition().x),mouse.getPosition(window).y-(queen.getBody().getPosition().y));
        //queen.getBody().setRotation(angle);
        //queen.target(mPos);
        world.Step(timeStep,velocityIterations,positionIterations);
        queen.update(mPos);

        window.clear((sf::Color::White));
                  for(b2Body* bodyIter = world.GetBodyList(); bodyIter!=0; bodyIter = bodyIter->GetNext())
        {
            if((int)bodyIter->GetUserData() == 2)
            {
                b2Vec2 pos;
                //pos = bodyIter->GetPosition();
                //pos.x+=cam.x;
                //pos.y+=cam.y;
               // bodyIter->SetTransform(pos,bodyIter->GetAngle());

                sf::Sprite sprite;
                sprite.setTexture(boxTexture);
                sprite.setOrigin(16.0f,16.0f);
                sprite.setPosition(30*bodyIter->GetPosition().x,30*bodyIter->GetPosition().y);
                sprite.setRotation((bodyIter->GetAngle()*(180/3.14159)));
                window.draw(sprite);
                //std::cout<<playerSprite.getPosition().x<<std::endl;
                //std::cout<<playerSprite.getPosition().y<<std::endl;
            }
        }
        window.draw(queen.getBody());
        window.display();

    }
    return 0;

}
