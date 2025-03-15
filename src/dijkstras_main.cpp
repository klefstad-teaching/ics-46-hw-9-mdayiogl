#include "dijkstras.h"

int main() {
    cout << "Enter graph filename: ";
    string filename;
    cin >> filename;

    Graph G;
    try {
        file_to_graph(filename, G);
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> dist = dijkstra_shortest_path(G, 0, previous);

    for (int v = 0; v < G.numVertices; v++) {
        cout << "Shortest path from 0 to " << v << ": ";
        vector<int> path = extract_shortest_path(dist, previous, v);
        if (path.empty()) {
            cout << "No path" << endl;
        } else {
            print_path(path, dist[v]);
        }
    }
    return 0;
}
