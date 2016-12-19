#include "includes.h"


sf::Vector2f normalize(sf::Vector2f source)
{
    float mag = sqrt((source.x * source.x) + (source.y * source.y));
    if (mag != 0)
        {
            source = sf::Vector2f(source.x / mag, source.y / mag);
        //return source;
        }

        return source;
}
//b2Vec2 b2Norma


