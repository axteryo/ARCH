#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <iostream>
#include <fstream>
#include "dist/json/json.h"

#include "unMoveableBody.h"
#include "MoveableBody.h"
#include "StaticGraphic.h"
#include "AnimatableGraphic.h"
#include "wallObject.h"

extern std::vector<GameObject*> gObjList;
class LevelManager
{
    public:
        LevelManager();
        virtual ~LevelManager();
        void loadLevel(std::string mapFile);
         GameObject *createObject(int data,sf::Vector2f pos);

        /**Map dimensions(Tile Count)**/
        sf::Vector2f v2f_mapDimension;
        /**Tile dimensions in pixels**/
        sf::Vector2f v2f_tileDimension;
        /**A List for the maps layers **/
        std::vector<Json::Value> mapLayers;
        /**Sprite sheet coordinates**/
        std::vector<sf::Vector2f> ssCoordinates;

        Json::Value baseMapRoot;
        Json::Reader myReader;
        std::ifstream currentMapFile;

        std::ifstream shapeFile;
        Json::Value shapeRoot;


        /**Map data list**/
        sf::Image spriteSheet;
        sf::Texture texture;



    protected:
    private:
};

#endif // LEVELMANAGER_H
