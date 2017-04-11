
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>

using namespace std;

//----------------------- GAME CLASS -----------------------//
class GameClass{
    
public:
    
    int width;
    int height;
    
    int border_x;
    int border_y;
    int border_t;
    
    GameClass(){
        width = 800;
        height = 800;
        border_x = 600;
        border_y = 500;
        border_t = 10;
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
    int size;
    bool isMoving;
    
    Ball(){
        x = 0;
        y = 0;
        vx = -3;
        vy = 3;
        size = 5;
        isMoving = false;
    }
    
    void checkBorder(){
        if(y > scene.border_y || y < -scene.border_y)
            vy = -vy;
    }
    
    void checkPaddleCollsion(){
        
        if(p1.x+10 == x && p1.y-100 < y && p1.y+100 > y){
            vx = -vx;
        }
        else if(p2.x-10 == x && p2.y-100 < y && p2.y+100 > y){
            vx = -vx;
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
        glVertex2f(x+size,y+size);
        glVertex2f(x+size,y-size);
        glVertex2f(x-size,y-size);
        glVertex2f(x-size,y+size);
        
    }
    
    
}ball;

//----------------------- DRAW func -----------------------//

void draw () {
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    
    scene.draw_border();
    
    p1.draw();
    p2.draw();
    
    ball.draw();
    
    glEnd();
    glutSwapBuffers();

}


//----------------------- KEYBOARD funcs -----------------------//

void keyboard(unsigned char key, int x, int y){
    
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
    //glutPostRedisplay();
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
    
    p1.move();
    p2.move();
    
    ball.move();
    
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


