#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

vector< pair<int,int> > p;
vector< pair<int,int> > l;

const int INSIDE = 0;
const int TOP = 8;
const int BOTTOM = 4;
const int RIGHT = 2;
const int LEFT = 1;
boolean flag = false;


void init(){
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

static void display(void)
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

void drawWindow()
{
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

void drawLine()
{
    glBegin(GL_LINES);
        glVertex2f(l[0].first,l[0].second);
        glVertex2f(l[1].first,l[1].second);
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

void clip()
{

    float x1 = l[0].first;
    float y1 = l[0].second;
    float x2 = l[1].first;
    float y2 = l[1].second;

    int val1 = assignBit(x1,y1);
    int val2 = assignBit(x2,y2);
    int t1;

    while(true)
    {
        if(val1==0 && val2==0)
        {
            cout<<"Completely inside";
            drawLine();
            return;
        }

        else if(val1 & val2)
        {
            cout<<"Completely Outside \n";
            return;
        }

        else
        {
            int valOut,x,y;

            if(val1 != 0)
                valOut = val1;
            else
                valOut = val2;

            if(valOut & TOP){
                t1 = x1 + (x2 - x1) * (p[1].second - y1) / (y2 - y1);
                if (t1 > p[0].first && t1 < p[1].first){
                    x = t1;
                    y = p[1].second;
                }
            }
            if(valOut & LEFT){
                t1 = y1 + (y2 - y1) * (p[0].first - x1) / (x2 - x1);
                if (t1 > p[0].second && t1 < p[1].second){
                    y = t1;
                    x = p[0].first;
                }

            }
            if(valOut & RIGHT){
                t1 = y1 + (y2 - y1) * (p[1].first - x1) / (x2 - x1);
                if (t1 > p[0].second && t1 < p[1].second){
                    y = t1;
                    x = p[1].first;
                }

            }
            if(valOut & BOTTOM){
                t1 = x1 + (x2 - x1) * (p[0].second - y1) / (y2 - y1);
                if (t1 > p[0].first && t1 < p[1].first){
                    x = t1;
                    y = p[0].second;
                }
            }


            if(valOut ==  val1 ){
                l[0].first = x;
                l[0].second = y;
                val1=0;
            }
            else{
                l[1].first = x;
                l[1].second = y;
                val2=0;
                drawLine();
                return;
            }
        }
    }
}
void handleMouse(int button, int status, int x, int y)
{
    if (button == GLUT_LEFT && status == GLUT_DOWN)
    {
        glColor3f(1,1,1);
        pair<int,int> po(x,480-y);
        glBegin(GL_POINTS);
            glVertex2d(po.first,po.second);
        glEnd();
        glFlush();

        if(flag == false)
            p.push_back(po);
        else
            l.push_back(po);
    }

    else if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN && flag == false)
    {
        flag = true;
        drawWindow();
    }

    else if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN && flag == true)
    {
        clip();
        l.clear();
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
    glutMouseFunc(handleMouse);
    glutMainLoop();

    return EXIT_SUCCESS;
}
