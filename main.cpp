#include "petri_net.hpp"

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
}