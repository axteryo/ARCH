#include "Game.h"
#include "AudioSystem.h"
#include <string>



Game::Game()
{
    v2f_windowSize = sf::Vector2f(1024,768);
    window = new sf::RenderWindow(sf::VideoMode(v2f_windowSize.x,v2f_windowSize.y),"Initiative_ARCH");

    gameCamera.setCoords(sf::Vector2i(0,0),v2f_windowSize);
    world->SetContactListener(collisionSystem);
    audioSystem->loadAudio();
    controller.loadDefaultBindings();


    lastTime = 0.0;
    newTime = 0.0;
    lastTime=clock.getElapsedTime().asSeconds();
    elapsed = 0.0;
    accumulator = 0.0;
    alpha = 0.0;
    isVsyncOn = true;
    isCollisionViewOn = false;
    gameRunning = true;

    dt = 1.0f/60.0f;
    timeStep = 1.0/60.0f;
    velocityIterations = 6;
    positionIterations = 2;

    window->setVerticalSyncEnabled(isVsyncOn);
    GameState = new GameStateManager();

    currentInterface = nullptr;
    interfaceRoot =json.loadJson("data/InterfaceData.json");
    textureRoot = json.loadJson("data/gui_textures.json");

    sf::Image im;
    im.loadFromFile("assets/gui_textures.png");
    interface_batcher.setBatchTexture(im);
    gameCamera.update();

    for(int i = 0;i <interfaceRoot["interface"].size();i++)
    {
        Interface* in = new Interface(interfaceRoot["interface"][i]["name"].asString(),new GameEventListener());
        for(int ii = 0; ii <interfaceRoot["interface"][i]["ui_elements"].size();ii++)
        {
            UI_Element* e;
            if(interfaceRoot["interface"][i]["ui_elements"][ii]["ui_type"].asString().compare("panel")==0)
            {
                e = new UI_Panel(interfaceRoot["interface"][i]["ui_elements"][ii]["id"].asString());
                in->setMainPanel(static_cast<UI_Panel*>(e));
            }
            else if(interfaceRoot["interface"][i]["ui_elements"][ii]["ui_type"].asString().compare("button")==0)
            {
                e = new UI_Button(interfaceRoot["interface"][i]["ui_elements"][ii]["id"].asString());
                in->addButton(static_cast<UI_Button*>(e));
            }

            for(int j = 0;j <textureRoot["frames"].size();j++)
            {
                if(textureRoot["frames"][j]["filename"].asString().compare(interfaceRoot["interface"][i]["ui_elements"][ii]["texture"].asString())==0)
                {
                    sf::IntRect frame = sf::IntRect(textureRoot["frames"][j]["frame"]["x"].asInt(),
                            textureRoot["frames"][j]["frame"]["y"].asInt(),
                            textureRoot["frames"][j]["frame"]["w"].asInt(),
                            textureRoot["frames"][j]["frame"]["h"].asInt());

                    e->setGraphicCoordinates(frame);
                }
                if(e->getID().compare("button")==0);
                {
                    if(textureRoot["frames"][j]["filename"].asString().compare(interfaceRoot["interface"][i]["ui_elements"][ii]["on_control_over"]["texture"].asString())==0)
                    {
                        sf::IntRect frame = sf::IntRect(textureRoot["frames"][j]["frame"]["x"].asInt(),
                            textureRoot["frames"][j]["frame"]["y"].asInt(),
                            textureRoot["frames"][j]["frame"]["w"].asInt(),
                            textureRoot["frames"][j]["frame"]["h"].asInt());
                    e->setOnControlOverTexture(frame);
                    }
                }

            }
            e->setRelativePosition(sf::Vector2f(interfaceRoot["interface"][i]["ui_elements"][ii]["relative_position"][0].asFloat(),
                                                interfaceRoot["interface"][i]["ui_elements"][ii]["relative_position"][1].asFloat()));
        }
        interfaceList.push_back(in);
    }

    setCurrentInterFace("MainMenu");
    currentInterface->activate();
}

