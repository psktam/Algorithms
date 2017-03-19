#include <vector>
#include <unordered_map>
#include <string>


#ifndef GRAPHS_HPP_INCLUDED
#define GRAPHS_HPP_INCLUDED
using namespace std;


class Graph{
    /**
    This class is used to represent a graph in an adjacency-list format
    */
public:
    // PROPERTIES
    vector <int> nodes;
    unordered_map <int, vector <int> *> edges;

    // METHODS
    /**
    Base constructor of Graph, which simply instantiates the nodes
    property
    */
    Graph(vector <int> nodes);

    /**
    Returns a graph that has the edges of this graph reversed
    */
    Graph *transpose();

    /**
    Adds a directed edge between the given node IDs. These IDs must be
    present in the graph in order for this node to be created.
    */
    void add_edge(int source, int sink);

    /**
    Add a new node, given that the node doesn't already exist in the
    graph.
    */
    void add_node(int newnode);

    /**
    Tells you whether or not a certain node is already in the graph
    */
    bool contains(int node_id);

    /**
    Returns a representation of this graph as a string that you can
    print.
    */
    string graph_to_string();
};


/**
Use this function to load a graph from a filename.
*/
Graph *load_graph(string);


/**
Perform depth-first search on a given graph.
*/
vector <Graph *> dfs(Graph *&graph, unordered_map <int, int> &finish_times);

#endif  // GRAPHS_HPP_INCLUDED
