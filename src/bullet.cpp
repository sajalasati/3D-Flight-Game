#include "bullets.h"
#include "main.h"

Bullet::Bullet(float x, float y, float z, float dr_x, float dr_y, float dr_z) {
    this->position = glm::vec3(x, y, z);
    this->dir_cos = glm::vec3(dr_x, dr_y, dr_z);
    this->rotation = 0.0f;
    this->distance = 0.0f;
    this->speed = 0.05;
    float base_width = 0.5f;
    static GLfloat vertex_buffer_data[]={
        -base_width/2,0.0f,-base_width/2, // triangle 1 : begin
        -base_width/2,0.0f, base_width/2,
        -base_width/2, base_width, base_width/2, // triangle 1 : end
        base_width/2, base_width,-base_width/2, // triangle 2 : begin
        -base_width/2,0.0f,-base_width/2,
        -base_width/2, base_width,-base_width/2, // triangle 2 : end
        base_width/2,0.0f, base_width/2,
        -base_width/2,0.0f,-base_width/2,
        base_width/2,0.0f,-base_width/2,
        base_width/2, base_width,-base_width/2,
        base_width/2,0.0f,-base_width/2,
        -base_width/2,0.0f,-base_width/2,
        -base_width/2,0.0f,-base_width/2,
        -base_width/2, base_width, base_width/2,
        -base_width/2, base_width,-base_width/2,
        base_width/2,0.0f, base_width/2,
        -base_width/2,0.0f, base_width/2,
        -base_width/2,0.0f,-base_width/2,
        -base_width/2, base_width, base_width/2,
        -base_width/2,0.0f, base_width/2,
        base_width/2,0.0f, base_width/2,
        base_width/2, base_width, base_width/2,
        base_width/2,0.0f,-base_width/2,
        base_width/2, base_width,-base_width/2,
        base_width/2,0.0f,-base_width/2,
        base_width/2, base_width, base_width/2,
        base_width/2,0.0f, base_width/2,
        base_width/2, base_width, base_width/2,
        base_width/2, base_width,-base_width/2,
        -base_width/2, base_width,-base_width/2,
        base_width/2, base_width, base_width/2,
        -base_width/2, base_width,-base_width/2,
        -base_width/2, base_width, base_width/2,
        base_width/2, base_width, base_width/2,
        -base_width/2, base_width, base_width/2,
        base_width/2,0.0f, base_width/2
    };
    static GLfloat vertex_color_data[108];
    for(int i=0;i<36;++i){
        if(i%3==0){
            vertex_color_data[3*i] = 0.0f;
            vertex_color_data[3*i+1] = 1.0f;
            vertex_color_data[3*i+2] = 0.0f;
        }
        else if(i%3==1){
            vertex_color_data[3*i] = 1.0f;
            vertex_color_data[3*i+1] = 0.0f;
            vertex_color_data[3*i+2] = 0.0f;
        }
        else{
            vertex_color_data[3*i] = 0.0f;
            vertex_color_data[3*i+1] = 0.0f;
            vertex_color_data[3*i+2] = 1.0f;
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, vertex_color_data, GL_FILL);
}

void Bullet::draw(glm::mat4 VP) {
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

void Bullet::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bullet::set_dir_cos(float dr_x, float dr_y, float dr_z) {
    float modulus = sqrt(dr_x*dr_x + dr_y*dr_y + dr_z*dr_z);
    dr_x /= modulus; dr_x /= modulus; dr_x /= modulus;
    this->position = glm::vec3(dr_x, dr_y, dr_z);
}

void Bullet::tick() {
    this->distance += this->speed;
    this->position.x += (this->speed * this->dir_cos[0]);
    this->position.y += (this->speed * this->dir_cos[1]);
    this->position.z += (this->speed * this->dir_cos[2]);
}

bool Bullet::check_collision(float x, float y, float z) {
    glm::vec3 a = this->position;
    float dist = sqrt(abs(x-a[0])*abs(x-a[0]) + abs(y-a[1])*abs(y-a[1]) + abs(z-a[2])*abs(z-a[2]));
    // std::cout<<dist<<"\n";
    return dist <= 1.0f;
}