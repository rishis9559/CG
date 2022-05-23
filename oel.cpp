//ordered edge list

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;
vector< pair<int,int> > polygon;
int yMin = 1000;
int yMax = -1;

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
void drawPolygon()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
    for(int i=0;i<polygon.size();i++)
    {
        glVertex2d(polygon[i].first,polygon[i].second);
    }
    glEnd();
    glFlush();
}

pair<float,float> getIntersection(float x1,float y1,float x2,float y2,int scanLine){
    float m;
    if(x2-x1==0){
        m = 0;
        pair<float,float> p(x2,scanLine);
        return p;
    }
    m = (y2-y1)/float(x2-x1);
    float x = (scanLine-y1)/m + x1;
    pair<float,float> p(x,scanLine);
    return p;
}

void orderList(){
    for(int scanLine = yMin;scanLine<yMax;scanLine++){
        vector< pair<float,float> > intersections;
        for(int i=0;i<polygon.size();i++){
            pair<float,float> p;
            bool assigned = false;
            if(i==polygon.size()-1){
                if(min(polygon[i].second,polygon[0].second)<=scanLine && max(polygon[i].second,polygon[0].second)>= scanLine){
                    p = getIntersection(polygon[i].first,polygon[i].second,polygon[0].first,polygon[0].second,scanLine);
                    assigned = true;
                }
            }
            else{
                if(min(polygon[i].second,polygon[i+1].second)<=scanLine && max(polygon[i].second,polygon[i+1].second)>=scanLine){
                    p = getIntersection(polygon[i].first,polygon[i].second,polygon[i+1].first,polygon[i+1].second,scanLine);
                    assigned = true;
                }
            }

            if(assigned){
                auto it = find(intersections.begin(),intersections.end(),p);
                if(it == intersections.end()){
                    intersections.push_back(p);
                }
                else{
                    cout<<"ELSE\n";
                    if(i-1>=0 && i!=polygon.size()-1 && ((polygon[i-1].second>=p.second && p.second<=polygon[i+1].second) ||
                                  (polygon[i-1].second<=p.second && p.second>=polygon[i+1].second)) ){
                        cout<<"ELSE IF : "<<i<<"\n";
                        intersections.push_back(p);
                    }
                }
            }
        }
        sort(intersections.begin(),intersections.end());
        int loopval = intersections.size()-1;
        cout<<"Scan Line : "<<scanLine;
        cout<<"\nIntersections Size : "<<intersections.size()<<"\n\n";
        for(int i1 = 0;i1<loopval;i1++){
            if(i1%2==0){
                glBegin(GL_LINES);
                    glVertex2d(intersections[i1].first,intersections[i1].second);
                    glVertex2d(intersections[i1+1].first,intersections[i1+1].second);
                glEnd();
                glFlush();
            }
        }
    }
}

void mouseFn(int button, int status, int x,int y)
{
    if(button == GLUT_LEFT_BUTTON && status==GLUT_DOWN)
    {
        pair<int,int> p;
        glBegin(GL_POINTS);
            glVertex2d(x,480-y);
        glEnd();
        glFlush();
        p.first = x;
        p.second = 480-y;
        cout<<x<<" -- "<<p.second<<"\n";
        yMin = min(yMin,p.second);
        yMax = max(yMax,p.second);
        polygon.push_back(p);
    }
    if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
    {
        cout<<"\n\n";
        drawPolygon();
        orderList();
    }
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
    glutMouseFunc(mouseFn);
    glutMainLoop();

    return EXIT_SUCCESS;
}
