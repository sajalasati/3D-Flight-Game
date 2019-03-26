#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float base_width;
    float base_length;
    float extra;
    int lives;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
    double speed;
private:
    VAO *object;
    VAO *object2;
};
#endif // ENEMY_H