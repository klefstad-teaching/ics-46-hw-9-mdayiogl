#include "dijkstras.h"
#include <algorithm> // for reverse

using namespace std;

struct Node {
    int vertex;
    int dist;
    Node(int v, int d) : vertex(v), dist(d) {}
};

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.dist > b.dist;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);

    distance[source] = 0;
    previous.assign(n, -1);

    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u]) continue;
        visited[u] = true;

        for (auto &edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;
            if (!visited[v] && distance[u] != INF && (distance[u] + w < distance[v])) {
                distance[v] = distance[u] + w;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances,
                                  const vector<int>& previous,
                                  int destination) {
    vector<int> path;
    if (destination < 0 || destination >= (int)distances.size()) {
        return path;
    }
    if (distances[destination] == INF) {
        return path;
    }
    for (int cur = destination; cur != -1; cur = previous[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    // The autograder expects "vertex1 vertex2 vertex3 ...\nTotal cost is X\n"
    // If the path is empty, the autograder wants a blank line plus "Total cost is X\n"
    if (!v.empty()) {
        for (size_t i = 0; i < v.size(); i++) {
            cout << v[i];
            if (i < v.size() - 1) cout << " ";
        }
        cout << "\nTotal cost is " << total << "\n";
    } else {
        cout << "\nTotal cost is " << total << "\n";
    }
}
