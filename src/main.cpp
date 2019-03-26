#include<unistd.h>
#include "main.h"
#include "timer.h"
#include "plane.h"
#include "ground.h"
#include "mountain.h"
#include "speedometer.h"
#include "needle.h"
#include "healthbar.h"
#include "speedbar.h"
#include "display.h"
#include "aim.h"
#include "missile.h"
#include "enemy.h"
#include "bullets.h"
#include "arrow.h"
#include "bomb.h"
#include "fuel_point.h"
#include "parachute.h"
#include "rings.h"
#include "compass.h"
#include "compass_needle.h"
#include "enemy_arrow.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Plane plane1;
Aim aim;
Ground ground;
EnemyArrow enemy_arrow;
list < Mountain > mountains;
list < Missile > missiles;
list < Enemy > enemies;
list < Bullet > bullets;
list < Fuel > fuelpoints;
list < Bomb > bombs;
list < Parachute > parachutes;
list < Ring > rings;

//dashboard
Speedometer fuelmeter, altimeter;
Needle needle1, needle2;
CompassNeedle needle3;
Healthbar healthbar;
Speedbar speedbar;
Display display, display2;
Arrow arrow;
Compass compass;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float eye_x=0, eye_y=0, eye_z=0;
float target_x=0, target_y=0, target_z=0, follow_cam_height=4;
int cam_pos=1;
int player_health=10000;
float max_fuel_capacity = 10000, max_speed = 0.5f;
float upper_height_limit = 50.0f;
// pos = 1 for plane view
// pos = 2 for top view
// pos = 3 for tower view
// pos = 4 for follow cam view
// pos = 5 for helicopter cam view
float g_roll, g_yaw, cam_zoom;
float prev_x, prev_y;
bool apply_gravity_var = true;
float shoot_angle = 10.0f, shoot_limit = 5.0f;
float _x, _y;
int loopin_loop=0;

Timer t60(1.0 / 60);
Timer t2(0.2);
Timer t3(1.0);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    if(cam_pos==5){
        cam_zoom += yoffset*0.1;
        // if(yoffset >0) exit(0);
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    /*first way*/

    // float delta_x = xpos-prev_x, delta_y = ypos-prev_y;
    // float del_x = min(1.0f,abs(delta_x));
    // if(delta_x<0) del_x *= -1;
    // if(delta_y<0) del_y *= -1;
    // // cout<<del_x<<" "<<del_y<<endl;
    // prev_x = xpos; prev_y = ypos;
    // float del_y = min(1.0f,abs(delta_y));
    // g_yaw += del_x;
    // g_roll += del_y;
    
    /*second way*/

    // g_roll = (xpos-300)/10;
    // g_yaw = plane1.rotation_yaw + (ypos-300)/10;
}



void set_camera_eye_target(){
    if(cam_pos==4){
        eye_z = plane1.position.z + 7*cos(plane1.rotation_yaw*M_PI/180.0);
        eye_x = plane1.position.x + 7*sin(plane1.rotation_yaw*M_PI/180.0);
        target_y = plane1.position.y;
        target_x = plane1.position.x;
        target_z = plane1.position.z;
        eye_y = target_y+follow_cam_height;
    }
    else if(cam_pos==1){
        //plane view
        eye_y = plane1.position.y;
        target_y = plane1.position.y;
        float d = 0.5*plane1.nose + 1.5*plane1.length + 2.0f;
        eye_z = plane1.position.z - d*cos(plane1.rotation_yaw*M_PI/180.0);
        eye_x = plane1.position.x - d*sin(plane1.rotation_yaw*M_PI/180.0);
        d += 1.0f;
        target_z = plane1.position.z - d*cos(plane1.rotation_yaw*M_PI/180.0);
        target_x = plane1.position.x - d*sin(plane1.rotation_yaw*M_PI/180.0);
    }
    else if(cam_pos==2){
        //top view
        // eye_z = 4; eye_y = 150; eye_x = 0;
        // target_z = 2; target_x = 0; target_y = 10;
        eye_z = -40; eye_y = 200; eye_x=25;
        target_z = -42; target_y = 10; target_x=25;
    }
    else if(cam_pos==3){
        //tower view
        eye_x = 20;
        eye_y = 20;
        eye_z = 0;
        target_y = plane1.position.y;
        target_x = plane1.position.x;
        target_z = plane1.position.z;
    }
    else{
        target_x = plane1.position.x;
        target_y = plane1.position.y;
        target_z = plane1.position.z;
        eye_x = target_x + cam_zoom*sin(g_yaw*M_PI/180.0);
        eye_z = target_z + cam_zoom*cos(g_yaw*M_PI/180.0)*cos(g_roll*M_PI/180.0);
        eye_y = target_y + 4 - cam_zoom*cos(g_yaw*M_PI/180.0)*sin(g_roll*M_PI/180.0);
    }
}

