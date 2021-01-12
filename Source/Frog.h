#pragma once
#define _USE_MATH_DEFINES
#include "cmath"
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "config.h"
#include "InputManager.h"

class Frog :
    public GameObject
{
public:
    Frog();
    ~Frog();
    void Update();
    void Draw(sf::RenderWindow& _window);
    void jump(Direction _direction);
    bool isJumping();
    void handleInput(InputManager* _inputManager);
    void resetPlayer();
    sf::RectangleShape getCollisionBounds();

private:
    bool m_isJumping;
    sf::Vector2f m_currentPosition, m_destinationPosition, m_direction;
    float m_velocity;
    sf::RectangleShape m_collisionBounds;
};

