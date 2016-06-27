#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <math.h>
#include "Store.h"
#include "Pong.h"
#include "BoxWiz.h"
#include "Actor.h"
#include "GameObj.h"


using namespace std;
using namespace sf;
using std::vector;

//Sfml Main
void pause(int t)
  {
      this_thread::sleep_for(chrono::seconds(t));
  }
class pBody
{
//private:
public:
    int rad;
    float mas;
    sf::Vector2f wDim;
    sf::CircleShape body;
    sf::Vector2f location;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;


    pBody(int radius,float mass,Vector2f loc, Vector2f dimension)
    {
        wDim = dimension;
        rad = radius;
        mas = mass;
        location = loc;
        velocity = sf::Vector2f(0,0);
        acceleration = sf::Vector2f(0,0);
        body.setRadius(radius);
        body.setPointCount(60);
        body.setFillColor(sf::Color::Blue);
        body.setPosition(location);
        body.setOutlineThickness(1);
        body.setOutlineColor(sf::Color::White);
    }
    void update()
    {
        velocity+=acceleration;
        location+=velocity;
        body.setPosition(location);
        acceleration.x*=0;
        acceleration.y*=0;
        if(sqrt((velocity.x*velocity.x)+(velocity.y*velocity.y)) > 10)
        {
            //cout<< velocity.x*velocity.x<< endl;
            float mag = sqrt((velocity.x*velocity.x)+(velocity.y*velocity.y));
            if (mag != 0)
                {

                    velocity.x/=mag;
                    velocity.y/=mag;

                }

            velocity.x*=10;
            velocity.y*=10;
            //cout<< velocity.x << endl;
        }

    }
        void checkEdges()
    {
        if (location.x < 0 )
            {
            location.x = wDim.x;
            //velocity.x *= -1;
            }
        if (location.x + (rad+rad)>wDim.x)
        {
            location.x = wDim.x -(rad+rad);
            //velocity.x *= -1;
        }
        if (location.y < 0 )
            {
            location.y = 0;
            //velocity.y *= -1;

            }
        if (location.y +(rad+rad) >wDim.y)
        {
            location.y = wDim.y - (rad+rad);
            //velocity.y *= -1;
            //applyForce(Vector2f(0,-10));

        }
         if (location.x == wDim.x/2 && location.y == wDim.y/2)
        {
            delete this;
        }


    }

    sf::CircleShape getBody()
    {
        return body;
    }

    sf::Vector2f getLocation()
    {
        return location;
    }

    void applyForce(Vector2f force)
    {
        sf::Vector2f f = force;
        f.x/=mas;
        f.y/=mas;
        acceleration +=f;
    }
    sf::Vector2f getVelocity()
    {
        sf::Vector2f v;
        v = velocity;
        return v;
    }

};



class launcher
{
public:
    launcher()
    {

    }
private:

};


 bool grounded;
class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact)
    {
        ///Check if fixture A is the player
        void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if((int)bodyUserData == 1)
        std::cout<<"This is the player"<<std::endl;


        bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if((int)bodyUserData == 2)
        std::cout<<"This is the Ground"<<std::endl;
        grounded = true;


    }
    void EndContact(b2Contact* contact)
    {
         ///Check if fixture A is the player
        void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if((int)bodyUserData == 1)
        {

        bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if((int)bodyUserData == 2)
            grounded = false;
        }


    }

};
MyContactListener mcl;

/** We need this to easily convert between pixel and real-world coordinates*/
static const float SCALE = 30.f;

/** Create the base for the boxes to land */
void CreateGround( float X, float Y);

