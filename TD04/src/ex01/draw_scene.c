#include "draw_scene.h"
#include "3D_tools.h"

void drawBase() {
}

void drawArm() {
}

void drawPan() {
}

void drawFrame()
{
    // dessin du repère
    glBegin(GL_LINES);
    glColor3f(1., 0., 0.);
    glVertex3f(0., 0., 0.);
    glVertex3f(25, 0., 0.);
    glColor3f(0., 1., 0.);
    glVertex3i(0., 0., 0.);
    glVertex3i(0., 25, 0.);
    glColor3f(0., 0., 1.);
    glVertex3i(0., 0., 0.);
    glVertex3i(0., 0., 25);
    glEnd();
}
