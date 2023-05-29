#ifndef MYLIB_H
#define MYLIB_H
#include <iostream>
#include <math.h>

using namespace std;
typedef struct point {
    int x;
    int y;
    int way;
}Pt;

Pt *random_walk (Pt *obj);
void point_show (Pt *obj);
void menu_func (Pt *obj);
#endif // MYLIB_H