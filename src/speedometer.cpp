#include "speedometer.h"
#include "main.h"

Speedometer::Speedometer(float x, float y, float z, int type) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->radius = 1.0f;
    this->width = 0.1f;
    this->length = 0.1f;
    int n = 200;
    GLfloat vertex_buffer_data[18*n];
    GLfloat g_color_buffer_data[18*n];
    float angle = M_PI/n;
    float c = cos(angle), s = sin(angle);
    vertex_buffer_data[0]=this->radius+this->width;
    vertex_buffer_data[1]=0.0f;
    vertex_buffer_data[2]=0.0f;
    vertex_buffer_data[3]=this->radius+this->width;
    vertex_buffer_data[4]=this->length;
    vertex_buffer_data[5]=0.0f;
    vertex_buffer_data[6]=this->radius;
    vertex_buffer_data[7]=this->length;
    vertex_buffer_data[8]=0.0f;
    vertex_buffer_data[9]=this->radius+this->width;
    vertex_buffer_data[10]=0.0f;
    vertex_buffer_data[11]=0.0f;
    vertex_buffer_data[12]=this->radius;
    vertex_buffer_data[13]=0.0f;
    vertex_buffer_data[14]=0.0f;
    vertex_buffer_data[15]=this->radius;
    vertex_buffer_data[16]=this->length;
    vertex_buffer_data[17]=0.0f;

    float ang = 0.0f;

    for(int i=1; i<=n-1; ++i){
        float c = cos(angle), s = sin(angle);
        vertex_buffer_data[18*i] = c*vertex_buffer_data[18*(i-1)] - s*vertex_buffer_data[18*(i-1)+1];
        vertex_buffer_data[18*i+1] = s*vertex_buffer_data[18*(i-1)] + c*vertex_buffer_data[18*(i-1)+1];
        vertex_buffer_data[18*i+2] = 0.0f;
        vertex_buffer_data[18*i+3] = c*vertex_buffer_data[18*(i-1)+3] - s*vertex_buffer_data[18*(i-1)+4];
        vertex_buffer_data[18*i+4] = s*vertex_buffer_data[18*(i-1)+3] + c*vertex_buffer_data[18*(i-1)+4];
        vertex_buffer_data[18*i+5] = 0.0f;
        vertex_buffer_data[18*i+6] = c*vertex_buffer_data[18*(i-1)+6] - s*vertex_buffer_data[18*(i-1)+7];
        vertex_buffer_data[18*i+7] = s*vertex_buffer_data[18*(i-1)+6] + c*vertex_buffer_data[18*(i-1)+7];
        vertex_buffer_data[18*i+8] = 0.0f;
        vertex_buffer_data[18*i+9] = c*vertex_buffer_data[18*(i-1)+9] - s*vertex_buffer_data[18*(i-1)+10];
        vertex_buffer_data[18*i+10] = s*vertex_buffer_data[18*(i-1)+9] + c*vertex_buffer_data[18*(i-1)+10];
        vertex_buffer_data[18*i+11] = 0.0f;
        vertex_buffer_data[18*i+12] = c*vertex_buffer_data[18*(i-1)+12] - s*vertex_buffer_data[18*(i-1)+13];
        vertex_buffer_data[18*i+13] = s*vertex_buffer_data[18*(i-1)+12] + c*vertex_buffer_data[18*(i-1)+13];
        vertex_buffer_data[18*i+14] = 0.0f;
        vertex_buffer_data[18*i+15] = c*vertex_buffer_data[18*(i-1)+15] - s*vertex_buffer_data[18*(i-1)+16];
        vertex_buffer_data[18*i+16] = s*vertex_buffer_data[18*(i-1)+15] + c*vertex_buffer_data[18*(i-1)+16];
        vertex_buffer_data[18*i+17] = 0.0f;
    }
    if(type==1){
        for(int i=0;i<6*n;++i){
            if(i<= 6*n*0.40f){
                g_color_buffer_data[3*i]=0.094f;
                g_color_buffer_data[3*i+1]=0.486f;
                g_color_buffer_data[3*i+2]=0.0f;
            }
            else if(i<= 6*n*0.80){
                g_color_buffer_data[3*i]=0.909f;
                g_color_buffer_data[3*i+1]=0.705f;
                g_color_buffer_data[3*i+2]=0.098f;
            }
            else{
                g_color_buffer_data[3*i]=0.909f;
                g_color_buffer_data[3*i+1]=0.098f;
                g_color_buffer_data[3*i+2]=0.098f;
            }
        }
    }
    else{
        for(int i=0;i<6*n;++i){
            if(i<= 6*n*0.40f){
                g_color_buffer_data[3*i]=0.909f;
                g_color_buffer_data[3*i+1]=0.098f;
                g_color_buffer_data[3*i+2]=0.098f;
            }
            else if(i<= 6*n*0.80){
                g_color_buffer_data[3*i]=0.909f;
                g_color_buffer_data[3*i+1]=0.705f;
                g_color_buffer_data[3*i+2]=0.098f;
            }
            else{
                g_color_buffer_data[3*i]=0.094f;
                g_color_buffer_data[3*i+1]=0.486f;
                g_color_buffer_data[3*i+2]=0.0f;
                g_color_buffer_data[3*i]=0.909f;
                g_color_buffer_data[3*i+1]=0.098f;
                g_color_buffer_data[3*i+2]=0.098f;
            }
        }
    }
    
    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data, g_color_buffer_data, GL_FILL);
}

void Speedometer::draw(glm::mat4 VP) {
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

void Speedometer::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Speedometer::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}