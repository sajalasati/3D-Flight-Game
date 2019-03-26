#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, float ang1, float ang2);
    glm::vec3 position;
    float length;
    float nose;
    float width;
    float radius1;
    float radius2;
    float slope;
    float ang1; //pitch
    float ang2; //yaw
    float x0;
    float y0;
    float z0;
    float d;
    float rotation_roll;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bounding_box_t bounding_box();
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
};

#endif // MISSILE_H