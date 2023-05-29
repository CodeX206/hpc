#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void dfs(vector<vector<int>>& graph, vector<bool>& visited, int node) {
    visited[node] = true;
    cout << node << " "; 

    #pragma omp parallel for
    for (int next_node : graph[node]) {
        if (!visited[next_node]) {
            dfs(graph, visited, next_node);
        }
    }
}

int main() {
    int n, m; 
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> graph(n + 1); 
    vector<bool> visited(n + 1, false); 

    cout << "Enter the edges: " << endl;
    for (int i = 1; i <= m; i++) {
        int u, v; 
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start_node; // start node of DFS
    cout << "Enter the start node: ";
    cin >> start_node;

    double start_time = omp_get_wtime();

    cout << "DFS traversal starting from node " << start_node << ": ";
    dfs(graph, visited, start_node);
    cout << endl;

    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    cout << "Execution time: " << execution_time << " seconds" << endl;

    return 0;
}