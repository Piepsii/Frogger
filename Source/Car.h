#pragma once
#include "GameObject.h"
class Car :
    public GameObject
{
public:
    Car(int _line, float _x, Direction _direction, int _size);
    ~Car();
};

