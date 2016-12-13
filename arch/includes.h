#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <string>
#include <math.h>


#include "GameObject.h"

//#include <thread>


class GameObject;
class Actor;


extern b2Vec2 gravity;
extern b2World* world;
extern std::vector<GameObject> objectList;
sf::Vector2f normalize(sf::Vector2f source);


#endif  //INCLUDES_H_INCLUDED
