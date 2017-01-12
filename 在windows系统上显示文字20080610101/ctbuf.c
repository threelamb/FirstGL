// ctbuf.c

#include "ctbuf.h"

#include <stdlib.h>

static GLuint g_texID = 0;
static ctitem_t* g_items = 0;
static int g_count = 0;
static int g_total = 0;
static int g_fontsize = 0;
static int g_texturesize = 0;

static void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

static void drawChar_To_SubTexture(
        wchar_t w, int texcoord_x, int texcoord_y) {
    HDC hDC = wglGetCurrentDC();

    glPushAttrib(GL_COLOR_BUFFER_BIT |
            GL_ENABLE_BIT | GL_VIEWPORT_BIT);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);

    // 把将要绘制字符的地方涂黑
    glViewport(0, 0, g_fontsize, g_fontsize);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
        glRectf(-1.0f, -1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // 设置颜色为白色
    glColor3f(1.0f, 1.0f, 1.0f);

    // 计算绘制的位置
    {
        int width, x, y;
        GetCharWidth32W(hDC, w, w, &width);    // 取得字符的宽度
        x = (g_fontsize - width) / 2;
        y = g_fontsize / 8;
        glWindowPos2iARB(x, y);
    }

    // 绘制字符
    // 绘制前应该将各种可能影响字符颜色的效果关闭
    // 以保证能够绘制出白色的字符
    {
        GLuint list = glGenLists(1);

        wglUseFontBitmaps(hDC, w, 1, list);
        glCallList(list);
        glDeleteLists(list, 1);
    }

    // 复制字符像素到纹理
    glBindTexture(GL_TEXTURE_2D, g_texID);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0,
        texcoord_x, texcoord_y,
        0, 0, g_fontsize, g_fontsize);

    glPopAttrib();
}

void ctbuf_init(int fontsize, int texturesize, const char* font) {
    int i;

    ctbuf_destroy();

    g_count = texturesize / fontsize;
    g_total = g_count * g_count;
    g_fontsize = fontsize;
    g_texturesize = texturesize;

    glGenTextures(1, &g_texID);
    glBindTexture(GL_TEXTURE_2D, g_texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE4,
        texturesize, texturesize, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    g_items = (ctitem_t*)malloc(g_total * sizeof(ctitem_t));
    for(i=0; i<g_total; ++i) {
        g_items[i].valid = 0;
        g_items[i].texcoord_x = (i%g_count * fontsize) / (GLfloat)texturesize;
        g_items[i].texcoord_y = (i/g_count * fontsize) / (GLfloat)texturesize;
    }

    selectFont(fontsize, DEFAULT_CHARSET, font);
}

void ctbuf_destroy(void) {
    glDeleteTextures(1, &g_texID);
    free(g_items);
    g_items = NULL;
    g_count = 0;
    g_total = 0;
    g_fontsize = 0;
    g_texturesize = 0;
}

void ctbuf_bind(void) {
    glBindTexture(GL_TEXTURE_2D, g_texID);
}

const ctitem_t* ctbuf_find(wchar_t c) {
    int i;
    // 寻找是否已经在缓冲中存在
    for(i=0; i<g_total; ++i)
        if( g_items[i].valid && g_items[i].c == c )
            return &g_items[i];

    // 若不存在，寻找空位以便产生新的数据
    for(i=0; i<g_total; ++i)
        if( !g_items[i].valid )
            break;

    // 没有空位，删除一个数据以得到空位
    if( i == g_total ) {
        // 这里随机的删除一个
        i = rand() % g_total;
    }

    // 在空位上产生新的数据
    g_items[i].valid = 1;
    g_items[i].c = c;
    drawChar_To_SubTexture(c,
        (int)(g_items[i].texcoord_x * g_texturesize),
        (int)(g_items[i].texcoord_y * g_texturesize));

    // 返回
    return &g_items[i];
}

void ctbuf_drawString(const char* str, GLfloat cwidth, GLfloat cheight) {
    int i, len;
    wchar_t* wstring;
    GLfloat texinc;

    len = 0;
    for(i=0; str[i]!='\0'; ++i)
    {
        if( IsDBCSLeadByte(str[i]) )
            ++i;
        ++len;
    }

    wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    ctbuf_bind();

    texinc = (GLfloat)g_fontsize / g_texturesize;
    for(i=0; i<len; ++i) {
        const ctitem_t* pItem = ctbuf_find(wstring[i]);
        glBegin(GL_QUADS);
            glTexCoord2f(pItem->texcoord_x, pItem->texcoord_y);
            glVertex2f(cwidth * i, 0.0f);
            glTexCoord2f(pItem->texcoord_x + texinc, pItem->texcoord_y);
            glVertex2f(cwidth * (i+1), 0.0f);
            glTexCoord2f(pItem->texcoord_x + texinc, pItem->texcoord_y + texinc);
            glVertex2f(cwidth * (i+1), cheight);
            glTexCoord2f(pItem->texcoord_x, pItem->texcoord_y + texinc);
            glVertex2f(cwidth * i, cheight);
        glEnd();
    }

    free(wstring);
}

GLfloat ctbuf_texinc() {
    return (GLfloat)g_fontsize / g_texturesize;
}
