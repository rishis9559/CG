#include <windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

vector< pair<float,float> > p;
vector< pair<float,float> > l;
bool flag = false;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

static void display(void)
{
    glFlush();
}

void drawSquare(){
    glClearColor(0,0,0,0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
    glColor3d(1,1,1);
        glVertex2f(p[0].first,p[0].second);
        glVertex2f(p[1].first,p[0].second);
        glVertex2f(p[1].first,p[1].second);
        glVertex2f(p[0].first,p[1].second);
    glEnd();
    glFlush();
}

int assignBit(float x,float y)
{
    int code = INSIDE;
    if (x < p[0].first)
        code |= LEFT;
    else if (x > p[1].first)
        code |= RIGHT;
    if (y < p[0].second)
        code |= BOTTOM;
    else if (y > p[1].second)
        code |= TOP;

    return code;
}

void plotLine()
{
    glBegin(GL_LINES);
        glVertex2f(l[0].first,l[0].second);
        glVertex2f(l[1].first,l[1].second);
    glEnd();
    glFlush();
}

void clip()
{
    float x1 = l[0].first;
    float y1 = l[0].second;
    float x2 = l[1].first;
    float y2 = l[1].second;

    int val1 = assignBit(x1,y1);
    int val2 = assignBit(x2,y2);

    while(true){

        if(val1==0 && val2==0)
        {
            cout<<"Completely inside \n";
            plotLine();
            return;
        }

        else if(val1 & val2)
        {
            cout<<"Completely Outside \n";
            return;
        }

        else{
            int val_out;
            float x, y;

            if (val1 != 0)
                val_out = val1;
            else
                val_out = val2;

            if(val_out & TOP){
                x = x1 + (x2 - x1) * (p[1].second - y1) / (y2 - y1);
                y = p[1].second;
            }
            if(val_out & LEFT){
                y = y1 + (y2 - y1) * (p[0].first - x1) / (x2 - x1);
                x = p[0].first;
            }
            if(val_out & RIGHT){
                y = y1 + (y2 - y1) * (p[1].first - x1) / (x2 - x1);
                x = p[1].first;
            }
            if(val_out & BOTTOM){
                x = x1 + (x2 - x1) * (p[0].second - y1) / (y2 - y1);
                y = p[0].second;
            }

            if (val_out == val1) {
                l[0].first = x;
                l[0].second = y;
                cout<<"assigned l[0] \n";
                val1 = 0;
            }
            else {
                l[1].first = x;
                l[1].second = y;
                cout<<"assigned l[1] \n";
                val2 = 0;
                plotLine();
                return;
            }
        }
    }
}

void mouseHandling(int button,int status,int x,int y){
    if(button==GLUT_LEFT_BUTTON && status==GLUT_DOWN){
        pair<int,int> pr(x,480-y);
        if(flag==false)
            p.push_back(pr);
        else
            l.push_back(pr);
    }else if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN && flag==false){
        drawSquare();
        flag = true;
    }
    else if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN && flag==true){
        clip();
        l.clear();
    }
}

void init(){
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
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
    glutMouseFunc(mouseHandling);
    glutMainLoop();

    return EXIT_SUCCESS;
}
