#include "SpriteBatcher.h"

SpriteBatcher::SpriteBatcher()
{
    //ctor
}
void SpriteBatcher::setBatchTexture(sf::Image i)
{
    if(!batch_texture.loadFromImage(i))
    {
        std::cout<<"Unable to load batch texture"<<std::endl;
    }

}
void SpriteBatcher::addToBatch(entity* e)
{
    GraphicsComponent* g;
    States::renderState state;
    if(e->getID().compare("entity_player")==0)
    {
        player* p;
        p = static_cast<player*>(e);
        g = p->getGraphic();
        g->update(e);
        state = g->getCurrentState();

    }



}

SpriteBatcher::~SpriteBatcher()
{

}
