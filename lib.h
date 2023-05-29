#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Coordinates {
    public:
    int x;
    int y;
    int distance_check (int obj_x, int obj_y); 
};

class Object : public Coordinates {
    private:
    int way = 0;
    public:
    vector <int> path_x, path_y;
    Object (int p_x, int p_y);
    void path_print ();
    void random_walk ();
    void current_pos_check ();
};