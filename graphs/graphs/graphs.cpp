#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>

#include "string_utils.hpp"
#include "graphs.hpp"

using namespace std;


Graph::Graph(vector <int> nodes){
    this->nodes = nodes;
    for (int node_id: nodes){
        this->edges[node_id] = new vector <int>;
    }
}

Graph *Graph::transpose(){
    Graph *transposed_graph = new Graph(this->nodes);
    for (auto kv: this->edges){
        int node = kv.first;
        vector <int> *adjacency_list = kv.second;

        for (int neighbor: *adjacency_list){
            transposed_graph->add_edge(neighbor, node);
        }
    }
    return transposed_graph;
}

void Graph::add_edge(int source, int sink){
    this->edges[source]->push_back(sink);
}

void Graph::add_node(int newnode){
    this->nodes.push_back(newnode);
    this->edges[newnode] = new vector <int>;
}

bool Graph::contains(int node_id){
    return (find(this->nodes.begin(),
                 this->nodes.end(),
                 node_id) != this->nodes.end());
}

string Graph::graph_to_string(){
    string retstring = "Graph with following nodes and edges:\n";
    for (int node_id: this->nodes){
        retstring += ("    Node " + to_string(node_id) + " connected to " +
                      to_string(this->edges[node_id]->size()) + " neighbors:");
        for (int neighbor: *(this->edges[node_id])){
            retstring += " " + to_string(neighbor);
        }
        retstring += "\n";
    }
    return retstring;
}

Graph *dfs_helper(int root, Graph *&graph,
                  unordered_map <int, bool> &discovered,
                  unordered_map <int, int> &finish_times,
                  int &time){
    Graph *dfs_tree = new Graph({root});

    stack <int> discovery_stack;
    stack <int> current_path;
    unordered_map <int, int> children_on_stack;  // Different from neighbors on stack

    discovered[root] = true;
    current_path.push(root);
    children_on_stack[root] = 0;
    // Push all of the neighbors of the root onto the discovery stack.
    for (int neighbor: *(graph->edges[root])){
        if (!discovered[neighbor]){
            // Every time you put a node on the discovery stack, you need to decrement entries in
            // remaining_neighbors for all nodes that lead to this node, and increment its neighbors_on_stack entry
            discovered[neighbor] = true;
            discovery_stack.push(neighbor);
            children_on_stack[root]++;
        }
    }

    // Now, engage the while loop.
    while (!discovery_stack.empty() || !current_path.empty()){
        if (!discovery_stack.empty()){
            int new_node_to_process = discovery_stack.top();
            discovery_stack.pop();
            children_on_stack[current_path.top()]--;
            dfs_tree->add_node(new_node_to_process);
            dfs_tree->add_edge(current_path.top(), new_node_to_process);
            current_path.push(new_node_to_process);

            children_on_stack[new_node_to_process] = 0;
            for (int neighbor: *(graph->edges[new_node_to_process])){
                if (!discovered[neighbor]){
                    discovered[neighbor] = true;
                    discovery_stack.push(neighbor);
                    children_on_stack[new_node_to_process]++;
                }
            }
        }

        while (!current_path.empty() && (children_on_stack[current_path.top()] == 0)){
            int current_top = current_path.top();
            current_path.pop();
            finish_times[current_top] = time++;
        }
    }
    return dfs_tree;
}


vector <Graph *> dfs(Graph *&graph, unordered_map <int, int> &finish_times){
    unordered_map <int, bool> discovered;

    for (int node: graph->nodes){
        discovered[node] = false;
        finish_times[node] = -1;
    }

    int time = 0;
    vector <Graph *> forest;
    for (int node: graph->nodes){
        if (!discovered[node]){
            forest.push_back(dfs_helper(node, graph,
                                        discovered,
                                        finish_times,
                                        time));
        }
    }
    return forest;
}


Graph *load_graph(string filename){
    ifstream graph_stream;
    graph_stream.open(filename);

    Graph *retgraph = new Graph({});

    // Go through the file and process each edge, adding Nodes to the id->node map as necessary
    string line;
    set <int> found_nodes;
    while (getline(graph_stream, line)){
        vector<string> edge = split(line, ' ');
        int tail = stoi(edge[1]);
        int head = stoi(edge[0]);
        if (found_nodes.find(tail) == found_nodes.end()){
            found_nodes.insert(tail);
            retgraph->add_node(tail);
        }
        if (found_nodes.find(head) == found_nodes.end()){
            found_nodes.insert(head);
            retgraph->add_node(head);
        }
        retgraph->add_edge(tail, head);
    }
    graph_stream.close();
    return retgraph;
}


// WEIGHTED DIRECTED GRAPH STUFF

WeightedGraph::WeightedGraph(vector <int> nodes){
    for (int node: nodes){
        this->add_node(node);
    }
}

void WeightedGraph::add_edge(int source, int dest, double weight){
    this->edges[source]->push_back(dest);
    this->weights[source]->push_back(weight);
}

void WeightedGraph::add_node(int node_id){
    if (this->nodes.find(node_id) == this->nodes.end()){
        this->nodes.insert(node_id);
        this->edges[node_id] = new vector <int>;
        this->weights[node_id] = new vector <double>;
    }
}


WeightedGraph *load_weighted_graph(string filename){
    ifstream graph_stream;
    graph_stream.open(filename);

    WeightedGraph *retgraph = new WeightedGraph({});
    string line;

    while (getline(graph_stream, line)){
        vector <string> edges = split(line, '\t');
        int this_node = stoi(edges[0]);
        retgraph->add_node(this_node);

        for (size_t i=1; i < edges.size(); i++){
            vector <string> node_and_weight = split(edges[i], ',');
            int neighbor_id = stoi(node_and_weight[0]);
            double edge_weight = (double)stoi(node_and_weight[1]);

            retgraph->add_node(neighbor_id);
            retgraph->add_edge(this_node, neighbor_id, edge_weight);
        }
    }
    return retgraph;
}

