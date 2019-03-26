#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H

class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z, float distance, float shoot_pitch);
    glm::vec3 position;
    glm::vec3 dir_cos;
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
#endif // CHECKPOINT_H