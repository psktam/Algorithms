#include "hash_table.hpp"
#include <math.h>
#include <vector>
#include <list>


ChainingTable::ChainingTable(std::size_t table_size){
    // Find the closest power of 2, minus 1.
    std::size_t closest_power;
    if (table_size > 1){
        float f = (float)table_size;
        unsigned int const t = 1U << ((*(unsigned int *)&f >> 23) - 0x7f);
        closest_power = t << (t < table_size);
        closest_power--;
    }
    else{
        closest_power = 1;
    }
    this->elements = new std::vector <std::list <int> *> (closest_power);
    // For each element, initialize to an empty list
    for (std::size_t i=0; i < closest_power; i++){
        (*this->elements)[i] = new std::list <int>;
    }
}

void ChainingTable::insert_elem(int element){
    // Simply hash and resolve conflicts by chaining
    std::size_t hash_val = this->hash_function(element);
    if (!this->elem_search(element))
        (*this->elements)[hash_val]->push_back(element);
}


bool ChainingTable::elem_search(int element){
    std::size_t hash_val = this->hash_function(element);
    for (int elem: *(*this->elements)[hash_val]){
        if (elem == element)
            return true;
    }
    return false;
}


std::size_t ChainingTable::hash_function(int element){
    // Apply the simple multiplication-based hash function here. Implement crazier
    // hash functions later.
    double scaling_coeff = 0.6180339887;
    std::size_t m = this->elements->size();
    double hash_val = (double)element * scaling_coeff;
    hash_val = fmod(hash_val, 1.0) + (double)(element < 0);
    hash_val = hash_val * (double)m;
    return (std::size_t)hash_val;
}
