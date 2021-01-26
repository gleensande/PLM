#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include "task.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::stack;


class CListGraph {
 private:
    vector<Task> tasks;
    vector<vector<int>> edges;
    vector<bool> visited;
    // vector<int> topological;
 public:
    CListGraph(size_t vertices_count);
    void AddEdge(int v1, int v2);
    int VerticesCount() const { return edges.size(); }
    vector<int> GetConnectedVertices(int vertex) const;
	int getVerticesCount() const;
    void set_task(int i, Task t);
    Task get_task(int i);
    void print_graph();
    // void DFS();
    int BFS(int start_vertex, int stop_vertex);
    vector<int> BFS_path(int start_vertex, int stop_vertex);
};
