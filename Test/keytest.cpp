#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <math.h>



#include "dist/json/json.h"


class TestObject
{
    public:
    sf::RectangleShape rect;

    TestObject()
    {
        rect.setSize(sf::Vector2f(20,20));
        rect.setFillColor(sf::Color::Red);
        rect.setPosition(200,400);
    }

    void turnRed()
    {
        rect.setFillColor(sf::Color::Red);
    }
    void turnBlue()
    {
        rect.setFillColor(sf::Color::Blue);
    }
    void turnGreen()
    {
        rect.setFillColor(sf::Color::Green);
    }
    void turnYellow()
    {
        rect.setFillColor(sf::Color::Yellow);
    }
};

class GameController
{
    public:
    std::string turnRedAction;
    std::string turnBlueAction;
    std::string turnYellowAction;
    std::string turnGreenAction;




    void loadBinding()
    {

        Json::Value root;
        Json::Reader reader;
        std::ifstream file;
        file.open("keyMap.json");

        bool parsedSuccess = reader.parse(file,root,false);
        if(!parsedSuccess)
        {
            std::cout<<"failed to parse JSON"<< std::endl
            <<reader.getFormattedErrorMessages()
            <<std::endl;

        }


        turnRedAction = root["turnRed"].asString();
        turnBlueAction = root["turnBlue"].asString();
        turnYellowAction = root["turnYellow"].asString();
        turnGreenAction = root["turnGreen"].asString();
    }

        bool isBindedKeyPressed(std::string bindingToCheck)
        {
        if (bindingToCheck == "Left")

        {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			return true;
		else
			return false;
        }
        else if (bindingToCheck == "Right")
        {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			return true;
		else
			return false;
        }
        else if (bindingToCheck == "Up")
        {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			return true;
		else
			return false;
        }
        else if (bindingToCheck == "Down")
        {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
           return true;
        else
            return false;
        }
    }

    bool isBindedKeyReleased(std::string bindingToCheck, sf::Event e)
        {

        if (bindingToCheck == "Left")

        {
		if ( e.key.code == sf::Keyboard::Left)
			return true;
		else
			return false;
        }
        else if (bindingToCheck == "Right")
        {
		if (e.key.code == sf::Keyboard::Right)
			return true;
		else
			return false;
        }
        else if (bindingToCheck == "Up")
        {
		if ( e.key.code == sf::Keyboard::Up)
			return true;
		else
			return false;
        }
        else if (bindingToCheck == "Down")
        {
        if(e.key.code == sf::Keyboard::Down)
           return true;
        else
            return false;
        }
    }


    bool isActionKeyPressed(std::string actionToCheck)
    {

        if(actionToCheck == "turnRed")
        {
            if(isBindedKeyPressed(turnRedAction))
            {

                return true;
            }

            else
            {
                return false;

            }

        }
        else if(actionToCheck == "turnBlue")
        {
            if(isBindedKeyPressed(turnBlueAction))
                return true;
            else
                return false;

        }
        else if(actionToCheck == "turnYellow")
        {
            if(isBindedKeyPressed(turnYellowAction))
                return true;
            else
                return false;
        }
        else if(actionToCheck == "turnGreen")
        {
            if(isBindedKeyPressed(turnGreenAction))
                return true;
            else
                return false;
        }

    }

    bool isActionKeyReleased(std::string actionToCheck, sf::Event e)
     {

        if(actionToCheck == "turnRed")
        {
            if(isBindedKeyReleased(turnRedAction,e))
            {

                return true;
            }

            else
            {
                return false;

            }

        }

        else if(actionToCheck == "turnBlue")
        {
            if(isBindedKeyReleased(turnBlueAction,e))
                return true;
            else
                return false;

        }
        else if(actionToCheck == "turnYellow")
        {
            if(isBindedKeyReleased(turnYellowAction,e))
                return true;
            else
                return false;
        }
        else if(actionToCheck == "turnGreen")
        {
            if(isBindedKeyReleased(turnGreenAction,e))
                return true;
            else
                return false;
        }

    }

    void setBinding()
    {

    }
};


int main()
{
    sf::Vector2f wSize(1000,800);
    sf::RenderWindow window(sf::VideoMode(wSize.x,wSize.y,32),"Hello KeyTest");
    window.setFramerateLimit(60);
    sf::Event event;
    sf::Mouse mouse;
    std::string Input;

    TestObject tO;
    GameController* gC;
    gC = new GameController();
    gC->loadBinding();
    float x = .1+.2+.3;

    std::cout<< x<<std::endl;



    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();

            }
            if (event.type == sf::Event::KeyPressed)
            {
                       if(gC->isActionKeyPressed("turnRed"))
            {
                tO.turnRed();
            }
            else if(gC->isActionKeyPressed("turnBlue"))
            {
                tO.turnBlue();
            }
             else if(gC->isActionKeyPressed("turnGreen"))
            {
                tO.turnGreen();
            }
            else if(gC->isActionKeyPressed("turnYellow"))
            {
                tO.turnYellow();
            }
            }
            if(event.type == sf::Event::KeyReleased)
            {
            if(gC->isActionKeyReleased("turnRed",event))
            {
                std::cout<<"Red key released"<<std::endl;
            }
            else if(gC->isActionKeyReleased("turnBlue",event))
            {
                std::cout<<"Blue key released"<<std::endl;
            }
             else if(gC->isActionKeyReleased("turnGreen",event))
            {
                std::cout<<"Green key released"<<std::endl;
            }
            else if(gC->isActionKeyReleased("turnYellow",event))
            {
                std::cout<<"Yellow key released"<<std::endl;
            }
            }

        }
         if(gC->isActionKeyPressed("turnRed"))
            {
                tO.turnRed();
            }
            else if(gC->isActionKeyPressed("turnBlue"))
            {
                tO.turnBlue();
            }
             else if(gC->isActionKeyPressed("turnGreen"))
            {
                tO.turnGreen();
            }
            else if(gC->isActionKeyPressed("turnYellow"))
            {
                tO.turnYellow();
            }

         window.clear((sf::Color::White));
         window.draw(tO.rect);
         window.display();
    }

       return 0;

}

