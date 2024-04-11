#ifndef PHYSICS_H
#define PHYSICS_H

#include "raylib.h" 
#include "MovementController.h" 


Vector2 createVector2(float x, float y);

Vector2 Euler(Vector2 a, float h);


extern Vector2 Gravity;

void Collision_Sky(Ship& ship);
void Collision_Ground(Ship& ship);
void Collision_Left(Ship& ship);
void Collision_Right(Ship& ship);

void CheckCollision(Ship& ship);

void SetForce(Ship& ship);

void ApplyEuler(Ship& ship, float deltaTime);


void ApplyGravity(Ship& ship, float deltaTime);

#endif // PHYSICS_H
