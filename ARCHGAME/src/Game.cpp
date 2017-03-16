#include "Game.h"

GameController controller;

Game::Game()
{
    v2f_windowSize = sf::Vector2f(1024,768);
    window = new sf::RenderWindow(sf::VideoMode(v2f_windowSize.x,v2f_windowSize.y),"Initiative_ARCH");
    window->setVerticalSyncEnabled(true);
    //world->SetAutoClearForces(false);

    gameRunning = true;

    dt = .01f;

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

    ///Game Controller Bindings are loaded
    controller.loadBindings();
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
        while(accumulator>=timeStep)
        {
            ///increment accumulator
            accumulator-=timeStep;
            ///update logic
                update(dt);
            ///update Physics
            world->Step(timeStep,velocityIterations,positionIterations);
            //world->Step(timeStep,velocityIterations,positionIterations);
            //world->ClearForces();



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
    window->clear(sf::Color::Black);
    gameLevel.render(window);
    /*for(b2Body* bodyIter = world->GetBodyList(); bodyIter!=0; bodyIter = bodyIter->GetNext())
        {
                b2PolygonShape* polygonShape;
                //sf::ConvexShape colShape;
                //sf::Shape colShape;
                //colShape = sf::ConvexShape;



                for (b2Fixture* f = bodyIter->GetFixtureList(); f; f = f->GetNext())
                {
                    b2Shape::Type shapeType = f->GetType();
                    if(shapeType == b2Shape::e_polygon)
                    {
                        sf::ConvexShape colShape;
                        polygonShape = (b2PolygonShape*)f->GetShape();
                         colShape.setPointCount(polygonShape->GetVertexCount());
                        int i = 0;
                        for(int ii = polygonShape->GetVertexCount()-1; ii>=0 ; ii--)
                        {
                            colShape.setPoint(ii,sf::Vector2f((polygonShape->GetVertex(i).x)*30,(polygonShape->GetVertex(i).y)*30));
                            i++;
                        }
                        colShape.setFillColor(sf::Color::Transparent);
                        colShape.setOutlineColor(sf::Color::Blue);
                        colShape.setOutlineThickness(1);
                        colShape.setPosition(bodyIter->GetPosition().x*30,bodyIter->GetPosition().y*30);
                        colShape.setRotation((bodyIter->GetTransform().q.GetAngle()*((180/3.14159))));
                        window->draw(colShape);

                    }
                    if(shapeType == b2Shape::e_circle)
                    {

                        polygonShape = (b2PolygonShape*)f->GetShape();
                        sf::CircleShape colShape;
                        colShape.setFillColor(sf::Color::Transparent);
                        colShape.setOutlineColor(sf::Color::Red);
                        colShape.setOutlineThickness(1);
                        colShape.setOrigin(polygonShape->m_radius*30,polygonShape->m_radius*30);
                        colShape.setRadius(polygonShape->m_radius*30);
                        colShape.setPosition(bodyIter->GetPosition().x*30,bodyIter->GetPosition().y*30);
                        window->draw(colShape);
                    }

                }

        }*/
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