void update_aim_position(){
    //new position of aim will be calculated and set acc
    float dd = aim.distance;
    float xx = plane1.position.x - dd*cos(shoot_angle*M_PI/180.0)*sin(plane1.rotation_yaw*M_PI/180.0);
    float yy = plane1.position.y - dd*sin(shoot_angle*M_PI/180.0);
    float zz = plane1.position.z - dd*cos(shoot_angle*M_PI/180.0)*cos(plane1.rotation_yaw*M_PI/180.0);
    aim.set_position(xx,yy,zz,plane1.rotation_yaw);
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    //first set camera eye and target
    set_camera_eye_target();//acc to the view selected

    // then do this
    update_aim_position();
    for(auto it=missiles.begin();it!=missiles.end();++it){
        float dd = (*it).d;
        float anng1 = ((*it).ang1)*M_PI/180.0, anng2 = ((*it).ang2)*M_PI/180.0;
        float xxx = (*it).x0 - dd*cos(anng1)*sin(anng2);
        float yyy = (*it).y0 - dd*sin(anng1);
        float zzz = (*it).z0 - dd*cos(anng1)*cos(anng2);
        (*it).set_position(xxx,yyy,zzz);
    }

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( eye_x, eye_y, eye_z); // for higher level
    glm::vec3 eye2 ( 0, 0,1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    glm::vec3 target (target_x, target_y,target_z);
    glm::vec3 target2 (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    glm::vec3 up2 (0, 1, 0);
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Matrices.view2 = glm::lookAt( eye2, target2, up2 ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP2 = Matrices.projection2 * Matrices.view2;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ground.draw(VP);
    plane1.draw(VP);
    // enemy_arrow.draw(VP);
    for(auto it=missiles.begin();it!=missiles.end();++it){
        (*it).draw(VP); 
    }
    for(auto it=enemies.begin();it!=enemies.end();++it){
        (*it).draw(VP); 
    }
    for(auto it=bullets.begin();it!=bullets.end();++it){
        (*it).draw(VP); 
    }
    for(auto it=fuelpoints.begin();it!=fuelpoints.end();++it){
        (*it).draw(VP); 
    }
    for(auto it=bombs.begin();it!=bombs.end();++it){
        (*it).draw(VP); 
    }
    for(auto it=parachutes.begin();it!=parachutes.end();++it){
        (*it).draw(VP); 
    }
    for(auto it=rings.begin();it!=rings.end();++it){
        (*it).draw(VP); 
    }
    for(auto it=mountains.begin();it!=mountains.end();++it){
        (*it).draw(VP); 
    }

    // dashboard
    fuelmeter.draw(VP2);
    needle1.rotation =180.0f - ((plane1.fuel)/(max_fuel_capacity))*180.0f;
    // needle1.rotation = 180.0f;
    needle1.draw(VP2);
    needle2.rotation = 180.0f-((plane1.position.y)/(upper_height_limit))*180.0f;
    // if(needle2.rotation<=0) needle2.rotation = 0.0f;
    needle2.draw(VP2);

    healthbar.set_objects(plane1.health);
    healthbar.draw(VP2);

    speedbar.set_objects(abs(plane1.speed));
    speedbar.draw(VP2);

    // speedbar
    compass.draw(VP2);

    needle3.rotation = -plane1.rotation_yaw;
    needle3.draw(VP2);

    display.set_objects(plane1.score);
    display.draw(VP2);
    altimeter.draw(VP2);
    display2.set_objects((int)plane1.position.y);
    display2.draw(VP2);
    if(enemies.size()) {
        // x,z compenents only
        auto it = enemies.begin();
        double x1 = (*it).position.x, z1 = (*it).position.z, y1 = (*it).position.y;
        double x2 = plane1.position.x, z2 = plane1.position.z;
        double vec[]={eye_x-x1,eye_z-z1};//plane vec
        double vec2[]={eye_x-x2,eye_z-z2}; //towards enemy vec
        double mag1 = sqrt(vec[0]*vec[0]+ vec[1]*vec[1]);
        double mag2 = sqrt(vec2[0]*vec2[0]+ vec2[1]*vec2[1]);
        double cos_arrow_angle = (vec[0]*vec2[1] - vec[1]*vec2[0])/mag2;
        cos_arrow_angle /= mag1;
        double arrow_angle = asin(cos_arrow_angle);
        // cout<<arrow_angle*180.0/M_PI<<endl;
        arrow.change_rotation(arrow_angle*180.0/M_PI);
        arrow.draw(VP2);

        enemy_arrow.set_position(x1,3.5f + enemy_arrow.head_height, z1);
        enemy_arrow.draw(VP);
    }
    //draw at the last
    if(cam_pos==4){
        // draw aim circle
        aim.draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    apply_gravity_var = true;
    int tilt_left  = glfwGetKey(window, GLFW_KEY_A);
    int tilt_right = glfwGetKey(window, GLFW_KEY_D);
    int ccw = glfwGetKey(window, GLFW_KEY_Q);
    int cw = glfwGetKey(window, GLFW_KEY_E);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int fwd = glfwGetKey(window, GLFW_KEY_W);
    int bwd = glfwGetKey(window, GLFW_KEY_X);
    int loopin = glfwGetKey(window, GLFW_KEY_L);
    if(cam_pos==3 && loopin){
        loopin = 1;
        return;
    }
    if (tilt_left) {
        plane1.roll(1);
    }
    if(tilt_right){
        plane1.roll(-1);
    }
    if(cw){
        plane1.yaw(-1);
        aim.rotation -= 0.5;
    }
    if(ccw){
        plane1.yaw(1);
        aim.rotation += 0.5;
    }
    if(up){
        plane1.move_up();
        apply_gravity_var = false;
    }
    if(down){
        plane1.move_down();
    }
    if(fwd){
        plane1.move_forward();
    }
    if(bwd){
        plane1.move_backward();  
    }
    int camview_1 = glfwGetKey(window, GLFW_KEY_1);
    int camview_2 = glfwGetKey(window, GLFW_KEY_2);
    int camview_3 = glfwGetKey(window, GLFW_KEY_3);
    int camview_4 = glfwGetKey(window, GLFW_KEY_4);
    int camview_5 = glfwGetKey(window, GLFW_KEY_5);
    if (camview_1) {
        cam_pos = 1;
    }
    if (camview_2) {
        cam_pos = 2;
    }
    if (camview_3) {
        cam_pos = 3;
    }
    if (camview_4) {
        cam_pos = 4;
    }
    if (camview_5) {
        // cout<<"fuck"<<endl;
        cam_pos = 5;
        g_roll = 0.0f;
        g_yaw = plane1.rotation_yaw;
        cam_zoom = 7.0f;
        prev_x = 0.0f;
        prev_y = 0.0f;
        //remain fixed never changed
        target_y = plane1.position.y;
        target_x = plane1.position.x;
        target_z = plane1.position.z;
        //initialised eye components       
        eye_y = target_y+4;
        eye_z = plane1.position.z + cam_zoom*cos(g_yaw*M_PI/180.0);
        eye_x = plane1.position.x + cam_zoom*sin(g_yaw*M_PI/180.0);
    }
    if(cam_pos==5){
        // adjust the yaw and roll for the camera to see
        double _x, _y;
        glfwGetCursorPos(window, &_x, &_y);
        _x = 300 - _x;
        _y = 300 - _y;
        g_yaw = 0.4*(_x) + plane1.rotation_yaw;
        g_roll = 0.4*(_y);
    }
}

void tick_input2(GLFWwindow *window) {
    int throw_missile = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if(throw_missile){
        missiles.push_back(Missile(plane1.position.x, plane1.position.y, plane1.position.z, shoot_angle, plane1.rotation_yaw));
    }
    int drop_bomb = glfwGetKey(window, GLFW_KEY_B);
    if(drop_bomb){
        bombs.push_back(Bomb(plane1.position.x, plane1.position.y, plane1.position.z));
    }
}

void tick_elements() {
    plane1.tick();
    // plane1.move_forward();
    plane1.fuel -= 1;
    // plane1.speed -= 0.001;
    enemy_arrow.tick();
    //missiles
    for(auto it = missiles.begin();it!=missiles.end();){
        (*it).tick();
        if((*it).position.y <= 0){
            it = missiles.erase(it);
        }
        else ++it;
    }
    //fuelpoints
    for(auto it = fuelpoints.begin();it!=fuelpoints.end();++it){
        (*it).tick();
    }
    //parachutes
    for(auto it = parachutes.begin();it!=parachutes.end();++it){
        (*it).tick();
    }
    for(auto it = bombs.begin();it!=bombs.end();){
        (*it).tick();
        if((*it).position.y <=-2){
            it = bombs.erase(it);
        }
        else ++it;
    }
    for(auto it = bullets.begin(); it!=bullets.end();){
        (*it).tick();
        if((*it).distance >= shoot_limit){
            it = bullets.erase(it);
        }
        else ++it;
    }
}

void tick_elements2(){
    if(enemies.size()){
        auto it = enemies.begin();
        float x = (*it).position[0], y = (*it).position[1], z = (*it).position[2];
        float dir_x = -x + plane1.position.x;
        float dir_y = -y + plane1.position.y;
        float dir_z = -z + plane1.position.z;
        float dist = sqrt(abs(dir_x)*abs(dir_x) + abs(dir_z)*abs(dir_z));
        
        //considering only ground distance not aerial distance
        if(dist<=60)bullets.push_back(Bullet(x,y,z,dir_x,dir_y,dir_z));
    }
}

bool control_functions(){
    if(plane1.fuel <= 0){
        cout<<"No fuel left!! Game Over!"<<endl;
        return false;
    }
    if(plane1.health <= 0){
        cout<<"Player's got NO health!! Game Over!"<<endl;
        return false;
    }
    return true;
}

void check_collisions(){
    //fuelpoint with plane
    for(auto it = fuelpoints.begin(); it!=fuelpoints.end();){
        if((*it).check_collision(plane1.position.x, plane1.position.y, plane1.position.z)){
            plane1.gotfuel(3000);
            it = fuelpoints.erase(it);
        }
        else ++it;
    }

    //bullet with mountain


    // missile with mountain

    //bullet with plane
    for(auto it = bullets.begin(); it!=bullets.end();){
        if((*it).check_collision(plane1.position.x, plane1.position.y, plane1.position.z)){
            plane1.health -= 200;
            it = bullets.erase(it);
        }
        else ++it;
    }

    //plane with volcano
    for(auto it = mountains.begin(); it!=mountains.end();){
        float dx = (*it).position.x - plane1.position.x;
        float dz = (*it).position.z - plane1.position.z;
        float dist = sqrt(dx*dx + dz*dz);
        if(dist <= 0.75 * ((*it).base)){
            // plane1.health = 0;
            it = mountains.erase(it);
        }
        else ++it;
    }
    //bomb with enemy
    for(auto it = bombs.begin(); it!=bombs.end();){
        int flag=0;
        for(auto it2 = enemies.begin(); it2!=enemies.end();){
            if(detect_collision((*it).bounding_box(),(*it2).bounding_box())){
                (*it2).lives -= 1; ++flag;
                plane1.score += 20;
            }
            if((*it2).lives <= 0){
                it2 = enemies.erase(it2);
            }
            else ++it2;
            break;
        }
        if(flag) it = bombs.erase(it);
        else ++it;
    }
    //missile with enemy
    for(auto it = missiles.begin(); it!=missiles.end();){
        int flag=0;
        for(auto it2 = enemies.begin(); it2!=enemies.end();){
            if(detect_collision((*it).bounding_box(),(*it2).bounding_box())){
                (*it2).lives -= 5; ++flag;
            }
            if((*it2).lives <= 0){
                it2 = enemies.erase(it2);
                plane1.score += 50;
            }
            else ++it2;
            break;
        }
        if(flag) it = missiles.erase(it);
        else ++it;
    }
    //missile with parachute
    for(auto it = missiles.begin(); it!=missiles.end();){
        int flag=0;
        for(auto it2 = parachutes.begin(); it2!=parachutes.end();){
            if(detect_collision((*it).bounding_box(),(*it2).bounding_box())){
                it2 = parachutes.erase(it2);
                plane1.score += 30;
                ++flag;
            }
            else ++it2;
        }
        if(flag) it = missiles.erase(it);
        else ++it;
    }
    //smoke ring with plane
    for(auto it = rings.begin(); it!=rings.end();++it){
        if(detect_collision(plane1.bounding_box2(), (*it).bounding_box())){
            plane1.score += (*it).points;
            (*it).points = 0;
        }
    }

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    plane1 = Plane(0, 10, 50);
    aim = Aim(0,0,0,30,shoot_angle);
    enemy_arrow = EnemyArrow(0,10,0);
    ground = Ground(0,0,COLOR_GROUND);
    
    //left side
    mountains.push_back(Mountain(-20,0,-15,COLOR_PINK));
    mountains.push_back(Mountain(-22,0,-30,COLOR_PINK));
    mountains.push_back(Mountain(-20,0, -45,COLOR_PINK));
    mountains.push_back(Mountain(-22,0,-60,COLOR_PINK));
    mountains.push_back(Mountain(-20,0,-75,COLOR_PINK));
    
    //right side
    mountains.push_back(Mountain(60,0,-15,COLOR_PINK));
    mountains.push_back(Mountain(62,0,-30,COLOR_PINK));
    mountains.push_back(Mountain(60,0, -45,COLOR_PINK));
    mountains.push_back(Mountain(62,0,-60,COLOR_PINK));
    mountains.push_back(Mountain(60,0,-75,COLOR_PINK));

    //front
    mountains.push_back(Mountain(0,0,-100,COLOR_PINK));
    mountains.push_back(Mountain(40,0,-120,COLOR_PINK));
    mountains.push_back(Mountain(20,0,-85,COLOR_PINK));
    mountains.push_back(Mountain(40,0,-85,COLOR_PINK));

    enemies.push_back(Enemy(-30.0f,0.0f,-5.0f));
    enemies.push_back(Enemy(-45.0f,0.0f,-40.0f));
    enemies.push_back(Enemy(0.0f,0.0f,-75.0f));
    enemies.push_back(Enemy(30.0f,0.0f,-100.0f));
    enemies.push_back(Enemy(52.0f,0.0f,-32.0f));
    enemies.push_back(Enemy(80.0f,0.0f,-80.0f));
    enemies.push_back(Enemy(75.0f,0.0f,-10.0f));

    fuelpoints.push_back(Fuel(10.0f,10.0f,-5.0f));
    fuelpoints.push_back(Fuel(55.0f,10.0f,-100.0f));
    fuelpoints.push_back(Fuel(-45.0f,10.0f,-90.0f));
    fuelpoints.push_back(Fuel(70.0f,10.0f,-20.0f));

    parachutes.push_back(Parachute(-10.0f,10.0f,-5.0f));
    parachutes.push_back(Parachute(-40.0f,12.0f,-75.0f));
    parachutes.push_back(Parachute(30.0f,15.0f,-50.0f));
    parachutes.push_back(Parachute(80.0f,8.0f,-20.0f));
    parachutes.push_back(Parachute(-20.0f,9.0f,-90.0f));
    parachutes.push_back(Parachute(78.0f,10.0f,-60.0f));

    rings.push_back(Ring(0.0f,10.0f,-5.0f,COLOR_BLACK,0,10));
    rings.push_back(Ring(0.0f,10.0f,-10.0f,COLOR_BLACK,0,10));
    rings.push_back(Ring(0.0f,10.0f,-15.0f,COLOR_BLACK,0,10));
    rings.push_back(Ring(0.0f,10.0f,-20.0f,COLOR_BLACK,0,10));

    rings.push_back(Ring(30.0f,15.0f,-50.0f,COLOR_DARK_GREEN,30,20));
    rings.push_back(Ring(30.0f,15.0f,-55.0f,COLOR_DARK_GREEN,30,20));
    rings.push_back(Ring(30.0f,15.0f,-60.0f,COLOR_DARK_GREEN,30,20));
    rings.push_back(Ring(30.0f,15.0f,-65.0f,COLOR_DARK_GREEN,30,20));

    rings.push_back(Ring(-55.0f,20.0f,-45.0f,COLOR_PURPLE,-30,20));
    rings.push_back(Ring(-55.0f,20.0f,-50.0f,COLOR_PURPLE,-30,20));
    rings.push_back(Ring(-55.0f,20.0f,-55.0f,COLOR_PURPLE,-30,20));
    rings.push_back(Ring(-55.0f,20.0f,-60.0f,COLOR_PURPLE,-30,20));

    //dashboard
    arrow = Arrow(0,3.6,0);
    fuelmeter = Speedometer(-2.8,-3.6,0,1);//left side
    needle1 = Needle(-2.8,-3.6,0,COLOR_NEEDLE,1);
    altimeter = Speedometer(2.2,-3.6,0,1);
    needle2 = Needle(2.2,-3.6,0,COLOR_NEEDLE,2);
    healthbar = Healthbar(-1.55f,-3.8f,0.0f,player_health/2);
    speedbar = Speedbar(3.8f,-3.8f,0.0f,plane1.speed);
    display = Display(-0.9f,-3.0f,0.0f,1);
    display2 = Display(1.9f,-3.5f,0.0f,2);
    compass = Compass(-3.0f,3.0f,0.0f);
    needle3 = CompassNeedle(-3.0,3.0,0.0f);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            if(!loopin_loop){
                tick_input(window);
                if(t2.processTick()){
                    tick_input2(window);
                }
            }
            if(!loopin_loop){
                tick_elements();
                if(t3.processTick()){
                    tick_elements2();
                }
                check_collisions();
            }
            else{
                
            }

            //last function call - to check a condition to end game
            //check for zero health or something to end the game
            // life, altitude, life less than zero, volcano
            if(control_functions()==false){
                quit(window);
            }
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) && (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(60*M_PI/180.00, (double)1, 0.1, (double)10000);
    Matrices.projection2 = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}