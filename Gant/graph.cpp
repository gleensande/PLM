#include "graph.hpp"

// конструктор графа по количеству вершин
CListGraph::CListGraph(size_t vertices_count) {
    edges_.resize(vertices_count);
    tasks.resize(vertices_count);
}

// добавление связи между вершиной номер v1 и номер v2
void CListGraph::AddEdge(int v1, int v2) {
    edges_[v1].push_back(v2);
}

// получение всех вершин, связанных с данной
vector<int> CListGraph::GetConnectedVertices(int vertex) const {
    vector<int> vertices = edges_[vertex];
    return vertices;
}

// обход графа
int CListGraph::BFS(int start_vertex, int stop_vertex) {
    queue<int> q;
    vector<bool> visited(VerticesCount(), false);    
    vector<int> s(VerticesCount(), INT_MAX);
    vector<int> p(VerticesCount(), 0);

    q.push(start_vertex);
    visited[start_vertex] = true;
    s[start_vertex] = 0;
    p[start_vertex] = 1;

    int current = start_vertex;
    while(!q.empty()) {
        current = q.front();
        q.pop();
        
        vector<int> neighbours = GetConnectedVertices(current);
        for (int i = 0; i < neighbours.size(); i++) {
			int neighbour = neighbours[i];
            if (visited[neighbour] == false) {
                if (s[current] + 1 < s[neighbour]) {
                    p[neighbour] = p[current];
                    s[neighbour] = s[current] + 1;
                    q.push(neighbour);
                } else if (s[current] + 1 == s[neighbour]) {
                    p[neighbour] += p[current];
                }
            }
        }

        visited[current] = true;
    }
    for (int i = 0; i < p.size(); i++) {
        cout << p[i] << endl;
    }
    return s[stop_vertex];
}

// получение количества всех вершин графа
int CListGraph::getVerticesCount() const {
	return edges_.size();
}

Task CListGraph::get_task(int i) {
    return tasks[i];
}

void CListGraph::set_task(int i, Task t) {
    tasks[i] = t;
}

int CListGraph::search_earliest_task() {
    int min_start_time = 1000000;
    int index, temp;
    for (int i = 0; i < tasks.size(); i++) {
        temp = tasks[i].get_start_time();
        if (temp < min_start_time) {
            min_start_time = temp;
            index = i;
        }
    }
    return index;
}

int CListGraph::search_latest_task() {
    int max_end_time = 0;
    int index, temp;
    for (int i = 0; i < tasks.size(); i++) {
        temp = tasks[i].get_end_time();
        if (temp > max_end_time) {
            max_end_time = temp;
            index = i;
        }
    }
    return index;
}

void CListGraph::print_graph() {
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << i << " "; 
        tasks[i].print_data();
    }
}

// пример использования графа
int example() {
    int v;
    cin >> v;

    int n;
    cin >> n;

    CListGraph graph(v);

    int v1, v2;
    for (int i = 0; i < n; i++) {
        cin >> v1 >> v2;
        graph.AddEdge(v1, v2);
    }

    int u, w;
    cin >> u >> w;
    cout << graph.BFS(u, w) << endl;

    return 0;
}
