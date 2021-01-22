#include "graph.hpp"

// конструктор графа по количеству вершин
CListGraph::CListGraph(size_t vertices_count) {
    edges.resize(vertices_count);
    tasks.resize(vertices_count);
    visited.resize(vertices_count, false);
}

// добавление связи между вершиной номер v1 и номер v2
void CListGraph::AddEdge(int v1, int v2) {
    edges[v1].push_back(v2);
}

// получение всех вершин, связанных с данной
vector<int> CListGraph::GetConnectedVertices(int vertex) const {
    vector<int> vertices = edges[vertex];
    return vertices;
}

// получение количества всех вершин графа
int CListGraph::getVerticesCount() const {
	return edges.size();
}

Task CListGraph::get_task(int i) {
    return tasks[i];
}

void CListGraph::set_task(int i, Task t) {
    tasks[i] = t;
}

void CListGraph::print_graph() {
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << i << " "; 
        tasks[i].print();
    }
}

void CListGraph::DFS(/*int start, int finish*/) {
    stack<int> s;
    int strat_v = 0;
    s.push(strat_v);

    while (!s.empty()) {
        int vertex = s.top();
        s.pop();
        cout << vertex << endl;
        int out_count = 0;
        for (int i = 0; i < edges[vertex].size(); i++) {
            if (visited[edges[vertex][i]] == false) {
                s.push(edges[vertex][i]);
                visited[edges[vertex][i]] = true;
                out_count++;
            }
        }
        if (out_count == 0) 
            topological.push_back(vertex);
    }
}

// обход графа
int CListGraph::BFS(int start_vertex, int stop_vertex) {
    queue<int> q;
    vector<bool> visited(VerticesCount(), false);    
    vector<int> s(VerticesCount(), INT_MAX);
    vector<int> p(VerticesCount(), 0);

    q.push(start_vertex);
    visited[start_vertex] = true;
    s[start_vertex] = -tasks[start_vertex].get_weight();
    p[start_vertex] = -1;

    int current = start_vertex;
    while(!q.empty()) {
        current = q.front();
        q.pop();
        
        vector<int> neighbours = GetConnectedVertices(current);
        for (int i = 0; i < neighbours.size(); i++) {
			int neighbour = neighbours[i];
            if (visited[neighbour] == false) {
                int weight = -((tasks[neighbour].get_start_time() - tasks[current].get_end_time()) + tasks[neighbour].get_weight());
                if (s[current] + weight < s[neighbour]) {
                    p[neighbour] = p[current];
                    s[neighbour] = s[current] + weight;
                    q.push(neighbour);
                }
            }
        }

        visited[current] = true;
    }

    return s[stop_vertex];
}

// обход графа
vector<int> CListGraph::BFS_path(int start_vertex, int stop_vertex) {
    queue<int> q;
    vector<bool> visited(VerticesCount(), false);    
    vector<int> s(VerticesCount(), INT_MAX);
    vector<int> p(VerticesCount(), 0);

    q.push(start_vertex);
    visited[start_vertex] = true;
    s[start_vertex] = tasks[start_vertex].get_weight();
    p[start_vertex] = -1;

    int current = start_vertex;
    while(!q.empty()) {
        current = q.front();
        q.pop();
        
        vector<int> neighbours = GetConnectedVertices(current);
        for (int i = 0; i < neighbours.size(); i++) {
			int neighbour = neighbours[i];
            if (visited[neighbour] == false) {
                int weight = (tasks[neighbour].get_start_time() - tasks[current].get_end_time()) + tasks[neighbour].get_weight();
                if (s[current] + weight < s[neighbour]) {
                    p[neighbour] = current;
                    s[neighbour] = s[current] + weight;
                    q.push(neighbour);
                }
            }
        }

        visited[current] = true;
    }

    vector<int> path;
    if (!visited[stop_vertex])
        return {-1};
    else {
        for (int v = stop_vertex; v != -1; v = p[v]) {
            path.push_back(v);
        }
    }

    return path;
}