#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "transition.hpp"
#include "position.hpp"

using namespace std;

class Petri_net {
 private:
    vector<Position> P;
    vector<Transition> T;
 public:
    void use_transition(int T_num);
    void read_from_file(string filename = "input.txt");
    void print();
    void set_start_chips(vector<pair <int, int> > start_chips);
};