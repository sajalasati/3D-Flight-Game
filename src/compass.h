#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float radius;
    float width;
    float length;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
};

#endif // COMPASS_H