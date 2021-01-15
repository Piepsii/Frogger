#pragma once
#define _USE_MATH_DEFINES
#include "cmath"
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "config.h"
#include "InputManager.h"

class Frog :
    public GameObject
{
public:
    Frog();
    ~Frog();
    void Update();
    void jump(Direction _direction);
    bool isJumping();
    void handleInput(InputManager* _inputManager);
    void resetPlayer();
    sf::RectangleShape getCollisionRect();
    void setOnLog(bool _param, sf::Vector2f _direction);
    bool isOnLog();

private:
    bool m_isJumping, m_isOnLog;
    sf::Vector2f m_destinationPosition, m_direction, m_floatDirection;
    float m_velocity;
    sf::RectangleShape m_collisionRect;

    sf::Sound m_jump;
    sf::SoundBuffer m_jumpBuffer;
};

