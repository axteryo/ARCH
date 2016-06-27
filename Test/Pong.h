#ifndef PONG_H
#define PONG_H

#include <iostream>
#include <string>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Pong
{
    private:
        enum state
        {
            In_Game ,
            Main_Menu
        } GameState;
        bool gameRunning;
        sf::Vector2f windowDimension;
        sf::Vector2f paddleMeasurement;

        sf::RectangleShape player1;
        sf::Vector2f player1Pos;
        sf::Vector2f player1Bounds;
        int score1;
        std::stringstream scoreS1;
        sf::Text player1Score;
        sf::RectangleShape player2;
        sf::Vector2f player2Pos;
        sf::Vector2f player2Bounds;
        int score2;
        std::stringstream scoreS2;
        sf::Text player2Score;

        sf::RectangleShape ball;
        sf::Vector2f ballVelocity;
        sf::Vector2f ballDirection;
        sf::Vector2f ballPos;

        sf::RectangleShape board;
        sf::Vector2f boardPos;
        sf::Vector2f boardBounds;
        sf::Vector2f ballBounds;
        sf::RenderWindow* window;
        sf::Keyboard keyboard;
        sf::Mouse mouse;
        sf::Vector2i mousePos;
        sf::Event event;

        std::string button;
        sf::Text startButton;
        sf::Text title;
        sf::Text exitButton;
        sf::Font font;
        bool mouseOver;

    public:

        Pong();

        void start();

        void processInput(state currentState);

        void update(state currentState);

        void render(state currentState);

        int main();


};

#endif // PONG_H
