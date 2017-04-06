#include <limits>
#include <queue>
#include "dijkstra.hpp"
#include "graphs.hpp"


double inf = numeric_limits <double>::infinity();


void relax_edge(int source, int dest, double weight,
                unordered_map <int, double> &total_dist_map,
                DijkstraGraph *&shortest_path_graph){
    double new_distance = total_dist_map[source] + weight;
    if (new_distance < total_dist_map[dest]){
        // If the proposed distance is smaller than what it currently
        // is, we assign a new distance and then wire the edge in the
        // appropriate shortest-paths graph
        total_dist_map[dest] = new_distance;
        shortest_path_graph->add_edge(source, dest, weight);
    }
}


void DijkstraGraph::add_edge(int source, int dest, double weight){
    if (this->edges[source]->size() == 0){
        this->edges[source]->push_back(dest);
        this->weights[source]->push_back(weight);
    }
    else{
        (*this->edges[source])[0] = dest;
        (*this->weights[source])[0] = weight;
    }
}


DijkstraGraph *shortest_paths(WeightedGraph *&graph, int source_node,
                              unordered_map <int, double> &least_dist_map){
    // Initialize distances. Everything except the source is distance 0
    auto cmp = [&least_dist_map](int left, int right){
            return least_dist_map[left] > least_dist_map[right];
        };
    priority_queue <int, vector <int>, decltype(cmp)> node_heap(cmp);
    vector <int> nodes;
    DijkstraGraph *retgraph = new DijkstraGraph(nodes);
    for (int node: graph->nodes){
        retgraph->add_node(node);
    }
    vector <int> processed_nodes;

    for (int node: graph->nodes){
        least_dist_map[node] = inf;
        retgraph->add_node(node);
    }
    least_dist_map[source_node] = 0;
    for (int node: graph->nodes){
        node_heap.push(node);
    }

    while (node_heap.size() > 0){
        int closest_node = node_heap.top();
        node_heap.pop();
        processed_nodes.push_back(closest_node);

        for (size_t idx=0; idx < graph->edges[closest_node]->size(); idx++){
            int neighbor = (*graph->edges[closest_node])[idx];
            double weight = (*graph->weights[closest_node])[idx];

            relax_edge(closest_node, neighbor, weight, least_dist_map, retgraph);
        }
    }
    return retgraph;
}
