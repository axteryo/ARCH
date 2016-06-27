         #include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <cmath>
#include <chrono>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;
using namespace sf;


class bullet
{
public:
    int radius;
    float mass;
    sf::Vector2f dimension;
    sf::CircleShape body;
    sf::Vector2f location;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f direction;
    sf::Vector2f target;


    bullet(int rad,float mas,Vector2f loc, Vector2f wDim, Vector2f targ)
    {
        dimension = wDim;
        radius = rad;
        mass = mas;
        location = loc;
        target = targ;
        //location = sf::Vector2f(0,0);
        velocity = sf::Vector2f(0,0);
        acceleration = sf::Vector2f(0,0);
        direction =sf::Vector2f(target.x-location.x,target.y-location.y);

        body.setRadius(radius);
        body.setPointCount(3);
        body.setFillColor(sf::Color::Green);
        body.setPosition(location);
        body.setOutlineThickness(1);
        body.setOutlineColor(sf::Color::White);
    }
    void update()
    {
       // cout<< location.x << endl;
        /*if(location.x >(dimension.x/2)-radius && location.x <(dimension.x/2)+radius )
        {
            if(location.y >(dimension.y/2)-radius && location.y <(dimension.y/2)+radius )
                velocity = sf::Vector2f(0,0);
                direction = sf::Vector2f(0,0);





        }
        else*/

            //







            //cout<< velocity.x << endl;


                        float mag = sqrt((direction.x*direction.x)+(direction.y*direction.y));
                        if (mag != 0)
                        {

                            direction.x/=mag;
                            direction.y/=mag;
                            direction.x*=50;
                            direction.y*=50;

                        }
        //velocity+=acceleration;
        velocity+=direction;
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
                    velocity.x*=5;
                    velocity.y*=5;

                }
        }


    }
        void checkEdges()
    {
        if (location.x < 0 )
            {
            location.x = dimension.x;
            //velocity.x *= -1;
            }
        if (location.x + (radius+radius)>dimension.x)
        {
            location.x = dimension.x -(radius+radius);
            //velocity.x *= -1;
        }
        if (location.y < 0 )
            {
            location.y = 0;
            //velocity.y *= -1;

            }
        if (location.y +(radius+radius) >dimension.y)
        {
            location.y = dimension.y - (radius+radius);
            //velocity.y *= -1;
            //applyForce(Vector2f(0,-10));

        }
        /* */


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
        f.x/=mass;
        f.y/=mass;
        acceleration +=f;
    }
    sf::Vector2f getVelocity()
    {
        sf::Vector2f v;
        v = velocity;
        return v;
    }

};




class projectile
{
public:
    int radius;
    float mass;
    sf::Vector2f dimension;
    sf::CircleShape body;
    sf::Vector2f location;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f direction;
    sf::Vector2f target;


