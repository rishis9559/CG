#include <windows.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <bits/stdc++.h>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1000
using namespace std;

vector< pair<int,int> > points;
vector< pair<int,int> > window;
void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,SCREEN_WIDTH,0,SCREEN_HEIGHT);
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glFlush();
}

void plotPoints(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}

void drawLine()
{
    glBegin(GL_LINES);
        glVertex2f(points[0].first,points[0].second);
        glVertex2f(points[1].first,points[1].second);
    glEnd();
    glFlush();
}

void drawLine(int x1, int y1, int x2, int y2)
{
    glColor3f(0,1,0);
    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
    glFlush();
}

void drawWindow()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
        glVertex2d(window[0].first,window[0].second);
        glVertex2d(window[0].first,window[1].second);
        glVertex2d(window[1].first,window[1].second);
        glVertex2d(window[1].first,window[0].second);
    glEnd();
    glFlush();
}

void LBC()
{
   // cout<<"inside";
    float delx = points[1].first - points[0].first, dely = points[1].second - points[0].second;
    float p[4];
    p[0] = -delx;
    p[1] = delx;
    p[2] = -dely;
    p[3] = dely;

    float q[4];
    q[0] = (points[0].first - window[0].first) ;
    q[1] = (window[1].first -  points[0].first) ;
    q[2] = (points[0].second - window[0].second);
    q[3] = (window[1].second - points[0].second );

    float r[4];
    r[0]=q[0]/p[0];
    r[1]=q[1]/p[1];
    r[2]=q[2]/p[2];
    r[3]=q[3]/p[3] ;

    float u1=0,u2=1;
    for(int i=0;i<4;i++)
    {
        if(p[i] < 0) u1 = max(u1,r[i]);
        else u2 = min(u2,r[i]);
    }

    cout<<"u1: "<<u1<<" u2: "<<u2<<endl;
    if(u1<u2)
    {
        float x1 = points[0].first + delx*u1;
        float y1 = points[0].second + dely*u1;

        float x2 = points[0].first + delx*u2;
        float y2 = points[0].second + dely*u2;

        cout<<"x1: "<<x1<<" y1:"<<y1<<" x2:"<<x2<<" y2:"<<y2;
        drawLine(x1,y1, x2,y2);
    }


}


void mouse_handle(int button, int status, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && status ==  GLUT_DOWN)
    {
        pair<int,int> p;
        p.first = x;
        p.second = SCREEN_HEIGHT - y;

        glColor3d(1,0,0);
        plotPoints(p.first,p.second);

        points.push_back(p);
        // cout<<"X: "<<p.first<<" Y: "<<p.second<<endl;
    }

    if(points.size() == 2 && status == GLUT_DOWN)
    {
        drawLine();
    }

    if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
    {
        pair<int,int> p;
        p.first = x;
        p.second = SCREEN_HEIGHT - y;
        glColor3d(1,0,0);
        plotPoints(p.first,p.second);


        cout<<"w.x: "<<p.first<<" w.y: "<<p.second<<endl;
        window.push_back(p);
    }

    if(window.size() == 2 && status == GLUT_DOWN)
    {
        drawWindow();
        LBC();
    }

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(50,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Liang Clipping");
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse_handle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
