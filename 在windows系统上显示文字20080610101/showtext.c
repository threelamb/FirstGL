#include "ctbuf.h"
#include "textarea.h"

const char* g_string =
"���Ͻ�װ����(Metal Gear Solid)��β�����\n"
"���ߣ�(BloodSin)(2000-11-10)\n"
"\n"
"������ BEST IS YET TO COME (���ü�������) \n"
"���ʣ������� RIKA MURANAKA \n"
"������ DAVID DOWNES \n"
"¼�Ƶص㣺 BEECH PARK STUDIO��IRELAND (������) \n"
"�ݳ��� AOIFE NI FHEARRAIGH \n"
"ʹ�������� ������ܣ� ���������٣� С���٣� ��������飬 ������ \n"
"\n"
"��ʴ��⣺ \n"
"\n"
"�����ǵ���ǰ�� \n"
"��С�������Ǹ��� \n"
"�����ǵù�ȥ�� \n"
"������ʹ����΢Ц \n"
"\n"
"�������������õ� \n"
"������������� \n"
"���������Ǽ򵥵� \n"
"�����Ŭ������ \n"
"\n"
"��������ǰ�İ����﷢����ʲô \n"
"�����ڹ�ȥ�ĺ�ҹ�﷢����ʲô \n"
"\n"
"�����ǵ���ǰ�� \n"
"��С�������Ǳ��� \n"
"�����ǵù�ȥ�� \n"
"������ʹ���ǿ��� \n"
"\n"
"ֻ���Ҷ����� \n"
"���� \n"
"�������ǣ� \n"
"�о�����ʧ����������� \n"
"\n"
"Ϊʲô����Ҫ�����˺��أ� \n"
"Ϊʲô����Ҫ���������أ� \n"
"\n"
"���������������� \n"
"�������ȥŬ�� \n"
"���������ǻ���� \n"
"�������ȥ��ȡ \n"
"\n"
"������� \n"
"�Ҳ���Ψһ�� \n"
"������� \n"
"���ǲ��ǹ¶��� ����������� \n"
"�Ϳ�粫�� \n"
"\n"
"�����ǵ���ǰ�� \n"
"�����������ǿ��� \n"
"�����ǵù�ȥ�� \n"
"������ʹ���ǻ�Ц \n"
"\n"
"��֪�� \n"
"�������Ժܼ� \n"
"������ \n"
"�������Ժ����� \n"
"\n"
"��Ϊ \n"
"�����õ����鼴������ \n"
"��Ϊ���������������� \n"
"���ü�������\n";

textarea_t* p_textarea = NULL;

void display(void) {
    static int isFirstCall = 1;

    if( isFirstCall ) {
        isFirstCall = 0;
        ctbuf_init(24, 256, "����");
        p_textarea = ta_create(-0.7f, -0.5f, 0.7f, 0.5f,
            20, 10, g_string);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    // ��ʾ�������
    glEnable(GL_TEXTURE_2D);
    ta_display(p_textarea);

    // �ð�͸����Ч����ʾһ������
    // �������ʵ����Ҫ��ʾ�ķ�Χ
    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    glRectf(-0.7f, -0.5f, 0.7f, 0.5f);
    glDisable(GL_BLEND);

    // ��ʾһЩ������Ϣ
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-1.0f, 0.9f, 0.0f);
    ctbuf_drawString("�����ʾ����", 0.1f, 0.1f);
    glTranslatef(0.0f, -0.1f, 0.0f);
    ctbuf_drawString("��W/S��ʵ���ϡ��·�ҳ", 0.1f, 0.1f);
    glTranslatef(0.0f, -0.1f, 0.0f);
    ctbuf_drawString("��ESC�˳�", 0.1f, 0.1f);
    glPopMatrix();

    glutSwapBuffers();
}

void idle(void) {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w': case 'W':
            ta_scroll(p_textarea, -0.01f);
            glutPostRedisplay();
            break;
        case 's': case 'S':
            ta_scroll(p_textarea, 0.01f);
            glutPostRedisplay();
            break;
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
    glutCreateWindow("��ʾ����");
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyboard);
    // glutFullScreen();
    glutMainLoop();
}
