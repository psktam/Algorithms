#include <iostream>
#include <list>
#include "hash_table.hpp"

using namespace std;

int main()
{
    ChainingTable table(10);
    cout << "Created table with " << table.elements->size() << " elements\n";
    for (int i=0; i < 10; i++){
        size_t hv = table.hash_function(i);
        cout << "Hash value for " << i << " is: ";
        cout << hv << endl;
        table.insert_elem(i);

        cout << "Current list at bucket " << hv << endl;
        for (int ii: *(*table.elements)[hv]){
            cout << ii;
        }
        cout << endl;
    }

    cout << "9 is contained in the table: ";
    cout << table.elem_search(9) << endl;
    cout << "10 is contained in the table: ";
    cout << table.elem_search(10) << endl;

}
