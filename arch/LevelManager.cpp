#include "LevelManager.h"

std::vector<GameObject*> gObjList;
std::vector<Player*> chObjList;


/** Upon creation of the level manager object, it first parses the file for collision shapes **/
LevelManager::LevelManager()
{
    v2f_mapDimension = sf::Vector2f(0,0);
    v2f_tileDimension = sf::Vector2f(0,0);
    playerSprite.loadFromFile("assets/archii_texture.png");
    std::cout<<"loaded player_image"<<std::endl;

    playerTexture.loadFromImage(playerSprite);

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

Player *LevelManager::createCharacter(std::string shape,sf::Vector2f pos)
{
    Player* p = new Player(new MoveableBody(),new AnimatableGraphic(playerTexture));
    std::string name;


    b2PolygonShape polyShape;
        for(int i = 0; i < shapeRoot[shape].size(); i++)
        {
            b2Vec2 vertices[shapeRoot[shape][i]["shape"].size()/2];
            int x = shapeRoot[shape][i]["shape"].size()-2;
            int y = x+1;
            std::cout<<x<<std::endl;
	//FOr vertices in the "shapes array"
            for (int ii = 0; ii < shapeRoot[shape][i]["shape"].size(); ++ii)
            {
                if(x>=0)
                {
                    vertices[ii].Set((shapeRoot[shape][i]["shape"][x].asFloat()-p->_physicsBody->body->GetPosition().x*30.0)/30.0,
                                     (shapeRoot[shape][i]["shape"][y].asFloat()-p->_physicsBody->body->GetPosition().y*30.0)/30.0);

                    x-=2;
                    y = x+1;


                }

            }

        polyShape.Set(vertices,shapeRoot[shape][i]["shape"].size()/2);

        p->_physicsBody->fixtureDef.shape = &polyShape;
        p->_physicsBody->fixtureDef.friction = 0.0f;
        p->_physicsBody->fixtureDef.density = 2.0f;

        p->_physicsBody->body->CreateFixture(&p->_physicsBody->fixtureDef);
    }
    p->setPosition(pos.x,pos.y);


    return p;

}

GameObject  *LevelManager::createObject(std::string shape,sf::Vector2f pos)
{

   wallObject* w = new wallObject(new unMoveableBody());


    std::string name;

    b2Vec2 vertices[4];
    b2PolygonShape polyShape;






        for(int i = 0; i < shapeRoot[shape].size(); i++)
        {
            int x = 6;
            int y = x+1;
	//FOr vertices in the "shapes array"
            for (int ii = 0; ii < shapeRoot[shape][i]["shape"].size(); ++ii)
            {
                if(x>=0)
                {
                    vertices[ii].Set((shapeRoot[shape][i]["shape"][x].asInt()-w->_physicsBody->body->GetPosition().x*30)/30,
                                     (shapeRoot[shape][i]["shape"][y].asInt()-w->_physicsBody->body->GetPosition().y*30)/30);
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

///THE MAP FILE MUST FIRST BE OPENED AND PARSED FROM JSON TO VARIABLES*******/
/**********************************************************************/
/**********************************************************************/
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



        ///store the tileWidth Dimensions
        v2f_tileDimension = sf::Vector2f(baseMapRoot["tilewidth"].asFloat(),baseMapRoot["tileheight"].asFloat());
        ///store the tileCount Dimensions
        v2f_mapDimension = sf::Vector2f(baseMapRoot["width"].asFloat(),baseMapRoot["height"].asFloat());//*v2f_tileDimension.x,baseMapRoot["height"].asFloat()*v2f_tileDimension.y);


/**********************************************************************/
/**********************************************************************/
///Seperate the map layers
     for(int i = 0;i < baseMapRoot["layers"].size();++i)
        {
           // if(baseMapRoot["layers"][i]["type"].asString().compare("tileLayer"))
            //{
                mapLayers.push_back(baseMapRoot["layers"][i]);
            //}


        }

std::cout<<"Layers seperated"<<std::endl;


/**********************************************************************/
/**********************************************************************/

/**store spritesheet**/

    ///load and store sprite sheet from file into image
    spriteSheet.loadFromFile(baseMapRoot["tilesets"][0]["image"].asString());
    ///store sprite sheet from image into texture
    spriteSheetTexture.loadFromImage(spriteSheet);
    ///store sprite sheet dimensions in vector
    sf::Vector2f ssDim(baseMapRoot["tilesets"][0]["imagewidth"].asFloat(),baseMapRoot["tilesets"][0]["imageheight"].asFloat());


    ///store level data in a vector List
    for(int i = 0; i< mapLayers[0]["data"].size();++i)
    {
        level.push_back(mapLayers[0]["data"][i].asInt());
         //std::cout<<level[i]<<std::endl;
    }

/**********************************************************************/
/**********************************************************************/


    /** store tile coordinates from the spritesheet texture**/

    int x,y;
    x = 0;
    y = 0;
    //std::cout<<baseMapRoot["tilsets"]<<std::endl;
    for (int i = 0; i<baseMapRoot["tilesets"][0]["tilecount"].asInt(); ++i)
    {
        ssCoordinates.push_back(sf::Vector2f(x,y));
        x+=32;
        if(x == ssDim.x)
        {
            x = 0;
            y+=v2f_tileDimension.y;
        }

    }

    std::cout<<"Sprite Sheet stored"<<std::endl;

/**********************************************************************/
/**********************************************************************/


/**create and store objects**/

    /** to create and store the map,
     we will have to set numerous quads
      in the vertex array to represent each tile**/
    tileMap.setPrimitiveType(sf::Quads);
    ///Set the amount of vertices per quad the map will store based on the number of tiles.
    tileMap.resize(v2f_mapDimension.x*v2f_mapDimension.y*4);


    int xx,yy;
    xx = 0;
    yy = 0;
    int rowCount = 0;
    int colCount = 0;
    int j = 0;

    /** First, Loop through the level data to determine which tile is being placed.
        Second, check to see if the tile is not an empty tile.
        third, create a pointer to a quad in the vertex array and set the position of the tile based
        on an incremental pattern and it's position in the map.
        repeat for each column by row until map is stored with tiles.
        **/
    for(int i = 0; i<level.size(); ++i)
        {
            if(level[i]>0)
            {

            sf::Vertex* quad = &tileMap[j];

            quad[j].position=sf::Vector2f(xx,yy);
            quad[j+1].position=sf::Vector2f(xx+32,yy);
            quad[j+2].position=sf::Vector2f(xx+32,yy+32);
            quad[j+3].position=sf::Vector2f(xx,yy+32);

            quad[j].texCoords= sf::Vector2f(ssCoordinates[level[i]-1].x,ssCoordinates[level[i]-1].y);
            quad[j+1].texCoords= sf::Vector2f(ssCoordinates[level[i]-1].x+32,ssCoordinates[level[i]-1].y);
            quad[j+2].texCoords= sf::Vector2f(ssCoordinates[level[i]-1].x+32,ssCoordinates[level[i]-1].y+32);
            quad[j+3].texCoords= sf::Vector2f(ssCoordinates[level[i]-1].x,ssCoordinates[level[i]-1].y+32);
            }
            j+=2;
            xx+=32;
            ++rowCount;
            if(rowCount==v2f_mapDimension.x)
            {
                rowCount = 0;

                xx = 0;
                yy+=32;

            }


        }
/**Create Collision Objects **/
        for(int n = 0;n < baseMapRoot["layers"].size();n++)
        {






                           // if(baseMapRoot["layers"][n]["name"].asString().compare("collision"))
                            //{
                                for(int m = 0; m <baseMapRoot["layers"][n]["objects"].size();++m)
                                {   if(baseMapRoot["layers"][n]["name"].asString().compare("collision")==0)
                                    {
                                    /*
                                        std::cout<<"We made it"<<std::endl;
                                        gObjList.push_back(createObject(baseMapRoot["layers"][n]["objects"][m]["type"].asString(),
                                   sf::Vector2f(baseMapRoot["layers"][n]["objects"][m]["x"].asFloat(),
                                                baseMapRoot["layers"][n]["objects"][m]["y"].asFloat())));
                                        */
                                    }
                                    if(baseMapRoot["layers"][n]["name"].asString().compare("spawnPoints")==0)
                                    {


                                        chObjList.push_back(createCharacter(baseMapRoot["layers"][n]["objects"][m]["type"].asString(),
                                    sf::Vector2f(baseMapRoot["layers"][n]["objects"][m]["x"].asFloat(),
                                                 baseMapRoot["layers"][n]["objects"][m]["y"].asFloat())));


                                    }
                                }
                   // else
                    //{
                     //   std::cout<<"nothing"<<std::endl;
                    //}
                       /* *//*
                       for(int m = 0; m <baseMapRoot["layers"][n]["objects"].size();++m)
                        {


                        if(baseMapRoot["layers"][n]["objects"][m]["type"].asString().compare("archii_texture"))
                        {

                        }
                        else{
                                 std::cout<<"spawn"<<std::endl;

                        }

                        }



                    /*}
                    if(baseMapRoot["layers"][n]["name"].asString().compare("spawnPoints"))
                    {
                        for(int m = 0; m <baseMapRoot["layers"][n]["objects"].size();++m)
                        {

                        }
                    }
                    else
                    {

                    }


*/




        }

}

 void LevelManager::draw(sf::RenderTarget& target,sf::RenderStates states) const
{

    states.transform *=getTransform();

    states.texture= &spriteSheetTexture;

    target.draw(tileMap,states);
}
