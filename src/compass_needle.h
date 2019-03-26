#include "main.h"

#ifndef COMPASS_NEEDLE
#define COMPASS_NEEDLE


class CompassNeedle {
public:
    CompassNeedle() {}
    CompassNeedle(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float base;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
};

#endif // COMPASS_NEEDLE