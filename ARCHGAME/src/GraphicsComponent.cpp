#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent()
{
    textureCoord = sf::IntRect(0,0,0,0);
    currentRenderState.position = sf::Vector2f(0,0);
    currentRenderState.rotation = 0;
    previousRenderState = currentRenderState;

}

States::renderState GraphicsComponent::getCurrentState()
{
    return currentRenderState;
}
States::renderState GraphicsComponent::getPreviousState()
{
    return previousRenderState;
}

sf::IntRect GraphicsComponent::getTextureCoord()
{
    return textureCoord;
}
void GraphicsComponent::setTextureCoord(sf::IntRect c)
{
    textureCoord = c;
}

void GraphicsComponent::update(entity* e)
{
    previousRenderState = currentRenderState;
    currentRenderState.position=States::to_v2f(e->getPosition());
    currentRenderState.rotation=States::to_degrees(e->getRotation());
}

GraphicsComponent::~GraphicsComponent()
{
    //dtor
}
