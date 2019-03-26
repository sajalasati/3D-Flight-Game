#include "mountain.h"
#include "main.h"

Mountain::Mountain(float x, float y, float z, color_t color) {
    //base centre at 0,0,0
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    const int no_of_vertices = 12;
    static GLfloat vertex_buffer_data[no_of_vertices*3];
    float base = 5, height = 5;
    this->base = base;
    this->height = height;
    float mountain_array[] = {
        -base/2,0.0f,-base/2,
        -base/2,0.0f,base/2,
        0.0f,height,0.0f,

        -base/2,0.0f,-base/2,
        base/2,0.0f,-base/2,
        0.0f,height,0.0f,

        base/2,0.0f,-base/2,
        base/2,0.0f,base/2,
        0.0f,height,0.0f,

        -base/2,0.0f,base/2,
        base/2,0.0f,base/2,
        0.0f,height,0.0f,

    };
    static GLfloat g_color_buffer_data[]={
        0.925f,0.39f,0.294f,
        0.925f,0.39f,0.294f,
        0.2195f,0.1098f,0.02155f,

        0.909f,0.5215f,0.133f,
        0.909f,0.5215f,0.133f,
        0.2195f,0.1098f,0.02155f,

        0.925f,0.39f,0.294f,
        0.925f,0.39f,0.294f,
        0.2195f,0.1098f,0.02155f,

        0.909f,0.5215f,0.133f,
        0.909f,0.5215f,0.133f,
        0.2195f,0.1098f,0.02155f,
    };
    int cur=0;
    for(int i=0; i<36;++i){
        //appending basic mountain
        vertex_buffer_data[cur] = mountain_array[i];
        ++cur;
    }
    this->object = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, g_color_buffer_data, GL_FILL);
}

void Mountain::draw(glm::mat4 VP) {
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

void Mountain::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Mountain::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}