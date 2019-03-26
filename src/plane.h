#include "main.h"

#ifndef PLANE_H
#define PLANE_H

class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z);
    glm::vec3 position;
    float rotation_roll, rotation_yaw, rotation_pitch;
    float min_pitch;
    float fuel;
    float max_pitch;
    float length;
    int health;
    int score;
    float nose;
    float width;
    float radius1;
    float radius2;
    float slope;
    float up_down_speed;
    float roll_speed;
    float yaw_speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void move_forward();
    void move_backward();
    void move_up();
    void move_down();
    void apply_gravity();
    void roll(float x);
    void yaw(float x);
    void gotfuel(float f);
    double speed;
    double bwdspeed;
    float accn;
    bounding_box_t bounding_box();
    bounding_box_t bounding_box2();
private:
    VAO *object;
    VAO *object2;
};

#endif // PLANE_H