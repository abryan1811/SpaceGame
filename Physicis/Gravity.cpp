#include<iostream>
#include "Gravity.h"

struct Vector1
{
    Vector1(float _y)
        :y(_y)
    {};

    Vector1()
        :y(0.0f)
    {};

    float y;
};

struct Point
{   
    float mass;
    Vector1 f;    
    Vector1 r;
    Vector1 dr;
    Vector1 v;
    Vector1 dv;

     Point()
    {};
};

Vector1 Euler(Vector1 a, float h)
{
    return Vector1(a.y * h);
}

const Vector1 Gravity(-1.625f);
Vector1 Thrust(0.0f);

void SetForce(Point& p)
{
    p.f.y = (Gravity.y + Thrust.y) * p.mass;
}