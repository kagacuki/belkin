#include "lib.h"

int main () {
    //Тесты
     srand(time(NULL));
    Object* dot1 = new Object (1, 2);
    dot1->random_walk();
    dot1->random_walk();
    dot1->path_print();
    dot1->current_pos_check();
    int x=1, y=1;
    dot1->distance_check(x, y);
}