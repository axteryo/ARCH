#include "Pong.h"

#include <iostream>
#include <string>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

Pong::Pong()
{
    if(!font.loadFromFile("arial.ttf"))
    {
        std::cout<< "we fudged up";
    }
    title = sf::Text("PONG",font,50);
    title.setColor(sf::Color::White);

    startButton = sf::Text("START",font,25);
    startButton.setColor(sf::Color::White);
    exitButton = sf::Text("EXIT",font,25);
    exitButton.setColor(sf::Color::White);
    mouseOver = false;



    windowDimension = sf::Vector2f(640,480);
    window = new sf::RenderWindow(sf::VideoMode(windowDimension.x,windowDimension.y),"Pong");
    window->setFramerateLimit( 60 );
    GameState = Main_Menu;
    gameRunning = true;

    paddleMeasurement = sf::Vector2f(20,100);
    boardBounds = sf::Vector2f(600,440);


    //sf::RectangleShape board;
    board.setPosition(static_cast<sf::Vector2f>(sf::Vector2i(((windowDimension.x-boardBounds.x)/2), ((windowDimension.y-boardBounds.y)/2))));
    boardPos = board.getPosition();
    board.setSize(sf::Vector2f(boardBounds.x,boardBounds.y));
    board.setFillColor(sf::Color::Black);

    //sf::RectangleShape player1;
    player1.setPosition(static_cast<sf::Vector2f>(sf::Vector2i(boardPos.x,((boardBounds.y-100)/2))));
    player1.setSize(paddleMeasurement);
    player1.setFillColor(sf::Color::Blue);

    //sf::RectangleShape player2;
    player2.setPosition(static_cast<sf::Vector2f>(sf::Vector2i(boardBounds.x,((boardBounds.y-100)/2))));;
    player2.setSize(paddleMeasurement);
    player2.setFillColor(sf::Color::Blue);

    //sf::RectangleShape ball;
    ball.setPosition(static_cast<sf::Vector2f>(sf::Vector2i(((windowDimension.x-20)/2), ((windowDimension.y-20)/2))));
    ball.setSize(sf::Vector2f(20,20));
    ball.setFillColor(sf::Color::Red);
    ballDirection = sf::Vector2f(-1,1);
    ballVelocity = sf::Vector2f(5,5);

    //Score stuff

    score1 = 0;
    score2 = 0;
    scoreS1 << score1;
    scoreS2 << score2;



    player1Score = sf::Text(scoreS1.str(),font,50);
    player1Score.setPosition(100,40);
    player2Score = sf::Text(scoreS2.str(),font,50);
    player2Score.setPosition(boardBounds.x-100,40);



}

void Pong::start()
{
    while (window->isOpen())
    {

            processInput(GameState);
            update(GameState);
            render(GameState);
            if (!gameRunning)
                window->close();
    }
    //window->close();
}



void Pong::processInput(state currentState)
{
    switch(currentState)
    {
    case Main_Menu:
        while(window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameRunning = false;


             if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
            {
                if (mouseOver)
                    if (button == "start")
                    {
                        GameState = In_Game;
                        mouseOver = false;
                    }

                    if (button == "exit")
                    {
                        gameRunning = false;
                    }

            }
        }
        break;

    case In_Game:
        while(window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameRunning = false;


             if (event.type == sf::Event::MouseMoved)
            {

            }
        }

    }
}

