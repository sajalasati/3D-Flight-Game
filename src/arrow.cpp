#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->speed = 0.0f;
    this->width_body = 0.4;
    this->width_arrow = 0.8;
    this->length1 = 1.0f;
    this->length2 = 0.4f;
    static GLfloat vertex_buffer_data[]={
        -this->width_body/2,0.0f,0.0f,
        -this->width_body/2,-this->length1,0.0f,
        this->width_body/2,-this->length1,0.0f,
        this->width_body/2,-this->length1,0.0f,
        -this->width_body/2,0.0f,0.0f,
        this->width_body/2,0.0f,0.0f,
        -this->width_arrow/2,0.0f,0.0f,
        this->width_arrow/2,0.0f,0.0f,
        0.0f,this->length2,0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, COLOR_LIFERED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube around which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {
    // nothing
}

void Arrow::change_rotation(float rot) {
    this->rotation = rot;
}