#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <string>
#include <math.h>
//#include <iostream>
//#include <thread>
//#include <chrono>

class GameObject;


extern b2Vec2 gravity;
extern b2World* world;
extern std::vector<GameObject> objectList;

#endif  //INCLUDES_H_INCLUDED
