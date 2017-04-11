#include <vector>
#include <list>

#ifndef HASH_TABLE_HPP_INCLUDED
#define HASH_TABLE_HPP_INCLUDED


class ChainingTable{
/// This class defines a hash table that resolves collisions
/// by chaining. Due to the nature of this project, I'm going
/// to limit myself to the case where the things we're storing
/// are just integers

public:

    // properties, dawg
    // The vector stores pointers to linked lists of integers
    std::vector <std::list<int> *> *elements;

    /// Constructor to create the table, already at a certain size.
    /// This should create a table with size the closest power of 2 - 1,
    /// regarding the given size.
    ChainingTable(std::size_t table_size);

    /// This method adds a new element to the hash table, at the
    /// specified key.
    void insert_elem(int element);

    /// Lets you know that the given element is in the HT
    bool elem_search(int element);

    /// Generates the hash code for the given input
    std::size_t hash_function(int element);
};


#endif // HASH_TABLE_HPP_INCLUDED
