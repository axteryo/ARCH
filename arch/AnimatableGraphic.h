#ifndef ANIMATABLEGRAPHIC_H
#define ANIMATABLEGRAPHIC_H

#include "GraphicsBody.h"


class AnimatableGraphic: public GraphicsBody
{
    public:
        AnimatableGraphic(sf::Texture t);
        virtual ~AnimatableGraphic();
        void update(GameObject* gObj);
        sf::Sprite getSprite();
    protected:
    private:
};

#endif // ANIMATABLEGRAPHIC_H
