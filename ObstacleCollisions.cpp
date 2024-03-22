#include "ObstacleCollisions.h"

    Rectangle Asteroid::GetAsteroidRectangle() const {
        return (Rectangle){ position.x, position.y, sourceRect.width * scale, sourceRect.height * scale };
    }

    // Initialiser list to set up member variables from the constructor for more usage in the code.
    Asteroid::Asteroid(Vector2 startPos, Texture2D tex, float spd, float scl)
    : position(startPos), texture(tex), speed(spd), scale(scl), frame(0), updateTime(1.0f / 16.0f), runningTime(0.0f) {
    sourceRect.width = (texture.width) / 16; // for 16 columns
    sourceRect.height = (texture.height) / 2; // for 2 rows
    sourceRect.x = 0;
    sourceRect.y = 0;
    }

    void Asteroid::Update(float deltaTime) {
    position.y += speed * deltaTime;
    UpdateFrame(deltaTime);
    }

    void Asteroid::Draw() {

        Rectangle scaledRect = {
            position.x,
            position.y,
            sourceRect.width * scale,
            sourceRect.height * scale
        };

        Vector2 origin = {0.0f, 0.0f};
        DrawTexturePro(texture, sourceRect, scaledRect, origin, 0.0f, WHITE);
    }

    // bool to check if its left the screen
    bool Asteroid::IsOffScreen(int windowHeight) {
    return position.y > windowHeight;
    }

    // Animation logic
    void Asteroid::UpdateFrame(float deltaTime) {
        runningTime += deltaTime;
        if (runningTime >= updateTime) {
            runningTime = 0.0f;
            frame = (frame + 1) % 16; // Loop through frames on a row
            sourceRect.x = frame * sourceRect.width;
            // Toggle between the two rows
            if (frame == 0) {
            sourceRect.y = (sourceRect.y == 0) ? sourceRect.height : 0;
            }
        }
    }
