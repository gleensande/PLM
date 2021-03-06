#include "graph.hpp"

Graph::Graph() {
    current = -1;
    END.push_back(-1);
    LOOP.push_back(-2);
    POSSIBLE.push_back(-3);
}

void Graph::add_first_vertex(vector<int>& chips_positions) {
    vertices.push_back(chips_positions);
    current = vertices.size() - 1;
}

void Graph::add_possible_arcs_to_current(vector<int>& possible_ts_nums) {
    int possible_i;
    for (int i = 0; i < possible_ts_nums.size(); i++) {
        vertices.push_back(POSSIBLE);
        possible_i = vertices.size() - 1;
        arcs.push_back(make_pair(current, possible_i));
        arcs_values.push_back(possible_ts_nums[i]);
    }
}

void Graph::add_end_arc_to_current() {
    vertices.push_back(END);
    int end_i = vertices.size() - 1;
    arcs.push_back(make_pair(current, end_i));
    arcs_values.push_back(END_T);
}

bool Graph::use_transition(int t_num, vector<int>& chips_positions) {
    int loop_pair;
    for (int i = 0; i < arcs_values.size(); i++) {
        if (arcs[i].first == current && arcs_values[i] == t_num) {
            if ((loop_pair = check_loop(chips_positions)) != -1) {
                vertices[arcs[i].second] = LOOP;
                loops.push_back(make_pair(loop_pair, arcs[i].second));
                return false;
            } else {
                current = arcs[i].second;
                vertices[current] = chips_positions;
            }
        }
    }
    return true;
}

void Graph::print() {
    cout << "Current: " << current << endl;
    cout << "Vertices: " << endl;
    for (int i = 0; i < vertices.size(); i++) {
        cout << i << ". {";
        if (vertices[i][0] < 0) {
            switch(vertices[i][0]) {
                case -1: cout << "END"; break;
                case -2: cout << "LOOP"; break;
                case -3: cout << "POSSIBLE"; break;
            }
        } else {
            for (int j = 0; j < vertices[i].size(); j++) {
                cout << vertices[i][j];
                if (j != vertices[i].size() - 1) {
                    cout << ", ";
                }
            }
        }
        cout << "}" << endl;
    }
    cout << "Arcs: " << endl;
    for (int i = 0; i < arcs.size(); i++) {
        if(arcs_values[i] == END_T){
            cout << arcs[i].first << "----E--->" << arcs[i].second << endl;
        } else {
            cout << arcs[i].first << "----" << arcs_values[i] << "--->" << arcs[i].second << endl;
        }
    }
    cout << endl;
}

int Graph::check_loop(vector<int>& chips_positions) { 
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == chips_positions) {
            return i;
        }
    }
    return -1;
}

int Graph::get_next_transition() {
    for (int i = 0; i < arcs.size(); i++) {
        if (arcs[i].first == current) {
            if (vertices[arcs[i].second] == POSSIBLE) {
                return arcs_values[i];
            }
        }
    }
    return backtrack();
}

int Graph::get_any_possible_arc(int v) {
    for (int i = 0; i < arcs.size(); i++) {
        if (arcs[i].first == v && vertices[arcs[i].second] == POSSIBLE) {
            return i;
        }
    }

    return -1;
}

bool Graph::has_possible_arcs() {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == POSSIBLE) {
            return true;
        }
    }

    return false;
}

int Graph::backtrack() {
    cout << "BACKTRACK:" << endl;
    while(get_any_possible_arc(current) == -1 && has_possible_arcs()) {
        int new_current = -1;
        for (int i = 0; i < arcs.size() && new_current == -1; i++) {
            if (arcs[i].second == current) {
                new_current = arcs[i].first;
            }
        }
        current = new_current;
        cout << current << " ";
    }
    cout << endl;

    if (has_possible_arcs()) {
        return arcs_values[get_any_possible_arc(current)];
    }
    
    return -1;
}

vector<int> Graph::get_current_chips_position() {
    return vertices[current];
}
