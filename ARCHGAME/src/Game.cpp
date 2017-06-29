#include "Game.h"
#include "AudioSystem.h"

GameController controller;




Game::Game()
{
    v2f_windowSize = sf::Vector2f(1024,768);
    window = new sf::RenderWindow(sf::VideoMode(v2f_windowSize.x,v2f_windowSize.y),"Initiative_ARCH");

    gameCamera.setCoords(sf::Vector2i(90,600),v2f_windowSize);
    world->SetContactListener(collisionSystem);
    audioSystem->loadAudio();
    isVsyncOn = true;
    isCollisionViewOn = false;
    gameRunning = true;
    dt = 1.0f/60.0f;
    timeStep = 1.0/60.0f;
    velocityIterations = 6;
    positionIterations = 2;
    //isVsynced = true;
    window->setVerticalSyncEnabled(isVsyncOn);
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
    //audioSystem->playAudio("metalClang1");
    int i = GameEventQueue.size();
    while(i>=1)
    {
        std::cout<<GameEventQueue.size()<<std::endl;
        delete GameEventQueue.front();
        GameEventQueue.pop();
        i--;
    }
    while(window->isOpen())
    {


        ///Process user input
        processInput();

        /// The clock goes forward so we store the current time in newTime
        ///Then we get how much has elapsed bu subtracting the lastTime
        newTime = clock.getElapsedTime().asSeconds();
        elapsed =clock.restart().asSeconds(); //newTime-lastTime;
//        std::cout<<"Elapsed time:"<<1/elapsed<<std::endl;

        lastTime = newTime;
        accumulator +=elapsed;

        double alpha;

      ///update logic at a fixed rate of 60
        if(isVsyncOn)
        {
            int a = 0;
            while(accumulator<dt)
            {
                //std::cout<<"Elapsed time:"<<1/elapsed<<std::endl;
                accumulator+=(dt/80);
                //std::cout<<"we are here"<<std::endl;
                //std::cout<<"LEFTOVER TIME:"
                //<<accumulator<<std::endl;
                //a++;
            }
            //std::cout<<a<<std::endl;
        }

        while(accumulator>=dt)
        {
            accumulator-=dt;
            gameLevel.physicsUpdate(dt,accumulator);
            collisionSystem->update();
            update(dt);
            int i = GameEventQueue.size();

            while(i>=1)
            {
               // std::cout<<GameEventQueue.size()<<std::endl;
               switch(GameEventQueue.front()->getEventType())
                {
                case GameEvent::EVENT_ACTION:
                    audioSystem->handleEvent(GameEventQueue.front());
                    break;

                case GameEvent::EVENT_COLLISION:
                    audioSystem->handleEvent(GameEventQueue.front());
                    break;

                case GameEvent::EVENT_ENTITY:
                    break;

                case GameEvent::EVENT_SEQUENCE:
                    audioSystem->handleEvent(GameEventQueue.front());
                    gameLevel.handleEvent(GameEventQueue.front());
                    break;

                case GameEvent::EVENT_GAMESTATE:
                    audioSystem->handleEvent(GameEventQueue.front());
                    gameLevel.handleEvent(GameEventQueue.front());
                    break;

                case GameEvent::EVENT_MENU:
                    audioSystem->handleEvent(GameEventQueue.front());
                    break;
                }


                delete GameEventQueue.front();
                GameEventQueue.pop();
                i--;
            }
        }
        audioSystem->update();
        alpha = (accumulator/dt);

        /**REMOVES ENTITIES**/
        clean();
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
    refresh();
    gameLevel.render(window,alpha);
    if(isCollisionViewOn)
    {
        for(b2Body* bodyIter = world->GetBodyList(); bodyIter!=0; bodyIter = bodyIter->GetNext())
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
        }
         window->draw(gameCamera.camBoundary);
    }

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
                toggleVsync();
            }
            if(keyBoard.isKeyPressed(keyBoard.Num2))
            {
                toggleCollisionView();
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

void Game::toggleCollisionView()
{
    if(isCollisionViewOn)
    {
        isCollisionViewOn = false;
    }
    else
    {
        isCollisionViewOn = true;
    }
}

void Game::toggleVsync()
{
    if(isVsyncOn)
    {
        isVsyncOn = false;
        std::cout<<"VSYNC IS OFF"<<std::endl;
    }
    else
    {
        isVsyncOn = true;
        std::cout<<"VSYNC IS ON"<<std::endl;
    }
    window->setVerticalSyncEnabled(isVsyncOn);
}

void Game::refresh()
{
    window->setView(gameCamera.camView);
    window->clear(sf::Color::Black);
}

void Game::clean()
{
   int i = deathStack.size();
   while(i>=1)
   {
        std::cout<<deathStack.top()->getID()<<" has been deleted"<<std::endl;
        delete deathStack.top();
        deathStack.pop();
        i--;
   }
}



Game::~Game()
{
    delete window;

    //dtor
}
