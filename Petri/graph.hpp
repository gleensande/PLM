#pragma once
#include <iostream>
#include <vector>

using namespace std;

#define END_T -1

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
    void add_end_arc_to_current();
    bool use_transition(int t_num, vector<int>& chips_positions);
    void print();
    int check_loop(vector<int>& chips_positions);
    int get_next_transition();
    int get_any_possible_arc(int v);
    bool has_possible_arcs();
    int backtrack();
    vector<int> get_current_chips_position();
};
