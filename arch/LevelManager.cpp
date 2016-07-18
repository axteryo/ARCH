#include "LevelManager.h"

std::vector<GameObject*> gObjList;
LevelManager::LevelManager()
{
    v2f_mapDimension = sf::Vector2f(0,0);
    v2f_tileDimension = sf::Vector2f(0,0);

    ///Loads up the necessary shapes
     shapeFile.open("shapes.json");
      bool parsedSuccess = myReader.parse(shapeFile,shapeRoot,false);
        if(!parsedSuccess)
        {
            std::cout<<"failed to parse JSON"<< std::endl
            <<myReader.getFormattedErrorMessages()<<std::endl;

        }
        else
            std::cout<<"The shapeFile has been parsed"<<std::endl;
}

LevelManager::~LevelManager()
{
    //dtor
}

GameObject  *LevelManager::createObject(int data,sf::Vector2f pos)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);

    texture.loadFromImage(spriteSheet,sf::IntRect(ssCoordinates[data-1].x,
                                                  ssCoordinates[data-1].y
                                                  ,32,32));

   wallObject* w = new wallObject(new unMoveableBody(),new StaticGraphic(texture));


    std::string name;
    b2Vec2 vertices[4];
    b2PolygonShape polyShape;
    if(data == 1)
    {
        name = "RightTriangle_Left";
    }

    else if(data == 2)
    {
        name = "Square";
    }

    else if (data == 3)
    {
        name = "RightTriangle_Right";
    }

    else if (data == 4)
    {
        name = "RightTriangle_LeftUp";
    }

    else if (data == 5)
    {
        //name = "RightTriangl"
    }

    else if (data == 6)
    {
        name = "RightTriangle_RightUp";
    }

        for(int i = 0; i < shapeRoot[name].size(); i++)
        {
            int x = 6;
            int y = x+1;
	//FOr vertices in the "shapes array"
            for (int ii = 0; ii < shapeRoot[name][i]["shape"].size(); ++ii)
            {
                if(x>=0)
                {
                    vertices[ii].Set((shapeRoot[name][i]["shape"][x].asInt()-w->_physicsBody->body->GetPosition().x*30)/30,
                                     (shapeRoot[name][i]["shape"][y].asInt()-w->_physicsBody->body->GetPosition().y*30)/30);
                    x-=2;
                    y = x+1;
                }
            }
            int counter = 4;
            polyShape.Set(vertices,counter);
        w->_physicsBody->fixtureDef.shape = &polyShape;
        w->_physicsBody->fixtureDef.friction = 0.0f;
        w->_physicsBody->fixtureDef.density = 2.0f;

        w->_physicsBody->body->CreateFixture(&w->_physicsBody->fixtureDef);
    }
    w->setPosition(pos.x,pos.y);

return w;
}

void LevelManager::loadLevel(std::string mapFile)
{

///Open the mapfile and parse it
    currentMapFile.open(mapFile);
    bool parsedSuccess = myReader.parse(currentMapFile,baseMapRoot,false);
    if(!parsedSuccess)
        {
            std::cout<<"failed to parse JSON"<< std::endl
            <<myReader.getFormattedErrorMessages()
            <<std::endl;
        }
    else
        {
            std::cout<<"Map file has been parsed"<<std::endl;
        }
        v2f_tileDimension = sf::Vector2f(baseMapRoot["tilewidth"].asFloat(),baseMapRoot["tileheight"].asFloat());
        v2f_mapDimension = sf::Vector2f(baseMapRoot["width"].asFloat()*v2f_tileDimension.x,baseMapRoot["height"].asFloat()*v2f_tileDimension.y);

///Seperate the map layers
     for(int i = 0;i < baseMapRoot["layers"].size();++i)
        {
            mapLayers.push_back(baseMapRoot["layers"][i]);
        }
std::cout<<"Layers seperated"<<std::endl;
///Store the spritesheet
    spriteSheet.loadFromFile(baseMapRoot["tilesets"][0]["image"].asString());
    texture.loadFromImage(spriteSheet);
    sf::Vector2f ssDim(baseMapRoot["tilesets"][0]["imagewidth"].asFloat(),baseMapRoot["tilesets"][0]["imageheight"].asFloat());

    int x,y;
    x = 0;
    y = 0;
    //std::cout<<baseMapRoot["tilsets"]<<std::endl;
    for (int i = 0; i<baseMapRoot["tilesets"][0]["tilecount"].asInt(); ++i)
    {

        std::cout<<x<<","<<y<<std::endl;
        ssCoordinates.push_back(sf::Vector2f(x,y));


        x+=v2f_tileDimension.x;

        if(x == ssDim.x)
        {

            x = 0;
            y+=v2f_tileDimension.y;
        }

    }

    std::cout<<"Sprite Sheet stored"<<std::endl;

///create and store objects
    int xx,yy;
    xx = 0;
    yy = 0;
    int rowCount = 0;
    for(int i = 0; i<mapLayers.size(); ++i)
    {
        for(int j = 0; j<mapLayers[i]["data"].size(); ++j)
        {

            if(mapLayers[i]["data"][j].asInt()>0)
            {
                gObjList.push_back(createObject(mapLayers[i]["data"][j].asInt(),sf::Vector2f(xx,yy)));
                std::cout<<yy<<std::endl;
                //std::cout<<mapLayers[i]["data"][j]<<std::endl;
            }


            xx+=32;
            ++rowCount;
            if(rowCount==10)
            {
                rowCount = 0;
                xx = 0;
                yy+=32;
            }

        }


    }
    std::cout<<"Objects created"<<std::endl;
}
