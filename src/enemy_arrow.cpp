#include "enemy_arrow.h"
#include "main.h"

EnemyArrow::EnemyArrow(float x, float y, float z) {
    //base centre at 0,0,0
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->speed = 5.0f;
    float base_length = 0.8f, base_width = 0.8f;
    this->base_length = base_length;
    this->base_width = base_width;
    float extra = 3.0;
    this->extra = extra;
    this->lives = 5;
    this->head_base = 1.6f;
    this->head_height = 1.6f;
    static GLfloat vertex_buffer_data[]={
        -base_width/2,0.0f,-base_width/2, // triangle 1 : begin
        -base_width/2,0.0f, base_width/2,
        -base_width/2, base_width+extra, base_width/2, // triangle 1 : end
        base_width/2, base_width+extra,-base_width/2, // triangle 2 : begin
        -base_width/2,0.0f,-base_width/2,
        -base_width/2, base_width+extra,-base_width/2, // triangle 2 : end
        base_width/2,0.0f, base_width/2,
        -base_width/2,0.0f,-base_width/2,
        base_width/2,0.0f,-base_width/2,
        base_width/2, base_width+extra,-base_width/2,
        base_width/2,0.0f,-base_width/2,
        -base_width/2,0.0f,-base_width/2,
        -base_width/2,0.0f,-base_width/2,
        -base_width/2, base_width+extra, base_width/2,
        -base_width/2, base_width+extra,-base_width/2,
        base_width/2,0.0f, base_width/2,
        -base_width/2,0.0f, base_width/2,
        -base_width/2,0.0f,-base_width/2,
        -base_width/2, base_width+extra, base_width/2,
        -base_width/2,0.0f, base_width/2,
        base_width/2,0.0f, base_width/2,
        base_width/2, base_width+extra, base_width/2,
        base_width/2,0.0f,-base_width/2,
        base_width/2, base_width+extra,-base_width/2,
        base_width/2,0.0f,-base_width/2,
        base_width/2, base_width+extra, base_width/2,
        base_width/2,0.0f, base_width/2,
        base_width/2, base_width+extra, base_width/2,
        base_width/2, base_width+extra,-base_width/2,
        -base_width/2, base_width+extra,-base_width/2,
        base_width/2, base_width+extra, base_width/2,
        -base_width/2, base_width+extra,-base_width/2,
        -base_width/2, base_width+extra, base_width/2,
        base_width/2, base_width+extra, base_width/2,
        -base_width/2, base_width+extra, base_width/2,
        base_width/2,0.0f, base_width/2
    };
    static GLfloat vertex_color_data[108];
    for(int i=0;i<36;++i){
        if(i%3==0){
            vertex_color_data[3*i] = 0.0f;
            vertex_color_data[3*i+1] = 0.5f;
            vertex_color_data[3*i+2] = 0.1f;
        }
        else if(i%3==1){
            vertex_color_data[3*i] = 0.5f;
            vertex_color_data[3*i+1] = 0.1f;
            vertex_color_data[3*i+2] = 0.0f;
        }
        else{
            vertex_color_data[3*i] = 0.1f;
            vertex_color_data[3*i+1] = 0.0f;
            vertex_color_data[3*i+2] = 0.5f;
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_DARK_RED, GL_FILL);
    static GLfloat vertex_buffer_data2[]={
        -this->head_base/2,0.01f,0.0f,
        this->head_base/2,0.01f,0.0f,
        0.0f,-this->head_height+0.01f,0.0f,

        -this->head_base/2,0.01f,0.0f,
        this->head_base/2,0.01f,0.0f,
        0.0f,-this->head_height+0.01f,0.0f,

        -this->head_base/2,0.01f,-this->head_base/2,
        0.0f,-this->head_height+0.01f,0.0f,
        -this->head_base/2,0.01f,this->head_base/2,

        this->head_base/2,0.01f,-this->head_base/2,
        0.0f,-this->head_height+0.01f,0.0f,
        this->head_base/2,0.01f,this->head_base/2,
    };
    this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2, COLOR_DARK_RED, GL_FILL);
}

void EnemyArrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void EnemyArrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void EnemyArrow::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t EnemyArrow::bounding_box() {
    return {this->position.x, this->position.y, this->position.z, 2* this->base_width, this->base_width + 2*this->extra, 2 * this->base_width};
}