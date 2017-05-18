#include "GameController.h"


GameController::GameController()
{
    //ctor
    playerThrustAction="";
    playerBrakeAction = "";
    playerTurnLeftAction="";
    playerTurnRightAction="";
    playerUseAttack1Action="";
    playerUseAttack2Action="";
}

GameController::~GameController()
{
    //dtor
}

void GameController::loadBindings()
{
    Json::Value root;
    Json::Reader reader;
    std::ifstream file;
    file.open("assets/keyMap.json");

    bool parsedSuccess = reader.parse(file,root,false);
    if(!parsedSuccess)
    {
        std::cout<<"failed to parse JSON"<< std::endl
        <<reader.getFormattedErrorMessages()
        <<std::endl;
    }
    else
    {
        std::cout<<"Controller Bindings have successfully been loaded"<<std::endl;
    }
    playerThrustAction=root["thrust"].asString();
    playerBrakeAction = root["brake"].asString();
    playerTurnLeftAction=root["turnLeft"].asString();
    playerTurnRightAction=root["turnRight"].asString();
    playerUseAttack1Action=root["useAttack1"].asString();
    playerUseAttack2Action=root["useAttack2"].asString();

    file.close();
}

bool GameController::isBindedKeyPressed(std::string bindingToCheck)
{
    if(bindingToCheck.compare("Up")==0)
    {
        if(keyBoard.isKeyPressed(keyBoard.Up))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(bindingToCheck.compare("Down")==0)
    {
        if(keyBoard.isKeyPressed(keyBoard.Down))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(bindingToCheck.compare("Left")==0)
    {
        if(keyBoard.isKeyPressed(keyBoard.Left))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(bindingToCheck.compare("Right")==0)
    {
        if(keyBoard.isKeyPressed(keyBoard.Right))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(bindingToCheck.compare("Space")==0)
    {
        if(keyBoard.isKeyPressed(keyBoard.Space))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
     if(bindingToCheck.compare("LShift")==0)
    {
        if(keyBoard.isKeyPressed(keyBoard.LShift))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(bindingToCheck.compare("W")==0)
    {
        if(keyBoard.isKeyPressed(keyBoard.W))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(bindingToCheck.compare("A")==0)
    {
        if(keyBoard.isKeyPressed(keyBoard.A))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;

}

bool GameController::isActionKeyPressed(std::string actionToCheck)
{
    if(actionToCheck.compare("thrust")==0)
    {
        if(isBindedKeyPressed(playerThrustAction))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(actionToCheck.compare("brake")==0)
    {
        if(isBindedKeyPressed(playerBrakeAction))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(actionToCheck.compare("turnRight")==0)
    {
        if(isBindedKeyPressed(playerTurnRightAction))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(actionToCheck.compare("turnLeft")==0)
    {
        if(isBindedKeyPressed(playerTurnLeftAction))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(actionToCheck.compare("useAttack1")==0)
    {
        if(isBindedKeyPressed(playerUseAttack1Action))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
     if(actionToCheck.compare("useAttack2")==0)
    {
        if(isBindedKeyPressed(playerUseAttack2Action))
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    return false;
}
