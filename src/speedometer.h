#include "main.h"

#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H


class Speedometer {
public:
    Speedometer() {}
    Speedometer(float x, float y, float z, int type);
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
};

#endif // SPEEDOMETER_H