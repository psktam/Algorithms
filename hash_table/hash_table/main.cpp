#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include "hash_table.hpp"

using namespace std;


// Parsing functions to load the 2sum text file
vector <long long int> *load_file(string filename){
    /// Loads a filename and outputs the list of integers that it
    /// stores

    ifstream ifs(filename);
    string line;
    vector <long long int> *retvector = new vector <long long int> (0);
    while (getline(ifs, line)){
        retvector->push_back(stoll(line));
    }
    return retvector;
}


int main()
{
    string filename;
    cout << "File to load: ";
    cin >> filename;
    cout << "Loading... ";
    vector <long long int> *numbers = load_file(filename);
    cout << "done\n";

    // Now, insert all of these numbers into a hash table
    cout << "Inserting into hash table...\n";
    ChainingTable table(numbers->size() * 25);
    for (size_t i = 0; i < numbers->size(); i ++){
        table.insert_elem((*numbers)[i]);
        if (i % 10000 == 0){
            cout << "Inserted " << i << " of " << numbers->size() << " elements so far\n";
        }
    }
    for (long long int num: *numbers){
        table.insert_elem(num);

    }

}
