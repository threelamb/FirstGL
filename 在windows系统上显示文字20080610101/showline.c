#include "ctbuf.h"

void display(void) {
    static int isFirstCall = 1;

    if( isFirstCall ) {
        isFirstCall = 0;
        ctbuf_init(32, 256, "黑体");
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, 0.0f);
    ctbuf_drawString("美好明天就要到来", 0.1f, 0.15f);
    glTranslatef(0.0f, -0.15f, 0.0f);
    ctbuf_drawString("Best is yet to come", 0.1f, 0.15f);
    glPopMatrix();

    glutSwapBuffers();
}

void idle(void) {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("显示文字");
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyboard);
    // glutFullScreen();
    glutMainLoop();
}
