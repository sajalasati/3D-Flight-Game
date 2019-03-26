#include "parachute.h"
#include "main.h"

const int n_circles = 200;
static GLfloat vertex_buffer_data[18*n_circles];
static GLfloat g_color_buffer_data[18*n_circles];

void multiply_matrices_parachute(int i, float angle){
    float c = cos(angle), s = sin(angle);
    vertex_buffer_data[18*i] = c*vertex_buffer_data[18*(i-1)] - s*vertex_buffer_data[18*(i-1)+1];
    vertex_buffer_data[18*i+1] = s*vertex_buffer_data[18*(i-1)] + c*vertex_buffer_data[18*(i-1)+1];
    vertex_buffer_data[18*i+2] = vertex_buffer_data[18*(i-1)+2];
    vertex_buffer_data[18*i+3] = c*vertex_buffer_data[18*(i-1)+3] - s*vertex_buffer_data[18*(i-1)+4];
    vertex_buffer_data[18*i+4] = s*vertex_buffer_data[18*(i-1)+3] + c*vertex_buffer_data[18*(i-1)+4];
    vertex_buffer_data[18*i+5] = vertex_buffer_data[18*(i-1)+5];
    vertex_buffer_data[18*i+6] = c*vertex_buffer_data[18*(i-1)+6] - s*vertex_buffer_data[18*(i-1)+7];
    vertex_buffer_data[18*i+7] = s*vertex_buffer_data[18*(i-1)+6] + c*vertex_buffer_data[18*(i-1)+7];
    vertex_buffer_data[18*i+8] = vertex_buffer_data[18*(i-1)+8];
    vertex_buffer_data[18*i+9] = c*vertex_buffer_data[18*(i-1)+9] - s*vertex_buffer_data[18*(i-1)+10];
    vertex_buffer_data[18*i+10] = s*vertex_buffer_data[18*(i-1)+9] + c*vertex_buffer_data[18*(i-1)+10];
    vertex_buffer_data[18*i+11] = vertex_buffer_data[18*(i-1)+11];
    vertex_buffer_data[18*i+12] = c*vertex_buffer_data[18*(i-1)+12] - s*vertex_buffer_data[18*(i-1)+13];
    vertex_buffer_data[18*i+13] = s*vertex_buffer_data[18*(i-1)+12] + c*vertex_buffer_data[18*(i-1)+13];
    vertex_buffer_data[18*i+14] = vertex_buffer_data[18*(i-1)+14];
    vertex_buffer_data[18*i+15] = c*vertex_buffer_data[18*(i-1)+15] - s*vertex_buffer_data[18*(i-1)+16];
    vertex_buffer_data[18*i+16] = s*vertex_buffer_data[18*(i-1)+15] + c*vertex_buffer_data[18*(i-1)+16];
    vertex_buffer_data[18*i+17] = vertex_buffer_data[18*(i-1)+17];
}

