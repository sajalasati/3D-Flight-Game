#include "main.h"

#ifndef BOMB_H
#define BOMB_H

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float radius;
    float distance;
    float height;
    float length;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bounding_box_t bounding_box();
    void tick();
    double speed;
private:
    VAO *object;
};
#endif // BOMB_H