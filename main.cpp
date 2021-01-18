#include "petri_net.hpp"
#include "graph.hpp"

int main() {
    // создание сети Петри
    Petri_net P;
    P.read_from_file();

    // задание начальных данных
    //cout << "Введите номера позиций и сколько в ней фишек:" << endl;
    vector<pair <int, int> > start_chips;
    /*int v, chip_num;
    while(cin) {
        cin >> v >> chip_num;
        start_chips.push_back(make_pair(v, chip_num));
    }*/
    start_chips.push_back(make_pair(4, 1));
    start_chips.push_back(make_pair(5, 1));
    P.set_start_chips(start_chips);

    // создание графа результата и его заполнение
    Graph G;

    // добавление первой вершины в граф
    vector<int> chips_positions = P.check_chips();
    G.add_first_vertex(chips_positions);
    G.print();

    bool stop = false;
    vector<int> possible_ts_nums, current_chips_position_in_G;
    int next_ts;
    while (!stop) {
        // добавление возможных переходов (Transitions)
        cout << "ADD POSIBLES:" << endl;
        possible_ts_nums = P.check_possible_ts();
        cout << "possible_ts" << endl;
        for (int i = 0; i < possible_ts_nums.size(); i++) {
            cout << possible_ts_nums[i] << " ";
        }
        cout << endl;
        if (possible_ts_nums.size() != 0) {
            G.add_possible_arcs_to_current(possible_ts_nums);
        } else {
            G.add_end_arc_to_current();
        }
        G.print();

        // получение и выполнение следующего перехода
        cout << "USE TRANSITION:" << endl;
        next_ts = G.get_next_transition();
        current_chips_position_in_G = G.get_current_chips_position();
        cout << "Newx T = " << next_ts << endl;
        if (next_ts == -1) {
            stop = true;
        } else {
            P.use_transition(next_ts, current_chips_position_in_G);
            chips_positions = P.check_chips();
            cout << "Chips_positions" << endl;
            for (int i = 0; i < chips_positions.size(); i++) {
                cout << chips_positions[i] << " ";
            }
            cout << endl;
            if (!G.use_transition(next_ts, chips_positions)) {
                current_chips_position_in_G = G.get_current_chips_position();
                //P.use_transition(next_ts, current_chips_position_in_G);
            }
            G.print();
        }
    }

    G.print();
}