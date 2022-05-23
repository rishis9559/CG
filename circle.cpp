#include <windows.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;
# define SCREEN_HEIGHT 480

vector< pair<int,int> > PointsArr;


void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1000,0,480);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void drawCircle()
{
    int x0 = PointsArr[0].first;
    int y0 = PointsArr[0].second;
    int x1 = PointsArr[1].first;
    int y1 = PointsArr[1].second;

    int r = sqrt(pow((x0-x1),2) + pow((y0-y1),2));


    int x = 0, y = r, x_centre = x0, y_centre = y0;
    int P = 1 - r;

    glBegin(GL_POINTS);
    while (x < y)
    {
        if (P < 0)
        {
            P = P + 2*x + 1;
            x += 1;
        }
        else
        {
            P = P + 2*x - 2*y + 1;
            x += 1;
            y -= 1;
        }
        glColor3f(0, 0, 1);
        glVertex2f(x + x_centre ,y + y_centre);

        glColor3f(0, 1, 0);
        glVertex2f(x + x_centre ,-y + y_centre);

        glColor3f(1, 0, 0);
        glVertex2f(-x + x_centre ,y + y_centre);

        glColor3f(1, 1, 0);
        glVertex2f(-x + x_centre ,-y + y_centre);

        glColor3f(1, 0, 1);
        glVertex2f(y + x_centre ,x + y_centre);

        glColor3f(0, 1, 1);
        glVertex2f(-y + x_centre ,x + y_centre);

        glColor3f(0.2, 0.9, 0.9);
        glVertex2f(y + x_centre ,-x + y_centre);

        glColor3f(1, 1, 1);
        glVertex2f(-y + x_centre ,-x + y_centre);

    }

    glEnd();
    glFlush();
}

void mouse_handling(int button,int status,int x,int y){
    if (button == GLUT_LEFT_BUTTON && status == GLUT_DOWN)
    {
        pair<int,int> p;
        p.first = x;
        p.second =  SCREEN_HEIGHT - y;
        PointsArr.push_back(p);
        glBegin(GL_POINTS);
        glVertex2f(x, SCREEN_HEIGHT - y);
        glEnd();
        glFlush();
    }

    if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN && PointsArr.size()==2 ){
        drawCircle();
        PointsArr.clear();
    }
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
    glutMouseFunc(mouse_handling);
    glutMainLoop();
}
