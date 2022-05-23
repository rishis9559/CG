#include <windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 20, 20, -20);
      glVertex3f(-20, 20, -20);
      glVertex3f(-20, 20,  20);
      glVertex3f( 20, 20,  20);

      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 20, -20,  20);
      glVertex3f(-20, -20,  20);
      glVertex3f(-20, -20, -20);
      glVertex3f( 20, -20, -20);

      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 20,  20, 20);
      glVertex3f(-20,  20, 20);
      glVertex3f(-20, -20, 20);
      glVertex3f( 20, -20, 20);

      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 20, -20, -20);
      glVertex3f(-20, -20, -20);
      glVertex3f(-20,  20, -20);
      glVertex3f( 20,  20, -20);

      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-20,  20,  20);
      glVertex3f(-20,  20, -20);
      glVertex3f(-20, -20, -20);
      glVertex3f(-20, -20,  20);

      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(20,  20, -20);
      glVertex3f(20,  20,  20);
      glVertex3f(20, -20,  20);
      glVertex3f(20, -20, -20);
   glEnd();
   glFlush();
}

static void idle(void)
{

    glutPostRedisplay();
}

void init(){
    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble fov = 90.0; // 90 degrees
    GLdouble aspect = 1.0;
    GLdouble near_dist = 50;
    GLdouble far_dist = 300;
    gluPerspective(fov, aspect, near_dist, far_dist);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -200);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB);

    glutCreateWindow("GLUT Shapes");
    init();

    //glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
