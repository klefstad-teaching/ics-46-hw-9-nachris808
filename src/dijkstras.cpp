#include "dijkstras.h"
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.size();
    vector<int> distances(numVertices,INF);
    vector<bool> visited(numVertices,false);
    distances[source] = 0;
    previous[source] = -1;
    priority_queue<pair<int, int>> minHeap; //<vertex,weight>
    minHeap.push({source,0});  //0,0 currently
    while (!minHeap.empty()){
        int u = minHeap.top().first;
        cout << "MinHeap top vertex: " << u << endl;
        minHeap.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge edge: G[u]){
            int v = edge.dst;
            cout << "edge.dst: " << v << endl;
            int weight = edge.weight;
            cout << "edge.weight: " << weight << endl;
            if (!visited[v] && distances[u] + weight < distances[v]){
                cout << "distances[v] before: " << distances[v] << endl;
                distances[v] = distances[u] + weight;
                cout << "distances[v] after: " << distances[v] << endl;
                previous[v] = u;
                minHeap.push({v,distances[v]});
            } 
        }
    }    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
return distances;
}

void print_path(const vector<int>& v, int total){
    int sum = 0;
    for (auto i : v){
        cout << v[i] << " ";
        sum += v[i];
    }
    cout << endl;
    cout << "Total cost is " << sum << endl;
}