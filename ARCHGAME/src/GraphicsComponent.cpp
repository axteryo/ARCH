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
    //playAnimation();
}

void GraphicsComponent::playAnimation()
{
       /*if(!playingAnimation)
        {
        //std::cout<<"We are getting here"<<std::endl;
        setFrame(defaultFrame);

        }

        else
        {
            if(frameCounter<=0)
            {

                frameCounter = currentAnimation.frames[currentAnimation.currentFrame].duration;
                setFrame(currentAnimation.frames[currentAnimation.currentFrame].textureCoords);

                currentAnimation.currentFrame+=1;
            }
            if(currentAnimation.currentFrame>=currentAnimation.frames.size())
            {
                playingAnimation = false;
                Animation b;
                currentAnimation = b;
            }
            frameCounter-=1;
        }*/
}

void GraphicsComponent::onPlayAnimation(std::string animation)
{
    /*if(!playingAnimation)
    {
        for(int i = 0;i<animationList.size();i++)
        {
            if(animation.compare(animationList[i].animationName)==0)
            {
                currentAnimation = animationList[i];
                playingAnimation = true;
            }
        }
    }*/

}
void GraphicsComponent::onPlayAnimationByTag(std::string animation)
{
    /*if(!playingAnimation)
    {
        for(int i = 0;i<animationList.size();i++)
        {
            if(animation.compare(animationList[i].tag)==0)
            {
                currentAnimation = animationList[i];
                playingAnimation = true;
            }
        }
    }*/

}

void GraphicsComponent::addAnimation(Animation anim)
{
    //animationList.push_back(anim);
}

BatchQuad GraphicsComponent::getQuad()
{
    BatchQuad quad;
    quad.point1 = sf::Vector2f(currentRenderState.position.x-textureCoord.width/2,currentRenderState.position.y+textureCoord.height/2);
    quad.point2 = sf::Vector2f(currentRenderState.position.x+textureCoord.width/2,currentRenderState.position.y+textureCoord.height/2);
    quad.point3 = sf::Vector2f(currentRenderState.position.x+textureCoord.width/2,currentRenderState.position.y-textureCoord.height/2);
    quad.point4 = sf::Vector2f(currentRenderState.position.x-textureCoord.width/2,currentRenderState.position.y-textureCoord.height/2);

    quad.texPoint1 = sf::Vector2f(textureCoord.left,textureCoord.top);
    quad.texPoint2 = sf::Vector2f(textureCoord.left+textureCoord.width,textureCoord.top);
    quad.texPoint3 = sf::Vector2f(textureCoord.left+textureCoord.width,textureCoord.top+textureCoord.height);
    quad.texPoint4 = sf::Vector2f(textureCoord.left,textureCoord.top+textureCoord.height);

    ///Set the rotation of the quad based on the graphicComponents container entity
    quad.center = sf::Vector2f((quad.point1.x+quad.point2.x+quad.point3.x+quad.point4.x)/4,
                               (quad.point1.y+quad.point2.y+quad.point3.y+quad.point4.y)/4);
    quad.rotation =currentRenderState.rotation;
    sf::Transform rotation;
    rotation.rotate(quad.rotation,quad.center);
    quad.point1 = rotation.transformPoint(quad.point1);
    quad.point2 =rotation.transformPoint(quad.point2);
    quad.point3 =rotation.transformPoint(quad.point3);
    quad.point4 =rotation.transformPoint(quad.point4);

    return quad;
}

GraphicsComponent::~GraphicsComponent()
{
    //dtor
}
