#include "petri_net.hpp"
#include "graph.hpp"

int main() {
    // создание сети Петри
    Petri_net P;
    P.read_from_file();

    // задание начальных данных
    cout << "Введите номера позиций и сколько в ней фишек:" << endl;
    vector<pair <int, int> > start_chips;
    int v, chip_num;
    while(cin) {
        cin >> v >> chip_num;
        start_chips.push_back(make_pair(v, chip_num));
    }
    P.set_start_chips(start_chips);

    // создание графа результата и его заполнение
    Graph G;

    // добавление первой вершины в граф
    vector<int> chips_positions = P.check_chips();
    G.add_first_vertex(chips_positions);
    G.print();

    // добавление возможных переходов (Transitions)
    vector<int> possible_ts_nums = P.check_possible_ts();
    if (possible_ts_nums.size() != 0) {
        G.add_possible_arcs_to_current(possible_ts_nums);
    } else {
        G.add_end_arc_to_current();
    }
    G.print();

    /*int t_num = 1;
    vector<int> chips_positions_1 = {1, 5};
    G.use_transition(t_num, chips_positions_1);
    G.print();*/
}