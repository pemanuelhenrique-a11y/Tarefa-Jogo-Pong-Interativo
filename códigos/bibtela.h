#ifndef _BIBTELA
#define _BIBTELA

/*
* Includes
*/
#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>

/*
* Function prototypes
*/
void init_screen(int x, int y);
void end_screen(void);
void clear_screen(void);
void xygoto(int x, int y);
int xyprint(int x, int y, const char* str);
void xyprintch(int x, int y, const char ch);
void xyprintint(int x, int y, const char* mask, const int num);
void xyprintfloat(int x, int y, const char* mask, const float num);

void xyhline(int x, int y1, int y2, const char *ch);
void xyvline(int y, int x1, int x2, const char *ch);
void xywindow(int x1, int y1, int x2, int y2, int border);
void xyscanfstr(int x, int y, const char* mask, char* str);
void xyscanfint(int x, int y, const char* mask, int* number);
void xyscanfloat(int x, int y, const char* mask, float* number);
char xygetch(int x, int y);

#endif
