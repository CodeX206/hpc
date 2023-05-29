#include <omp.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int num_vertices, num_edges, source;
    cout << "Enter the number of nodes and edges: ";
    cin >> num_vertices >> num_edges;

    vector<vector<int>> adj_list(num_vertices + 1);
    cout << "Enter the edges:" << endl;
    for (int i = 0; i < num_edges; i++) {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    
    cout << "Enter the start node: ";
    cin >> source;

    queue<int> q;
    vector<bool> visited(num_vertices + 1, false);

    double start_time = omp_get_wtime();
    q.push(source);
    visited[source] = true;
	
    while (!q.empty()) {
        int level_size = q.size();

        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < level_size; i++) {
                int curr_vertex;
                #pragma omp critical
                {
                    curr_vertex = q.front();
                    q.pop();
                }

                cout << curr_vertex << " ";

                for (int j = 0; j < adj_list[curr_vertex].size(); j++) {
                    int neighbour = adj_list[curr_vertex][j];
                    #pragma omp critical
                    {
                        if (!visited[neighbour]) {
                            visited[neighbour] = true;
                            q.push(neighbour);
                        }
                    }
                }
            }
        }
    }

    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    cout << "Execution time: " << execution_time << " seconds" << endl;

    return 0;
}
