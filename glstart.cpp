
#include "TXLib.h"
#include <gl\glut.h>


void Draw();
void Initialize();



int main(int argc, char** argv)
    {
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 200);
    glutCreateWindow("Lesson 1");

    glutDisplayFunc (Draw);
    Initialize();
    glutMainLoop();
    return 0;
    }




void Draw()
    {
    }

void Initialize()
    {
    }
