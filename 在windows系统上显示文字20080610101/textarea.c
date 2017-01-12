#include "textarea.h"

#include "ctbuf.h"

#include <stdlib.h>
#include <math.h>

textarea_t* ta_create(
    GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y,
    int char_in_row, int char_in_col, const char* data) {
    textarea_t* ret = NULL;
    wchar_t* wdata = NULL;
    wchar_t* wdata_start = NULL;

    // 分配内存，填充基本的数据
    ret = (textarea_t*)malloc(sizeof(textarea_t));
    ret->min_x = min_x;
    ret->min_y = min_y;
    ret->max_x = max_x;
    ret->max_y = max_y;
    ret->char_in_row = char_in_row;
    ret->char_in_col = char_in_col;
    ret->scroll_pos = 0.0f;

    // 把参数中的字符串转化为宽字符
    {
        int len = 0;
        int i;
        for(i=0; data[i]!='\0'; ++i)
        {
            if( IsDBCSLeadByte(data[i]) )
                ++i;
            ++len;
        }

        wdata = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
        wdata_start = wdata;
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, data, -1, wdata, len);
        wdata[len] = L'\0';
    }

    // 把参数中的字符串拆分成多行，每行正好可以够显示
    ret->line_count = 0;
    ret->lines = NULL;
    while( *wdata != L'\0' ) {
        wchar_t* tmpLine = (wchar_t*)malloc(
                (char_in_row + 1) * sizeof(wchar_t));
        wchar_t* s;
        int count = 0;
        for(s=tmpLine; *wdata != L'\0';) {
            wchar_t c;
            *s++ = (c=*wdata++);
            if( ++count == char_in_row || c == L'\n' )
                break;
        }
        *s = L'\0';

        ++ret->line_count;
        ret->lines = (wchar_t**)realloc(
                ret->lines, (ret->line_count) * sizeof(wchar_t*));
        ret->lines[ret->line_count-1] = tmpLine;
    }

    free(wdata_start);

    return ret;
}

void ta_destroy(textarea_t* pta) {
    int i;
    for(i=0; i<pta->line_count; ++i)
        free(pta->lines[i]);
    free(pta);
}

void ta_scroll(textarea_t* pta, GLfloat range) {
    GLfloat char_height = (pta->max_y - pta->min_y) / pta->char_in_col;
    GLfloat max_scroll = char_height * (pta->line_count - 1);
    pta->scroll_pos += range;
    if( pta->scroll_pos < 0.0f )
        pta->scroll_pos = 0.0f;
    if( pta->scroll_pos > max_scroll )
        pta->scroll_pos = max_scroll;
}

void ta_display(textarea_t* pta) {
    int i, start;
    GLfloat texinc = ctbuf_texinc();

    GLfloat char_height = (pta->max_y - pta->min_y) / pta->char_in_col;
    GLfloat char_width = (pta->max_x - pta->min_x) / pta->char_in_row;
    GLfloat char_scroll = fmod(pta->scroll_pos, char_height);

    // 计算开始显示的行数
    start = (int)(pta->scroll_pos/char_height);

    // 显示每一行的字符
    for(i=0; i<=pta->char_in_col && i+start<pta->line_count; ++i) {
        const wchar_t* p = pta->lines[i+start];
        int j = 0;
        for(; *p!=L'\0'; ++p, ++j) {
            const ctitem_t* pItem = ctbuf_find(*p);
            glBegin(GL_QUADS);
                glTexCoord2f(pItem->texcoord_x, pItem->texcoord_y);
                glVertex2f(
                    char_width * j + pta->min_x,
                    pta->max_y - char_height * (i+1) + char_scroll);
                glTexCoord2f(pItem->texcoord_x + texinc, pItem->texcoord_y);
                glVertex2f(
                    char_width * (j+1) + pta->min_x,
                    pta->max_y - char_height * (i+1) + char_scroll);
                glTexCoord2f(pItem->texcoord_x + texinc, pItem->texcoord_y + texinc);
                glVertex2f(
                    char_width * (j+1) + pta->min_x,
                    pta->max_y - char_height * i + char_scroll);
                glTexCoord2f(pItem->texcoord_x, pItem->texcoord_y + texinc);
                glVertex2f(
                    char_width * j + pta->min_x,
                    pta->max_y - char_height * i + char_scroll);
            glEnd();
        }
    }
}
