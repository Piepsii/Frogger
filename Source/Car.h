#pragma once
#include "Obstacle.h"
class Car :
    public Obstacle
{
public:
    Car(int _line, float _x, Direction _direction, int _size);
    ~Car();
    void Update();
    void Draw(sf::RenderWindow& _window);
};

