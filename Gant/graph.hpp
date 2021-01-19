#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "task.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;


// класс неориентированного графа, основанный на списках
class CListGraph {
 public:
    CListGraph(size_t vertices_count);
    void AddEdge(int v1, int v2);
    int VerticesCount() const { return edges_.size(); }
    vector<int> GetConnectedVertices(int vertex) const;
    int BFS(int start_vertex, int stop_vertex);
	int getVerticesCount() const;
    void set_task(int i, Task t);
    Task get_task(int i);
    void print_graph();
    int search_earliest_task();
    int search_latest_task();
 private:
    vector<Task> tasks;
    vector<vector<int>> edges_;
};
