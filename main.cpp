#include "petri_net.hpp"
#include "graph.hpp"

int main() {
    Petri_net P;
    P.read_from_file();

    cout << "Введите номера позиций и сколько в ней фишек:" << endl;
    vector<pair <int, int> > start_chips;
    int v, chip_num;
    while(cin) {
        cin >> v >> chip_num;
        start_chips.push_back(make_pair(v, chip_num));
    }
    P.set_start_chips(start_chips);
    P.print();

    Graph G;

    vector<int> chips_positions = {5, 6};
    G.add_first_vertex(chips_positions);
    G.print();

    vector<int> possible_ts_nums = {1, 5};
    G.add_possible_arcs_to_current(possible_ts_nums);
    G.print();

    int t_num = 1;
    vector<int> chips_positions_1 = {1, 5};
    G.use_transition(t_num, chips_positions_1);
    G.print();
}