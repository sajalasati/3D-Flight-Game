#include "compass_needle.h"
#include "main.h"

CompassNeedle::CompassNeedle(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->speed = 0.0f;
    this->base = 0.25;
    this->height = 0.9f;
    static GLfloat vertex_buffer_data[]={
        -this->base/2,0.0f,0.0f,
        this->base/2,0.0f,0.0f,
        0.0f,this->height,0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data,COLOR_LIFERED, GL_FILL);
    static GLfloat vertex_buffer_data2[]={
        -this->base/2,0.0f,0.0f,
        this->base/2,0.0f,0.0f,
        0.0f,-this->height,0.0f,
    };
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_DIGIT_WHITE , GL_FILL);
}

void CompassNeedle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void CompassNeedle::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void CompassNeedle::tick() {
    // this->rotation += 5*speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}