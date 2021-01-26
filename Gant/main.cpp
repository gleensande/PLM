#include <iostream>
#include <fstream>
#include <string>
#include "graph.hpp"

using namespace std;

int main() {
    string filename = "input.txt";
    ifstream input;
    input.open(filename);
    if (!input) {
        cout << "ERROR: can't open file " << filename << endl;
        return 0;
    }

    int tasks_count;
    input >> tasks_count;
    CListGraph Gant(tasks_count);
    
    string task_name;
    int task_i, task_start_time, task_end_time;
    task_i = 0;
    while(input >> task_name >> task_start_time >> task_end_time) {
        Task t;
        t.create(task_name, task_start_time, task_end_time);
        Gant.set_task(task_i, t);
        task_i++;
    }
    input.close();

    filename = "edges.txt";
    input.open(filename);
    if (!input) {
        cout << "ERROR: can't open file " << filename << endl;
        return 0;
    }

    int v1, v2;
    while(input >> v1 >> v2) {
        Gant.AddEdge(v1, v2);
    }
    input.close();

    int max = 0, i_max, j_max, length;
    for (int i = 0; i < tasks_count; i++) {
        for (int j = 0; j < tasks_count; j++) {
            length = -Gant.BFS(i, j);
            if (length > max && length != INT_MAX) {
                i_max = i;
                j_max = j;
                max = length;
            }
        }
    }

    cout << "Длина критического пути: " << max << endl << endl;
    cout << "Критический путь найден между задачами: " << endl;
    Gant.get_task(i_max).print();
    Gant.get_task(j_max).print();
    cout << endl;

    vector<int> path = Gant.BFS_path(i_max, j_max);
    cout << "Путь :" << endl;
    for (int i = path.size() - 1; i >= 0; i--) {
        Gant.get_task(path[i]).print();
    }
    cout << endl;


    return 0;
}