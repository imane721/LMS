//
// Created by Emy on 3/26/22.
//

#ifndef IL_MALLOC_MYHASHTABLE_H
#define IL_MALLOC_MYHASHTABLE_H
#include <utility>

class MyHashTable {
    // Member Variables
    std::pair<void *, size_t> *tablePointer;
    size_t tableCapacity;
    size_t tableSize;
public:
    // Constructor and Deconstructor
    MyHashTable();
    ~MyHashTable();

    // Hash functions
    int hashValue(void *ptr);
    void grow();
    void insert(void *ptr, size_t neededSize);
    size_t deleteAdd(void *ptr);
    void findAndInsert(void *ptr, size_t neededSize, int hash);
    size_t findAndDelete(const void *ptr, int hash);

    // Getters
    std::pair<void *, size_t> *getTable();
    size_t getCapacity();
    size_t getSize();

};
void compareMallocs(int entries, int entrySize);
#endif //IL_MALLOC_MYHASHTABLE_H
