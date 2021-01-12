#pragma once
#include "GameObject.h"

class Log :
    public GameObject
{
public:
    Log(int _line, float _x, Direction _direction, int _size);
    ~Log();
    void Update();
    void Draw(sf::RenderWindow& _window);
};

