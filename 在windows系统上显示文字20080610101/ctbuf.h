// ctbuf.h
// 把字符缓存到纹理中

#ifndef _ctbuf_H_
#define _ctbuf_H_

#include <stdlib.h>
#include "GLee.h"
#include <GL/glut.h>
#include <windows.h>

typedef struct __ctitem__ {
    char valid;
    wchar_t c;
    GLfloat texcoord_x;
    GLfloat texcoord_y;
} ctitem_t;

// 初始化
// 可以指定字体大小、纹理大小、字体名称
void ctbuf_init(int fontsize, int texturesize, const char* font);

// 销毁所有资源
void ctbuf_destroy(void);

// 把文字纹理指定为当前纹理
void ctbuf_bind(void);

// 在缓冲中寻找对应文字的纹理
// 如果对应文字的纹理不存在，则生成之
// 可以通过返回值得到纹理坐标，并进行显示
const ctitem_t* ctbuf_find(wchar_t c);

// 绘制字符串
// 会自动调用ctbuf_bind函数
void ctbuf_drawString(const char* str, GLfloat cwidth, GLfloat cheight);

// 取得纹理坐标的增加值，如果本函数返回k，则
// (0, 0), (k, 0), (k, k), (0, k)四个纹理坐标正好表示了一个汉字
GLfloat ctbuf_texinc();

#endif
