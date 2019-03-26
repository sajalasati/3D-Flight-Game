#include "ground.h"
#include "main.h"

Ground::Ground(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    const int no_of_vertices = 6;
    float length = 1000.0f;
    static GLfloat vertex_buffer_data[18];
    float basic_ground[] = {
        -length,0.0f,-length,
        -length, 0.0f,length,
         length,0.0f,-length,
         length,0.0f,-length,
        length,0.0f,length,
        -length,0.0f,length,
    };
    static GLfloat vertex_color_data[]={
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
    };

    int cur=0;
    for(int i=0; i<18;++i){
        //appending basic ground
        vertex_buffer_data[cur] = basic_ground[i];
        ++cur;
    }
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, vertex_color_data, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ground::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ground::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}