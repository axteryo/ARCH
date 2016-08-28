#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <math.h>

#include "dist/json/json.h"

int main()
{
    sf::Vector2f wSize(1000,800);
    sf::RenderWindow window(sf::VideoMode(wSize.x,wSize.y,32),"Hello MapTest");
    window.setFramerateLimit(60);
    sf::Event event;
    sf::Mouse mouse;
    std::string Input;



     /**Map dimensions(Tile Count)**/
   sf::Vector2f v2f_mapDimension;
   /**Tile dimensions in pixels**/
   sf::Vector2f v2f_tileDimension;
   /**A List for the maps layers **/
   std::vector<Json::Value> mapLayers;
   /**Sprite sheet coordinates**/
    std::vector<sf::Vector2f> ssCoordinates;
     sf::Image spriteSheet;
     /**Map data list**/
   std::vector<int> level;
    /** Map Array **/
     sf::VertexArray tileMap;





    Json::Value baseMapRoot;
    Json::Reader mapReader;
    std::ifstream currentMapFile;
    currentMapFile.open("testmap2.json");
    bool parsedSuccess = mapReader.parse(currentMapFile,baseMapRoot,false);
    if(!parsedSuccess)
    {
        std::cout<<"failed to parse JSON"<< std::endl
        <<mapReader.getFormattedErrorMessages()
        <<std::endl;
    }
     v2f_tileDimension = sf::Vector2f(baseMapRoot["tilewidth"].asFloat(),baseMapRoot["tileheight"].asFloat());
     v2f_mapDimension = sf::Vector2f(baseMapRoot["width"].asFloat(),baseMapRoot["height"].asFloat());

/**store spritesheet**/
    spriteSheet.loadFromFile(baseMapRoot["tilesets"][0]["image"].asString());
    for(int i = 0;i < baseMapRoot["layers"].size();++i)
    {
        mapLayers.push_back(baseMapRoot["layers"][i]);
    }

    for(int i = 0; i< mapLayers[0]["data"].size();++i)
    {
        level.push_back(mapLayers[0]["data"][i].asInt());
         std::cout<<level[i]<<std::endl;
    }


    /** store tile coordinates on texture**/
    sf::Vector2f ssDim(baseMapRoot["tilesets"][0]["imagewidth"].asFloat(),baseMapRoot["tilesets"][0]["imageheight"].asFloat());

    int x,y;
    x = 0;
    y = 0;
    //std::cout<<baseMapRoot["tilsets"]<<std::endl;
    for (int i = 0; i<baseMapRoot["tilesets"][0]["tilecount"].asInt(); ++i)
    {

        //std::cout<<x<<","<<y<<std::endl;
        ssCoordinates.push_back(sf::Vector2f(x,y));


        x+=32;

        if(x == ssDim.x)
        {

            x = 0;
            y+=v2f_tileDimension.y;
        }

    }
    std::cout<<level.size()<<std::endl;
     std::cout<<"Sprite Sheet stored"<<std::endl;

    tileMap.setPrimitiveType(sf::Quads);
      tileMap.resize(v2f_mapDimension.x*v2f_mapDimension.y*4);


    int xx,yy;
    xx = 0;
    yy = 0;
    int rowCount = 0;
    int colCount = 0;
    int j = 0;

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

            //std::cout<<i<<std::endl;


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
std::cout<<colCount<<std::endl;



    sf::Texture spriteSheetTexture;


    spriteSheetTexture.loadFromImage(spriteSheet);

    sf::Texture pineTexture;
    pineTexture.loadFromFile("pine_sprite.png");




/*
    tileMap[0].position=sf::Vector2f(0,0);
    tileMap[1].position=sf::Vector2f(32,0);
    tileMap[2].position=sf::Vector2f(32,32);
    tileMap[3].position=sf::Vector2f(0,32);

    tileMap[0].texCoords= sf::Vector2f(32,0);
    tileMap[1].texCoords= sf::Vector2f(64,0);
    tileMap[2].texCoords= sf::Vector2f(64,32);
    tileMap[3].texCoords= sf::Vector2f(32,32);

    tileMap[4].position=sf::Vector2f(64,0);
    tileMap[5].position=sf::Vector2f(96,0);
    tileMap[6].position=sf::Vector2f(96,32);
    tileMap[7].position=sf::Vector2f(64,32);

     tileMap[4].texCoords= sf::Vector2f(32,0);
    tileMap[5].texCoords= sf::Vector2f(64,0);
    tileMap[6].texCoords= sf::Vector2f(64,32);
    tileMap[7].texCoords= sf::Vector2f(32,32);
    */

    sf::Texture boxTexture;
    boxTexture.loadFromFile("box.png");







    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();

            }
        }
        window.clear(sf::Color::White);



        window.draw(tileMap,&spriteSheetTexture);
        window.display();

    }


    return 0;
}
