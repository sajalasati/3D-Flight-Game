#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z) {
    // base centre circle is 0,0,0
    //vertically dropped on enemy
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->speed = 0.1f;
    this->height = 0.4f;
    this->radius = 0.4f;
    const int n_circles = 100;
    static GLfloat vertex_buffer_data[9*n_circles];
    static GLfloat g_color_buffer_data[9*n_circles];
    float theta = M_PI / n_circles;
    float ang = 2*theta;
    int cur=0;
    for (int i = 0; i < n_circles; i++)
    {
        float x_cord = cos(theta) * this->radius;
        float z_cord = sin(theta) * this->radius;
        vertex_buffer_data[cur] = 0.0f; ++cur;
        vertex_buffer_data[cur] = this->height; ++cur;
        vertex_buffer_data[cur] = 0.0f; ++cur;
        vertex_buffer_data[cur] = x_cord; ++cur;
        vertex_buffer_data[cur] = 0.0f; ++cur;
        vertex_buffer_data[cur] = z_cord; ++cur;
        theta += ang;
        x_cord = cos(theta) * this->radius;
        z_cord = sin(theta) * this->radius;
        vertex_buffer_data[cur] = x_cord; ++cur;
        vertex_buffer_data[cur] = 0.0f; ++cur;
        vertex_buffer_data[cur] = z_cord; ++cur;
    }
    for(int i=0;i<9*n_circles;i+=3)
    {
        g_color_buffer_data[i] = 0.286f;
        g_color_buffer_data[i+1] = 0.356f;
        g_color_buffer_data[i+2] = 0.0431f;
    }
    this->object = create3DObject(GL_TRIANGLES, 3*n_circles, vertex_buffer_data, g_color_buffer_data, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_LIFERED, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
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

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick() {
    // nothing
    this->position.y -= this->speed;
}

bounding_box_t Bomb::bounding_box() {
    return {this->position.x, this->position.y, this->position.z, this->radius, this->height ,this->radius};
}