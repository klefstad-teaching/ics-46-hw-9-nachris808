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
    minHeap.push({source,0});  
    while (!minHeap.empty()){
        int u = minHeap.top().first;
        minHeap.pop();
        if (visited[u]) 
            continue;
        visited[u] = true;
        for (Edge edge: G[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v,distances[v]});
            } 
        }
    }    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    
    vector<int> path;
    path.push_back(destination);
    for(int i = destination; previous[i] != INF; i = previous[i]){
        path.push_back(previous.at(i));
    }
    reverse(path.begin(),path.end()); 
    return path;
}

void print_path(const vector<int>& v, int total){
    for (auto i : v){
        cout << i << " ";
    }
    cout << endl;
    if (total == INF) 
        cout << "No word ladder found";
    else
        cout << "Total cost is " << total;
    cout << endl;
}