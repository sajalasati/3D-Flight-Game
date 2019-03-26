#include "plane.h"
#include "main.h"

static const int n = 200;
static const int n_circ = 100;
static GLfloat vertex_buffer_data[18*n+36+9*n_circ+18];
static GLfloat vertex_buffer_data2[9*n_circ];
static GLfloat g_color_buffer_data[18*n+36+9*n_circ+18];
static GLfloat g_color_buffer_data2[9*n_circ];

void multiply_matrices(int i, float angle){
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

Plane::Plane(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->speed = 0.0f;
    this->accn = 0.001;
    this->bwdspeed = 0.5;
    this->health = player_health;
    this->score = 0;
    this->fuel = max_fuel_capacity;
    this->rotation_roll =0.0f;
    this->rotation_yaw =0.0f;
    this->rotation_pitch =0.0f;
    this->radius1 = 0.4f;
    this->radius2 = 0.4f;
    this->width = 0.05f;
    this->length = 3.0f;
    this->nose = 2.0f;
    this->max_pitch = 18.5f;
    this->min_pitch = -6.0f;
    this->up_down_speed = 0.05;
    this->roll_speed = 1.0;
    this->yaw_speed = 1.0;
    float new_z = -(this->nose + this->length)/2;
    this->slope = 0.314; //some angle for frustum
    float angle = 2*M_PI/n;
    //farthest distance from plane's centre = new_z + this->length + 2.0f

    //main body
    float fact = (this->radius2 / this->radius1) * (this->width / 2);
    vertex_buffer_data[0]=-(this->width)/2;
    vertex_buffer_data[1]=this->radius1;
    vertex_buffer_data[2]=-new_z;
    vertex_buffer_data[3]=(this->width)/2;
    vertex_buffer_data[4]=this->radius1;
    vertex_buffer_data[5]=-new_z;
    vertex_buffer_data[6]=fact;
    vertex_buffer_data[7]=this->radius2;
    vertex_buffer_data[8]=-new_z-this->length;
    vertex_buffer_data[9]=-(this->width)/2;
    vertex_buffer_data[10]=this->radius1;
    vertex_buffer_data[11]=-new_z;
    vertex_buffer_data[12]=-fact;
    vertex_buffer_data[13]=this->radius2;
    vertex_buffer_data[14]=-new_z-this->length;
    vertex_buffer_data[15]=fact;
    vertex_buffer_data[16]=this->radius2;
    vertex_buffer_data[17]=-new_z-this->length;
    for(int i=1; i<n;++i){
        multiply_matrices(i,angle);
    }
    for(int i=0; i<n;i++){
        if(i%4 < 2){
            for(int j=0;j<18;++j){
                g_color_buffer_data[j+18*i] = 0.62f;
            }
        }
        else{
            for(int j=0;j<18;++j){
                g_color_buffer_data[j+18*i] = 0.42f;
            }
        }
    }

    //side fins - 1st pair
    int cur = 18*n; //start from cur
    int s1=cur,e1;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-1.1f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-2.5f; ++cur;
    vertex_buffer_data[cur]=3.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.5f; ++cur;
    vertex_buffer_data[cur]=0.0f;  ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-1.1f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-2.5f; ++cur;
    vertex_buffer_data[cur]=-3.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.5f; ++cur;
    e1 = cur;
    for(int i=s1;i<e1;i+=3){
        g_color_buffer_data[i] = 0.407f;
        g_color_buffer_data[i+1] = 0.164f;
        g_color_buffer_data[i+2] = 0.043f;
    } 

    // create flat ends of fins
    int s3 = cur, e3;
    vertex_buffer_data[cur]=0.0f;  ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-2.5f; ++cur;
    vertex_buffer_data[cur]=-3.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.8f; ++cur;
    vertex_buffer_data[cur]=-3.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.5f; ++cur;
    vertex_buffer_data[cur]=0.0f;  ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-2.5f; ++cur;
    vertex_buffer_data[cur]=3.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.8f; ++cur;
    vertex_buffer_data[cur]=3.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.5f; ++cur;
    e3 = cur;
    for(int i=s3;i<e3;i+=3){
        g_color_buffer_data[i] = 0.172f;
        g_color_buffer_data[i] = 0.466f;
        g_color_buffer_data[i] = 0.7568f;
    }



    // second set of wings - with flat ends
    int s4=cur,e4;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.3f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.7f; ++cur;
    vertex_buffer_data[cur]=1.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.1f; ++cur;
    vertex_buffer_data[cur]=0.0f;  ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.3f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.7f; ++cur;
    vertex_buffer_data[cur]=-1.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.1f; ++cur;
    e4 = cur;
    for(int i=s4;i<e4;i+=3){
        g_color_buffer_data[i] = 0.407f;
        g_color_buffer_data[i+1] = 0.164f;
        g_color_buffer_data[i+2] = 0.043f;
    }

    int s5 = cur, e5;
    vertex_buffer_data[cur]=0.0f;  ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.7f; ++cur;
    vertex_buffer_data[cur]=-1.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.2f; ++cur;
    vertex_buffer_data[cur]=-1.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.1f; ++cur;
    vertex_buffer_data[cur]=0.0f;  ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.7f; ++cur;
    vertex_buffer_data[cur]=1.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.2f; ++cur;
    vertex_buffer_data[cur]=1.0f; ++cur;
    vertex_buffer_data[cur]=0.0f; ++cur;
    vertex_buffer_data[cur]=-new_z-0.1f; ++cur;
    e5 = cur;
    for(int i=s5;i<e5;i+=3){
        g_color_buffer_data[i] = 0.172f;
        g_color_buffer_data[i] = 0.466f;
        g_color_buffer_data[i] = 0.7568f;
    }


    // circle at the back
    int cur1=0;
    double theta = M_PI / n_circ, ang = (2 * M_PI) / n_circ;
    for (int i = 0; i < n_circ; i++)
    {
        float x_cord = cos(theta) * this->radius1;
        float y_cord = sin(theta) * this->radius1;
        vertex_buffer_data2[cur1] = 0.0f; ++cur1;
        vertex_buffer_data2[cur1] = 0.0f; ++cur1;
        vertex_buffer_data2[cur1] = -new_z; ++cur1;
        vertex_buffer_data2[cur1] = x_cord; ++cur1;
        vertex_buffer_data2[cur1] = y_cord; ++cur1;
        vertex_buffer_data2[cur1] = -new_z; ++cur1;
        theta += ang;
        x_cord = cos(theta) * this->radius1;
        y_cord = sin(theta) * this->radius1;
        vertex_buffer_data2[cur1] = x_cord; ++cur1;
        vertex_buffer_data2[cur1] = y_cord; ++cur1;
        vertex_buffer_data2[cur1] = -new_z; ++cur1;
    }
    for(int i=0;i<9*n_circ;i+=3){
        if(i%12==0){
            g_color_buffer_data2[i] = 1.0f;
            g_color_buffer_data2[i+1] = 0.0f;
            g_color_buffer_data2[i+2] = 0.0f;
        }
        else{
            g_color_buffer_data2[i] = 1.0f;
            g_color_buffer_data2[i+1] = 0.5f;
            g_color_buffer_data2[i+2] = 0.0f;
        }
    }

    // nose
    theta = M_PI / n_circ;
    int s2=cur,e2;
    for (int i = 0; i < n_circ; i++)
    {
        float x_cord = cos(theta) * this->radius2;
        float y_cord = sin(theta) * this->radius2;
        vertex_buffer_data[cur] = 0.0f; ++cur;
        vertex_buffer_data[cur] = 0.0f; ++cur;
        vertex_buffer_data[cur] = -new_z-this->length-2.0f; ++cur;
        vertex_buffer_data[cur] = x_cord; ++cur;
        vertex_buffer_data[cur] = y_cord; ++cur;
        vertex_buffer_data[cur] = -new_z-this->length; ++cur;
        theta += ang;
        x_cord = cos(theta) * this->radius2;
        y_cord = sin(theta) * this->radius2;
        vertex_buffer_data[cur] = x_cord; ++cur;
        vertex_buffer_data[cur] = y_cord; ++cur;
        vertex_buffer_data[cur] = -new_z-this->length; ++cur;
    }
    e2 = cur;
    for(int i=s2;i<e2;i+=3)
    {
        g_color_buffer_data[i] = 0.498f;
        g_color_buffer_data[i+1] = 0.298f;
        g_color_buffer_data[i+2] = 0.356f;
    }


    this->object = create3DObject(GL_TRIANGLES, 6*n+12+6+6*n_circ, vertex_buffer_data, g_color_buffer_data, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n_circ, vertex_buffer_data2, g_color_buffer_data2, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_roll = glm::rotate((float) (this->rotation_roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate_yaw = glm::rotate((float) (this->rotation_yaw * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_pitch = glm::rotate((float) (this->rotation_pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube around which we waant to rotate
    
    //first rotate wrt local origin then translate to actual world coordinate
    Matrices.model *= translate;
    Matrices.model *= rotate_yaw;
    Matrices.model *= rotate_pitch;
    Matrices.model *= rotate_roll;
    
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Plane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::tick(){
    float d = this->speed;
    if(d < 0){
        this->position.z -= d*cos(this->rotation_yaw*M_PI/180.0);
        this->position.x -= d*sin(this->rotation_yaw*M_PI/180.0);
    }
    else{
        this->position.z -= d*cos(this->rotation_yaw*M_PI/180.0);
        this->position.x -= d*sin(this->rotation_yaw*M_PI/180.0);
    }
}

void Plane::move_forward(){
    if(this->speed < 0) this->speed = 0.05f;
    this->speed += this->accn;
    if(this->speed >= max_speed) this->speed = max_speed;
}

void Plane::move_backward(){
    this->speed = -0.05f;
    // this->speed -= this->accn;
    // if(this->speed <= -max_speed) this->speed = -max_speed;
}

void Plane::move_up(){
    this->position.y += this->up_down_speed;
    if(this->position.y >= upper_height_limit){
        this->position.y = upper_height_limit;
    }
}

void Plane::move_down(){
    this->position.y -= this->up_down_speed;
}

void Plane::apply_gravity(){
    this->position.y -= ((this->up_down_speed)/4.0f);
}

void Plane::roll(float x){
    this->rotation_roll += (x * this->roll_speed);
}

void Plane::yaw(float x){
    this->rotation_yaw += (x * this->yaw_speed);
}

void Plane::gotfuel(float f){
    this->fuel += f;
    if(this->fuel > max_fuel_capacity)
        this->fuel = max_fuel_capacity;
}

bounding_box_t Plane::bounding_box2(){
    float d = 0.2f;
    return {this->position.x, this->position.y, this->position.z, 5*d , 5*d, d};
}
