#include "main.h"

#ifndef SPEEDBAR
#define SPEEDBAR

class Speedbar {
public:
    Speedbar() {}
    Speedbar(float x, float y, float z, int health);
    glm::vec3 position;
    float rotation;
    float height;
    float bar_width;
    float length;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_objects(float speed);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif // SPEEDBAR