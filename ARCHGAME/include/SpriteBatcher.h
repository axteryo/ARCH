#ifndef SPRITEBATCHER_H
#define SPRITEBATCHER_H

#include "GraphicsComponent.h"
//#include "entity.h"
#include "player.h"
//#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "json/json.h"

#include "batch.h"

class batch;



class SpriteBatcher
{
    public:
        SpriteBatcher();
        virtual ~SpriteBatcher();
        void loadEntityTextures();
        void setBatchTexture(sf::Image i);
        void setFrameTexture(GraphicsComponent* g,std::string textureName);
        void addToBatch(entity* e,double alpha);
        void batchSprites();
        batch getBatch();
        batch b;




    protected:
        struct batchQuad
        {
            sf::Vector2f point1;
            sf::Vector2f point2;
            sf::Vector2f point3;
            sf::Vector2f point4;

            sf::Vector2f texPoint1;
            sf::Vector2f texPoint2;
            sf::Vector2f texPoint3;
            sf::Vector2f texPoint4;

            sf::Vector2f center;
            float rotation;
        };





    private:
        sf::VertexArray batch_vertArray;
        sf::Texture  batch_texture;
        std::vector<batchQuad> batch_list;

        Json::Value textureRoot;
        Json::Reader myReader;
        std::ifstream textureFile;


};

#endif // SPRITEBATCHER_H
