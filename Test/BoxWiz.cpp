#include "BoxWiz.h"

b2Vec2 gravity(0.0f,0.0f);
b2World world(gravity);

BoxWiz::BoxWiz()
{
    /**Setup Window**/
    windowDim = sf::Vector2f(640,480);
    window = new sf::RenderWindow(sf::VideoMode(windowDim.x,windowDim.y),"BoxWiz Protoype");
    window->setFramerateLimit(60);
    GameState =In_Game;

    float32 timeStep = 1.0f/60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;



}

void BoxWiz::start(state curState)
{
    while(window->isOpen())
    {
        processInput(GameState);
        update(GameState);
        render(GameState);
    }

}

void BoxWiz::processInput(state curState)
{

}

void BoxWiz::update(state curState)
{

}

void BoxWiz::render(state curState)
{

}

/**int main()
{
    /**prepares ground
    b2BodyDef ground;
    ground.position.Set(400/SCALE,500/SCALE);
    b2Body* groundBody = world.CreateBody(&ground);
    b2PolygonShape groundBox;
    groundBox.SetAsBox((800/2)/SCALE,(16.0f/2)/SCALE);
    groundBody->CreateFixture(&groundBox,0.1f);
    return 0;
}**/


