// ctbuf.h
// ���ַ����浽������

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

// ��ʼ��
// ����ָ�������С�������С����������
void ctbuf_init(int fontsize, int texturesize, const char* font);

// ����������Դ
void ctbuf_destroy(void);

// ����������ָ��Ϊ��ǰ����
void ctbuf_bind(void);

// �ڻ�����Ѱ�Ҷ�Ӧ���ֵ�����
// �����Ӧ���ֵ��������ڣ�������֮
// ����ͨ������ֵ�õ��������꣬��������ʾ
const ctitem_t* ctbuf_find(wchar_t c);

// �����ַ���
// ���Զ�����ctbuf_bind����
void ctbuf_drawString(const char* str, GLfloat cwidth, GLfloat cheight);

// ȡ���������������ֵ���������������k����
// (0, 0), (k, 0), (k, k), (0, k)�ĸ������������ñ�ʾ��һ������
GLfloat ctbuf_texinc();

#endif
