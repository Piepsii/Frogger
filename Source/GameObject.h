#pragma once
#include "SFML/Graphics.hpp"

class GameObject
{
public:
    GameObject();
    ~GameObject();
    virtual void Update() = 0;
    virtual void Draw(sf::RenderWindow& _window) = 0;
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
};

