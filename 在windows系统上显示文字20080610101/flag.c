//#include "GLee.h"
#include <GL/glut.h>
#include <windows.h>
#include <math.h>

void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

#define FONT_SIZE       64
#define TEXTURE_SIZE    FONT_SIZE

GLuint drawChar_To_Texture(const char* s) {
    wchar_t w;
    HDC hDC = wglGetCurrentDC();

    // 选择字体字号、颜色
    // 不指定字体名字，操作系统提供默认字体
    // 设置颜色为白色
    selectFont(FONT_SIZE, DEFAULT_CHARSET, "");
    glColor3f(1.0f, 1.0f, 1.0f);

    // 转化为宽字符
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s, 2, &w, 1);

    // 计算绘制的位置
    {
        int width, x, y;
        GetCharWidth32W(hDC, w, w, &width);    // 取得字符的宽度
        x = (TEXTURE_SIZE - width) / 2;
        y = FONT_SIZE / 8;
        //glWindowPos2iARB(x, y);
    }

    // 绘制字符
    // 绘制前应该将各种可能影响字符颜色的效果关闭
    // 以保证能够绘制出白色的字符
    {
        GLuint list = glGenLists(1);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
        glDisable(GL_TEXTURE_2D);

        wglUseFontBitmaps(hDC, w, 1, list);
        glCallList(list);
        glDeleteLists(list, 1);
    }

    // 复制字符像素到纹理
    // 注意纹理的格式
    // 不使用通常的GL_RGBA，而使用GL_LUMINANCE4
    // 因为字符本来只有一种颜色，使用GL_RGBA浪费了存储空间
    // GL_RGBA可能占16位或者32位，而GL_LUMINANCE4只占4位
    {
        GLuint texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE4,
            0, 0, TEXTURE_SIZE, TEXTURE_SIZE, 0);
        glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        return texID;
    }
}

// 设置法线向量
// 三个不在同一直线上的点可以确定一个平面
// 先计算这个平面的法线向量，然后指定到OpenGL
void setNormal(const GLfloat v1[3],
               const GLfloat v2[3],
               const GLfloat v3[3]) {
    // 首先根据三个点坐标，相减计算出两个向量
    const GLfloat s1[] = {
        v2[0]-v1[0], v2[1]-v1[1], v2[2]-v1[2]};
    const GLfloat s2[] = {
        v3[0]-v1[0], v3[1]-v1[1], v3[2]-v1[2]};

    // 两个向量叉乘得到法线向量的方向
    GLfloat n[] = {
        s1[1]*s2[2] - s1[2]*s2[1],
        s1[2]*s2[0] - s1[0]*s2[2],
        s1[0]*s2[1] - s1[1]*s2[0]
    };

    // 把法线向量缩放至单位长度
    GLfloat abs = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
    n[0] /= abs;
    n[1] /= abs;
    n[2] /= abs;

    // 指定到OpenGL
    glNormal3fv(n);
}

#define PI          (3.1415926f)

#define MIN_X       (-0.5f)
#define MAX_X       (0.5f)
#define MIN_Y       (-0.5f)
#define MAX_Y       (0.5f)
#define SEGS        ((int)((MAX_X - MIN_X) * (512/2)))
#define RANGE       (0.05f)
#define CIRCLES     (2.0f)
#define SPEED       (5.0f)

GLfloat theta = 0.0f;

// 绘制一面旗帜
void draw(void) {
    int i;
    // 每绘制一段，坐标x应该增加的量
    const GLfloat x_inc = (MAX_X - MIN_X) / SEGS;
    // 每绘制一段，纹理坐标s应该增加的量
    const GLfloat t_inc = 1.0f / SEGS;
    // 每绘制一段，常数theta应该增加的量
    const GLfloat theta_inc = 2 * PI * CIRCLES / SEGS;

    // 用GL_QUAD_STRIP来绘制相连的四边形
    glBegin(GL_QUAD_STRIP);
    for(i=0; i<=SEGS; ++i) {
        // 按照z = sin(t * c1 + c2) * c3 + c4的公式计算z坐标
        const GLfloat z = RANGE * sin(i*theta_inc + theta);

        // 一段只需要指定两个点
        // 第三个点其实是下一段的第一个点
        // 之所以使用三个点，是为了构成一个平面
        // 便于计算法线向量
        const GLfloat
            v1[] = {i*x_inc + MIN_X, MAX_Y, z},
            v2[] = {i*x_inc + MIN_X, MIN_Y, z},
            v3[] = {
                (i+1)*x_inc + MIN_X,
                MAX_Y,
                RANGE * sin((i+1)*theta_inc + theta)};

        // 调用一个函数来计算法线向量
        setNormal(v1, v2, v3);

        // 设置合适的纹理坐标和顶点坐标
        glTexCoord2f(i*t_inc, 1.0f);
        glVertex3fv(v1);
        glTexCoord2f(i*t_inc, 0.0f);
        glVertex3fv(v2);
    }
    glEnd();
}

void display(void) {
    static int isFirstCall = 1;
    static GLuint texID = 0;

    if( isFirstCall ) {    // 第一次调用，产生一个纹理
        isFirstCall = 0;
        texID = drawChar_To_Texture("曹");

        // 深度测试
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        {
            // 文字的颜色
            GLfloat color[] = {1.0f, 1.0f, 0.0f, 1.0f};
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
            glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color);
        }

        // 光照
        {
            GLfloat
                light_position[] = {2.0f, 3.0f, 5.0f, 0.0f},
                light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f},
                light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f},
                mat_ambient[] = {0.0f, 0.0f, 1.0f, 1.0f},
                mat_specular[] = {0.5f, 0.5f, 0.5f, 1.0f},
                mat_emission[] = {0.0f, 0.0f, 0.3f, 1.0f};
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_ambient);
            glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
            glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        }

        // 设置观察点
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, 1.0, 0.1, 5.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(1.0, -1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    draw();

    glutSwapBuffers();
}

void idle(void) {
    theta += (SPEED * PI / 180.0f);
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(512, 512);
    glutCreateWindow("OpenGL");
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    glutMainLoop();
}
