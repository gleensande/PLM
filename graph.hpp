#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Graph {
 private:
    vector<int> END, LOOP, POSSIBLE;

    int current;
    vector<vector <int> > vertices;
    vector<pair <int, int> > arcs;
    vector<int> arcs_values;
    vector<pair <int, int> > loops;
 public:
    Graph();
    void add_first_vertex(vector<int>& chips_positions);
    void add_possible_arcs_to_current(vector<int>& possible_ts_nums);
    void add_end_arcs_to_current(vector<int>& end_ts_nums);
    void use_transition(int t_num, vector<int>& chips_positions);
    void print();
    int check_loop(vector<int>& chips_positions);
    int get_next_transition();
    int backtrack();
};
