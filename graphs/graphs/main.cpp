#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "graphs.hpp"
#include "dijkstra.hpp"

using namespace std;


void graph_problem(){
    cout << "What filename to load> ";
    string graph_filename;
    cin >> graph_filename;
    cout << "Loading graph...\n";

    Graph *graph = load_graph(graph_filename);
    cout << "Loaded " << graph->nodes.size() << " elements\n";
    cout << "Running DFS: first pass\n";
    unordered_map <int, int> finish_order;
    vector <Graph *> dfs_forest = dfs(graph, finish_order);
    cout << "Finished first DFS pass\n";
    cout << "The output DFS forest has " << dfs_forest.size() << " roots\n";

    // In order to induce DFS to run on the graph backwards, we create the
    // reversed-edge graph with nodes in order according to finish_order
    cout << "Constructing reverse-ordered nodes: \n";
    int num_nodes = (int)graph->nodes.size();
    vector <int> reverse_nodes(num_nodes, -1);
    vector <int> indices;
    for (pair <int, int> kv: finish_order){
        int node_id = kv.first;
        int finish_time = kv.second;
        indices.push_back(num_nodes - 1 - finish_time);
        reverse_nodes[num_nodes - 1 - finish_time] = node_id;
    }

    cout << "Inverting edges...\n";
    Graph *reverse_graph = graph->transpose();
    reverse_graph->nodes = reverse_nodes;
    cout << "DFS second pass\n";
    unordered_map <int, int> rev_finish_order;
    vector <Graph *> sccs = dfs(reverse_graph, rev_finish_order);
    cout << "Found " << sccs.size() << " SCCs\n";
    vector <int> scc_sizes;
    int total_in_sccs = 0;
    for (Graph *scc: sccs){
        scc_sizes.push_back(scc->nodes.size());
        total_in_sccs += scc->nodes.size();
    }
    cout << "Total number of nodes in SCCs: " << total_in_sccs << endl;
    cout << "Largest SCC has " << *max_element(scc_sizes.begin(), scc_sizes.end()) << endl;
    sort(scc_sizes.begin(), scc_sizes.end());
    vector <int>::reverse_iterator rit = scc_sizes.rbegin();
    for (int i = 0; i < 7; i++){
        cout << "SCC with size " << *(rit++) << endl;
    }
}


void weighted_graph_problem(){
    WeightedGraph *tempgraph = new WeightedGraph({1, 2, 3, 4});
    tempgraph->add_edge(1, 2, 10.0);
    tempgraph->add_edge(2, 4, 10.0);
    tempgraph->add_edge(1, 3, 5);
    tempgraph->add_edge(3, 4, 20);
    tempgraph->add_edge(3, 2, 1);
    unordered_map <int, double> dist_map;

    DijkstraGraph *shortest_paths_graph = shortest_paths(tempgraph, 1, dist_map);

    for (int node: tempgraph->nodes){
        cout << "Shortest distance from 1 to " << node << " is " << dist_map[node] << endl;
    }
}

int main()
{
    weighted_graph_problem();
}
