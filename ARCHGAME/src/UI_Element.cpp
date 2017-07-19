#include "UI_Element.h"

UI_Element::UI_Element()
{
}

UI_Element::~UI_Element()
{
    //dtor
}
std::string UI_Element::getID()
{
    return id;
}

void UI_Element::setGraphicCoordinates(sf::IntRect c)
{

    default_texture_coordinates = c;
    texture_coordinates = default_texture_coordinates;
    hasTexture = true;

    dimensions.x = texture_coordinates.width;
    dimensions.y = texture_coordinates.height;
    rotation = 0;
    createRectBody(dimensions,sf::Color::Transparent,sf::Color::Blue,5,rotation);
}
void UI_Element::setOnControlOverTexture(sf::IntRect i)
{
    onControlOver_texture_coordinates = i;
}

void UI_Element::createRectBody(sf::Vector2f dim, sf::Color fillC,sf::Color outlineC,int lineSize, float rotat)
{
    rectbody.setSize(dim);
    rectbody.setFillColor(fillC);
    rectbody.setOutlineColor(outlineC);
    rectbody.setOutlineThickness(lineSize);
    rectbody.setRotation(rotat);
    hasRectBody = true;
}

void UI_Element::setRelativePosition(sf::Vector2f pos)
{
    relative_position = pos;
}
void UI_Element::setPosition(sf::Vector2f pos)
{
    position = sf::Vector2f(relative_position.x+pos.x,relative_position.y+pos.y);
    if(hasRectBody)
    {
        rectbody.setPosition(position);
    }
}

sf::Vector2f UI_Element::getPosition()
{
    return position;
}
sf::Vector2f UI_Element::getDimensions()
{
    return dimensions;
}

bool UI_Element::isPointWithinBounds(sf::Vector2f pos)
{
    if(rectbody.getGlobalBounds().contains(pos.x,pos.y))
    {
        return true;
    }
    return false;
}

sf::RectangleShape UI_Element::getRectBody()
{
    return rectbody;
}
BatchQuad UI_Element::getQuad()
{
    BatchQuad quad;


    quad.point4 = sf::Vector2f(position.x-dimensions.x/2,
                               position.y+dimensions.y/2);

    quad.point3 = sf::Vector2f(position.x+dimensions.x/2,
                               position.y+dimensions.y/2);

    quad.point2 = sf::Vector2f(position.x+dimensions.x/2,
                               position.y-dimensions.y/2);

    quad.point1 = sf::Vector2f(position.x-dimensions.x/2,
                               position.y-dimensions.y/2);

    quad.texPoint1 = sf::Vector2f(texture_coordinates.left,texture_coordinates.top);
    quad.texPoint2 = sf::Vector2f(texture_coordinates.left+texture_coordinates.width,texture_coordinates.top);
    quad.texPoint3 = sf::Vector2f(texture_coordinates.left+texture_coordinates.width,texture_coordinates.top+texture_coordinates.height);
    quad.texPoint4 = sf::Vector2f(texture_coordinates.left,texture_coordinates.top+texture_coordinates.height);

    quad.center = sf::Vector2f((quad.point1.x+quad.point2.x+quad.point3.x+quad.point4.x)/4,
                               (quad.point1.y+quad.point2.y+quad.point3.y+quad.point4.y)/4);
    quad.rotation = rotation;
    sf::Transform r;
    r.translate(dimensions.x/2,dimensions.y/2);
    //r.rotate(quad.rotation,quad.center);
    quad.point1 = r.transformPoint(quad.point1);
    quad.point2 =r.transformPoint(quad.point2);
    quad.point3 =r.transformPoint(quad.point3);
    quad.point4 =r.transformPoint(quad.point4);

    return quad;
}

