#include "ctbuf.h"
#include "textarea.h"

const char* g_string =
"《合金装备》(Metal Gear Solid)结尾曲歌词\n"
"作者：(BloodSin)(2000-11-10)\n"
"\n"
"曲名： BEST IS YET TO COME (美好即将到来) \n"
"作词，作曲： RIKA MURANAKA \n"
"编曲： DAVID DOWNES \n"
"录制地点： BEECH PARK STUDIO，IRELAND (爱尔兰) \n"
"演唱： AOIFE NI FHEARRAIGH \n"
"使用乐器： 低音风管， 超重音提琴， 小提琴， 打击乐曲组， 电子琴 \n"
"\n"
"歌词大意： \n"
"\n"
"可曾记得以前吗？ \n"
"当小事让我们高兴 \n"
"可曾记得过去吗？ \n"
"当简事使我们微笑 \n"
"\n"
"生命可以是美好的 \n"
"如果你让它那样 \n"
"生命可以是简单的 \n"
"如果你努力尝试 \n"
"\n"
"不管在以前的白昼里发生过什么 \n"
"无论在过去的黑夜里发生过什么 \n"
"\n"
"可曾记得以前吗？ \n"
"当小事让我们悲伤 \n"
"可曾记得过去吗？ \n"
"当简事使我们哭泣 \n"
"\n"
"只是我而已吗？ \n"
"或者 \n"
"还是我们？ \n"
"感觉到迷失在这个世界里 \n"
"\n"
"为什么我们要互相伤害呢？ \n"
"为什么我们要流出热泪呢？ \n"
"\n"
"生命可以是美丽的 \n"
"如果你们去努力 \n"
"生命可以是欢快的 \n"
"如果我们去争取 \n"
"\n"
"请告诉我 \n"
"我不是唯一的 \n"
"请告诉我 \n"
"我们不是孤独的 在这个世界里 \n"
"和狂风搏斗 \n"
"\n"
"可曾记得以前吗？ \n"
"当简事让我们开心 \n"
"可曾记得过去吗？ \n"
"当简事使我们欢笑 \n"
"\n"
"你知道 \n"
"生命可以很简单 \n"
"你明白 \n"
"生命可以很容易 \n"
"\n"
"因为 \n"
"最美好的事情即将到来 \n"
"因为。。。。。。。。 \n"
"美好即将到来\n";

textarea_t* p_textarea = NULL;

void display(void) {
    static int isFirstCall = 1;

    if( isFirstCall ) {
        isFirstCall = 0;
        ctbuf_init(24, 256, "隶书");
        p_textarea = ta_create(-0.7f, -0.5f, 0.7f, 0.5f,
            20, 10, g_string);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    // 显示歌词文字
    glEnable(GL_TEXTURE_2D);
    ta_display(p_textarea);

    // 用半透明的效果显示一个方框
    // 这个框是实际需要显示的范围
    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    glRectf(-0.7f, -0.5f, 0.7f, 0.5f);
    glDisable(GL_BLEND);

    // 显示一些帮助信息
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-1.0f, 0.9f, 0.0f);
    ctbuf_drawString("歌词显示程序", 0.1f, 0.1f);
    glTranslatef(0.0f, -0.1f, 0.0f);
    ctbuf_drawString("按W/S键实现上、下翻页", 0.1f, 0.1f);
    glTranslatef(0.0f, -0.1f, 0.0f);
    ctbuf_drawString("按ESC退出", 0.1f, 0.1f);
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
    glutCreateWindow("显示文字");
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    glutKeyboardFunc(&keyboard);
    // glutFullScreen();
    glutMainLoop();
}
