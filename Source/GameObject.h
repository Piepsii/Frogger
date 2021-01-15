#pragma once
#include "SFML/Graphics.hpp"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();
    virtual void Update();
    virtual void Draw(sf::RenderWindow& _window);
    enum class Direction
    {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    sf::Texture* m_texture;
    sf::Sprite m_sprite;
    Direction m_direction;
    sf::Vector2f m_directionVector;
    float m_speed;

    sf::Vector2f getDirectionVector();
};

