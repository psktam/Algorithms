#include <unordered_map>
#include <vector>
#include "graphs.hpp"

using namespace std;

#ifndef DIJKSTRA_HPP_INCLUDED
#define DIJKSTRA_HPP_INCLUDED

void relax_edge(int source, int dest, int weight,
                unordered_map <int, int> &total_dist_map,
                WeightedGraph *&shortest_path_graph);


class DijkstraGraph : public WeightedGraph{

public:

    ///This maps node id to list of distances
    unordered_map <int, float> total_distance_map;

    using WeightedGraph::WeightedGraph;
    /**
    Overwrite the base class' method to only allow up to one edge between nodes
    */
    void add_edge(int source, int dest, double weight);
};


/**
Finds all of the shortest paths from the given source node, and also fills in
the provided shortest paths map
*/
DijkstraGraph *shortest_paths(WeightedGraph *&graph, int source_node,
                              unordered_map <int, double> &least_dist_map);

#endif // DIJKSTRA_HPP_INCLUDED
