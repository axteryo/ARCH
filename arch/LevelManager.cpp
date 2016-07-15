#include "LevelManager.h"

LevelManager::LevelManager()
{
    v2f_mapDimension = sf::Vector2f(0,0);
    v2f_tileDimension = sf::Vector2f(0,0);

    ///Loads up the necessary shapes
     shapeFile.open("assets/shape.json");
      bool parsedSuccess = myReader.parse(shapeFile,shapeRoot,false);
        if(!parsedSuccess)
        {
            std::cout<<"failed to parse JSON"<< std::endl
            <<myReader.getFormattedErrorMessages()<<std::endl;

        }
}

LevelManager::~LevelManager()
{
    //dtor
}
GameObject  *LevelManager::createObject()
{
    //return new wallObject(new unMoveableBody(),new StaticGraphic(texture));
}

void LevelManager::loadLevel(std::string mapFile)
{
    currentMapFile.open(mapFile);
        bool parsedSuccess = myReader.parse(currentMapFile,baseMapRoot,false);
        if(!parsedSuccess)
        {
            std::cout<<"failed to parse JSON"<< std::endl
            <<myReader.getFormattedErrorMessages()
            <<std::endl;
        }
}
