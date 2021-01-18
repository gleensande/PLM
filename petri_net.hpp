#pragma once
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
    vector<pair <int, int> > chips_positions;  // < Номер вершины, кол-во чипсов >
 public:
    void use_transition(int T_num, vector<int>& current_chips_pos_in_G);
    void read_from_file(string filename = "input.txt");
    void print();
    void set_start_chips(vector<pair <int, int> > start_chips);
    bool is_chips_in_P(int position);
    vector<int> check_chips();  // Проверка, где находятся чипсы в данный момент 
    vector<int> check_possible_ts();  // Проверка, куда можно двигаться чипсам - номера Т
    bool check_transition_use(Transition transition);  // Проверка наличия достаточного количества чипсов для перехода - 0 или 1
    void update_chip_position(vector<int>& current_chips_pos_in_G);
};