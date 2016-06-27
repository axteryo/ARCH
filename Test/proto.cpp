#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <string>

using namespace std;


int other()
{

    sf::RenderWindow window(sf::VideoMode(640,480),"Pong");
    sf::Event event;

    //sf::RectangleShape player2;

    //PLayer 1 variables
    sf::RectangleShape player1;
    player1.setPosition(sf::Vector2f(25,25));
    player1.setSize(sf::Vector2f(25,100));
    player1.setFillColor(sf::Color::Blue);
    player1.setOutlineColor(sf::Color::Yellow);
    //player1.setOutlineThickness(2);
    sf::Vector2f pBounds;


    //PLayer 2 variables
    sf::RectangleShape player2;
    player2.setPosition(sf::Vector2f(590,25));
    player2.setSize(sf::Vector2f(25,100));
    player2.setFillColor(sf::Color::Yellow);
    player2.setOutlineColor(sf::Color::Blue);
    //player2.setOutlineThickness(2);
    sf::Vector2f pBounds2;


    //Ball variables
    sf::RectangleShape ball;
    ball.setPosition(static_cast<sf::Vector2f>(sf::Vector2i(((640-25)/2), ((480-25)/2))));
    ball.setSize(sf::Vector2f(25,25));
    ball.setFillColor(sf::Color::Red);
    sf::Vector2f bBounds;
    sf::Vector2f bVelocity(-0.2,-0.2);

    sf::Vector2f  pos = player1.getOrigin();
    //player2.setSize(sf::Vector2(25,100));
    while(window.isOpen())
    {

        window.clear(sf::Color::White);
        window.draw(player1);
        window.draw(ball);
        window.draw(player2);
        window.display();

        sf::FloatRect pBox = player1.getGlobalBounds();
        sf::FloatRect bBox = ball.getGlobalBounds();



        ball.move(bVelocity.x,bVelocity.y);
        bBounds = ball.getPosition();
        if (bBounds.x <25)
            bVelocity.x = .2;
        if (bBounds.y <25)
            bVelocity.y =.2;
        if (bBounds.x >=590)
            bVelocity.x = -.2;
        if (bBounds.y >=430)
            bVelocity.y = -.2;


        pBounds = player1.getPosition();
        if (pBounds.y < 25)
            player1.setPosition(25,25);
        if (pBounds.y >355)
            player1.setPosition(25,355);


        if (pBox.intersects(bBox))
            //cout << "There's been an intersection.";
            bVelocity.x = .2;



        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
            window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Up: player1.move(0,10);
                    break;
                    case sf::Keyboard::Down: player1.move(0,10);
                    break;
                        //case sf::Keyboard::Left: player1.move(-10,0);
                        //break;
                        //case sf::Keyboard::Right: player1.move(10,0);
                        //break;
                }
                if (event.key.code==sf::Keyboard::Escape)
                    window.close();
            }
            if (event.type == sf::Event::MouseMoved)
            {
                //window.setMouseCursorVisible(false);
                sf::Vector2i pos = sf::Mouse::getPosition(window);

                //if(pos.y > player1.getPosition().y)
                  //  player1.move(0,15);
                //if(pos.y < player1.getPosition().y)
                   // player1.move(0,-15);
                player1.setPosition(25,pos.y-50);

            }

        }

    }

    return 0;

}

