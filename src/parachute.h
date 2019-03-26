#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H

class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float radius;
    float distance;
    float height;
    float depth;
    float width;
    float maxup;
    float maxdown;
    int direc;
    float box_size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bounding_box_t bounding_box();
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};
#endif // PARACHUTE_H