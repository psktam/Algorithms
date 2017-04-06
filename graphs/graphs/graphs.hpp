#include <vector>
#include <unordered_map>
#include <string>
#include <set>


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


class WeightedGraph{
    /**
    This class is used to represent a graph with weighted edges in an adjacency-list format
    */
public:
    // PROPERTIES
    set <int> nodes;
    unordered_map <int, vector <int> *> edges;
    unordered_map <int, vector <double> *> weights;  // keeps track of the weight for the corresponding neighbor

    // METHODS
    /**
    Base constructor of a weighted directed graph, which simply instantiates the node property,
    so there are no edges.
    */
    WeightedGraph(vector <int> nodes);

    /**
    Adds a directed edge between the given node IDs with the given weight. These IDs
    must be present in the graph for the node to even be created.
    */
    void add_edge(int source, int dest, double weight);

    /**
    Add a node with a given ID to the the graph. If it already exists, does nothing.
    */
    void add_node(int node_id);
};


/**
Call this function to load a weighted graph from a file
*/
WeightedGraph *load_weighted_graph(string filename);

#endif  // GRAPHS_HPP_INCLUDED
