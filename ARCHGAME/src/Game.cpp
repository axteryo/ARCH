#include "Game.h"



Game::Game()
{
    v2f_windowSize = sf::Vector2f(1024,768);
    window = new sf::RenderWindow(sf::VideoMode(v2f_windowSize.x,v2f_windowSize.y),"Initiative_ARCH");
    window->setVerticalSyncEnabled(false);

    gameRunning = true;

    dt = 1.0f/30.0f;

    timeStep = 1.0/60.0;
    velocityIterations = 6;
    positionIterations = 2;


}

void Game::start()
{
    float lastTime = 0.0;
    float newTime = 0.0;
    lastTime=clock.getElapsedTime().asSeconds();
    float elapsed = 0.0;
    float accumulator = 0.0;
    ///load function is called here to load the entities and assets of the game level
    gameLevel.load();

    while(window->isOpen())
    {
        /// The clock goes forward so we store the current time in newTime
        ///Then we get how much has elapsed bu subtracting the lastTime
        newTime = clock.getElapsedTime().asSeconds();
        elapsed = newTime-lastTime;

        if(elapsed>0.25)
        {
            elapsed = 0.25;
        }

        lastTime = newTime;
        accumulator +=elapsed;

        ///Process user input
        processInput();

        ///update logic at a fixed rate of 30
        while(accumulator>=dt)
        {
            ///increment accumulator
            accumulator-=dt;
            ///update logic
            update(dt);
            ///update Physics
            world->Step(timeStep,velocityIterations,positionIterations);

        }
        ///render freely
        render();
        if (!gameRunning)
        {
            window->close();
        }
    }

}
void Game::render()
{
    window->clear(sf::Color::White);
    gameLevel.render(window);
    window->display();
}
/** The game is updated **/
void Game::update(float dt)
{
    gameLevel.update(dt);
}

/** Input is Processed through the windows pollEvent() function **/
void Game::processInput()
{
    while(window->pollEvent(event))
    {
        if(event.type==sf::Event::Closed)
        {
            gameRunning = false;
        }
        ///Closes the window if the escape key is pressed
        if(event.type == sf::Event::KeyPressed)
        {
            if(keyBoard.isKeyPressed(keyBoard.Escape))
            {
                gameRunning = false;
            }
        }
        if(event.type == sf::Event::MouseMoved)
        {

        }
    }

}


Game::~Game()
{
    delete window;

    //dtor
}
