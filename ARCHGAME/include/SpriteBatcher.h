#ifndef SPRITEBATCHER_H
#define SPRITEBATCHER_H

#include "GraphicsComponent.h"
#include "entity.h"

//#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "json/json.h"

#include "batch.h"
#include "ActorEntity.h"

class batch;



class SpriteBatcher
{
    public:
        SpriteBatcher();
        virtual ~SpriteBatcher();
        void loadEntityTextures();
        void loadAnimations();
        void setBatchTexture(sf::Image i);
        void setFrameTexture(GraphicsComponent* g,std::string textureName);
        Animation setAnimation(std::string animationName);
        void addToBatch(entity* e,double alpha);
        void batchSprites();
        batch getBatch();
        batch b;


    protected:



    private:
        sf::VertexArray batch_vertArray;
        sf::Texture  batch_texture;
        std::vector<BatchQuad> batch_list;

        Json::Value textureRoot;
        Json::Reader myReader;
        std::ifstream textureFile;

        Json::Value animationRoot;
        Json::Reader animReader;
        std::ifstream animationFile;


};

#endif // SPRITEBATCHER_H