void Game::start()
{

    while(window->isOpen())
    {

        ///Process user input
        processInput();
        newTime = clock.getElapsedTime().asSeconds();
        elapsed =clock.restart().asSeconds();
        lastTime = newTime;
        accumulator +=elapsed;



        /****************************************/
        switch(GameState->system_game_state)
        {
            case GameState->SYSTEM_IN_MAIN_MENU:
                runMainMenu();
            break;
            /****************************************/
            case GameState->SYSTEM_START_LEVEL:
                gameLevel.setup();
                GameState->system_game_state = GameState->SYSTEM_IN_LEVEL;
            break;
           /****************************************/
            case GameState->SYSTEM_IN_LEVEL:
            if(isVsyncOn)
            {
                while(accumulator<dt)
                {
                    accumulator+=(dt/80);
                }
            }
                switch(GameState->level_game_state)
                {
                    case GameState->LEVEL_LOADING:
                        gameLevel.load("data/testLevel.json");
                        gameLevel.initiate();
                        GameState->level_game_state =GameState->LEVEL_IN_GAME;
                    break;
                     /****************************************/
                    case GameState->LEVEL_IN_GAME:
                        runGameLevel();
                    break;
                    /*****************************************/
                    case GameState->LEVEL_PAUSED:
                    break;
                     /****************************************/
                }
            break;
            /****************************************/
        }
        /****************************************/
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
    //gameCamera.update();
    refresh();

    switch(GameState->system_game_state)
    {
        case GameState->SYSTEM_IN_MAIN_MENU:
            window->draw(currentInterface->mainPanel->getRectBody());
            interface_batcher.addQuad(currentInterface->mainPanel->getQuad());
            for(int i = 0;i<currentInterface->buttonList.size();i++)
            {
                window->draw(currentInterface->buttonList[i]->getRectBody());
                interface_batcher.addQuad(currentInterface->buttonList[i]->getQuad());
            }
            interface_batcher.batchQuads();
            window->draw(interface_batcher);
            //currentInterface->draw(window);
        break;
        /****************************************/
        case GameState->SYSTEM_IN_LEVEL:
            gameLevel.render(window,alpha);
            /****************************************/
            switch(GameState->level_game_state)
            {
                case GameState->LEVEL_PAUSED:
                break;
            }
            /****************************************/
        break;
        /****************************************/
    }


    switch(GameState->debug_state)
    {
        case GameState->DEBUG_OFF:
        break;
        /****************************************/
        case GameState->DEBUG_ON:
            /*int val = 1/elapsed;
            st
            elapsedText.setString("FPS : " + text);
            elapsedText.setCharacterSize(10);
            elapsedText.setFillColor(sf::Color::White);

                    //std::cout<<"LEFTOVER TIME:"
                    //<<accumulator<<std::endl;*/
            /****************************************/
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
            /****************************************/
            window->draw(gameCamera.camBoundary);
            //window->draw(elapsedText);
        break;
        /****************************************/

    }


    window->display();
}
/** The game is updated **/
void Game::update(float dt)
{

}

/** Input is Processed through the windows pollEvent() function **/
void Game::processInput()
{
    while(window->pollEvent(event))
    {
        if(currentInterface!=nullptr)
        {
            currentInterface->processWindowEvents(event);
            if(currentInterface->isActive())
            {

                currentInterface->update(controller);
            }
        }
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

void Game::setCurrentInterFace(std::string i)
{
    if(currentInterface!=nullptr)
    {
        currentInterface->deactivate();
    }
    for(int j = 0;j<interfaceList.size();j++)
    {
        if(interfaceList[j]->getID().compare(i)==0)
        {
            currentInterface = interfaceList[j];
            currentInterface->setup(gameCamera.camView);
            break;
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


/**The Core**/
void Game::runMainMenu()
{
        while(accumulator>=dt)
        {
            accumulator-=dt;

            //mainMenu->update();
            resolveEvents();
        }

}
void Game::runGameLevel()
{
        ///update logic at a fixed rate of 60
        while(accumulator>=dt)
        {
            accumulator-=dt;
            gameLevel.physicsUpdate(dt,accumulator);
            collisionSystem->update();
            gameLevel.update(dt);
            resolveEvents();
        }
}

void Game::handleEvent(GameEvent* e)
{
    switch(e->getEventType())
    {
    case GameEvent::EVENT_INTERFACE:
        GameEvent_Interface* interfaceEvent = static_cast<GameEvent_Interface*>(e);
        switch(interfaceEvent->interface_state)
        {
        case BUTTON_SELECT:
            if(interfaceEvent->btnID.compare("start_button")==0)
            {
                currentInterface->deactivate();
                GameState->system_game_state = GameState->SYSTEM_START_LEVEL;
            }

            break;
        }
        break;
    }
}

void Game::resolveEvents()
{
           int i = GameEventQueue.size();
            while(i>=1)
            {
               switch(GameEventQueue.front()->getEventType())
                {
                case GameEvent::EVENT_ACTION:
                    audioSystem->handleEvent(GameEventQueue.front());
                    handleEvent(GameEventQueue.front());
                    break;

                case GameEvent::EVENT_COLLISION:
                    audioSystem->handleEvent(GameEventQueue.front());
                    break;

                case GameEvent::EVENT_ENTITY:
                    handleEvent(GameEventQueue.front());
                    break;

                case GameEvent::EVENT_SEQUENCE:
                    audioSystem->handleEvent(GameEventQueue.front());
                    gameLevel.handleEvent(GameEventQueue.front());
                    handleEvent(GameEventQueue.front());
                    break;

                case GameEvent::EVENT_GAMESTATE:
                    audioSystem->handleEvent(GameEventQueue.front());
                    gameLevel.handleEvent(GameEventQueue.front());
                    break;

                case GameEvent::EVENT_INTERFACE:
                    audioSystem->handleEvent(GameEventQueue.front());
                    handleEvent(GameEventQueue.front());
                    break;
                case GameEvent::EVENT_AUDIO:
                    audioSystem->handleEvent(GameEventQueue.front());
                    gameLevel.handleEvent(GameEventQueue.front());
                    break;
                }
                delete GameEventQueue.front();
                GameEventQueue.pop();
                i--;
            }
}

Game::~Game()
{
    delete window;

    //dtor
}