    projectile(int rad,float mas,Vector2f loc, Vector2f wDim, Vector2f targ)
    {
        dimension = wDim;
        radius = rad;
        mass = mas;
        location = loc;
        target = targ;
        //location = sf::Vector2f(0,0);
        velocity = sf::Vector2f(0,0);
        acceleration = sf::Vector2f(0,0);
        direction =sf::Vector2f(target.x-location.x,target.y-location.y);

        body.setRadius(radius);
        body.setPointCount(50);
        body.setFillColor(sf::Color::Red);
        body.setPosition(location);
        body.setOutlineThickness(1);
        body.setOutlineColor(sf::Color::White);
    }
    void update()
    {
       // cout<< location.x << endl;
        /*if(location.x >(dimension.x/2)-radius && location.x <(dimension.x/2)+radius )
        {
            if(location.y >(dimension.y/2)-radius && location.y <(dimension.y/2)+radius )
                velocity = sf::Vector2f(0,0);
                direction = sf::Vector2f(0,0);





        }
        else*/

            //







            //cout<< velocity.x << endl;


                        float mag = sqrt((direction.x*direction.x)+(direction.y*direction.y));
                        if (mag != 0)
                        {

                            direction.x/=mag;
                            direction.y/=mag;

                        }
        //velocity+=acceleration;
        velocity+=direction;
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
                    velocity.x*=5;
                    velocity.y*=5;

                }
        }


    }
        void checkEdges()
    {
        if (location.x < 0 )
            {
            location.x = dimension.x;
            //velocity.x *= -1;
            }
        if (location.x + (radius+radius)>dimension.x)
        {
            location.x = dimension.x -(radius+radius);
            //velocity.x *= -1;
        }
        if (location.y < 0 )
            {
            location.y = 0;
            //velocity.y *= -1;

            }
        if (location.y +(radius+radius) >dimension.y)
        {
            location.y = dimension.y - (radius+radius);
            //velocity.y *= -1;
            //applyForce(Vector2f(0,-10));

        }
        /* */


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
        f.x/=mass;
        f.y/=mass;
        acceleration +=f;
    }
    sf::Vector2f getVelocity()
    {
        sf::Vector2f v;
        v = velocity;
        return v;
    }

};



void start()
{

}

void processInput()
{

}

void draw()
{

}




