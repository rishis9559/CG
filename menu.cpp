#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

# define SCREEN_HEIGHT 480
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

# define M_PI 3.14159265358979323846

using namespace std;
static int menuValue = 0;

void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1000,0,480);
}

void drawLine(void)
{
    glColor3f(1,0,0);

    glBegin(GL_LINES);
        glVertex2f(100 ,0);
        glVertex2f(100 ,100);
    glEnd();
}

void drawRectangle(void) {
    glColor3f(1,0,0);

    glBegin(GL_POLYGON);
        glVertex2f(100 ,0);
        glVertex2f(100 ,100);
        glVertex2f(200 ,100);
        glVertex2f(200 ,0);
    glEnd();
}

void DrawCircle() {
    glBegin(GL_LINE_LOOP);
     for(int i =0; i <= 300; i++){
         double angle = 2 * M_PI * i / 300;
         double x = cos(angle);
         double y = sin(angle);
         glVertex2d(200+x*100,200+y*100);
     }
    glEnd();
}

void drawShape( GLint selectedOption) {
    switch(selectedOption){
        case 1:
                menuValue = 1;
                break;

        case 2:
                menuValue = 2;
                break;
        case 3:
                menuValue = 3;
                break;
        default:
                menuValue = 1;

    }
     glutPostRedisplay();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(menuValue == 1)
        drawLine();
    if(menuValue == 3)
        drawRectangle();
    if(menuValue == 2)
        DrawCircle();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");

    init();
    glutDisplayFunc(display);

    glutCreateMenu(drawShape);
        glutAddMenuEntry("Line",1);
        glutAddMenuEntry("circle",2);
        glutAddMenuEntry("Rectangle",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return EXIT_SUCCESS;
}
