#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H


#include "entity.h"

struct Frame
{
    sf::IntRect textureCoords;
    int duration;
};
struct Animation
{
    std::string animationName;
    std::string tag;
    int duration;
    int currentFrame;
    std::vector<Frame> frames;
};


class GraphicsComponent
{
    public:
        GraphicsComponent();
        virtual ~GraphicsComponent();

        void update(entity* e);
        //sf::Vector2f getPosition();
        renderState getCurrentState();
        renderState getPreviousState();

        void addAnimation(Animation anim);
        void onPlayAnimation(std::string animation);
        void onPlayAnimationByTag(std::string animTag);

        void playAnimation();

        sf::IntRect getTextureCoord();

        void setFrame(sf::IntRect c);
        void setDefaultFrame(sf::IntRect c);
        //void setState(States::renderState r);
    protected:




        /**Render Notes
            Sprite Batch:Place all character textures on one image.
            Possibly make GraphicsComponent Drawable
            Look into TexturePacker shoebox**/

        //sf::Texture texture;

    private:
        sf::IntRect defaultFrame;
        sf::IntRect textureCoord;
        renderState currentRenderState;
        renderState previousRenderState;
        std::vector<Animation> animationList;
        Animation currentAnimation;
        bool playingAnimation;

        int frameCounter;

};

#endif // GRAPHICSCOMPONENT_H
