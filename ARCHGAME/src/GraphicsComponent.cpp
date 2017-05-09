#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent()
{
    textureCoord = sf::IntRect(0,0,0,0);
    currentRenderState.position = sf::Vector2f(0,0);
    currentRenderState.rotation = 0;
    previousRenderState = currentRenderState;

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

void GraphicsComponent::update(entity* e)
{
    previousRenderState = State::to_renderState(e->getPreviousState());
    currentRenderState = State::to_renderState(e->getCurrentState());
}



GraphicsComponent::~GraphicsComponent()
{
    //dtor
}
