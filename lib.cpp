#include "lib.h"

//Конструктор, вектора path_x, path_y - для сохранения пути
Object::Object (int p_x, int p_y) {
    x = p_x;
    y = p_y;
    path_x.push_back(p_x);
    path_y.push_back(p_y);
}

//Вывод пройденного пути
void Object::path_print () {
    cout << "\nВесь пройденный путь: ";
    for (int i = 0; i < path_x.size(); i++)
        cout << "(" << path_x[i] << "," << path_y[i] << ")  "; 
}

//Рандомное перемещение с сохранением пути
void Object::random_walk () {
    int coord_x = rand() % 1000 - 500;
    int coord_y = rand() % 1000 - 500;
    int walked_x = fabs (x) + fabs (coord_x);
    int walked_y = fabs (y) + fabs (coord_y);
    x = coord_x;
    y = coord_y;
    way = way + walked_x + walked_y;
    path_x.push_back(x);
    path_y.push_back(y);
}

//Вывод информации об актуальном положении точки
void Object::current_pos_check () {
    cout << "\nТекущая позиция: (" << x << ", " << y << ")" << endl
    << "Длина пройденного пути: " << way << endl;
}

//Метод для определения расстояния до объекта
int Object::distance_check (int obj_x, int obj_y) {
    float dist; int diff_x, diff_y;
    if (obj_x == x || obj_y == y) 
        dist = fabs (x - obj_x) + fabs (y - obj_y);
    else {
        diff_x = fabs (x - obj_x);
        diff_y = fabs (y - obj_y);
        dist = sqrt (pow(diff_x, 2) + pow(diff_y, 2));
    }
    cout << "\nРасстояние между точкой и объектом составляет " << dist << endl;
    return dist;
}