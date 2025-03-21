#include "dijkstras.h"

int main(){
    Graph G;
    file_to_graph("src/small.txt", G);
    vector<int> prev(G.size());
    int source = 0;
    int dest = 2;
    vector <int> dist = dijkstra_shortest_path(G, source, prev);
    //print_path(dist, dist[dest]);
    vector<int> path = extract_shortest_path(dist, prev, dest);
    print_path(path, dist[dest]);
    return 0;
}