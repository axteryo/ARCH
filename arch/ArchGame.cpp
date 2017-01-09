#include "ArchGame.h"
#include "LevelManager.h"




b2Vec2 gravity = b2Vec2(0,0);
b2World* world = new b2World(gravity);


ArchGame::ArchGame()
{

    world->SetAllowSleeping(true);
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
    colFactory = new collisionFactory();
    subject = "object_player";
    world->SetContactListener(colFactory);
    p = nullptr;


    //t.loadFromFile("RightTriangle_Left.png");

    //w = new wallObject(new unMoveableBody, new StaticGraphic(t));

    gameRunning = true;
}


void ArchGame::start()
{

    level.loadLevel("track.json");
    controller.loadBinding();
    dynamicCam->camView.setSize(1400, 1200);

      /* if(chObjList[ii]->objectId == "object_enemy")
          {
              Enemy_D1* e;
              e =(Enemy_D1*)chObjList[ii];
              e->setTarget(p);

          }*/


    float lastTime = 0;
    float currentTime = 0;
    float fps = 0;

    while(window->isOpen())
    {
         for(int ii = 0; ii<chObjList.size();++ii)
        {
            if(chObjList[ii]->objectId == "object_player")
               {
                    p =(Player*)chObjList[ii];
               }
        }



        processInput(GameState);
         while (accumulator > ups)
        {

            accumulator -= ups;
            update(GameState);
            dynamicCam->follow(targ);
            world->Step(timeStep,velocityIterations,positionIterations);
        }

        render(GameState);






        //std::cout<<accumulator.asSeconds()<<std::endl;

        accumulator += clock.restart();
        fps = 1/cl.getElapsedTime().asSeconds();
        //std::cout<<"Body count:"<<world->GetBodyCount()<<std::endl;
        //std::cout<<"proxycount:"<<world->GetProxyCount()<<std::endl;


        cl.restart();
        //std::cout<<fps<<std::endl;



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


                dynamicCam->camView.setSize(event.size.width+400, event.size.height+200);
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;

                //std::cout << "View size x " << dynamicCam->camView.getSize().x <<std::endl;
                 //std::cout << "View size y " << dynamicCam->camView.getSize().y <<std::endl;


                // zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
                //dynamicCam->camView.zoom(2.5f);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                {

                     level.closeLevel();
                     level.loadLevel("testmap4.json");
                }
                  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                {
                    level.closeLevel();
                    level.loadLevel("track.json");
                }

                if(p)
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
                if(p)
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
        for(int ii = 0; ii<chObjList.size();++ii)
        {
            chObjList[ii]->update();


            if(subject==chObjList[ii]->objectId)
            {
                 targ = sf::Vector2i((chObjList[ii]->b2V_position.x*30)+(cos(chObjList[ii]->fl_rotation)*175)+(20*(chObjList[ii]->b2V_velocity.x)),
                                                 (chObjList[ii]->b2V_position.y*30)+(sin(chObjList[ii]->fl_rotation)*175)+(20*(chObjList[ii]->b2V_velocity.y)));
            }
        }
        for(int i = 0; i<gObjList.size();++i)
        {

            gObjList[i]->update();
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


        window->clear(sf::Color::Black);
        window->setView(dynamicCam->getView());
        window->draw(level);
        for(int ii = 0; ii<chObjList.size();++ii)
        {
            //
            window->draw(chObjList[ii]->getSprite());
        }
        //window->draw(p->getSprite());
        window->setView(dynamicCam->getView());




//for(int ii = 0; ii<chObjList.size();++ii)
  //      {


    //    }



        ///DEBUG COLLISION DRAWER

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

        break;
    }

}