void Pong::update(state currentState)
{
    mousePos = mouse.getPosition(*window);




    switch(currentState)
    {
    case Main_Menu:
        //sf::RectangleShape startRect()
        title.setPosition(((boardBounds.x-100)/2),40);
        startButton.setPosition(((boardBounds.x-40)/2),boardBounds.y-120);
        exitButton.setPosition(((boardBounds.x-20)/2),boardBounds.y-70);
        if (startButton.getGlobalBounds().contains(mousePos.x,mousePos.y))
        {
            mouseOver = true;
            button = "start";
            startButton.setColor(sf::Color::Blue);
        }
        else if (exitButton.getGlobalBounds().contains(mousePos.x,mousePos.y))
        {
            mouseOver = true;
            button = "exit";
            exitButton.setColor(sf::Color::Red);
        }
        else
        {
            mouseOver = false;
            button = "";
            startButton.setColor(sf::Color::White);
            exitButton.setColor(sf::Color::White);
        }

        break;

    case In_Game:

        sf::FloatRect pBox = player1.getGlobalBounds();
        sf::FloatRect pBox2 = player2.getGlobalBounds();
        sf::FloatRect bBox = ball.getGlobalBounds();

        ball.move(ballVelocity.x*ballDirection.x,ballVelocity.y*ballDirection.y);
        ballPos = ball.getPosition();
        player1Pos= static_cast<sf::Vector2f>(sf::Vector2i(20,mousePos.y-50));
        player2Pos = sf::Vector2f(player2.getPosition());

        //Collision Checks
        //Paddle Boundary
        if(player1Pos.y < boardPos.y)
            player1Pos = boardPos;
            player1.setPosition(player1Pos);
        if(player1Pos.y >boardBounds.y-80)
            player1Pos = sf::Vector2f(boardPos.x,boardBounds.y-80);
            player1.setPosition(player1Pos);
        player1Bounds = sf::Vector2f(player1Pos.x+20,player1Pos.y+100);


        if (player2Pos.y < boardPos.y)
            player2Pos.y = boardPos.y;
            player2.setPosition(player2Pos);
        if (player2Pos.y > boardBounds.y-80)
            player2Pos.y = boardBounds.y-80;
            player2.setPosition(player2Pos);


        //Ai
        if (ballDirection.x < 0)
            {
                if (player2Pos.y+50 <=(boardBounds.y/2))
                player2.move(0,1);
            else if (player2Pos.y+25 >(boardBounds.y/2))
                player2.move(0,-1);
            }

        else if (ballDirection.x >0)

            //if (ballPos.y <= player2Pos.y+20 || ballPos.y <= player2Pos.y+50 ||
            if (ballPos.y <= player2Pos.y+80)
            {
                player2Pos.y -= 4;
                //player2.setPosition(player2Pos);
            }

            else //if (ballPos.y <= player2Pos.y )
            {
                player2Pos.y +=4;
                //player2.setPosition(player2Pos);
            }

            player2.setPosition(player2Pos);


        //Ball Boundary
        if(ballPos.y <=boardPos.y)
            ballDirection.y = 1;

        else if(ballPos.y >=boardBounds.y)
            ballDirection.y =-1;

        //Paddle and ball collision
        if (pBox.intersects(bBox))
        {
            if (ballPos.y <player1Pos.y+25)
                 if (ballPos.x >player1Pos.x+5)
                    ballDirection = sf::Vector2f(1.5,-.75);

                //ballVelocity = sf::Vector2f(5,-4.5);
                //ballDirection = sf::Vector2f(1,1);
            if(ballPos.y <=player1Pos.y+75 && ballPos.y >=player1Pos.y+20)
                if (ballPos.x >player1Pos.x+5)
                    ballDirection = sf::Vector2f(1.5,.075);
                //std::cout<< "Touched 2" << std::endl;

            if(ballPos.y >player1Pos.y+75)
                //std::cout<< "Touched 3"<< std::endl;
                if (ballPos.x >player1Pos.x+5)
                    ballDirection = sf::Vector2f(1.5,.75);
        }
        /*
        paddle 2 collision with ball
        */
        if (pBox2.intersects(bBox))
        {
            if (ballPos.y <player2Pos.y+20)
                 if (ballPos.x+5 >player2Pos.x+5)
                ballDirection = sf::Vector2f(-1.5,-.75);

                //ballVelocity = sf::Vector2f(5,-4.5);
                //ballDirection = sf::Vector2f(1,1);
            if(ballPos.y <=player2Pos.y+75 && ballPos.y >player2Pos.y+25)
                //if (ballPos.x <player2Pos.x-5)
                ballDirection = sf::Vector2f(-1.5,.05);
                //std::cout<< "Touched 2" << std::endl;

            if(ballPos.y >player2Pos.y+75)
                //std::cout<< "Touched 3"<< std::endl;
                //if (ballPos.x <player2Pos.x-5)
                ballDirection = sf::Vector2f(-1.5,.5);

            }
        /*
        score system
        */
        if (ballPos.x <-40)
        {
            score2+=1;
            ballDirection.x = 1.5;
            //ballPos.y = rand() % 160 + 440;
            //ball.setPosition(ballPos);
        }
        if (ballPos.x > 680)
        {
            score1+=1;
            ballDirection.x = -1.5;
        }


        std::stringstream scoreS1;
        std::stringstream scoreS2;

        scoreS1 << score1;
        scoreS2 << score2;

        player1Score = sf::Text(scoreS1.str(),font,50);
        player1Score.setPosition(100,40);
        player2Score = sf::Text(scoreS2.str(),font,50);
        player2Score.setPosition(boardBounds.x-100,40);



        break;
    }

}

void Pong::render(state currentState)
{
        switch(currentState)
        {
            case Main_Menu:
                window->clear(sf::Color::White);
                window->draw(board);
                window->draw(title);
                window->draw(startButton);
                window->draw(exitButton);
                window->display();
                break;

            case In_Game:
                window->clear(sf::Color::White);
                window->draw(board);
                window->draw(player1);
                window->draw(player2);
                window->draw(ball);
                window->draw(player1Score);
                window->draw(player2Score);
                window->display();
                break;

        }

    }



    int main()
{
    Pong pong;
    pong.start();
    return 0;
}



