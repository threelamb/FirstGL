#ifndef _textarea_H_
#define _textarea_H_

#include <stdlib.h>
#include "GLee.h"
#include <GL/glut.h>
#include <windows.h>

typedef struct __textarea__ {
    // ��ʾ����
    GLfloat min_x;
    GLfloat min_y;
    GLfloat max_x;
    GLfloat max_y;

    // ������ʾ��������
    int char_in_row;
    int char_in_col;

    // ����λ��
    GLfloat scroll_pos;

    // ������
    int line_count;

    // ÿ�е��ַ���lines[i]��ʾ��i���ַ�
    wchar_t** lines;
} textarea_t;

// ����һ���µ��ַ�����
// ָ������Χmin_x, min_y, max_x, max_y
// ָ��ÿ�п���ʾ�ַ���char_in_row��ÿ�п���ʾ�ַ���char_in_col
// ָ��һ���ַ��������Ժܳ������Ի��У�
textarea_t* ta_create(
        GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y,
        int char_in_row, int char_in_col, const char* data);

// ����һ���ַ�����
void ta_destroy(textarea_t* pta);

// ����
void ta_scroll(textarea_t* pta, GLfloat range);

// ��ʾ�ַ�����
void ta_display(textarea_t* pta);

#endif
