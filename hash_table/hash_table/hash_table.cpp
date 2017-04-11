#include <math.h>
#include <iostream>
#include <vector>
#include <list>
#include "hash_table.hpp"

ChainingTable::ChainingTable(std::size_t table_size){
    // Find the closest power of 2, minus 1.
    std::size_t closest_power;
    if (table_size > 1){
        float f = (float)table_size;
        unsigned long long int const t = 1U << ((*(unsigned long long int *)&f >> 23) - 0x7f);
        closest_power = t << (t < table_size);
        closest_power--;
    }
    else{
        closest_power = 1;
    }
    this->elements = new std::vector <std::list <long long int> *> (closest_power);
    // For each element, initialize to an empty list
    for (std::size_t i=0; i < closest_power; i++){
        (*this->elements)[i] = new std::list <long long int>;
    }
}

void ChainingTable::insert_elem(long long int element){
    // Simply hash and resolve conflicts by chaining
    std::size_t hash_val = this->hash_function(element);
    if (hash_val >= this->elements->size()){
        std::cout << "BAD HASH VALUE : " << hash_val << std::endl;
        std::cout << "Table size is : " << this->elements->size() << std::endl;
    }
    if (!this->elem_search(element))
        //if ((*this->elements)[hash_val]->size() != 0)
        //    std::cout << "CRASH! " << hash_val <<  "\n";
        (*this->elements)[hash_val]->push_back(element);
}


bool ChainingTable::elem_search(long long int element){
    std::size_t hash_val = this->hash_function(element);
    for (long long int elem: *(*this->elements)[hash_val]){
        if (elem == element)
            return true;
    }
    return false;
}


std::size_t ChainingTable::hash_function(long long int element){
    // Implements FNV-1A hashing algorithm
    // Since the input is a long long int, that's 64 bits of information,
    // equating to 8 bytes
    unsigned long long hash_val = 0xcbf29ce484222325;
    unsigned long long fnv_prime = 0x100000001b3;
    for (unsigned char i=0; i < 8; i++){
        unsigned long long byte_of_data = 0x000000ff & (element >> i);
        hash_val = hash_val ^ byte_of_data;
        hash_val = hash_val * fnv_prime;
    }
    return hash_val % this->elements->size();
}
