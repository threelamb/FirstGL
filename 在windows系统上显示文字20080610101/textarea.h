#ifndef _textarea_H_
#define _textarea_H_

#include <stdlib.h>
#include "GLee.h"
#include <GL/glut.h>
#include <windows.h>

typedef struct __textarea__ {
    // 显示区域
    GLfloat min_x;
    GLfloat min_y;
    GLfloat max_x;
    GLfloat max_y;

    // 可以显示的行列数
    int char_in_row;
    int char_in_col;

    // 滚动位置
    GLfloat scroll_pos;

    // 总行数
    int line_count;

    // 每行的字符，lines[i]表示第i行字符
    wchar_t** lines;
} textarea_t;

// 创建一个新的字符区域
// 指定区域范围min_x, min_y, max_x, max_y
// 指定每行可显示字符数char_in_row，每列可显示字符数char_in_col
// 指定一个字符串（可以很长，可以换行）
textarea_t* ta_create(
        GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y,
        int char_in_row, int char_in_col, const char* data);

// 销毁一个字符区域
void ta_destroy(textarea_t* pta);

// 滚动
void ta_scroll(textarea_t* pta, GLfloat range);

// 显示字符区域
void ta_display(textarea_t* pta);

#endif
