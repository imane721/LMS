//
// Created by Emy on 3/26/22.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "MyHashTable.h"
#include "myMalloc.h"
#include <chrono>



TEST_CASE("MyMalloc") {
    MyMalloc myMalloc;
    int numbers[5];
    myMalloc.allocate(sizeof(numbers));
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;
    numbers[4] = 5;
    CHECK(myMalloc.myHashTable.getCapacity() == 256);
    CHECK(myMalloc.myHashTable.getSize() == 1);
    CHECK(numbers[0] == 1);
    CHECK(numbers[1] != 1);
    myMalloc.deallocate(numbers);
    CHECK(myMalloc.myHashTable.getSize() == 0);
}


TEST_CASE("Hash Table") {
    MyHashTable hashTable;

    SECTION("Constructor") {
        int capacity =hashTable.getCapacity();
        CHECK(capacity == 256);
        CHECK(hashTable.getSize() == 0);
        for (int i = 0; i < capacity; i++) {
            CHECK(hashTable.getTable()[i].first == nullptr);
            CHECK(hashTable.getTable()[i].second == 0);
        }
    }

    SECTION("Insert") {
        int number = 11;
        hashTable.insert(&number, 12);
        int hash = hashTable.hashValue(&number);
        CHECK(hashTable.getSize() == 1);
        CHECK(hashTable.getTable()[hash].second == 12);
        int number2 = 89;
        hashTable.insert(&number2, 24);
        int hash2 = hashTable.hashValue(&number2);
        CHECK(hashTable.getSize() == 2);
        CHECK(hashTable.getTable()[hash2].second == 24);
    }
    SECTION("Delete") {
        int number1 = 100;
        int number2 = 666;
        hashTable.insert(&number1, 10);
        hashTable.insert(&number2, 20);
        CHECK(hashTable.getSize() == 2);
        CHECK(hashTable.deleteAdd(&number1) == 10);
        CHECK(hashTable.getSize() == 1);
    }
    SECTION("Generate same hash") {
        int number = 11;
        int *nptr = &number;
        int hash1 = hashTable.hashValue(nptr);
        int hash2 = hashTable.hashValue(nptr);
        CHECK(hash1 == hash2);
    }
    SECTION("Generate different Hash ") {
        int number1 = 11;
        int number2 = 11;
        int hash1 = hashTable.hashValue(&number1);
        int hash2 = hashTable.hashValue(&number2);
        CHECK(hash1 != hash2);
    }
    SECTION("Grow") {
        int number = 11;
        hashTable.insert(&number, 20);
        CHECK(hashTable.getSize() == 1);
        CHECK(hashTable.getCapacity() == 256);
        hashTable.grow();
        CHECK(hashTable.getSize() == 1);
        CHECK(hashTable.getCapacity() == 512);
    }
}
TEST_CASE("Benchmark") {
    int TIMING = 10000;
    MyMalloc MyMalloc;
    double mallocTime = 0;
    double MyMallocTime = 0;

    for (int i = 0; i < TIMING; i++) {
        int number1 = i;

        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        MyMalloc.allocate(sizeof(number1));

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        double duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
        MyMallocTime += duration;

        int number2 = i;

        std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
        auto sysMalloc = malloc(sizeof(number2));

        std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

        double duration3 = std::chrono::duration_cast<std::chrono::microseconds>(t4-t3).count();
        mallocTime += duration3;
    }

    mallocTime /= TIMING;
    MyMallocTime /= TIMING;
    std::cout << "################### Benchmark #####################\n\n";
    std::cout << "MyMalloc avg run time: " << MyMallocTime << " microseconds: " << TIMING << " tests\n\n";
    std::cout << "malloc avg run time: " << mallocTime << " microseconds: " << TIMING << " tests\n\n";


    int entries=100000;
    int entrySize=10000;

    void* pointers[entries];


    std::cout.precision(1);
    std::cout << std::scientific;
    std::cout << "Number of Entries: " << (float) entries << " // Size of Entries: " << (float) entrySize << ":\n";

    //MyMalloc
    auto timeStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < entries; i++) {
        pointers[i] = MyMalloc.allocate(entrySize);
    }

    for (int i = 0; i < entries; i++) {
        MyMalloc.deallocate(pointers[i]);
    }
    auto timeEnd = std::chrono::high_resolution_clock::now();

    std::cout << "MyMalloc Allocate/Deallocate time in ms : " << std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count() << "ms \n";


    //timing Malloc
    timeStart = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < entries; i++) {
        pointers[i] = malloc(entrySize);
    }
    for (int i = 0; i < entries; i++) {
        free(pointers[i]);
    }

    timeEnd = std::chrono::high_resolution_clock::now();

    std::cout << "malloc Allocate/Deallocate time in ms : " << std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count() << "ms \n";
    std::cout << "\n";

}

