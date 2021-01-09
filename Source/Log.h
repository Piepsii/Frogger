#pragma once
#include "Obstacle.h"
class Log :
    public Obstacle
{
public:
    Log(int _line, float _x, Direction _direction, int _size);
    ~Log();
    void Update();
    void Draw(sf::RenderWindow& _window);
};

