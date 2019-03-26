#include "healthbar.h"
#include "main.h"

Healthbar::Healthbar(float x, float y, float z,int health) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->speed = 0.0f;
    this->length = 2.5f;
    this->height = 0.3;
    this->bar_width = 0.05;
    this->set_objects(health);
}

void Healthbar::draw(glm::mat4 VP) {
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
    draw3DObject(this->object3);
}

void Healthbar::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Healthbar::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Healthbar::set_objects(int health) {
    float hel = health, max_hel = player_health;
    float l1 = this->length, h1 = this->height, w1 = this->bar_width;
    float l2 = (hel/max_hel)*(l1- 2*w1);
    GLfloat vertex_buffer_data[]={
        0.0f,0.0f,0.0f,
        0.0f,h1,0.0f,
        l1,0.0f,0.0f,
        l1,0.0f,0.0f,
        l1,h1,0.0f,
        0.0f,h1,0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    GLfloat rect1[]={
        0.0f,0.0f,0.0f,     0.0f,h1,0.0f,      w1,0.0f,0.0f,
        w1,0.0f,0.0f,       w1,h1,0.0f,        0.0f,h1,0.0f
    };
    GLfloat rect2[]={
        0.0f,0.0f,0.0f,     0.0f,w1,0.0f,       l1,0.0f,0.0f,
        l1,0.0f,0.0f,       l1,w1,0.0f,         0.0f,w1,0.0f
    };
    GLfloat vertex_buffer_data2[72];
    int cur=0;
    for(int i=0;i<18;i+=3){
        vertex_buffer_data2[cur++] = rect1[i];
        vertex_buffer_data2[cur++] = rect1[i+1];
        vertex_buffer_data2[cur++] = rect1[i+2];
    }
    for(int i=0;i<18;i+=3){
        vertex_buffer_data2[cur++] = rect1[i]+l1-w1;
        vertex_buffer_data2[cur++] = rect1[i+1];
        vertex_buffer_data2[cur++] = rect1[i+2];
    }
    for(int i=0;i<18;i+=3){
        vertex_buffer_data2[cur++] = rect2[i];
        vertex_buffer_data2[cur++] = rect2[i+1];
        vertex_buffer_data2[cur++] = rect2[i+2];
    }
    for(int i=0;i<18;i+=3){
        vertex_buffer_data2[cur++] = rect2[i];
        vertex_buffer_data2[cur++] = rect2[i+1]+h1-w1;
        vertex_buffer_data2[cur++] = rect2[i+2];
    }
    this->object2 = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data2, COLOR_BROWN, GL_FILL);
    GLfloat vertex_buffer_data3[]={
        w1,w1,0.0f,
        w1,h1-w1,0.0f,
        w1+l2,w1,0.0f,
        w1+l2,w1,0.0f,
        w1,h1-w1,0.0f,
        w1+l2,h1-w1,0.0f,
    };
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, COLOR_LIFERED, GL_FILL);
}