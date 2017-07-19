#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <math.h>



#include "dist/json/json.h"

sf::Vector2f wSize(1000,800);
sf::Mouse mouse;
sf::RenderWindow window(sf::VideoMode(wSize.x,wSize.y,32),"Hello KeyTest");



class GameController
{
    public:
    std::string turnRedAction;
    std::string turnBlueAction;
    std::string turnYellowAction;
    std::string turnGreenAction;
    std::string selectForwardAction;
    std::string selectBackwardAction;
    std::string confirmSelectionAction;




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
        selectBackwardAction = root["selectBackward"].asString();
        selectForwardAction =root["selectForward"].asString();
        confirmSelectionAction =root["confirmSelection"].asString();
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
        else if (bindingToCheck == "Space")
        {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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

GameController* gC;


class UI_Component
{
public:
    sf::Vector2f position;
    sf::Vector2f relative_position;
    sf::Vector2f scale;
};
class UIC_Label: UI_Component
{
    public:
        sf::Text text;
        sf::Font font;

        void setFont(sf::Font f)
        {
            font = f;
        }

         void setLabelText(std::string str,int _size,sf::Color c)
        {
            text.setFont(font);
            text.setString(str);
            text.setCharacterSize(_size);
            text.setColor(c);
            text.setPosition(0,0);
        }
        void setPosition(sf::Vector2f pos)
        {
            position = pos;
            text.setPosition(pos);
        }
};

class UIC_Graphic : public UI_Component
{
    public:
        sf::Texture texture;
        sf::Sprite sprite;

        void loadTexture(std::string src)
        {
            texture.loadFromFile(src);
            sprite.setTexture(texture);
        }
        sf::Sprite getSprite()
        {
            return sprite;
        }
        void setPosition(sf::Vector2f pos)
        {
            position = pos;
            sprite.setPosition(pos);
        }
};

class UI_Element
{
    public:

    sf::Vector2f relative_position;
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;
    sf::RectangleShape body;
    UIC_Graphic graphic;
    bool hasTexture;
    bool hasRectBody;
    void setPosition(sf::Vector2f pos)
    {
        position = sf::Vector2f(pos.x+relative_position.x,pos.y+relative_position.y);
        body.setPosition(position);
        if(hasTexture)
        {
            graphic.setPosition(position);
        }
    }
     void setPositionRelative(sf::Vector2f pos)
    {
        relative_position = pos;
    }
    void createRectBody(sf::Vector2f sc, sf::Color fillC,sf::Color outlineC,int thicness, float rot)
    {
        scale = sc;
        rotation = rot;

        body.setSize(sc);
        body.setFillColor(fillC);
        body.setOutlineColor(outlineC);
        body.setOutlineThickness(thicness);
        body.setRotation(rot);
        hasRectBody = true;
    }
    void createGraphic(std::string src)
    {
        hasTexture = true;
        graphic.loadTexture(src);
    }
    sf::Vector2f getPosition()
    {
        return position;
    }
    enum UI_TYPE
    {
        BUTTON,
        //TEXT_DISPLAY,
        ICON,
        PANEL
    }ui_type;
    enum CONTROL_OVER_STATE
    {
        CONTROL_OVER_T,
        CONTROL_OVER_F
    }control_over_state;
    enum CONTROL_PRESS_STATE
    {
        CONTROL_PRESS_T,
        CONTROL_PRESS_F
    }control_press_state;

    sf::RectangleShape getBody()
    {
        return body;
    }
    //virtual void handleEvent(sf::Event e) = 0;
    bool isMouseOver(sf::Vector2f pos)
    {
        if(body.getGlobalBounds().contains(pos.x,pos.y))
        {
            return true;
        }
        return false;
    }
    bool isTextured()
    {
        return hasTexture;
    }

    UIC_Graphic getGraphic()
    {
        return graphic;
    }

};

class UI_Button : public UI_Element
{
public:
    UI_Button()
    {
        ui_type = BUTTON;
        control_press_state=CONTROL_PRESS_F;
        control_over_state =CONTROL_OVER_F;
    };



    void onControlOver()
    {
        control_over_state = CONTROL_OVER_T;
    }
    void onControlNotOver()
    {
        control_over_state = CONTROL_OVER_F;
    }
    void onControlPress()
    {
        control_press_state = CONTROL_PRESS_T;
    }
    void onControlRelease()
    {
        control_press_state = CONTROL_PRESS_F;
    }

    void handleEvent(sf::Event e)
    {
      /*  if(e.type == sf::Event::MouseMoved)
        {
            sf::Vector2i pos = mouse.getPosition(window);
            if(body.getGlobalBounds().contains(pos.x,pos.y))
            {
                control_over_state = CONTROL_OVER_T;
            }
            else{control_over_state = CONTROL_OVER_F;}
        }
        if((e.type == sf::Event::MouseButtonPressed) && (e.mouseButton.button == sf::Mouse::Left))
        {
            switch (control_over_state)
            {
            case CONTROL_OVER_T:
                control_press_state = CONTROL_PRESS_T;
                break;
            case CONTROL_OVER_F:
                control_press_state = CONTROL_PRESS_F;
                break;
            }
        }
        if((e.type == sf::Event::MouseButtonReleased) && (e.mouseButton.button == sf::Mouse::Left))
        {
            switch (control_over_state)
            {
            case CONTROL_OVER_T:
               control_press_state = CONTROL_PRESS_F;
                break;
            case CONTROL_OVER_F:
                 control_press_state = CONTROL_PRESS_F;
                break;
            }
        }*/
    }

    void update()
    {

        switch(control_over_state)
        {
        case CONTROL_OVER_T:
            body.setOutlineColor(sf::Color::Blue);
            break;
        case CONTROL_OVER_F:
            body.setOutlineColor(sf::Color::Red);
            break;
        }
        switch(control_press_state)
        {
        case CONTROL_PRESS_T:
            body.setFillColor(sf::Color::Blue);
            break;
        case CONTROL_PRESS_F:
            body.setFillColor(sf::Color::Transparent);
            break;
        }
    }
};


class UI_Panel : public UI_Element
{
public:
    UI_Panel()
    {
        ui_type = PANEL;
        control_press_state=CONTROL_PRESS_F;
        control_over_state =CONTROL_OVER_F;
    }

     virtual void handleEvent(sf::Event e)
     {

     }
};
class Interface
{
    public:
    UI_Panel* mainPanel;
    std::vector<UI_Button*> buttonList;
    UI_Element* selectedElement;
    UI_Button* activeButton;
    UI_Button* previousButton;
    sf::Vector2f position;
    std::string name;
    int currentButton;

    Interface(sf::Vector2f pos,std::string n)
    {

        mainPanel = new UI_Panel();
        mainPanel->createGraphic("assets/main_panel.png");
        sf::Vector2f panel_scale = sf::Vector2f(mainPanel->graphic.getSprite().getTextureRect().width,mainPanel->graphic.getSprite().getTextureRect().height);
        mainPanel->createRectBody(panel_scale,sf::Color::Transparent,sf::Color::Red,10,0);

        activeButton = nullptr;
        position = pos;
        mainPanel->setPosition(pos);

        int currentButton = 0;
        name = n;
    }

    void addButton(UI_Button* b)
    {
        buttonList.push_back(b);
    }
    void setup()
    {
        setActive(buttonList[currentButton]);
        mainPanel->setPositionRelative(sf::Vector2f(0,0));
        mainPanel->setPosition(sf::Vector2f(250,100));
        int rel_x, rel_y;
        rel_x = 180;
        rel_y = 200;
        for(int i = 0;i<buttonList.size();i++)
        {
            buttonList[i]->setPositionRelative(sf::Vector2f(rel_x,rel_y));
            rel_y+=150;
            buttonList[i]->setPosition(mainPanel->getPosition());
            buttonList[i]->update();
        }

    }

    void setActive(UI_Button* b)
    {
        if(activeButton!=nullptr)
        {
            activeButton->onControlNotOver();
            activeButton->onControlRelease();
            activeButton->update();
        }
         activeButton = b;
         activeButton->onControlOver();
    }
    void selectForward()
    {
        window.setMouseCursorVisible(false);
        currentButton-=1;
        if(currentButton<0)
        {
            currentButton=buttonList.size()-1;
        }
        setActive(buttonList[currentButton]);
    }
    void selectBackward()
    {
        window.setMouseCursorVisible(false);
        currentButton++;
        if(currentButton>=buttonList.size())
        {
            currentButton = 0;
        }
        setActive(buttonList[currentButton]);
    }
    void confirmSelection()
    {
        activeButton->onControlPress();
    }
    void unConfirmSelection()
    {
        activeButton->onControlRelease();
    }
    void update(GameController* controller)
    {
        if(controller->isActionKeyPressed("confirmSelection"))
        {
            confirmSelection();
        }
        else{unConfirmSelection();}

        if(controller->isActionKeyPressed("selectForward"))
        {
            selectForward();
        }
        if(controller->isActionKeyPressed("selectBackward"))
        {
            selectBackward();
        }
         activeButton->update();
    }
    void handleWindowEvent(sf::Event e)
    {
        for(int i = 0; i <buttonList.size();i++)
        {
            sf::Vector2i pos = mouse.getPosition(window);
            if(e.type == sf::Event::MouseMoved)
            {   window.setMouseCursorVisible(true);
                if(buttonList[i]->isMouseOver(sf::Vector2f(pos.x,pos.y)))
                {
                    setActive(buttonList[i]);
                    currentButton = i;
                }
            }
            if((e.type == sf::Event::MouseButtonPressed) && (e.mouseButton.button == sf::Mouse::Left))
            {
                 if(buttonList[i]->isMouseOver(sf::Vector2f(pos.x,pos.y)))
                {
                    confirmSelection();
                }
                //else{unConfirmSelec
            }
            if((e.type == sf::Event::MouseButtonReleased) && (e.mouseButton.button == sf::Mouse::Left))
            {
               /* switch (control_over_state)
                {
                case CONTROL_OVER_T:
                   control_press_state = CONTROL_PRESS_F;
                    break;
                case CONTROL_OVER_F:
                     control_press_state = CONTROL_PRESS_F;
                    break;
                }*/
            }
        }

    }


    void draw(sf::RenderWindow &w)
    {
        w.draw(mainPanel->getBody());
        w.draw(mainPanel->graphic.getSprite());
        for(int i = 0; i <buttonList.size(); i++)
        {
            if(buttonList[i]->isTextured())
            {
                w.draw(buttonList[i]->getGraphic().getSprite());

            }
            w.draw(buttonList[i]->getBody());
        }
    }
};
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


int main()
{

    sf::Event event;
    window.setFramerateLimit(60);



    std::string Input;

    TestObject tO;
    gC = new GameController();
    gC->loadBinding();
    float x = .1+.2+.3;


    //window.setMouseCursorVisible(false);

    sf::Font font;
     if(!font.loadFromFile("arial.ttf"))
    {
    std::cout<< "we fudged up";
    }

    UIC_Label label;
    label.setFont(font);
    label.setLabelText("BUTTON1",20,sf::Color::Black);
    //label.setPosition(myButton->position);
    Interface* testInterface = new Interface(sf::Vector2f(0,0),"TEST");

    UI_Button* myButton = new UI_Button();
    myButton->createGraphic("assets/start_button.png");
    sf::Vector2f button_scale = sf::Vector2f(myButton->graphic.getSprite().getTextureRect().width,myButton->graphic.getSprite().getTextureRect().height);
    myButton->createRectBody(button_scale,sf::Color::Transparent,sf::Color::Blue,5,0);

    UI_Button* myButton1 = new UI_Button();
    myButton1->createGraphic("assets/exit_button.png");
    button_scale = sf::Vector2f(myButton1->graphic.getSprite().getTextureRect().width,myButton1->graphic.getSprite().getTextureRect().height);
    myButton1->createRectBody(button_scale,sf::Color::Transparent,sf::Color::Blue,5,0);

    testInterface->addButton(myButton);
    testInterface->addButton(myButton1);

    testInterface->setup();

    while(window.isOpen())
    {
        //myButton->setLabelText();

        //myButton->update();
        //myButton1->update();
        //myButton2->update();

        while(window.pollEvent(event))
        {

            testInterface->handleWindowEvent(event);
           /* myButton->handleEvent(event);
            myButton1->handleEvent(event);
            myButton2->handleEvent(event);*/
            /*if(event.type == sf::Event::Closed)
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
            }*/

            testInterface->update(gC);


        }



         window.clear((sf::Color::White));
         //window.draw(tO.rect);
        /* window.draw(myButton->getBody());
          window.draw(myButton1->getBody());
           window.draw(myButton2->getBody());*/
         //window.draw(label.text);
         testInterface->draw(window);
         window.display();

    }

       return 0;

}

