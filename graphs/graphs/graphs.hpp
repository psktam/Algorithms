#include <vector>
#include <unordered_map>
#include <iostream>

#ifndef GRAPHS_HPP_INCLUDED
#define GRAPHS_HPP_INCLUDED
using namespace std;

class Node{
    /*
     * This class is used to represent a node in a graph in adjacency-list format
     */
public:
    //PROPERTIES
    int internal_id;
    vector<Node*> adjacency_list;
    //CONSTRUCTORS
    Node(int);
    //METHODS
    void add_edge(Node*);

};


typedef unordered_map <Node *, int> MapT;
typedef unordered_map <int, Node*> IMapT;  // Inverse mapping of ints to nodes

void dfs_visit(Node&, Node&, MapT&, MapT&, int&);
vector <Node*> dfs(vector<Node*>&, MapT&, MapT&);
void print_node(Node &, unsigned int);

#endif // GRAPHS_HPP_INCLUDED
