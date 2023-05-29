#include "mylib.h"

Pt* random_walk (Pt *obj) {
    int t_x = rand()%100 - 50; 
    int t_y = rand()%100 - 50;
    int S_x = fabs(obj->x) + fabs(t_x);
    int S_y = fabs(obj->y) + fabs(t_y);

    obj->x = t_x;
    obj->y = t_y;
    obj->way = obj->way + S_x + S_y;
    //Функция должна менять way
    return obj;
}

void point_show (Pt *obj) {
    cout 
    << "\nВ настоящее время точка имеет такие данные: "
    << "\nКоордината x: " << obj->x
    << "\nКоордината y: " << obj->y
    << "\nПройденный путь: " << obj->way
    << endl;
}

void menu_func (Pt *obj) {
    int ch, wh = 1;
    point_show(obj);
    cout 
    << "\nМеню: "
    << "\n1. Сдвинуть точку на другую (случайную) позицию."
    << "\n2. Выйти из программы." << endl;
    while (wh == 1) {
        cin >> ch;
        switch (ch)
        {
        case 1:
            random_walk(obj);
            point_show(obj);
            break;
        case 2:
        wh = 0;
            break;
        }
    }
}