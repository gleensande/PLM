#include "petri_net.hpp"
#include <set>

void Petri_net::read_from_file(string filename) {
    ifstream input;
    input.open(filename);
    if (!input) {
        cout << "ERROR: can't open file " << filename << endl;
        return;
    }

    int P_count, T_count;
    input >> P_count >> T_count;

    P.resize(P_count);
    for(int i = 0; i < P.size(); i++) {
        P[i].chip_count = 0;
    }
    T.resize(T_count);

    string from;
    int i_from, i_to;
    while (input >> from >> i_from >> i_to) {
        if (from == "P") {
            P[i_from].output_arcs.push_back(i_to);
            T[i_to].input_arcs.push_back(i_from);
        } else if (from == "T") {
            T[i_from].output_arcs.push_back(i_to);
            P[i_to].input_arcs.push_back(i_from);
        }
    }

    input.close();
}

void Petri_net::print() {
    cout << "T" << endl;
    for (int i = 0; i < T.size(); i++) {
        cout << "i: " << i << endl;
        cout << "input" << endl;
        for (int j = 0; j < T[i].input_arcs.size(); j++) {
            cout << T[i].input_arcs[j] << " ";
        }
        cout << endl;
        cout << "output" << endl;
        for (int j = 0; j < T[i].output_arcs.size(); j++) {
            cout << T[i].output_arcs[j] << " ";
        }
        cout << endl;
        cout << endl;
    }

    cout << "P" << endl;
    for (int i = 0; i < P.size(); i++) {
        cout << "i: " << i << endl;
        if(P[i].chip_count != 0) {
            cout << "Chips: " << P[i].chip_count << endl;
        }
        cout << "input" << endl;
        for (int j = 0; j < P[i].input_arcs.size(); j++) {
            cout << P[i].input_arcs[j] << " ";
        }
        cout << endl;
        cout << "output" << endl;
        for (int j = 0; j < P[i].output_arcs.size(); j++) {
            cout << P[i].output_arcs[j] << " ";
        }
        cout << endl;
        cout << endl;
    }
}

void Petri_net::set_start_chips(vector<pair <int, int> > start_chips) {
    for (int i = 0; i < start_chips.size(); i++) {
        int n = start_chips[i].first;
        P[n].chip_count = start_chips[i].second;
        chips_positions.push_back(make_pair(n, start_chips[i].second));
    }
}

vector<int> Petri_net::check_chips() {
    vector<int> P_with_chips;
    for (int i = 0; i < P.size(); i++) {
        if (P[i].chip_count != 0) {
            P_with_chips.push_back(i);
        }
    }
    return P_with_chips;
}

bool Petri_net::is_chips_in_P(int position) {
    bool result = false;
    for (int i = 0; i < chips_positions.size(); i++) {
        if (chips_positions[i].first == position) {
            result = true;
        }
    }
    return result;
}

bool Petri_net::check_transition_use(Transition transition) {
    bool is_ok = true;
    for (int i = 0; i < transition.input_arcs.size(); i++) {
        if(!is_chips_in_P(transition.input_arcs[i])) {
            is_ok = false;
        }
    }
    return is_ok;
}


vector<int> Petri_net::check_possible_ts() {
    set<int> ts;  // Доступные направления Т
    int position;  
    for (int i = 0; i < chips_positions.size(); i++) {
        position = chips_positions[i].first;  // Текущая позиция чипса
        vector<int> P_arcs_out = P[position].output_arcs;  // Направления движения в Т для текущего чипса
        for (int j = 0; j < P_arcs_out.size(); j++) {
            ts.insert(P_arcs_out[j]);
        }
    }

    vector<int> possible_ts;
    for (auto t : ts) {
        if (check_transition_use(T[t])) {  // Проверка, можно ли пройти через Т
            possible_ts.push_back(t);
            cout << t << endl;
        }
    }

    return possible_ts;
}