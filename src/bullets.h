#include "main.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y, float z, float dr_x, float dr_y, float dr_z);
    glm::vec3 position;
    glm::vec3 dir_cos;
    float rotation;
    float distance;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_dir_cos(float dr_x, float dr_y, float dr_z);
    bool check_collision(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BULLET_H