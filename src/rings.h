#include "main.h"

#ifndef RING_H
#define RING_H

class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z,color_t color, float rot, float points);
    glm::vec3 position;
    float rotation;
    float size;
    float radius;
    float width;
    float length;
    int points;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
    bool check_collision(bounding_box_t ball);
private:
    VAO *object;
};

#endif // RING_H