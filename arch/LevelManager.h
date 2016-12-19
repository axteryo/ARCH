#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <iostream>
#include <fstream>
#include "dist/json/json.h"

#include <SFML/Graphics.hpp>
#include "unMoveableBody.h"
#include "MoveableBody.h"
#include "StaticGraphic.h"
#include "AnimatableGraphic.h"
#include "Actor.h"
#include "GameObject.h"

#include "wallObject.h"
#include "Player.h"
#include "Enemy_D1.h"
#include "includes.h"


extern std::vector<GameObject*> gObjList;
/**NOTE TO SELF Change this to Actor* type list**/
extern std::vector<Actor*> chObjList;
class LevelManager : public sf::Drawable, public sf::Transformable
{
    private:

        /** Map Array **/
        sf::VertexArray tileMap;

        sf::Image spriteSheet;
        sf::Image playerSprite;
        sf::Image d1Image;
        sf::Texture spriteSheetTexture;
        sf::Texture playerTexture;
        sf::Texture d1Texture;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        LevelManager();
        virtual ~LevelManager();
        void loadLevel(std::string mapFile);

        GameObject *createObject(std::string shape,sf::Vector2f pos);
        Actor *createCharacter(std::string shape,sf::Vector2f pos);

        /**Map dimensions(Tile Count)**/
        sf::Vector2f v2f_mapDimension;
        /**Tile dimensions in pixels**/
        sf::Vector2f v2f_tileDimension;
        /**A List for the maps layers **/
        std::vector<Json::Value> mapLayers;
        /**Sprite sheet coordinates**/
        std::vector<sf::Vector2f> ssCoordinates;

        /**Map data list**/
        std::vector<int> level;

        Json::Value baseMapRoot;
        Json::Reader myReader;
        std::ifstream currentMapFile;

        std::ifstream shapeFile;
        Json::Value shapeRoot;







    protected:

};

#endif // LEVELMANAGER_H
