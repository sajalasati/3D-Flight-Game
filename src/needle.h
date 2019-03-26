#include "main.h"

#ifndef NEEDLE_H
#define NEEDLE_H


class Needle {
public:
    Needle() {}
    Needle(float x, float y, float z, color_t color, int type);
    glm::vec3 position;
    float rotation;
    float radius;
    float width;
    float length;
    int type;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // NEEDLE_H