#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

vector< pair<float,float> > p;
bool poly = true;
int val=0;

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void drawPoly(){
    glColor3d(1,1,1);
    glBegin(GL_POLYGON);
    for(int i=0;i<p.size();i++){
        glVertex2f(p[i].first,p[i].second);
    }
    //glVertex2f(p[0].first,p[0].second);
    glEnd();
    glFlush();
}

void FillPolygon(int x,int y,unsigned char pix[4],int R,int G,int B){

    unsigned char pixel[4];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if(x<0 || x>640 || y<0 || y>480){
        return;
    }

    if((int)pixel[0]== (int)pix[0] && (int)pixel[1] == (int)pix[1] && (int)pixel[2]== (int)pix[2])
    {
        glBegin(GL_POINTS);
        glColor3d(R,G,B);
        glVertex2d(x,y);
        glEnd();
        glFlush();
        FillPolygon(x,y+1,pixel,R,G,B);
        FillPolygon(x,y-1,pixel,R,G,B);
        FillPolygon(x+1,y,pixel,R,G,B);
        FillPolygon(x-1,y,pixel,R,G,B);
    }
}

void MouseFn(int button,int status,int x,int y){
    if(button==GLUT_LEFT_BUTTON && status==GLUT_DOWN && poly){
        pair<float,float> pr(x,480-y);
        glColor3d(1,1,1);
        glBegin(GL_POINTS);
        glVertex2f(x,480-y);
        glEnd();
        glFlush();
        p.push_back(pr);
    }
    else if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN && poly){
        drawPoly();
        poly = false;
    }

    else if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN && poly==false){
        unsigned char pixel[4];

        glReadPixels(x, 480-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        FillPolygon(x,480-y,pixel,1,0,0);
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
    glutMouseFunc(MouseFn);
    glutMainLoop();

    return EXIT_SUCCESS;
}