Parachute::Parachute(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->speed = 0.5f;
    this->radius = 2.0f;
    this->width = 0.05f;
    this->depth = 1.0f;
    this->maxup = y + 3.0f;
    this->maxdown = y - 3.0f;
    this->direc = 1;
    this->box_size = 1.0f;
    float theta = M_PI / n_circles;
    float angle = 2*theta;
    // int cur=0;
    // float fact = (this->radius / this->radius) * (this->width / 2);
    static GLfloat sample_data[]={
        this->radius,this->width,0.0f,
        this->radius,0.0f,0.0f,
        this->radius,0.0f,-this->depth,
        this->radius,0.0f,-this->depth,
        this->radius,this->width,0.0f,
        this->radius,this->width,-this->depth
    };
    for(int i=0;i<18;++i) vertex_buffer_data[i] = sample_data[i];

    for(int i=1; i<n_circles;++i){
        multiply_matrices_parachute(i,theta);
    }
    for(int i=0; i<18*n_circles;i++){
        g_color_buffer_data[i]=0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, 6*n_circles, vertex_buffer_data, g_color_buffer_data, GL_FILL);

    static GLfloat vertex_buffer_data2[]={
        -this->radius,0.0f,-this->depth / 2.0f,
        0.0f,-(this->radius) * 1.5f,-this->depth / 2.0f,
        -this->radius,0.0f,-this->depth/10-this->depth / 2.0f,
        0.0f,-(this->radius) * 1.5f,-this->depth / 2.0f,
        -this->radius,0.0f,-this->depth/10-this->depth / 2.0f,
        0.0f,-(this->radius) * 1.5f,-this->depth/10-this->depth / 2.0f,

        this->radius,0.0f,-this->depth / 2.0f,
        0.0f,-(this->radius) * 1.5f,-this->depth / 2.0f,
        this->radius,0.0f,-this->depth/10-this->depth / 2.0f,
        0.0f,-(this->radius) * 1.5f,-this->depth / 2.0f,
        this->radius,0.0f,-this->depth/10-this->depth / 2.0f,
        0.0f,-(this->radius) * 1.5f,-this->depth/10-this->depth / 2.0f,

    };
    this->object2 = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    float base_width = this->box_size;
    float come_down = -(this->radius) * 1.5f;
    float come_front = -base_width/2;
    static GLfloat vertex_buffer_data3[]={
        -base_width/2,come_down,-base_width/2+come_front, // triangle 1 : begin
        -base_width/2,come_down, base_width/2+come_front,
        -base_width/2, base_width+come_down, base_width/2+come_front, // triangle 1 : end
        base_width/2, base_width+come_down,-base_width/2+come_front, // triangle 2 : begin
        -base_width/2,come_down,-base_width/2+come_front,
        -base_width/2, base_width+come_down,-base_width/2+come_front, // triangle 2 : end
        base_width/2,come_down, base_width/2+come_front,
        -base_width/2,come_down,-base_width/2+come_front,
        base_width/2,come_down,-base_width/2+come_front,
        base_width/2, base_width+come_down,-base_width/2+come_front,
        base_width/2,come_down,-base_width/2+come_front,
        -base_width/2,come_down,-base_width/2+come_front,
        -base_width/2,come_down,-base_width/2+come_front,
        -base_width/2, base_width+come_down, base_width/2+come_front,
        -base_width/2, base_width+come_down,-base_width/2+come_front,
        base_width/2,come_down, base_width/2+come_front,
        -base_width/2,come_down, base_width/2+come_front,
        -base_width/2,come_down,-base_width/2+come_front,
        -base_width/2, base_width+come_down, base_width/2+come_front,
        -base_width/2,come_down, base_width/2+come_front,
        base_width/2,come_down, base_width/2+come_front,
        base_width/2, base_width+come_down, base_width/2+come_front,
        base_width/2,come_down,-base_width/2+come_front,
        base_width/2, base_width+come_down,-base_width/2+come_front,
        base_width/2,come_down,-base_width/2+come_front,
        base_width/2, base_width+come_down, base_width/2+come_front,
        base_width/2,come_down, base_width/2+come_front,
        base_width/2, base_width+come_down, base_width/2+come_front,
        base_width/2, base_width+come_down,-base_width/2+come_front,
        -base_width/2, base_width+come_down,-base_width/2+come_front,
        base_width/2, base_width+come_down, base_width/2+come_front,
        -base_width/2, base_width+come_down,-base_width/2+come_front,
        -base_width/2, base_width+come_down, base_width/2+come_front,
        base_width/2, base_width+come_down, base_width/2+come_front,
        -base_width/2, base_width+come_down, base_width/2+come_front,
        base_width/2,come_down, base_width/2+come_front
    };
    this->object3 = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data3, COLOR_BLACK, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube around which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick() {
    this->rotation += this->speed;
    if(this->direc == 1){
        //go up
        this->position[1] += 0.03;
        if(this->position[1] >= this->maxup){
            this->direc = 0;
            this->position[1] = this->maxup;
        }
    }
    else{
        //go down
        this->position[1] -= 0.03;
        if(this->position[1] <= this->maxdown){
            this->direc = 1;
            this->position[1] = this->maxdown;
        }
    }
}

bounding_box_t Parachute::bounding_box() {
    return {this->position.x, this->position.y, this->position.z, 2.5f * (this->radius) , 3.0f * (this->radius), 2 * (this->depth)};
}