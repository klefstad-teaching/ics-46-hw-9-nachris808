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
    previous[source] = INF; 
    priority_queue<pair<int,int>, vector<pair<int,int>>, compare_weight> minHeap; //<vertex,weight>
    minHeap.push({source,0});  //0,0 currently
    while (!minHeap.empty()){
        int u = minHeap.top().first;
        cout << "MinHeap top vertex: " << u << endl;
        minHeap.pop();
        if (visited[u]) 
            continue;
        visited[u] = true;
        for (Edge edge: G[u]){
            int v = edge.dst;
            cout << "edge.dst: " << v << endl;
            int weight = edge.weight;
            cout << "edge.weight: " << weight << endl;
            if (!visited[v] && distances[u] + weight < distances[v]){
                cout << "distances[" << v << "] before: " << distances[v] << endl;
                distances[v] = distances[u] + weight;
                cout << "distances[" << v << "] after: " << distances[v] << endl;
                previous[v] = u;
                minHeap.push({v,distances[v]});
            } 
        }
    }    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    int cost = distances.at(destination);
    
    vector<int> path;
    path.push_back(destination);
    for(int i = destination; previous[i] != INF; i = previous[i]){
        path.push_back(previous.at(i));
    }

    return path;
}

void print_path(const vector<int>& v, int total){
    for (auto i : v){
        cout << i << " ";
    }
    if (total == INF) 
        cout << "No word ladder found";
    else
        cout << "Total cost is " << total << endl;
    cout << endl;
}