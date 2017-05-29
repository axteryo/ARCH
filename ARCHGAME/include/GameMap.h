#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include "json/json.h"

#include "batch.h"
#include "level.h"
#include "ObjectEntity.h"



class GameMap// : public sf::Drawable, public sf::Transformable
{
    public:
        GameMap();
        virtual ~GameMap();

        void loadFile(std::string mapFile);
        void create();
        void close();

        std::vector<spawnPoint> getSpawnSpoints();
        std::vector<TriggerEntity*> getTriggers();


        batch getFirstLayer();
        batch getSecondLayer();
        batch layer1;
        batch layer2;
        std::vector<ObjectEntity*> walls;
        std::vector<TriggerEntity*> triggers;
        std::vector<spawnPoint> spawnData;

    protected:
    private:

        Json::Value baseMapRoot;
        Json::Reader mapReader;
        std::ifstream currentMapFile;
        sf::Image mapImage;
        sf::Texture mapTexture;
        sf::Vector2f v2f_mapDimensions;
        sf::Vector2f v2f_tileDimensions;
        sf::Vector2f v2f_textureSheetDimensions;
        std::vector<sf::Vector2f> textureSheetCoords;
        std::vector<int> levelData;


        std::vector<std::vector<int>> layerData;






};

#endif // GAMEMAP_H
