
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>
#include <time.h>


using namespace std;

//----------------------- GAME CLASS -----------------------//
class GameClass{
    
public:
    
    bool pause;
    
    int width;
    int height;
    
    int border_x;
    int border_y;
    int border_t;
    
    int p1_points;
    int p2_points;
    
    GameClass(){
        
        pause = true;

        width = 800;
        height = 800;
        
        border_x = 600;
        border_y = 500;
        border_t = 10;
        
        p1_points = 0;
        p2_points = 0;
    
    }
    
    void draw_border () {
        
        glColor3f(0,0,0);
        glVertex2f(-border_x - border_t,-border_y - border_t);
        glVertex2f(border_x + border_t,-border_y - border_t);
        glVertex2f(border_x + border_t,-border_y);
        glVertex2f(-border_x - border_t,-border_y);
        
        glVertex2f(-border_x - border_t,border_y + border_t);
        glVertex2f(border_x + border_t,border_y + border_t);
        glVertex2f(border_x + border_t,border_y);
        glVertex2f(-border_x - border_t,border_y);
        
        glVertex2f(-border_x - border_t,-border_y - border_t);
        glVertex2f(-border_x,-border_y - border_t);
        glVertex2f(-border_x,border_y + border_t);
        glVertex2f(-border_x - border_t, border_y + border_t);
        
        glVertex2f(border_x,-border_y - border_t);
        glVertex2f(border_x + border_t,-border_y - border_t);
        glVertex2f(border_x + border_t,border_y + border_t);
        glVertex2f(border_x, border_y + border_t);
        
        
        for(float i = -border_y; i <= border_y; i += 4*5){
            glVertex2f(-5,i + 5);
            glVertex2f(5,i + 5);
            glVertex2f(5,i - 5);
            glVertex2f(-5,i - 5);
        }
        
    }
    void draw_scores(){
        
        glColor3f(0, 0, 0);
        glRasterPos2f(30, 510 + 20);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + p1_points);
        glRasterPos2f(-50, 510 + 20);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + p2_points);
        
    }
    

}scene;

//----------------------- PADDLE CLASS -----------------------//

class Paddles {
    
public:
    
    float x;
    float y;
    float size;
    float speed;
    bool up, down;
    
    Paddles(){
        x = 0;
        y = 0;
        size = 200;
        speed = 5;
        up = down = false;
    }
    
    void init( float x){
        this->x = x;
    }
    
    void move_up(){
        if(y < scene.border_y - 100)
            y += speed;
    }
    void move_down(){
        if(y > -scene.border_y + 100)
            y -= speed;
    }
    
    void move () {
        
        if(up)
            move_up();
        if(down)
            move_down();
        
    }
    
    void draw(){
        
        glColor3f(0,0,0);
        glVertex2f(x + 10,y + size/2);
        glVertex2f(x + 10,y - size/2);
        glVertex2f(x - 10,y - size/2);
        glVertex2f(x - 10,y + size/2);
        
    }
    
}p1,p2;

//----------------------- BALL CLASS -----------------------//

class Ball {
    
public:
    float x;
    float y;
    float vx;
    float vy;
    float speed;
    int size;
    bool isMoving;
    
    Ball(){
        x = 0;
        y = 0;
        speed = 6;
        srand(time(NULL));
        vx =  1 + ((double) rand() / (RAND_MAX)) *  speed;
        vy = speed - vx;
        cout<<vx<<" "<<vy<<endl;
        size = 10;
    }
    
    void checkBorder(){
        if(y > scene.border_y || y < -scene.border_y)
            vy = -vy;
        if(x > scene.border_x ){
            vy = -vy;
            x = 0;
            y = 0;
            vx =  1 + ((double) rand() / (RAND_MAX)) *  speed;
            vy = speed - vx;
            size = 10;
            scene.pause = true;
            scene.p1_points++;
        }
        if(x < -scene.border_x ){
            vy = -vy;
            x = 0;
            y = 0;
            vx =  - 1 - ((double) rand() / (RAND_MAX)) *  speed;
            vy = speed - vx;
            size = 10;
            scene.pause = true;
            scene.p2_points++;
        }

    }
    
    void checkPaddleCollsion(){
        
        if(p1.x+10 >= x && p1.y-100 < y && p1.y+100 > y){
            vx = -vx + ((double) rand() / (RAND_MAX)) *  speed /2 ;
        }
        else if(p2.x-10 <= x && p2.y-100 < y && p2.y+100 > y){
            vx = -vx - ((double) rand() / (RAND_MAX)) *  speed /2;
        }
        
    }
    
    void move(){
        
        x += vx;
        y += vy;
        
        checkBorder();
        checkPaddleCollsion();
    }
    
    void draw(){
        
        glColor3f(0,0,1);
   
        glBegin(GL_QUADS);
       
        glVertex2f(x+size,y+size);
        glVertex2f(x+size,y-size);
        glVertex2f(x-size,y-size);
        glVertex2f(x-size,y+size);
        glEnd();
        
    }
    
    
}ball;

//----------------------- DRAW func -----------------------//

void draw () {
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    
    scene.draw_border();
    
    p1.draw();
    p2.draw();
    glEnd();
    ball.draw();
    
    scene.draw_scores();
    
    glutSwapBuffers();

}


//----------------------- KEYBOARD funcs -----------------------//

void keyboard(unsigned char key, int x, int y){
    
    scene.pause = false;
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'w':
            p1.up = true;
            break;
        case 's':
            p1.down = true;
            break;
        case 'i':
            p2.up = true;
            break;
        case 'k':
            p2.down = true;
            break;
    }
}

void keyboardUp(unsigned char key, int x, int y){
    
    switch (key) {
        case 'w':
            p1.up = false;
            break;
        case 's':
            p1.down = false;
            break;
        case 'i':
            p2.up = false;
            break;
        case 'k':
            p2.down = false;
            break;
    }
    //glutPostRedisplay();
}

//----------------------- TIMER func -----------------------//

void Timer (int value){
    
    if(!scene.pause){
        p1.move();
        p2.move();
        ball.move();
    }
    glutPostRedisplay();
    glutTimerFunc(1, Timer, 0);
}

//----------------------- SETS -----------------------//

void setPaddles(){
    
    p1.x = -550;
    p2.x = 550;
    
}

void setAll(){
    
    setPaddles();
    
}


//----------------------- MAIN -----------------------//
void windowSetup(){
    
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(scene.width, scene.width);
    glutInitWindowPosition(100,100);
    glutCreateWindow("#####AIR PONG#####");
    
}

int main(int argc, char** argv) {
    
    srand(time(NULL));
    
    glutInit(&argc, argv);
    
    windowSetup();
    
    setAll();
    
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(1, Timer, 0);
    
    glClearColor(1, 1, 1, 1);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-scene.width,scene.width,-scene.height,scene.height);
    glutMainLoop();
    return 0;
}


