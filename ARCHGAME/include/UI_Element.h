#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H
#include "GraphicsComponent.h"


class UI_Element
{
    public:
        UI_Element();
        virtual ~UI_Element();

        enum UI_TYPE
        {
            BUTTON,
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

        void setGraphicCoordinates(sf::IntRect c);
        void setOnControlOverTexture(sf::IntRect i);
        void createRectBody(sf::Vector2f dim, sf::Color fillC,sf::Color outlineC,int lineSize, float rotat);
        void setPosition(sf::Vector2f pos);
        void setRelativePosition(sf::Vector2f pos);

        std::string getID();
        sf::Vector2f getPosition();
        sf::Vector2f getDimensions();
        BatchQuad getQuad();
        sf::RectangleShape getRectBody();
        bool isPointWithinBounds(sf::Vector2f pos);

        protected:
        sf::Vector2f position;
        sf::Vector2f relative_position;
        sf::Vector2f dimensions;
        float rotation;
        bool hasTexture;
        sf::IntRect texture_coordinates;
        sf::IntRect default_texture_coordinates;
        sf::IntRect onControlOver_texture_coordinates;
        bool hasRectBody;
        sf::RectangleShape rectbody;
    protected:
        std::string id;
    private:
};

#endif // UI_ELEMENT_H
