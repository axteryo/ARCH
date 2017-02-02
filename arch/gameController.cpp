#include "gameController.h"

gameController::gameController()
{
    activateThrustersAction ="none";
    turnLeftAction = "none";
    turnRightAction = "none";
    useAttack1Action = "none";
}

gameController::~gameController()
{
    //dtor
}

void gameController::loadBinding()
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
    activateThrustersAction = root["activateThrusters"].asString();
    turnLeftAction = root["turnLeft"].asString();
    turnRightAction = root["turnRight"].asString();
    useAttack1Action = root["useAttack1"].asString();

}

bool gameController::isBindedKeyPressed(std::string bindingToCheck)
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
        else if (bindingToCheck == "Space")
        {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			return true;
		else
			return false;
        }

}

bool gameController::isBindedKeyReleased(std::string bindingToCheck, sf::Event e)
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
         else if (bindingToCheck == "Space")
        {
		if ( e.key.code == sf::Keyboard::Space)
			return true;
		else
			return false;
        }

}

bool gameController::isActionKeyPressed(std::string actionToCheck)
{
    if(actionToCheck == "activateThrusters")
    {
        if(isBindedKeyPressed(activateThrustersAction))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(actionToCheck == "turnRight")
    {
        if(isBindedKeyPressed(turnRightAction))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(actionToCheck == "turnLeft")
    {
        if(isBindedKeyPressed(turnLeftAction))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
     else if(actionToCheck == "useAttack1")
    {
        if(isBindedKeyPressed(useAttack1Action))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool gameController::isActionKeyReleased(std::string actionToCheck, sf::Event e)
{
    if(actionToCheck == "activateThrusters")
    {
        if(isBindedKeyReleased(activateThrustersAction,e))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(actionToCheck == "turnRight")
    {
        if(isBindedKeyReleased(turnRightAction,e))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(actionToCheck == "turnLeft")
    {
        if(isBindedKeyReleased(turnLeftAction,e))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
     else if(actionToCheck == "useAttack1")
    {
        if(isBindedKeyReleased(useAttack1Action,e))
        {
            return true;
        }
        else
        {
            return false;
        }
    }


}
