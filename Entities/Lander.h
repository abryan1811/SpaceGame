#include <raylib.h>

struct Ship
{
    Texture2D texture;
    Rectangle rec;   
    
    Vector2 Thrust;    
    float mass;
    Vector2 f; // Force
    Vector2 position;
    Vector2 dr; //Position Change within the frame
    Vector2 v; //Current Speed
    Vector2 dv; //Speed changed within the frame
};