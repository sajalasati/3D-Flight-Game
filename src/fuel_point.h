#include "main.h"

#ifndef FUEL_H
#define FUEL_H

class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float radius;
    float distance;
    float width;
    float length;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bool check_collision(float x, float y, float z);
    double speed;
private:
    VAO *object;
};
#endif // FUEL_H