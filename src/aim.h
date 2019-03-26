#include "main.h"

#ifndef AIM_H
#define AIM_H

class Aim {
public:
    Aim() {}
    Aim(float x, float y, float z, float distance, float shoot_pitch);
    glm::vec3 position;
    float rotation;
    float radius;
    float distance;
    float width;
    float length;
    float rotation_pitch;
    float rotation_yaw;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z, float new_yaw);
    void tick();
    double speed;
private:
    VAO *object;
};
#endif // AIM_H