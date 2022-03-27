//
// Created by Emy on 3/26/22.
//

#include "MyHashTable.h"
#include <sys/mman.h>
#include <chrono>
#include <stdio.h>
#include <thread>
#include <iostream>
#include "myMalloc.h"


/*The hash table will store addresses and the associated size of memory allocated to that address.
Hash the address to find the location to place the address/size into the hash table.
If there is a collision, look for the next available bucket to put the entry into.
When an address is freed up (in the main program), it needs to be removed from the hash table...
Think about what is required to remove an entry from a linear probed hash table.
Public methods the hash table should support: insert(), remove()
Private methods that can make the hash table implementation easier: find() (returns the address of an entry), grow().
grow() should create a new table that is twice the size of the current table, then re-hash all the current entries into the new table.
 */

MyHashTable::MyHashTable() {
    tablePointer = (std::pair<void*, size_t>*) mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    tableSize = 0;
    tableCapacity = 4096 / sizeof(tablePointer[0]);

    for (int x = 0; x < tableCapacity; x++) {
        tablePointer[x].first = nullptr;
        tablePointer[x].second = 0;
    }
}
MyHashTable::~MyHashTable() {
    for (int i = 0; i < tableCapacity; i++) {
        if (tablePointer[i].first != nullptr) {
            munmap(tablePointer[i].first, tablePointer[i].second);
        }
    }
    munmap(tablePointer, tableCapacity);
}

int MyHashTable::hashValue(void *ptr) {
    auto hash = (uint64_t) ptr;
    hash = hash << 12;
    return (int) ((hash >> 12) % tableCapacity);
}

void MyHashTable::grow() {
    size_t oldSize = tableCapacity * sizeof(tablePointer[0]);
    std::pair<void *, size_t>* oldTable = tablePointer;
    tableCapacity *= 2;

    // Make bigger table
    tablePointer = (std::pair<void*, size_t>*) mmap(nullptr, (tableCapacity * sizeof(tablePointer[0])), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    // Copy oldTable to new bigger Table
    for (int i = 0; i < (tableCapacity / 2); i++) {
        if (oldTable[i].first != nullptr) {
            int hash = hashValue(oldTable[i].first);
            findAndInsert(oldTable[i].first, oldTable[i].second, hash);
        }
    }

    // Clear old Table
    munmap(oldTable, oldSize);
}

void MyHashTable::findAndInsert(void *ptr, size_t neededSize, int hash) {
    while (tablePointer[hash].second != 0) {
        hash = (int) ((hash + 1) % tableCapacity);
    }
    tablePointer[hash].first = ptr;
    tablePointer[hash].second = neededSize;
}

size_t MyHashTable::findAndDelete(const void *ptr, int hash) {
    while (tablePointer[hash].first != nullptr && tablePointer[hash].first != ptr) {
        hash = (int) ((hash + 1) % tableCapacity);
    }
    size_t neededSize = tablePointer[hash].second;
    tablePointer[hash].first = nullptr;
    tablePointer[hash].second = 0;
    return neededSize;
}

void MyHashTable::insert(void *ptr, size_t neededSize) {
    // if current size is over 50% of the capacity, grow
    if (tableSize >= (tableCapacity * 0.5)) {
        grow();
    }
    int hash = hashValue(ptr);
    findAndInsert(ptr, neededSize, hash);
    tableSize++;
}

size_t MyHashTable::deleteAdd(void *ptr) {
    int hash = hashValue(ptr);
    size_t neededSize = findAndDelete(ptr, hash);
    tableSize--;
    return neededSize;
}

std::pair<void *, size_t> *MyHashTable::getTable() {
    return tablePointer;
}

size_t MyHashTable::getCapacity() {
    return tableCapacity;
}

size_t MyHashTable::getSize() {
    return tableSize;
}

void compareMallocs(int entries, int entrySize) {
    void* pointers[entries];
    MyMalloc allocater = MyMalloc();

    std::cout.precision(1);
    std::cout << std::scientific;
    std::cout << "# of Entries: " << (float) entries << " // the size of Entries: " << (float) entrySize << ":\n";


    auto timeStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < entries; i++) {
        pointers[i] = allocater.allocate(entrySize);
    }
    for (int i = 0; i < entries; i++) {
        allocater.deallocate(pointers[i]);
    }
    auto timeEnd = std::chrono::high_resolution_clock::now();

    std::cout << "MSDalloc Allocate/Deallocate time: " << std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count() << "ms \n";



    timeStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < entries; i++) {
        pointers[i] = malloc(entrySize);
    }
    for (int i = 0; i < entries; i++) {
        free(pointers[i]);
    }
    timeEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Malloc/Free time: " << std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count() << "ms \n";
    std::cout << "\n";
}