#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<bits/stdc++.h>
#include<iostream>

using namespace std;

vector< pair<float,float> > points;
vector< pair<float,float> > p;

bool flag = false;
void line(){
    glColor3d(1,1,0);
    glBegin(GL_LINES);
        glVertex2f(p[0].first, p[0].second);
        glVertex2f(p[1].first, p[1].second);
    glEnd();
    glFlush();
}
void drawRectangle(){
    glBegin(GL_LINE_STRIP);
    glColor3d(1,0,0);
    pair<float, float> bot_left = points[0];
    pair<float, float> top_right = points[1];
    pair<float, float> bot_right(top_right.first, bot_left.second);
    pair<float, float> top_left(bot_left.first, top_right.second);
    points.clear();
    points.push_back(bot_left);
    points.push_back(bot_right);
    points.push_back(top_right);
    points.push_back(top_left);
    for(int i=0;i<points.size();i++){
        glVertex2f(points[i].first,points[i].second);
    }
    glVertex2f(points[0].first,points[0].second);
    glEnd();
    glFlush();
}

void clip(){
    int x1 = p[0].first;
    int x2 = p[1].first;
    int y1 = p[0].second;
    int y2 = p[1].second;

    int del_x = x2-x1;
    int del_y = y2-y1;

    float P[] = {-del_x, del_x,-del_y,del_y};
    float Q[] = {x1-points[0].first,points[2].first - x1,y1-points[0].second,points[2].second - y1};
    float R[4];

    float u1 = 0;
    float u2 = 1;

    for(int i=0;i<4;i++){
        R[i] = Q[i]/P[i];
        cout<<P[i]<<" "<<R[i]<<endl;
    }

    for(int i=0;i<4;i++){
        if(P[i]>0){
            u2 = min(u2,R[i]);
        }else{
            u1 = max(u1,R[i]);
        }
    }

    float x_1,y_1,x_2,y_2;
    cout<<u1<<"--"<<u2<<endl;
    if(u1<u2){
        x_1 = x1+(x2-x1)*u1;
        y_1 = y1+(y2-y1)*u1;
        x_2 = x1+(x2-x1)*u2;
        y_2 = y1+(y2-y1)*u2;
    }
    cout<<x_1<<" "<<y_1<<endl;
    cout<<x_2<<" "<<y_2<<endl;
    line();
    glBegin(GL_LINES);
    glColor3d(1,1,1);
        glVertex2f(x_1,y_1);
        glVertex2f(x_2,y_2);
    glEnd();
    glFlush();

}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void keyFun(unsigned char key,int x,int y){
    switch(key){
        case 'a':
            cout<<"pressed left\n";
            break;
        case 'd':
            cout<<"pressed right\n";
            break;
    }
}

void specialFun(int key,int x,int y){
    switch(key){
    case GLUT_KEY_LEFT:
        cout<<"special Left!\n";
        break;
    case GLUT_KEY_RIGHT:
        cout<<"special right!\n";
        break;
    }
}

void mouseFun(int button,int status,int x,int y){
    if(button==GLUT_LEFT_BUTTON && status==GLUT_DOWN){
        pair<float,float> pr(x,480-y);
        if(flag==false){
            points.push_back(pr);
        }else{
            p.push_back(pr);
            if(p.size()==2){
                line();
                clip();
                p.clear();
            }
        }
    }
    if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN){
        if(flag==false){
            drawRectangle();
            flag = true;
        }
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
    glutKeyboardFunc(keyFun);
    glutSpecialFunc(specialFun);
    glutMouseFunc(mouseFun);

    glutMainLoop();

    return EXIT_SUCCESS;
}
