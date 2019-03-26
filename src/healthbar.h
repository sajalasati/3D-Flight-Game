#include "main.h"

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

class Healthbar {
public:
    Healthbar() {}
    Healthbar(float x, float y, float z, int health);
    glm::vec3 position;
    float rotation;
    float height;
    float bar_width;
    float length;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_objects(int health);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif // HEALTHBAR_H