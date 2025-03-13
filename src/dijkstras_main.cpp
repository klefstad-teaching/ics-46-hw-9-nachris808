#include "dijkstras.h"

int main(){
    Graph G;
    file_to_graph("src/small.txt", G);
    vector<int> prev;
    int source = 0;
    int dest = 3;
    vector <int> dist = dijkstra_shortest_path(G, 0, prev);
    vector<int> path = extract_shortest_path(dist, prev, dest);
    print_path(path, 0);

    return 0;
}