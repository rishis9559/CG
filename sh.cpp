//hodgman

#include <windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;
vector< pair<float,float> > window;
vector< pair<float,float> > polygon;
bool flag = false;

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void PRINT(vector< pair<float,float> > p){
    cout<<endl;
    for(int i=0;i<p.size();i++){
        cout<<"x : "<<p[i].first<<"   y : "<<p[i].second<<endl;
    }
}

void drawWindow(){
    glBegin(GL_LINE_STRIP);
        glVertex2f(window[0].first,window[0].second);
        glVertex2f(window[1].first,window[0].second);
        glVertex2f(window[1].first,window[1].second);
        glVertex2f(window[0].first,window[1].second);
        glVertex2f(window[0].first,window[0].second);
    glEnd();
    glFlush();
}

void drawPoly(vector< pair<float,float> >poly){
    glBegin(GL_POLYGON);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    for(int i=0;i<poly.size();i++){
        glVertex2f(poly[i].first,poly[i].second);
    }
    glEnd();
    glFlush();
}

vector< pair<float,float> > hodg(float x1,float y1,float x2,float y2,vector< pair<float,float> > poly,char FLAG){
    int i = 0;
    vector< pair<float,float> > p;
    float x_1,y_1,x_2,y_2;
    cout<<endl;

    while(i<poly.size()){
        if(i==(poly.size()-1)){
            x_1 = poly[i].first;
            y_1 = poly[i].second;
            x_2 = poly[0].first;
            y_2 = poly[0].second;
        }else{
            x_1 = poly[i].first;
            y_1 = poly[i].second;
            x_2 = poly[i+1].first;
            y_2 = poly[i+1].second;
        }
        if(FLAG=='L'){
            if(x_1>x1){
                if(x_2>x1){
                    pair<float,float> pr(x_2,y_2);
                    p.push_back(pr);
                }else{
                    //pair<float,float> pr(x_1,y_1);
                    //p.push_back(pr);
                    float m = (y_2-y_1)/(x_2-x_1);
                    float Y = y_1 + m*(x1-x_1);
                    pair<float,float> pr1(x1,Y);
                    p.push_back(pr1);
                }
            }
            else if(x_1<x1){
                if(x_2>x1){
                    float m = (y_2-y_1)/(x_2-x_1);
                    float Y = y_1 + m*(x1-x_1);
                    pair<float,float> pr1(x1,Y);
                    p.push_back(pr1);
                    pair<float,float> pr(x_2,y_2);
                    p.push_back(pr);
                }
            }
        }else if(FLAG=='R'){
            if(x_1<x1){
                if(x_2<x1){
                    pair<float,float> pr(x_2,y_2);
                    p.push_back(pr);
                }else{
                    pair<float,float> pr(x_1,y_1);
                    //p.push_back(pr);
                    float m = (y_2-y_1)/(x_2-x_1);
                    float Y = y_1 + m*(x1-x_1);
                    pair<float,float> pr1(x1,Y);
                    p.push_back(pr1);
                }
            }
            else if(x_1>x1){
                if(x_2<x1){
                    float m = (y_2-y_1)/(x_2-x_1);
                    float Y = y_1 + m*(x1-x_1);
                    pair<float,float> pr1(x1,Y);
                    p.push_back(pr1);
                    pair<float,float> pr(x_2,y_2);
                    p.push_back(pr);
                }
            }
        }else if(FLAG=='T'){
            if(y_1<y1){
                if(y_2<y1){
                    pair<float,float> pr(x_2,y_2);
                    p.push_back(pr);
                }else{
                    pair<float,float> pr(x_1,y_1);
                    //p.push_back(pr);
                    float m = (y_2-y_1)/(x_2-x_1);
                    float X = (y1-y_1)/m + x_1;
                    pair<float,float> pr1(X,y1);
                    p.push_back(pr1);
                }
            }else if(y_1>y1){
                if(y_2<y1){
                    float m = (y_2-y_1)/(x_2-x_1);
                    float X = (y1-y_1)/m + x_1;
                    pair<float,float> pr1(X,y1);
                    p.push_back(pr1);
                    pair<float,float> pr(x_2,y_2);
                    p.push_back(pr);
                }
            }
        }else{
            if(y_1>y1){
                if(y_2>y1){
                    pair<float,float> pr(x_2,y_2);
                    p.push_back(pr);
                }else{
                    pair<float,float> pr(x_1,y_1);
                    //p.push_back(pr);
                    float m = (y_2-y_1)/(x_2-x_1);
                    float X = (y1-y_1)/m + x_1;
                    pair<float,float> pr1(X,y1);
                    p.push_back(pr1);
                }
            }else if(y_1<y1){
                if(y_2>y1){
                    float m = (y_2-y_1)/(x_2-x_1);
                    float X = (y1-y_1)/m + x_1;
                    pair<float,float> pr1(X,y1);
                    p.push_back(pr1);
                    pair<float,float> pr(x_2,y_2);
                    p.push_back(pr);
                }
            }
        }
        i+=1;
    }
    return p;
}

void clip(vector< pair<float,float> > poly){
    poly = hodg(window[0].first,window[0].second,window[0].first,window[1].second,poly,'L');
    poly = hodg(window[1].first,window[0].second,window[1].first,window[1].second,poly,'R');
    poly = hodg(window[0].first,window[0].second,window[1].first,window[0].second,poly,'B');
    poly = hodg(window[0].first,window[1].second,window[1].first,window[1].second,poly,'T');
    drawPoly(poly);
}

void mouseFun(int button,int status,int x,int y){
    if(button==GLUT_LEFT_BUTTON && status==GLUT_DOWN){
        pair<float,float> pr(x,480-y);
        if(flag==false){
            window.push_back(pr);
        }else{
            polygon.push_back(pr);
        }
    }
    if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN){
        if(flag==false){
            drawWindow();
            flag = true;
        }else{
            PRINT(window);
            cout<<"----------------------------------------";
            PRINT(polygon);
            cout<<"----------------------------------------";
            clip(polygon);
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
    glutMouseFunc(mouseFun);

    glutMainLoop();

    return EXIT_SUCCESS;
}
