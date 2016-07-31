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

    void setBinding()
    {

    }
};


int main07()
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





    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();

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
