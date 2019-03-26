#include "main.h"

#ifndef ARROW_H
#define ARROW_H

class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float width_body;
    float width_arrow;
    float length1;//body
    float length2;//arrow height
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void change_rotation(float rot);
    void tick();
    double speed;
private:
    VAO *object;
};
#endif // ARROW_H