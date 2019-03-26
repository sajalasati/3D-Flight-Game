#include "needle.h"
#include "main.h"

Needle::Needle(float x, float y, float z, color_t color, int type) {
    this->position = glm::vec3(x, y, z);
    this->rotation = (type==1)? 0.0f: 140.0f;
    this->type = type;
    this->speed = (type==1)? 0.01f: -0.01f;
    float base = 0.08, height = 0.9f;
    static GLfloat vertex_buffer_data[]={
        0.0f,base/2,0.0f,
        0.0f,-base/2,0.0f,
        height,-base/2,0.0f,
        0.0f,base/2,0.0f,
        height,base/2,0.0f,
        height,-base/2,0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Needle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Needle::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Needle::tick() {
    this->rotation += 5*speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}