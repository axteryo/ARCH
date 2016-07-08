#include "ArchGame.h"




b2Vec2 gravity = b2Vec2(0,0);
b2World* world = new b2World(gravity);

ArchGame::ArchGame()
{
    v2f_windowSize = sf::Vector2f(800,600);
    window = new sf::RenderWindow(sf::VideoMode(v2f_windowSize.x,v2f_windowSize.y), "Project_Arch");
    window->setFramerateLimit(60);
    GameState = Main_Menu;
    timeStep = 1.0f/60.0f;
    velocityIterations = 8;
    positionIterations = 3;

    gameRunning = true;
}


void ArchGame::start()
{
    while(window->isOpen())
    {
        processInput(GameState);
        update(GameState);
        render(GameState);
        if (!gameRunning)
        {
            window->close();
        }

    }
}

void ArchGame::processInput(state currentState)
{
    switch(GameState)
    {
    case Main_Menu:
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                gameRunning = false;
            }
            if(event.type == sf::Event::KeyPressed)
            {

            }
        }
        break;
    case In_Game:
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                gameRunning = false;
            }
        }
        break;
    }

}

void ArchGame::update(state currentState)
{
    switch(GameState)
    {
    case Main_Menu:

        break;
    case In_Game:

        break;
    }

}

void ArchGame::render(state currentState)
{
    switch(GameState)
    {
    case Main_Menu:
        window->clear(sf::Color::White);
        window->display();
        break;
    case In_Game:
        window->clear(sf::Color::White);
        window->display();
        break;
    }

}
