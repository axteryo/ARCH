#include "ArchGame.h"
#include "LevelManager.h"




b2Vec2 gravity = b2Vec2(0,0);
b2World* world = new b2World(gravity);


ArchGame::ArchGame()
{
    v2f_windowSize = sf::Vector2f(1000,800);
    window = new sf::RenderWindow(sf::VideoMode(v2f_windowSize.x,v2f_windowSize.y), "Project_Arch");
    //window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    GameState = In_Game;
    timeStep = 1.0f/60.0f;
    velocityIterations = 8;
    positionIterations = 3;

    accumulator = sf::Time::Zero;
    ups = sf::seconds(1.f / 60.0f);
    playerAlive = false;

    dynamicCam = new cam(sf::Vector2f(0,0), v2f_windowSize);
    subject = "object_player";



    //t.loadFromFile("RightTriangle_Left.png");

    //w = new wallObject(new unMoveableBody, new StaticGraphic(t));

    gameRunning = true;
}


void ArchGame::start()
{

    level.loadLevel("track.json");
    controller.loadBinding();
    dynamicCam->camView.setSize(1400, 1200);
    for(int ii = 0; ii<chObjList.size();++ii)
    {
        if(chObjList[ii]->objectId == "object_player")
           {

                p =(Player*)chObjList[ii];
                playerAlive= true;

           }

    }

    while(window->isOpen())
    {

        render(GameState);
        processInput(GameState);
         while (accumulator > ups)
        {
            accumulator -= ups;
            update(GameState);
            dynamicCam->follow(targ);
        }
        window->setView(dynamicCam->getView());
        accumulator += clock.restart();



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
            if(event.type == sf::Event::Resized)
            {


                dynamicCam->camView.setSize(event.size.width+400, event.size.height+362);
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;

                //std::cout << "View size x " << dynamicCam->camView.getSize().x <<std::endl;
                 //std::cout << "View size y " << dynamicCam->camView.getSize().y <<std::endl;


                // zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
                //dynamicCam->camView.zoom(2.5f);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if(playerAlive)
                {
                    if(controller.isActionKeyPressed("activateThrusters"))
                    {
                        // for(int ii = 0; ii<chObjList.size();++ii)
                        //{
                            p->activateThrusters();
                        //}
                    }
                    if(controller.isActionKeyPressed("turnRight"))
                    {
                        // for(int ii = 0; ii<chObjList.size();++ii)
                        //{

                            p->turnRight();
                            //std::cout<<chObjList[ii]->_graphicsBody->sprite.getRotation()<<","<<chObjList[ii]->_physicsBody->body->GetAngle()*(180/3.14159) <<std::endl;
                        //}

                    }
                    if(controller.isActionKeyPressed("turnLeft"))
                    {
                         //for(int ii = 0; ii<chObjList.size();++ii)
                        //{
                            p->turnLeft();
                        //}
                    }


                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if(playerAlive)
                {
                    if(controller.isActionKeyReleased("activateThrusters",event))
                    {
                         //for(int ii = 0; ii<chObjList.size();++ii)
                        //{
                            p->cancelThrusters();
                        //}
                    }
                    else if(controller.isActionKeyReleased("turnRight",event))
                    {
                         //for(int ii = 0; ii<chObjList.size();++ii)
                        //{
                            p->cancelRightTurn();
                        //}

                    }
                    if(controller.isActionKeyReleased("turnLeft", event))
                    {
                         //for(int ii = 0; ii<chObjList.size();++ii)
                        //{
                            p->cancelLeftTurn();
                        //}
                    }
                }

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
        for(int ii = 0; ii<chObjList.size();++ii)
        {
            chObjList[ii]->update();
            if(subject==chObjList[ii]->objectId)
            {
                 targ = sf::Vector2f((chObjList[ii]->b2V_position.x*30)+cos(chObjList[ii]->fl_rotation)*0,
                                                 (chObjList[ii]->b2V_position.y*30)+sin(chObjList[ii]->fl_rotation)*0);
                                                 /*targ = targ+ sf::Vector2f(cos(chObjList[ii]->fl_rotation)*10,
                                                                     sin(chObjList[ii]->fl_rotation)*10);*/


            }
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
        window->clear(sf::Color::Black);

        window->draw(level);
        for(int ii = 0; ii<chObjList.size();++ii)
        {
            window->draw(chObjList[ii]->getSprite());
        }
//for(int ii = 0; ii<chObjList.size();++ii)
  //      {


    //    }



        ///DEBUG COLLISION DRAWER

        /*for(b2Body* bodyIter = world->GetBodyList(); bodyIter!=0; bodyIter = bodyIter->GetNext())
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
               window->draw(colShape);
        }*/



        window->display();

        break;
    }

}
