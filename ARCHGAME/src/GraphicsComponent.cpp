#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent()
{
    textureCoord = sf::IntRect(0,0,0,0);
    defaultFrame = sf::IntRect(0,0,0,0);
    currentRenderState.position = sf::Vector2f(0,0);
    currentRenderState.rotation = 0;
    previousRenderState = currentRenderState;
    playingAnimation = false;
    frameCounter = 0;

}

renderState GraphicsComponent::getCurrentState()
{
    return currentRenderState;
}
renderState GraphicsComponent::getPreviousState()
{
    return previousRenderState;
}

sf::IntRect GraphicsComponent::getTextureCoord()
{
    return textureCoord;
}
void GraphicsComponent::setFrame(sf::IntRect c)
{
    textureCoord = c;
}
void GraphicsComponent::setDefaultFrame(sf::IntRect c)
{
    defaultFrame = c;
}

void GraphicsComponent::update(entity* e)
{
    previousRenderState = State::to_renderState(e->getPreviousState());
    currentRenderState = State::to_renderState(e->getCurrentState());
    playAnimation();
}

void GraphicsComponent::playAnimation()
{
       if(!playingAnimation)
        {
        //std::cout<<"We are getting here"<<std::endl;
        setFrame(defaultFrame);

        }

        else
        {
            if(frameCounter<=0)
            {

                frameCounter = currentAnimation.duration;
                setFrame(currentAnimation.frames[currentAnimation.currentFrame]);

                currentAnimation.currentFrame+=1;
            }
            if(currentAnimation.currentFrame>=currentAnimation.frames.size())
            {
                playingAnimation = false;
                Animation b;
                currentAnimation = b;
            }
            frameCounter-=1;
        }
}

void GraphicsComponent::onPlayAnimation(std::string animation)
{
    if(!playingAnimation)
    {
        for(int i = 0;i<animationList.size();i++)
        {
            if(animation.compare(animationList[i].animationName)==0)
            {
                currentAnimation = animationList[i];
                playingAnimation = true;
            }
        }
    }

}
void GraphicsComponent::onPlayAnimationByTag(std::string animation)
{
    if(!playingAnimation)
    {
        for(int i = 0;i<animationList.size();i++)
        {
            if(animation.compare(animationList[i].tag)==0)
            {
                currentAnimation = animationList[i];
                playingAnimation = true;
            }
        }
    }

}

void GraphicsComponent::addAnimation(Animation anim)
{
    animationList.push_back(anim);
}



GraphicsComponent::~GraphicsComponent()
{
    //dtor
}
