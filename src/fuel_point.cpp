#include "fuel_point.h"
#include "main.h"

Fuel::Fuel(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->speed = 1.0f;
    this->width = 1.0f;
    static GLfloat vertex_buffer_data[]={
        -this->width/2,0.0f,-this->width/2, // triangle 1 : begin
        -this->width/2,0.0f, this->width/2,
        -this->width/2, this->width, this->width/2, // triangle 1 : end
        this->width/2, this->width,-this->width/2, // triangle 2 : begin
        -this->width/2,0.0f,-this->width/2,
        -this->width/2, this->width,-this->width/2, // triangle 2 : end
        this->width/2,0.0f, this->width/2,
        -this->width/2,0.0f,-this->width/2,
        this->width/2,0.0f,-this->width/2,
        this->width/2, this->width,-this->width/2,
        this->width/2,0.0f,-this->width/2,
        -this->width/2,0.0f,-this->width/2,
        -this->width/2,0.0f,-this->width/2,
        -this->width/2, this->width, this->width/2,
        -this->width/2, this->width,-this->width/2,
        this->width/2,0.0f, this->width/2,
        -this->width/2,0.0f, this->width/2,
        -this->width/2,0.0f,-this->width/2,
        -this->width/2, this->width, this->width/2,
        -this->width/2,0.0f, this->width/2,
        this->width/2,0.0f, this->width/2,
        this->width/2, this->width, this->width/2,
        this->width/2,0.0f,-this->width/2,
        this->width/2, this->width,-this->width/2,
        this->width/2,0.0f,-this->width/2,
        this->width/2, this->width, this->width/2,
        this->width/2,0.0f, this->width/2,
        this->width/2, this->width, this->width/2,
        this->width/2, this->width,-this->width/2,
        -this->width/2, this->width,-this->width/2,
        this->width/2, this->width, this->width/2,
        -this->width/2, this->width,-this->width/2,
        -this->width/2, this->width, this->width/2,
        this->width/2, this->width, this->width/2,
        -this->width/2, this->width, this->width/2,
        this->width/2,0.0f, this->width/2
    };
    static GLfloat vertex_color_data[108];
    for(int i=0;i<36;++i){
        if(i<12){
            vertex_color_data[3*i] = 1.0;
            vertex_color_data[3*i+1] = 0.854;
            vertex_color_data[3*i+2] = 0.219;
        }
        else if(i<24){
            vertex_color_data[3*i] = 1.0;
            vertex_color_data[3*i+1] = 0.6588;
            vertex_color_data[3*i+2] = 0.219;
        }
        else{
            vertex_color_data[3*i] = 0.619;
            vertex_color_data[3*i+1] = 0.776;
            vertex_color_data[3*i+2] = 0.0901;
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, vertex_color_data, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_LIFERED, GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube around which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fuel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Fuel::tick() {
    // nothing
    this->rotation += this->speed;
}

bool Fuel::check_collision(float x, float y, float z) {
    glm::vec3 a = this->position;
    float dist = sqrt(abs(x-a[0])*abs(x-a[0]) + abs(y-a[1])*abs(y-a[1]) + abs(z-a[2])*abs(z-a[2]));
    return dist <= 1.0f;
}