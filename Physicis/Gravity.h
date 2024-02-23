#include<iostream>

struct Vector1
{
    float y; // Vertical

    Vector1(float _y);
    Vector1();
};

struct Point{
    
    float mass;
    Vector1 f; //Force
    Vector1 r; //Position
    Vector1 dr; //Position Change
    Vector1 v; //Current Speed
    Vector1 dv; // Speedd Change

    Point();

};

Vector1 Euler(Vector1 a, float h);

extern Vector1 Gravity; //Gravity not a const - Allow us to play around with this force in game if we want to
extern Vector1 Thrust;

void SetForce(Point& p);