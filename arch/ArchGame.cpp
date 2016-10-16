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



    //t.loadFromFile("RightTriangle_Left.png");

    //w = new wallObject(new unMoveableBody, new StaticGraphic(t));

    gameRunning = true;
}


void ArchGame::start()
{

    level.loadLevel("testmap.json");
    controller.loadBinding();

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
            if (event.type == sf::Event::KeyPressed)
            {
                if(controller.isActionKeyPressed("activateThrusters"))
                {
                     for(int ii = 0; ii<chObjList.size();++ii)
                    {
                        chObjList[ii]->activateThrusters();
                    }
                }
                if(controller.isActionKeyPressed("turnRight"))
                {
                     for(int ii = 0; ii<chObjList.size();++ii)
                    {

                        chObjList[ii]->turnRight();
                        std::cout<<chObjList[ii]->_graphicsBody->sprite.getRotation()<<","<<chObjList[ii]->_physicsBody->body->GetAngle()*(180/3.14159) <<std::endl;
                    }

                }
                if(controller.isActionKeyPressed("turnLeft"))
                {
                     for(int ii = 0; ii<chObjList.size();++ii)
                    {
                        chObjList[ii]->turnLeft();
                    }
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {

                    if(controller.isActionKeyReleased("activateThrusters",event))
                {
                     for(int ii = 0; ii<chObjList.size();++ii)
                    {
                        chObjList[ii]->cancelThrusters();
                    }
                }
                else if(controller.isActionKeyReleased("turnRight",event))
                {
                     for(int ii = 0; ii<chObjList.size();++ii)
                    {
                        chObjList[ii]->cancelRightTurn();
                    }

                }
                if(controller.isActionKeyReleased("turnLeft", event))
                {
                     for(int ii = 0; ii<chObjList.size();++ii)
                    {
                        chObjList[ii]->cancelLeftTurn();
                    }
                }

            }
        }
        break;
    }

}

void ArchGame::update(state currentState)
{
    world->Step(timeStep,velocityIterations,positionIterations);

    switch(GameState)
    {
    case Main_Menu:


        break;
    case In_Game:
        for(int i = 0; i<gObjList.size();++i)
        {
            gObjList[i]->update();

        }
        for(int ii = 0; ii<chObjList.size();++ii)
        {
            chObjList[ii]->update();


        }


        break;
    }

}

void ArchGame::render(state currentState)
{
    switch(GameState)
    {
    case Main_Menu:

        break;
    case In_Game:
        window->clear(sf::Color::White);

window->draw(level);
        for(int ii = 0; ii<chObjList.size();++ii)
        {
            window->draw(chObjList[ii]->getSprite());
        }



        ///DEBUG COLLISION DRAWER

        for(b2Body* bodyIter = world->GetBodyList(); bodyIter!=0; bodyIter = bodyIter->GetNext())
        {
                b2PolygonShape* polygonShape;
                sf::ConvexShape colShape;


                for (b2Fixture* f = bodyIter->GetFixtureList(); f; f = f->GetNext())
                {
                    b2Shape::Type shapeType = f->GetType();
                    if(shapeType == b2Shape::e_polygon)
                    {
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

                    }

                }
                //window->draw(colShape);
        }



        window->display();

        break;
    }

}
