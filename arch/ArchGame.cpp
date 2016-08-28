#include "ArchGame.h"
#include "LevelManager.h"




b2Vec2 gravity = b2Vec2(0,0);
b2World* world = new b2World(gravity);

ArchGame::ArchGame()
{
    v2f_windowSize = sf::Vector2f(800,600);
    window = new sf::RenderWindow(sf::VideoMode(v2f_windowSize.x,v2f_windowSize.y), "Project_Arch");
    window->setFramerateLimit(60);
    GameState = In_Game;
    timeStep = 1.0f/60.0f;
    velocityIterations = 8;
    positionIterations = 3;

    t.loadFromFile("RightTriangle_Left.png");

    //w = new wallObject(new unMoveableBody, new StaticGraphic(t));

    gameRunning = true;
}


void ArchGame::start()
{
    LevelManager lm;
    lm.loadLevel("testmap3.json");

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
        for(int i = 0; i<gObjList.size();++i)
        {
            gObjList[i]->update();

        }


        break;
    }
    world->Step(timeStep,velocityIterations,positionIterations);

}

void ArchGame::render(state currentState)
{
    switch(GameState)
    {
    case Main_Menu:

        break;
    case In_Game:
        window->clear(sf::Color::White);
        for(int i = 0; i<gObjList.size();++i)
        {

            window->draw(gObjList[i]->getSprite());


        }
        std::cout<<"failed here"<<std::endl;

        ///DEBUG COLLISION DRAWER
       /* for(b2Body* bodyIter = world->GetBodyList(); bodyIter!=0; bodyIter = bodyIter->GetNext())
        {
b2PolygonShape* polygonShape;
                sf::ConvexShape colShape;
                colShape.setPointCount(4);

                for (b2Fixture* f = bodyIter->GetFixtureList(); f; f = f->GetNext())
                {
                    b2Shape::Type shapeType = f->GetType();
                    if(shapeType == b2Shape::e_polygon)
                    {
                        polygonShape = (b2PolygonShape*)f->GetShape();
                        colShape.setPoint(3,sf::Vector2f((polygonShape->GetVertex(0).x)*30,(polygonShape->GetVertex(0).y)*30));
                        colShape.setPoint(2,sf::Vector2f((polygonShape->GetVertex(1).x)*30,(polygonShape->GetVertex(1).y)*30));
                        colShape.setPoint(1,sf::Vector2f((polygonShape->GetVertex(2).x)*30,(polygonShape->GetVertex(2).y)*30));
                        colShape.setPoint(0,sf::Vector2f((polygonShape->GetVertex(3).x)*30,(polygonShape->GetVertex(3).y)*30));
                        colShape.setFillColor(sf::Color::Transparent);
                        colShape.setOutlineColor(sf::Color::Red);
                        colShape.setOutlineThickness(.5);
                        colShape.setPosition(bodyIter->GetPosition().x*30,bodyIter->GetPosition().y*30);
                        colShape.setRotation((bodyIter->GetTransform().q.GetAngle()*(180-(180/3.14159))));
                        window->draw(colShape);
                    }
                }
        }*/
        //window->draw(w->getSprite());
        window->display();

        break;
    }

}
