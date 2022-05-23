#include <windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include<cmath>
using namespace std;

# define SCREEN_HEIGHT 480

vector< pair<float,float> >points;
int Cnt = 0;

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void init(){
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void drawCircle(float r){

    float x = 0, y = r;
    float x_centre = points[0].first;
    float y_centre = points[0].second;

    glBegin(GL_POINTS);

    glVertex2f(x + x_centre,y + y_centre);
    glVertex2f(x + x_centre,-y + y_centre);
    glVertex2f(y + x_centre,x + y_centre);
    glVertex2f(-y + x_centre,x + y_centre);

    float P = 1 - r;

    while (y > x)
    {
        x++;
        if (P <= 0)
            P = P + 2*x + 1;
        else
        {
            y--;
            P = P - 2*y + 2*x + 1;
        }

        if (x > y)
            break;

        glVertex2f(x + x_centre,y + y_centre);
        glVertex2f(-x + x_centre,y + y_centre);
        glVertex2f(x + x_centre,-y + y_centre);
        glVertex2f(-x + x_centre,-y + y_centre);

        if (x != y)
        {
            glVertex2f(y + x_centre,x + y_centre);
            glVertex2f(-y + x_centre,x + y_centre);
            glVertex2f(y + x_centre,-x + y_centre);
            glVertex2f(-y + x_centre,-x + y_centre);
        }
    }

    glEnd();
}

void mouse_handling(int button,int status,int x,int y){
    cout<<endl<<Cnt;
    if (button == GLUT_LEFT_BUTTON && status == GLUT_DOWN)
    {
            glBegin(GL_POINTS);
            glVertex2f(x, SCREEN_HEIGHT - y);
            pair<float,float> p(x, SCREEN_HEIGHT - y);
            points.push_back(p);
            glEnd();
            glFlush();
            Cnt+=1;
    }

    if(button == GLUT_RIGHT_BUTTON && Cnt>=2 && status == GLUT_DOWN){
        float radius = pow(pow(points[0].first - points[1].first,2) + pow(points[0].second - points[1].second,2),0.5);
        drawCircle(radius);
    }
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse_handling);
    glutMainLoop();

    return EXIT_SUCCESS;
}
