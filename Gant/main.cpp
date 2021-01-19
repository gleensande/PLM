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

    Gant.print_graph();
    int start = Gant.search_earliest_task();
    int end = Gant.search_latest_task();
    cout << start << " " << end << endl;
    int result = Gant.BFS(start, end);
    cout << result << endl;
    return 0;
}