/** Create the boxes */
void CreateBox(b2World& World, int mouseX, int mouseY);
vector<GameObj*> groundList;
int main4()
{
//    Actor player1;
    /** The window we'll be using to display  stuff as well as its dimensional variables **/
    sf::Vector2f wSize(800,600);
    sf::RenderWindow window(sf::VideoMode(wSize.x,wSize.y,32),"Hello Box2d");
    window.setFramerateLimit(60);
    sf::Event event;
    sf::Mouse mouse;

    b2Vec2 gravity;
    b2World world(gravity);

    grounded = false;
    world.SetContactListener(&mcl);


    /** Prepare the box2d world**/



    /**prepares ground**/
    /*b2BodyDef ground;
    ground.position.Set(400/SCALE,500/SCALE);
    b2Body* groundBody = world.CreateBody(&ground);
    b2PolygonShape groundBox;
    groundBox.SetAsBox((800/2)/SCALE,(16.0f/2)/SCALE);
    groundBody->CreateFixture(&groundBox,0.1f);*/
    /*CreateGround(0,wSize.y );
    CreateGround(32,wSize.y);
    CreateGround(64,wSize.y);
    CreateGround(96,wSize.y);
    CreateGround(128,wSize.y);
    CreateGround(160,wSize.y);
    CreateGround(192,wSize.y );
    CreateGround(224,wSize.y);
    CreateGround(256,wSize.y);
    CreateGround(288,wSize.y);*/


    int x,y;
    x = 0;
    y = 0;


    for(int i = 0; i< 30;++i)
    {
        CreateGround(x,wSize.y);
        x+=32;

    }


/*

    b2BodyDef leftWall;
    leftWall.angle = 3.14159f/2;
    leftWall.position.Set(0/SCALE,300/SCALE);
    b2Body* lwBody = world.CreateBody(&leftWall);
    b2PolygonShape lwBox;
    lwBox.SetAsBox((800/2)/SCALE,(16.0f/2)/SCALE);
    b2FixtureDef lwFixture;
    lwFixture.shape = &lwBox;
    lwFixture.density = 0.1f;
    lwFixture.friction = 0.0f;
    lwBody->CreateFixture(&lwFixture);
    //lwBody->SetUserData((void*) 3);



    b2BodyDef rightWall;
    rightWall.position.Set((800.0f)/SCALE,(600.0f)/SCALE);
    rightWall.angle = -3.14159f/2.0f;
    b2Body* rwBody = world.CreateBody(&rightWall);
    b2PolygonShape rwBox;
    rwBox.SetAsBox((800/2)/SCALE,(16.0f/2)/SCALE);
    rwBody->CreateFixture(&rwBox,0.1f);
    //rwBody->SetUserData((void*) 3);

*/





    float32 timeStep = 1.0f/60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    b2Vec2 vel;



    /**Textures and junk**/
    sf::Texture groundTexture;
    sf::Texture boxTexture;
    groundTexture.loadFromFile("ground.png");
    boxTexture.loadFromFile("box.png");


    /**Player stuff**/
    sf::Sprite playerSprite;
    playerSprite.setTexture(boxTexture);
    playerSprite.setOrigin(16.0f,16.0f);

    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(wSize.x/2/30,wSize.y/2/30);
    playerBodyDef.fixedRotation = true;
    b2Body* playerBody = world.CreateBody(&playerBodyDef);
    b2PolygonShape playerShape;
    //playerShape.m_p.Set(0,0));
    //playerShape.m_radius = playerSprite.getGlobalBounds().width/2/SCALE;
    playerShape.SetAsBox((playerSprite.getGlobalBounds().width/2)/SCALE,(playerSprite.getGlobalBounds().height/2)/SCALE);
    std::cout << playerSprite.getGlobalBounds().width<<std::endl;
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerShape;
    playerFixtureDef.density = 0.1;
    playerBody->CreateFixture(&playerFixtureDef);
    int playerId = 1;
    playerBody->SetUserData((void*) playerId);





    ///playerSprite.setPosition(SCALE*bodyIter->GetPosition().x,SCALE*bodyIter->GetPosition().y);
    //playerSprite.setRotation(bodyIter->GetAngle()*(180/3.14159));

    while(window.isOpen())
    {
        window.clear(sf::Color::White);
        //player1.update();
         playerSprite.setPosition(SCALE*playerBody->GetPosition().x,SCALE*playerBody->GetPosition().y);
         playerSprite.setRotation(playerBody->GetAngle()*(180/3.14159));

        vel = playerBody->GetLinearVelocity();
        while (window.pollEvent(event))
        {
             if(event.type == sf::Event::Closed)
            {
            window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                CreateBox(world,mouse.getPosition(window).x,mouse.getPosition(window).y);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    vel.x = -5;
                    //playerBody->SetLinearVelocity(vel);
                    //player1.setLeft();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    vel.x = 5;
                    //player1.setRight();
                    //playerBody->SetLinearVelocity(vel);

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {

                    //player1.jump();
                    if(grounded)
                    {
                        vel.y = -5;
                    }




                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {


                }

                if(event.type == sf::Event::KeyReleased)
                {
                    if(event.key.code == sf::Keyboard::A)
                    {
                        vel.x = 0;
                       // player1.setStationary();
                    }
                    if(event.key.code == sf::Keyboard::D)
                    {
                        vel.x = 0;
                       // player1.setStationary();
                    }


                }


        }

        playerBody->SetLinearVelocity(vel);
        world.Step(timeStep,velocityIterations,positionIterations);
       /* for(b2Body* bodyIter = world.GetBodyList(); bodyIter!=0; bodyIter = bodyIter->GetNext())
        {
            if((int)bodyIter->GetUserData() == 1)
            {
                std::cout<< "Yes"<<std::endl;
                /*sf::Sprite sprite;
                sprite.setTexture(boxTexture);
                sprite.setOrigin(16.0f,16.0f);
                sprite.setPosition(SCALE*bodyIter->GetPosition().x,SCALE*bodyIter->GetPosition().y);
                sprite.setRotation(bodyIter->GetAngle()*(180/3.14159));
                window.draw(sprite);
            }
        }*/

            /*
            if(bodyIter->GetType() == b2_statBody)
            {
                sf::Sprite groundSprite;
                groundSprite.setTexture(groundTexture);
                groundSprite.setOrigin(400.0f,8.0f);
                groundSprite.setPosition(SCALE*bodyIter->GetPosition().x,SCALE*bodyIter->GetPosition().y);
                groundSprite.setRotation(bodyIter->GetAngle()*(180/3.14159));
                window.draw(groundSprite);

            }
        }
    }*/
        for(vector<GameObj*>::iterator i = groundList.begin(); i != groundList.end(); ++i)
                {


                    (*i)->update();

                    window.draw((*i)->getSprite());
                }
                window.draw(playerSprite);

                    //window.draw(player1.getSprite());
                    window.display();

    }


  return 0;
}

void CreateBox(b2World& world, int mouseX, int mouseY)
{

        /**prepares the Box**/
    b2BodyDef bodyDef;
    bodyDef.angularDamping =50.0f;
    //bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(mouseX/30,mouseY/30);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBody;
    dynamicBody.SetAsBox((32.0f/2)/SCALE,(32.0f/2)/SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBody;
    fixtureDef.density = 100.0f;
    fixtureDef.friction = 5.0f;
    body->CreateFixture(&fixtureDef);
    body->SetUserData((void* )2);
}
void CreateGround(float X, float Y)
{   GameObj* go  =  new GameObj();
    go->setLocation(X,Y);
    groundList.push_back(go);

}



int main5()
{

 sf::Vector2f windowSize(640,480);
 sf::RenderWindow window(sf::VideoMode(windowSize.x,windowSize.y), "Guardian");
 window.setFramerateLimit(30);
 float radius = 15;
  sf::Vector2f dir;
 sf::Vector2f cDir;

 sf::Event event;
 sf::Vector2f mousePos;
 sf::Mouse mouse;
 sf::Keyboard keyboard;

 sf::CircleShape ball;
 ball.setRadius(radius);
 ball.setPointCount(60);
 ball.setFillColor(sf::Color::Blue);
 ball.setOutlineThickness(10);
 ball.setOutlineColor(sf::Color::White);
 sf::Vector2f ballPos(windowSize.x/2,windowSize.y/2);
 sf::Vector2f speed(1,3.5);
ball.setPosition(sf::Vector2f(windowSize.x/2,windowSize.y/2));









 sf::VertexArray line(sf::Lines,2);
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;
    pBody dave(30,10,sf::Vector2f(0,0),windowSize);
    sf::Vector2f wind(.01,0);
    sf::Vector2f gravity(0,.1);
    float angle;
    float center;
    //sf::Vector2f direction;


    //t.reserve(10);
    float mass;
   // p.reserve(10);
    //pBody tri(20,1,sf::Vector2f(0,0),windowSize);
    //tri.body.setPointCount(3);

    sf::Vector2f corePos(windowSize.x/2,windowSize.y/2);
//    normalize(corePos);
    //tri.velocity= corePos;



    //projectile mis(20,1,sf::Vector2f(0,0),windowSize);



    //pBody p[0];





 /* for(int i = 0; i<=10; i+=1)
  {
    std::cout << "does this " << i << std::endl;
    mass =rand() % 10+1;
    pBody temp(2*mass,mass,windowSize);
    p.push_back(temp);
     //p[i] = ;
  }
  cout<< p.size();*/


    //triangle[2].color = sf::Color::Blue;

  while (window.isOpen())
    {


        //tri.velocity = cDir;
        //tri.checkEdges();
        //tri.update();

        //LINE stuff
        //Get the angle of the mouse not relative to the origin, but relative to the center point
        //lAcceleration


       // lLocation+=lVelocity;


        angle = atan2((mousePos.y-line[0].position.y),(mousePos.x - line[0].position.x));
        //cout << angl<< endl;

        //Get the relative direction using that angle
        dir.x = cos(angle);
        dir.y = sin(angle);
        //Draw the end point at direction relative to the center of the screen
        line[0].position=sf::Vector2f(windowSize.x/2,windowSize.y/2);
        line[1].position=sf::Vector2f( (dir.x*200+ line[0].position.x), (dir.y*200)+ line[0].position.y);


    //BALL STUFF
    //ballPos = ballPos + speed;
    //ball.setPosition(ballPos);
    /*
    if (ballPos.x + (radius*2) > windowSize.x || ballPos.x <0)
    {
        speed.x*=-1;
    }
    if (ballPos.y + (radius*2) > windowSize.y || ballPos.y <0)
    {
        speed.y*=-1;
    }*/



    while (window.pollEvent(event))
        {
      if (event.type == sf::Event::Closed)
        {
          window.close();
        }
      if (event.type == sf::Event::MouseMoved)
        {
          mousePos = sf::Vector2f(mouse.getPosition(window));



         //Line Stuff


        //normalize(mousePos);
          //mousePos = sf::Vector2f( mousePos.x*50,mousePos.y *50);
          //mousePos.x-= windowSize.x/2;
          //mousePos.y-=windowSize.y/2;

        }
      if (event.type == sf::Event::MouseButtonPressed)
      {

          //projectile* temp = new projectile(20,1,sf::Vector2f(0,0),windowSize);
          //*temp = projectile(20,1,sf::Vector2f(0,0),windowSize);



      }
      if (event.type == sf::Event::KeyPressed)
        {
          //if (event.key.code == sf::Keyboard::Left)



          if(event.key.code == sf::Keyboard::Right)
            dave.applyForce(wind);

        }
      }
      //dir = mousePos -dave.getLocation();
      //normalize(dir);

      //dir.x *=.5;
      //dir.y*=.5;

      //dir = sf::Vector2f(0,.5);
      //dave.applyForce(gravity);
      //dave.checkEdges();
      //dave.update();
      //tri.applyForce(corePos);





      window.clear(sf::Color::Black);
        //cDir= sf::Vector2f((windowSize.x/2)-mis.location.x,(windowSize.y/2)-mis.location.y);
       // normalize(cDir);
        //mis.applyForce(cDir);

    /*  for (int i = 0; i<= t.size(); i++)
      {
            /*cDir= sf::Vector2f((windowSize.x/2)-t[i].location.x,(windowSize.y/2)-t[i].location.y);
            normalize(cDir);
            cDir.x*=15;
            cDir.y*=15;

          t[i].velocity = cDir;
          cout << t.size()<< endl;
         // t[i]->checkEdges();
          //t[i]->update();

      vector<projectile*>::iterator:: i ;

      }*/
      int c = 0;



//t.clear();
      /*for(int i = 0;i <= p.size(); i+=1)
      {
          sf::Vector2f friction;
          friction = p[i].getVelocity();
          gravity = sf::Vector2f(0,.1*p[i].mas);
          p[i].applyForce(gravity);
          p[i].applyForce(wind);
          p[i].checkEdges();
          p[i].update();
          window.draw(p[i].getBody());
      }*/


      //mis.applyForce(gravity);
      //mis.checkEdges();
      //mis.update();

      //window.draw(ball);
      window.draw(line);
      //window.draw(dave.getBody());

      //window.draw(tri.getBody());
      //window.draw(mis.getBody());




      //window.draw(ball);
      window.display();
    }
    return 0;
  }

  /*void pause(int t)
  {
      this_thread::sleep_for(chrono::seconds(t));
  }*/


 /* int main()
  {
      string a1, a2, a3;

      cout << "What is your name?" << endl;

      getline(cin,a1);
      pause(1);
      cout << a1 << "?" << endl;
      pause(1);
      cout << "That's a horrible name." ;

      return 0;
  }*/

   /* int main()
  {
      int a;
      int b;
      int sum;

      cout << "enter a number.  \n" ;
      cin >> a;

      cout << "Enter another number \n";
      cin >> b;

      sum = a + b;

      cout << " The sum is \n" << sum;

      return 0;
  }*/

/*class LumberJack
{
    private:
        string name;
    public:
        LumberJack(string n)
        {
           setName(n);
        }
        void setName(string n)
        {
            name = n;
        }
        string getName()
        {
            return name;
        }
        void chopWood()
        {
            cout << "Chopping commence" << endl;
        }

};

int main()
{
    LumberJack lj("Ricky bobby");
    cout << lj.getName() << endl;
    lj.chopWood();

    LumberJack lj1 ("Jenny");
    cout << lj1.getName() << endl;
    lj1.chopWood();
}*/
/*int main()
{
    LumberJack lj;
    string name;

    cout << "What is your name, lumber Jack?"<< endl;
    cin >> name;
    lj.setName(name);

    cout <<"Your name is " << lj.getName() << endl;

    //joe.chopWood();
    return 0;
}*/


