#ifndef OBSTACLE_COLLISIONS_H 
#define OBSTACLE_COLLISIONS_H

#include "raylib.h"

class Asteroid 
{
public:
    Vector2 position;
    Texture2D texture;
    float speed;
    Rectangle sourceRect;
    int frame;
    float updateTime;
    float runningTime;
    float scale;

    Asteroid(Vector2 startPos, Texture2D tex, float spd, float scl);
    void Update(float deltaTime);
    void Draw();
    bool IsOffScreen(int windowHeight);

    Rectangle GetAsteroidRectangle() const;

private:
    void UpdateFrame(float deltaTime);
};

#endif // OBSTACLE_COLLISIONS_H