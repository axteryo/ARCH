#include "Game.h"

GameController controller;



Game::Game()
{
    v2f_windowSize = sf::Vector2f(1024,768);
    window = new sf::RenderWindow(sf::VideoMode(v2f_windowSize.x,v2f_windowSize.y),"Initiative_ARCH");
    tempView = sf::View(sf::Vector2f(90,600),v2f_windowSize);
    tempView.zoom(1.25);
    gameCamera.setCoords(sf::Vector2i(90,600),sf::Vector2f(1024,768));
    world->SetContactListener(collisionSystem);


    gameRunning = true;

    dt = 1.0f/60.0f;

    timeStep = 1.0/60.0f;
    velocityIterations = 6;
    positionIterations = 2;
    isVsynced = true;
    window->setVerticalSyncEnabled(isVsynced);

}

void Game::start()
{

    double lastTime = 0.0;
    double newTime = 0.0;
    lastTime=clock.getElapsedTime().asSeconds();
    double elapsed = 0.0;
    double accumulator = 0.0;
    int t = 0.0;
    int counter = 0;
    int counterRun = 0;
    int lastCounter = 0;




    ///Game Controller Bindings are loaded
    controller.loadBindings();
    ///load function is called here to load the entities and assets of the game level
    gameLevel.setup();
    gameLevel.load("data/testLevel.json");
    gameLevel.initiate();

    while(window->isOpen())
    {
        ///Process user input
        processInput();

        /// The clock goes forward so we store the current time in newTime
        ///Then we get how much has elapsed bu subtracting the lastTime
        newTime = clock.getElapsedTime().asSeconds();
        elapsed = newTime-lastTime;

        lastTime = newTime;
        accumulator +=elapsed;

        double alpha;

      ///update logic at a fixed rate of 60
        if(isVsynced)
        {

            while(accumulator<dt)
            {
                //std::cout<<"LEFTOVER TIME:"
                //<<accumulator<<std::endl;
                //std::cout<<"Elapsed time:"<<1/elapsed<<std::endl;

                accumulator+=(dt/60);
                //std::cout<<"we are here"<<std::endl;
                //std::cout<<"LEFTOVER TIME:"
                //<<accumulator<<std::endl;
            }


        }

        while(accumulator>=dt)
        {
            accumulator-=dt;
            gameLevel.physicsUpdate(dt,accumulator);
            collisionSystem->update();
            update(dt);
        }
        for(int i = 0; i<deathStack.size();i++)
        {

            if(deathStack.top()!=nullptr)
            {
                //entity* e = deathStack.top();
                delete deathStack.top();
            }

            deathStack.pop();
        }

        alpha = (accumulator/dt);

        ///render freely
        render(alpha);
        if (!gameRunning)
        {
            window->close();
        }
    }

}
void Game::_end()
{
    gameRunning = false;
}
void Game::render(double alpha)
{
    window->setView(gameCamera.camView);
    window->clear(sf::Color::Black);
    gameLevel.render(window,alpha);
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
                _end();
            }
            if(keyBoard.isKeyPressed(keyBoard.Num1))
            {
                if(isVsynced)
                {
                    isVsynced = false;
                    std::cout<<"VSync is OFF"<<std::endl;
                }
                else
                {
                    isVsynced = true;
                     std::cout<<"VSync is ON"<<std::endl;
                    //clock.restart();
                }
                window->setVerticalSyncEnabled(isVsynced);
            }
        }
        if(event.type == sf::Event::MouseMoved)
        {

        }
        if(event.type == sf::Event::Resized)
        {


           gameCamera.camView.setSize(v2f_windowSize.x+384,v2f_windowSize.y-48);
           gameCamera.camView.zoom(1.6);
           //window->setView();//event.size.width+512, event.size.height+1024);
            std::cout << "new width: " << event.size.width << std::endl;
            std::cout << "new height: " << event.size.height << std::endl;
        }
    }

}


Game::~Game()
{
    delete window;

    //dtor
}
