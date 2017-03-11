#include "graphs.hpp"

using namespace std;


void Node::add_edge(Node *neighbor){
    this->adjacency_list.push_back(neighbor);
}

Node::Node(int id){
    this->internal_id = id;
}


// Main DFS implementation
// DFS should return a forest of DFS trees.

vector <Node*> dfs(vector <Node*> &graph, MapT &start_time_map, MapT &stop_time_map){
    // Implements depth-first search on a given graph, input as a vector of nodes
    // It should also take as input unordered maps that map nodes to unsigned integers. As
    // DFS progresses, it will fill these maps with the discovery and end-times of each node

    // We first initialize the start and stop time maps with -1.
    for (Node *node: graph){
        start_time_map[node] = -1;
        stop_time_map[node] = -1;
    }

    // We then initialize the DFS forest to return, which will just be a vector of
    // pointers to Node objects. We also initialize the time to 0.
    vector <Node *> forest;
    int time = 0;

    // Now, we begin DFS in earnest
    for (Node *node: graph){
        if (start_time_map[node] == -1){
            // We have not discovered this node yet. Therefore, this node will become a root
            // in our DFS forest.
            Node *dfs_node = new Node(node->internal_id);
            forest.push_back(dfs_node);

            start_time_map[node] = ++time;
            // perform DFS visit here
            dfs_visit(*node, *dfs_node, start_time_map, stop_time_map, time);
            stop_time_map[node] = ++time;
        }
    }
    return forest;
}


void dfs_visit(Node &predecessor, Node &dfs_parent, MapT &start_time_map, MapT &stop_time_map, int &time){
    for (Node *neighbor: predecessor.adjacency_list){
        if (start_time_map[neighbor] == -1){
            // Node has not been discovered.
            Node *dfs_child = new Node(neighbor->internal_id);
            dfs_parent.add_edge(dfs_child);

            start_time_map[neighbor] = ++time;
            dfs_visit(*neighbor, *dfs_child, start_time_map, stop_time_map, time);
            stop_time_map[neighbor] = ++time;
        }
    }
}


void print_node(Node &node, unsigned int level){
    for (unsigned int i; i < level; i++)
    {
        cout << "    ";
    }
    cout << "Node with internal-id: " << node.internal_id << "Linked to: " << endl;
    for (Node *neighbor: node.adjacency_list){
        print_node(*neighbor, level + 1);
    }
}
