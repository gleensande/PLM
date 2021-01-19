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
            for (int j = 0; j < P[i].chip_count; j++) {
                P_with_chips.push_back(i);
            }
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
        }
    }

    return possible_ts;
}

void Petri_net::use_transition(int ts_num, vector<int>& current_chips_pos_in_G) {
    // установка начальных позиций фишек
    // установка начальных позиций фишек
    for (int i = 0; i < P.size(); i++) {
        P[i].chip_count = 0;
    }
    for (int i = 0; i < current_chips_pos_in_G.size(); i++) {
        P[current_chips_pos_in_G[i]].chip_count++;
    }

    // выполнение перехода
    Transition current_ts = T[ts_num];
    for (int i = 0; i < current_ts.input_arcs.size(); i++) {
        P[current_ts.input_arcs[i]].chip_count--;  // Сняли по 1 чипсе с каждой Position на входе в Т
    }
    for (int i = 0; i < current_ts.output_arcs.size(); i++) {
        P[current_ts.output_arcs[i]].chip_count++;  // Добавили по 1 чипсе на каждую Position на выходе из Т
    }

    // обновление вектора весов после выполнения перехода
    vector<pair <int, int> > new_chips_positions;
    vector<int> curr_chips = check_chips();
    new_chips_positions.push_back(make_pair(curr_chips[0], 1));
    for (int i = 1; i < curr_chips.size(); i++) {
        if (curr_chips[i] == curr_chips[i-1]) {
            new_chips_positions[new_chips_positions.size() -1].second++;
        } else {
            new_chips_positions.push_back(make_pair(curr_chips[i], 1));           
        }
    }
    chips_positions = new_chips_positions;
}

void Petri_net::update_chip_position(vector<int>& current_chips_pos_in_G) {
    // установка начальных позиций фишек
    for (int i = 0; i < P.size(); i++) {
        P[i].chip_count = 0;
    }
    for (int i = 0; i < current_chips_pos_in_G.size(); i++) {
        P[current_chips_pos_in_G[i]].chip_count++;
    }

    // обновление вектора весов
    vector<pair <int, int> > new_chips_positions;
    new_chips_positions.push_back(make_pair(current_chips_pos_in_G[0], 1));
    for (int i = 1; i < current_chips_pos_in_G.size(); i++) {
        if (current_chips_pos_in_G[i] == current_chips_pos_in_G[i-1]) {
            new_chips_positions[new_chips_positions.size() -1].second++;
        } else {
            new_chips_positions.push_back(make_pair(current_chips_pos_in_G[i], 1));           
        }
    }
    chips_positions = new_chips_positions;
}
