#include <windows.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

# define SCREEN_HEIGHT 480
# define X 320
# define Y 240

vector< pair<float, float> > points;

void Lines()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    for(unsigned int i=0;i<points.size();i++)
    {
        glVertex2f(points[i].first+X,points[i].second+Y);
    }
    glEnd();
    glFlush();
}

void Quadrant()
{
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2d(0, 240);
        glVertex2d(640, 240);
    glEnd();

    glBegin(GL_LINES);
        glVertex2d(320,0);
        glVertex2d(320,480);
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void AddAll_point(int choice,int val){
    for(unsigned int i=0;i<points.size();i++)
    {
        if(choice==1)
            points[i].second+=val;
        else
            points[i].first+=val;
    }
}

void scale(float val){
    float x = points[0].first;
    float y = points[0].second;
    float scale_val = 1.1*val;
    for(unsigned int i=0;i<points.size();i++)
    {
        float x1 = points[i].first-x;
        float y1 = points[i].second-y;
        points[i].first=x1*scale_val + x;
        points[i].second=y1*scale_val + y;
    }
    Lines();
    Quadrant();
}

static void display(void)
{
    Quadrant();
}

void print(int x,int y)
{
    cout<<"X : "<<x<<" Y : "<<y<<endl;
}

void mouse_handling(int button,int status,int x,int y)
{
    if (button == GLUT_LEFT_BUTTON && status == GLUT_DOWN)
    {
        pair<int,int> p(x-X, Y-y);
        points.push_back(p);
        glBegin(GL_POINTS);
            glVertex2d(x-X, Y-y);
        glEnd();
    }
    if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
    {
        Lines();
        Quadrant();
    }
}

void translate(int key,int x, int y){
    switch(key)
    {
        case GLUT_KEY_LEFT: AddAll_point(0,-5);
                            Lines();
                            Quadrant();
                            break;

        case GLUT_KEY_RIGHT: AddAll_point(0,5);
                            Lines();
                            Quadrant();
                            break;

        case GLUT_KEY_DOWN: AddAll_point(1,-5);
                            Lines();
                            Quadrant();
                            break;

        case GLUT_KEY_UP:   AddAll_point(1,5);
                            Lines();
                            Quadrant();
                            break;
        case GLUT_KEY_PAGE_UP :
                            scale(2);
                            break;
        case GLUT_KEY_PAGE_DOWN:
                            scale(0.5);
                            break;
    }
}

void reflect(int x, int y)
{
    for(unsigned int i=0; i<points.size(); i++)
    {
        points[i].first *= x;
        points[i].second *= y;
    }
    Lines();
    Quadrant();
}

void sheer(int x, int y)
{
    for(unsigned int i=0; i<points.size(); i++)
    {
        points[i].first = points[i].first + points[i].second*y;
        points[i].second = points[i].first*x + points[i].second;
    }
    Lines();
    Quadrant();
}

void rotate(int val)
{
    double theta = val*(5)*3.14159/180;
    float x = points[0].first;
    float y = points[0].second;
    for(unsigned int i=0;i<points.size();i++)
    {
        float x1 = points[i].first-x;
        float y1 = points[i].second-y;
        points[i].first = x1*cos(theta) - y1*sin(theta)+x;
        points[i].second = x1*sin(theta) + y1*cos(theta)+y;
    }
    Lines();
    Quadrant();
}

void processNormalKeys(unsigned char key, int x, int y)
{

	if (key == 'a')
        rotate(-1);
    else if(key == 'd')
        rotate(1);
    else if(key == 'x')
        reflect(1,-1);
    else if(key == 'y')
        reflect(-1,1);
    else if(key == 'o')
        reflect(-1,-1);
    else if(key == 's')
        sheer(1, 0);
}

int main(int argc, char *argv[])
{

    int screen_width = 640;
    int screen_height = 480;

    glutInit(&argc, argv);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse_handling);
    glutSpecialFunc(translate);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
    return EXIT_SUCCESS;
}
