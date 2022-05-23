#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define CENTER_X 320
#define CENTER_Y 240

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

float arrx[100], arry[100];

vector< vector<float> > points;

int cnt =0;

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
        glVertex2f(0,CENTER_Y);
        glVertex2f(SCREEN_WIDTH,CENTER_Y);
        glVertex2f(CENTER_X,0);
        glVertex2f(CENTER_X,SCREEN_HEIGHT);
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0;i<cnt;i++)
    {
        glVertex2f(arrx[i],arry[i]);
    }
    glEnd();
    glFlush();
}

void translate(int x, int y)
{
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = arrx[i]+x;
        arry[i] = arry[i]+y;
    }
}

void rotation(float theta)
{
    int cx = arrx[0];
    int cy = arry[0];
    theta = theta*(2*M_PI/360.0);
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = arrx[i] - cx;
        arry[i] = arry[i] - cy;
    }
    for(int i=0;i<cnt;i++)
    {
        float x = arrx[i];
        float y = arry[i];
        arrx[i] = x*cos(theta)-y*sin(theta);
        arry[i] = x*sin(theta)+y*cos(theta);
    }
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = arrx[i]+cx;
        arry[i] = arry[i]+cy;
    }
}

void reflectx()
{
    for(int i=0;i<cnt;i++)
    {
      arry[i] = SCREEN_HEIGHT-arry[i];
    }
}

void reflecty()
{
    for(int i=0;i<cnt;i++)
    {
      arrx[i] = SCREEN_WIDTH-arrx[i];
    }
}
void reflectxy()
{
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = SCREEN_WIDTH-arrx[i];
        arry[i] = SCREEN_HEIGHT-arry[i];
    }
}

void shearingx(float shx)
{
    int cx = arrx[0];
    int cy = arry[0];
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = arrx[i] - cx;
        arry[i] = arry[i] - cy;
    }
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = arrx[i]+ shx*arry[i];
    }
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = arrx[i]+cx;
        arry[i] = arry[i]+cy;
    }
}

void scale(float sx, float sy)
{
    int cx = arrx[0];
    int cy = arry[0];
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = arrx[i] - cx;
        arry[i] = arry[i] - cy;
    }
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = arrx[i]* sx;
        arry[i] = arry[i]* sy;
    }
    for(int i=0;i<cnt;i++)
    {
        arrx[i] = arrx[i] + cx;
        arry[i] = arry[i] + cy;
    }
}
void reflectmx(float m,float c)
{
    float x,y;
    for(int i=0;i<cnt;i++)
    {
        x = arrx[i];
        y = arry[i];
        arrx[i] = x*(((1-m*m)/(m*m+1))) + y *(2*m/(m*m +1)) - ((2*m*c)/m*m +1);
        arry[i] = x*((2*m)/(m*m+1)) + y*((m*m -1)/(m*m +1)) + ((2*c)/(m*m+1));
    }
}

void key(unsigned char k, int x, int y)
{
    cout<<"Key:"<<k<<endl;
    cout<<x<<" "<<y<<endl;
    switch (k)
    {
    case 'w':
        translate(0,10);
        break;
    case 'a':
        translate(-10,0);
        break;
    case 'd':
        translate(10,0);
        break;
    case 's':
        translate(0,-10);
        break;
    case 'k':
        scale(2,2);
        break;
    case 'l':
        scale(0.5,0.5);
        break;
    case 'r':
        rotation(5);
        break;
    case 't':
        rotation(-5);
        break;
    case 'v':
        reflectx();
        break;
    case 'b':
        reflecty();
        break;
    case 'n':
        reflectxy();
        break;
    case 'h':
        shearingx(0.25);
        break;
    case 'p':
        reflectmx(1,2);
        break;
    case 27:
      exit(0);
      break;
    default:
      break;
    }
    glutPostRedisplay();
}
static void mouse(int button, int status, int x, int y)
{

    if(button==GLUT_LEFT_BUTTON)
    {
        cout<<x<<","<<y<<endl;
        y = SCREEN_HEIGHT-y;
        vector<float> point;
        point.push_back(x);
        point.push_back(y);
        glBegin(GL_POINTS);
            glVertex2f( x,y);
        glEnd();

        points.push_back(point);
        cnt++;
    }
    if(button ==GLUT_RIGHT_BUTTON)
    {
        int i=0;
        for (i;i<cnt;i++)
        {
            arrx[i] = points[i][0];
            arry[i] = points[i][1];
        }
        glutKeyboardFunc(key);
    }
    glFlush();
}


void init()
{
    glClearColor(0.5,0.5,0.5,0.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,SCREEN_WIDTH,0,SCREEN_HEIGHT);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Transforms");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return EXIT_SUCCESS;
}
