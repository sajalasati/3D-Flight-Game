#include "main.h"

#ifndef MOUNTAIN_H
#define MOUNTAIN_H


class Mountain {
public:
    Mountain() {}
    Mountain(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float base, height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // MOUNTAIN_H