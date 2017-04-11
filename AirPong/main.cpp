//
//  main.cpp
//  AirPong
//
//  Created by Santosh Rajan on 4/10/17.
//  Copyright © 2017 Santosh Rajan. All rights reserved.
//
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
    
    GameClass(){
        width = 700;
        height = 700;
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
        if(y < 300)
            y += speed;
    }
    void move_down(){
        if(y > -300)
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
        size = 5;
        isMoving = false;
    }
    
    void move(){
        
    }
    
    void draw(){
        
        glColor3f(0,0,0);
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
        case 'f':
            glutFullScreen();
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
    
    p1.x = -500;
    p2.x = 500;
    
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