int main3()
{
    sf::Vector2f windowSize(960,720);
    sf::RenderWindow window(sf::VideoMode(windowSize.x,windowSize.y), "Guardian");
    window.setFramerateLimit(30);
    enum quad{first,second,third,fourth};


    sf::Event event;
    sf::Vector2f mousePos;
    sf::Mouse mouse;
    sf::Keyboard keyboard;
    sf::CircleShape core;
    core.setRadius(15);
    core.setPointCount(60);
    core.setFillColor(sf::Color::Blue);
    sf::Vector2f corePos((windowSize.x/2)-15,(windowSize.y/2)-15);
    core.setPosition(corePos);

    //random object to test camera movement
    sf::RectangleShape r;
    r.setSize(sf::Vector2f(20,20));
    r.setFillColor(sf::Color::Red);
    sf::Vector2f rPos = sf::Vector2f(200,120);
    r.setPosition(rPos);
    //camera zone
    sf::RectangleShape zone;
    //zone.setSize(sf::Vector2f(windowSize.x/2,windowSize.y/2));
    zone.setPosition(sf::Vector2f(windowSize.x/4,windowSize.y/4));
    sf::Vector2f  zonePos = zone.getPosition();
    sf::FloatRect zBox = zone.getGlobalBounds();
    zone.setSize(sf::Vector2f(windowSize.x/2,windowSize.y/2));
    //Objects that i don't want offsetted
    sf::Vector2f offset(0,0);

    //Destination for better more fluid movement
    sf::Vector2f dest(0,0);

    //Temp Mouse for directional movement via clicking
    sf::Vector2f targ(0,0);
    float tarAngle;

    bool moved = false;




  /*  sf::RectangleShape shield;
    shield.setSize(sf::Vector2f(10,10));
    shield.setFillColor(sf::Color::White);
    sf::Vector2f shieldPos;;*/

    float angle;
    sf::Vector2f dir;
    sf::Vector2f adir;


//LINE STUFF
    sf::VertexArray shield(sf::Lines,2);

	shield[0].position = sf::Vector2f(0,0);
	shield[1].position = sf::Vector2f(0,0);
	//shield[2].position = sf::Vector2f(0,0);

	shield[0].color = sf::Color::Red;
	shield[1].color = sf::Color::Red;
	sf::FloatRect coreBox;

	sf::VertexArray laser(sf::Lines,2);

	laser[0].position = sf::Vector2f(0,0);
	laser[1].position = sf::Vector2f(0,0);







	//shield[2].color = sf::Color::Blue;
	vector<sf::Vector2f> mP;

//    shield.setPosition()

// create a view with the rectangular area of the 2D world to show
sf::View view(sf::FloatRect(0,0, 800, 600));
    sf::Vector2f lLocation(0,0);
    sf::Vector2f lVelocity(0,0);
    sf::Vector2f lAcceleration(0,0);
    sf::CircleShape launch;
    launch.setFillColor(sf::Color::Green);
    launch.setRadius(15);
    launch.setPointCount(30);
    launch.setPosition(sf::Vector2f(0,0));
    float angl;
    float theta = 0;
    float rof = 10;
    int counter = 0;
    float laserDur = 0;
    bool laserCharge = false;

sf::CircleShape c;
c.setRadius(100);
sf::Vector2f cPos((windowSize.x/2)-100,(windowSize.y/2)-100);
c.setPosition(cPos);
c.setPointCount(300);



    //
    dest = sf::Vector2f(0,0);
    //vector<pBody> p;
    vector<projectile*> t;
    vector<bullet*> bulletList;
    vector<CircleShape*> colBox;

    while(window.isOpen())
    {

        window.clear(sf::Color::Black);


        //window.setView(view);



        /*switch(q)
        {
            case(first)
        }*/
        angl = atan2((lLocation.x - windowSize.x/2),lLocation.y-windowSize.y/2);
        //launch.setPosition(x+centerX,y+centerY);

        //lAcceleration = sf::Vector2f((cos(angl)),  sin(angl));
        lVelocity+=lAcceleration;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }


                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    //offset.x=-5;
                    core.setPosition(corePos);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {

                    //offset.x=5;
                    core.setPosition(corePos);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    //offset.y=5;
                    core.setPosition(corePos);

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    //offset.y=-5;
                    core.setPosition(corePos);

                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {

                    if(laserDur <= 0)
                    {

                        cout<< "laser here"<<endl;
                        laserCharge = true;
                        laserDur=10;

                    }






                    //bulletList.push_back(new projectile(5,1,shield[2].position,windowSize));

                }

                if(event.type == sf::Event::KeyReleased)
                {
                    if(event.key.code == sf::Keyboard::W)
                    {
                        offset.y=0;
                    }
                    if(event.key.code == sf::Keyboard::S)
                    {
                        offset.y=0;
                    }
                    if(event.key.code == sf::Keyboard::D)
                    {
                        offset.x=0;
                    }
                    if(event.key.code == sf::Keyboard::A)
                    {
                        offset.x=0;
                    }
                    if(event.key.code == sf::Keyboard::Space)
                    {

                        if(laserCharge)
                            laserCharge = false;
                        if(rof >=10)
                        {
                          bulletList.push_back(new bullet(5,1,sf::Vector2f((dir.x*10)+(corePos.x+15),(dir.y*10)+(corePos.y+15)),windowSize,laser[1].position));
                          rof = 0;
                        }









                    }
                }


             if (event.type == sf::Event::MouseButtonPressed)
                {
                    targ = sf::Vector2f(mouse.getPosition(window));
                    targ = targ +sf::Vector2f(-15,-15);
                    moved = true;



                }

                    /*

                NOTE TO SELF CHANGE TEMPMOUSE NAME TO TARGETLOCATION!!!!

                    */
                    //mousePos = sf::Vector2f(mouse.getPosition(window));

                    /*
                    //targ =window.mapCoordsToPixel(static_cast<sf::Vector2f>(targ),view);










                    //cout<< dest.y<<endl;





                    //offset.x+=10;
                    //offset.y+=10;
                    //core.setPosition(sf::Vector2f((mousePos.x+offset.x),(mousePos.y+offset.y)));
                    //view.move(10,10);

                }*/
            if (event.type == sf::Event::MouseMoved)
            {
                mousePos = sf::Vector2f(mouse.getPosition(window));
                /*
                cout<<"CorPos:"<<corePos.x<<","<< corePos.y<< endl;
                cout<<"Core Position :"<<core.getPosition().x<<","<< core.getPosition().y<< endl;
                cout<< dest.x<<","<<dest.y<<endl;*/




                //sf::Vector2f(corePos.x+30,corePos.y+30);



                //core.setPosition(corePos);


                //Pivot is the distance between the two points in the line.



                //shield[0].position.x+=dir.x*pivot.x;
                //shield[0].position.y-=dir.y*pivot.y;
                //cout<< shield[0].position.x <<"," <<shield[0].position.y<< endl;
                //cout<< shield[1].position.x <<"," <<shield[1].position.y<< endl;



                //window.setMouseCursorVisible(false);





                //shield.rotate(angle);


                //shield.setPosition(mousePos);
            }
    }





        //Get the angle of the mouse not relative to the origin, but relative to the center point
                angle = atan2((mousePos.y - corePos.y)-20,(mousePos.x-corePos.x)-20);

                //Get the relative direction using that angle
                dir.x = cos(angle);
                dir.y = sin(angle);

                adir.x = acos(angle);
                adir.y = asin(angle);
                //Draw the end point at direction relative to the center of the screen
                shield[1].position=sf::Vector2f((((dir.x*100)+(corePos.x+15))),((dir.y*100)+(corePos.y+15)));
                shield[0].position=sf::Vector2f((((dir.x*100)+(corePos.x+15))),(((dir.y*100)+(corePos.y+15))));
                sf::Vector2f pivot = sf::Vector2f(shield[0].position.x-shield[1].position.x,shield[0].position.y-shield[1].position.y);
                //cout << angle*(180/3.14159) << endl;
                //cout<< dir.x<< "," << dir.y<< endl;
                sf::Vector2f mPos1;
                sf::Vector2f mPos2;

                mPos1 = sf::Vector2f(dir);


                mP.push_back(mPos1);
                if (mP.size()>2)
                {
                    mP.erase(mP.begin());
                    //cout<< "here"<< endl;
                }

                //first
                if(angle*(180/3.14159)< 0 && angle*(180/3.14159) > -90)
                {
                    //for(int i = 0; i<mP.size();i++) cout << mP[i].x <<"," << mP[i].y << endl; cout<< mP.size()<< endl;
                    if(mP.size()> 1 && mP[0].x>= mP[1].x)
                    {
                        if(mP[0].y >=mP[1].y)
                        {
                           // cout<< "Moving Up and left"<< endl;
                            //shield[1].position.x-=dir.x*25;
                            shield[0].position.x+=dir.y*(25);
                            shield[0].position.y-=dir.x*(25);

                        }
                    }
                    else if(mP.size()> 1 && mP[0].x<= mP[1].x)
                    {
                        if(mP[0].y <=mP[1].y)
                        {
                            //cout<< "Moving Down and Right"<< endl;
                            shield[1].position.x+=dir.y*(25);
                            shield[1].position.y-=dir.x*(25);
                        }
                    }

                    //cout<< "first" << endl;

                }
                //second
                else if(angle*(180/3.14159)< -90 && angle*(180/3.14159) > -180)
                {
                    if(mP.size()> 1 && mP[0].x<= mP[1].x)
                    {
                        if(mP[0].y >=mP[1].y)
                        {
                            //cout<< "Moving Up and Right"<< endl;
                            shield[0].position.x+=dir.y*(25);
                            shield[0].position.y-=dir.x*(25);
                        }
                    }
                    else if(mP.size()> 1 && mP[0].x>= mP[1].x)
                    {
                        if(mP[0].y <=mP[1].y)
                        {
                           // cout<< "Moving Down and left"<< endl;
                            shield[1].position.x+=dir.y*(25);
                            shield[1].position.y-=dir.x*(25);
                        }
                    }
                    //cout<< "Second" << endl;
                }
                //third
                else if(angle*(180/3.14159)<180 && angle*(180/3.14159) > 90)
                {
                    if(mP.size()> 1 && mP[0].x>= mP[1].x)
                    {
                        if(mP[0].y >=mP[1].y)
                        {
                           // cout<< "Moving Up and left"<< endl;
                            shield[0].position.x+=dir.y*(25);
                            shield[0].position.y-=dir.x*(25);
                        }

                    }
                    else if(mP.size()> 1 && mP[0].x< mP[1].x)
                    {
                        if(mP[0].y <mP[1].y)
                        {
                           // cout<< "Moving Down and Right"<< endl;
                            shield[1].position.x+=dir.y*(25);
                            shield[1].position.y-=dir.x*(25);
                        }
                    }
                    //cout<< "third" << endl;
                }
                //fourth
                else if(angle*(180/3.14159) <90 && angle*(180/3.14159) > 0)
                {
                    if(mP.size()> 1 && mP[0].x< mP[1].x)
                    {
                        if(mP[0].y >mP[1].y)
                        {
                          //  cout<< "Moving Up and Right"<< endl;
                            shield[0].position.x+=dir.y*(25);
                            shield[0].position.y-=dir.x*(25);
                        }
                    }
                    else if(mP.size()> 1 && mP[0].x> mP[1].x)
                    {
                        if(mP[0].y <=mP[1].y)
                        {
                            //cout<< "Moving Down and left"<< endl;
                            shield[1].position.x+=dir.y*(25);
                            shield[1].position.y-=dir.x*(25);
                        }
                    }
                    //cout<< "fourth" << endl;
                }
        //shield.setPosition(mousePos);



        if (laserDur<= 0)
        {
            laser[0].position = sf::Vector2f(0,0);
            laser[1].position = sf::Vector2f(0,0);
            laserCharge = false;
        }
        if (laserCharge)
        {
            laser[0].color = sf::Color::Red;
            laser[1].color = sf::Color::Red;
            laser[0].position = sf::Vector2f((dir.x*10)+(corePos.x+15),(dir.y*10)+(corePos.y+15));
            laser[1].position = sf::Vector2f((dir.x*600)+(corePos.x+15),(dir.y*600)+(corePos.y+15));


        }
        if (!laserCharge)
        {
            laser[0].color = sf::Color::Green;
            laser[1].color = sf::Color::Green;
        }





                     coreBox = core.getGlobalBounds();
                    //zBox = zone.getGlobalBounds();
                    if (moved)
                    {   tarAngle = atan2((targ.y - corePos.y)-20,(targ.x-corePos.x)-20);
                        dest=sf::Vector2f(targ.x-corePos.x,targ.y-corePos.y);
                        float dMag = sqrt((dest.x*dest.x)+(dest.y*dest.y));
                        if (dMag != 0)
                        {

                            dest.x/=dMag;
                            dest.y/=dMag;
                            dest.x*=15;
                            dest.y*=15;

                            if(sqrt(((targ.x-corePos.x)*(targ.x-corePos.x)) +((targ.y-corePos.y)*(targ.y-corePos.y)))<75)
                                {
                                    dest.x/=3;
                                    dest.y/=3;
                                    if(sqrt(((targ.x-corePos.x)*(targ.x-corePos.x)) +((targ.y-corePos.y)*(targ.y-corePos.y)))<10)
                                        {

                                            dest.x/=5;
                                            dest.y/=5;


                                            if(sqrt(((targ.x-corePos.x)*(targ.x-corePos.x)) +((targ.y-corePos.y)*(targ.y-corePos.y)))<1)
                                                {
                                                    cout<< "They are equak"<< endl;
                                                    targ+=dest;


                                                }
                                        }
                                }


                        }
                                /*(if(sqrt(((corePos.x-windowSize.x/2)*(corePos.x-windowSize.x/2))+((corePos.y-windowSize.y/2)*(corePos.y-windowSize.y/2)))>100)
                                    {
                                    */


                                         //offset = dest;
                                         //targ.x-=dest.x/5;
                                         //targ.y-=dest.y/5;



                    }
                        //offset = dest;
                        //corePos+=dest;











                    //


                    //targ.x-=offset.x/5;
                    //targ.y-=offset.y/5;

               window.draw(c);
               //space enemies
               for(vector<projectile*>::iterator i = t.begin(); i != t.end(); ++i)
                {

                    //(*i)->checkEdges();
                    (*i)->location-=offset;
                    (*i)->update();

                    window.draw((*i)->getBody());
                }
                //bullets
                for(vector<bullet*>::iterator i = bulletList.begin(); i != bulletList.end(); ++i)
                {

                    //(*i)->checkEdges();
                    (*i)->location-=offset;
                    (*i)->update();

                   // window.draw((*i)->getBody());
           /*if((*i)->location.x >(windowSize.x/2)-(*i)->radius && (*i)->location.x <(windowSize.x/2)+(*i)->radius )
        {
            //if((*i)->location.y >(windowSize.y/2)-(*i)->radius && (*i)->location.y <(windowSize.y/2)+(*i)->radius )

                delete *i;
                t.erase(t.begin());
                cout<< t.size() << endl;
                //t.clear();


        }*/
                }
                for(int i = 0;i < t.size(); ++i)
                {
                   /* float s = (laser[1].position.y-laser[0].position.y)/(laser[1].position.x-laser[0].position.x);
                    if( y=(s*x)-(laser[0].position.x*s)+laser[0].position.y)
                    {   cout<<"Gets Here"<< endl;

                        delete t[i];
                        t.erase(t.begin()+i);
                    }*/

                    if(sqrt(((t[i]->location.x - cPos.x-100)*(t[i]->location.x -cPos.x-100)) + ((t[i]->location.y - cPos.y-100)*(t[i]->location.y -cPos.y-100)))<100)
                    {
                        delete t[i];
                 //cout<< "yes"<<endl;
                        t.erase(t.begin()+i);
                        cout<< t.size() << endl;
                    }
                     for(int j = 0;j < bulletList.size(); ++j)
                    {
                        if(sqrt(((t[i]->location.x+15- bulletList[j]->location.x)*(t[i]->location.x+15 -bulletList[j]->location.x)) + ((t[i]->location.y+15 - bulletList[j]->location.y)*(t[i]->location.y+15 -bulletList[j]->location.y)))<30)
                        {

                            delete t[i];
                            t.erase(t.begin()+i);
                            delete bulletList[j];
                            bulletList.erase(bulletList.begin()+j);
                        }
                    }
                }
                counter+=1;
                if(counter ==60)
                    {

                        t.push_back(new projectile(15,1,lLocation,windowSize,sf::Vector2f(cPos.x+100,cPos.y+100)));
                        counter = 0;
                    }


                    float x,y;

                    x =640*cos(theta);
                    y = 480*sin(theta);
                    lLocation = sf::Vector2f(x+(windowSize.x/2),y+(windowSize.y/2));
                    launch.setPosition(lLocation);
                    theta +=.05;
                    //cout<< targ.x-corePos.x<<endl;

                    //




                    //Inside x bound but outside upper Y bound
                    //view.setCenter(sf::Vector2f((windowSize.x/2)+dest.x,(windowSize.y/2)+dest.y));


                        //cout<< "yes it does"<<endl;


                            //cout<< "it does not"<< endl;









                        //view.move(dest);
                        //view.setCenter(corePos);


        laserDur-=1;

                        rPos-=offset;
                        cPos-=offset;
                        targ-=offset;
                        r.setPosition(rPos);
                        core.setPosition(corePos);
                        c.setPosition(cPos);
        rof+=1;



                        //view.setViewport(zone.getGlobalBounds);


                        //window.setView(view);
















        //window.draw(launch);

        window.draw(core);
        window.draw(laser);
        //window.draw(shield);
        //window.draw(r);


        window.display();
    }
    return 0;
}
