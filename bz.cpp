#include <windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

vector< pair<int,int > > points;

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

void init(){
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void drawRectangle(){
    glColor3d(0.1,0.1,0.1);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<points.size();i++){
        glVertex2f(points[i].first,points[i].second);
    }
    glEnd();
    glFlush();
}

float fn0(float t){
    return -t*t*t + 3*t*t - 3*t + 1;
}

float fn1(float t){
    return 3*t*t*t - 6*t*t + 3*t;
}

float fn2(float t){
    return -3*t*t*t + 3*t*t;
}

float fn3(float t){
    return t*t*t;
}

void drawBrezier(){
    glColor3d(1,1,0);
    glBegin(GL_POLYGON);
    for(float i=0;i<=1;i+=0.001){
        float x = 0,y = 0;
            x+=fn0(i)*points[0].first;
            x+=fn1(i)*points[1].first;
            x+=fn2(i)*points[2].first;
            x+=fn3(i)*points[3].first;

            y+=fn0(i)*points[0].second;
            y+=fn1(i)*points[1].second;
            y+=fn2(i)*points[2].second;
            y+=fn3(i)*points[3].second;
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}

void mouseFn(int button,int status,int x,int y){
    if(button==GLUT_LEFT_BUTTON && status==GLUT_DOWN){
        pair<float,float> pr(x,480-y);
        glBegin(GL_POINTS);
            glVertex2d(pr.first,pr.second);
        glEnd();
        glFlush();
        points.push_back(pr);
    }
    if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN){
        drawRectangle();
        drawBrezier();
        points.clear();
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB);

    glutCreateWindow("GLUT Shapes");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseFn);

    glutMainLoop();
    return EXIT_SUCCESS;
}
