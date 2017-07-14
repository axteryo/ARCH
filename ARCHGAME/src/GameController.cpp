#include "GameController.h"


GameController::GameController()
{
    //ctor
    playerThrustAction="";
    playerBrakeAction = "";
    playerTurnLeftAction="";
    playerTurnRightAction="";
    playerBoostAction= "";
    playerUseAttack1Action="";
    playerUseAttack2Action="";
    playerUseAttack3Action="";
    selectBackwardAction = "";
    selectForwardAction ="";
    confirmSelectionAction = "";
}

GameController::~GameController()
{
    //dtor
}

void GameController::loadDefaultBindings()
{
    baseKeyRoot = jsonHandler.loadJson("data/keyMap.json");
    if(!baseKeyRoot.empty())
    {
        std::cout<<"Controller Bindings have successfully been loaded"<<std::endl;

        playerThrustAction=baseKeyRoot["thrust"].asString();
        playerBrakeAction = baseKeyRoot["brake"].asString();
        playerTurnLeftAction=baseKeyRoot["turnLeft"].asString();
        playerTurnRightAction=baseKeyRoot["turnRight"].asString();
        playerBoostAction=baseKeyRoot["boost"].asString();
        playerUseAttack1Action=baseKeyRoot["useAttack1"].asString();
        playerUseAttack2Action=baseKeyRoot["useAttack2"].asString();
        playerUseAttack3Action=baseKeyRoot["useAttack3"].asString();
        selectBackwardAction = baseKeyRoot["selectBackward"].asString();
        selectForwardAction =baseKeyRoot["selectForward"].asString();
        confirmSelectionAction =baseKeyRoot["confirmSelection"].asString();
    }
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
    if(bindingToCheck.compare("S")==0)
    {
        if(keyBoard.isKeyPressed(keyBoard.S))
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
    if(actionToCheck.compare("boost")==0)
    {
        if(isBindedKeyPressed(playerBoostAction))
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
    if(actionToCheck.compare("useAttack3")==0)
    {
        if(isBindedKeyPressed(playerUseAttack3Action))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(actionToCheck.compare("selectForward")==0)
    {
        if(isBindedKeyPressed(selectForwardAction))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(actionToCheck.compare("selectBackward")==0)
    {
        if(isBindedKeyPressed(selectBackwardAction))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(actionToCheck.compare("confirmSelection")==0)
    {
        if(isBindedKeyPressed(confirmSelectionAction))
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
