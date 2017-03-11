#include <iostream>
#include <vector>
#include "graphs.hpp"

using namespace std;

int main()
{
    // Test the graph
    Node node1(1);
    Node node2(2);
    Node node3(3);

    // Create a simple cyclic graph
    node1.add_edge(&node2);
    node2.add_edge(&node3);
    node3.add_edge(&node1);

    vector <Node*> graph;
    graph.push_back(&node1);
    graph.push_back(&node2);
    graph.push_back(&node3);

    // Now, create the start/stop dictionaries
    MapT start_time_map;
    MapT stop_time_map;

    vector <Node*> forest = dfs(graph, start_time_map, stop_time_map);
    cout << "Printing DFS forest: " << endl;
    for (Node *node : forest){
        print_node(*node, 0);
    }
    cout << "Node 1: " << endl;
    cout << "    Start time: " << start_time_map[&node1] << endl;
    cout << "    Stop time: " << stop_time_map[&node1] << endl;
    cout << "Node 2: " << endl;
    cout << "    Start time: " << start_time_map[&node2] << endl;
    cout << "    Stop time: " << stop_time_map[&node2] << endl;
    cout << "Node 3: " << endl;
    cout << "    Start time: " << start_time_map[&node3] << endl;
    cout << "    Stop time: " << stop_time_map[&node3] << endl;
    return 0;
}
