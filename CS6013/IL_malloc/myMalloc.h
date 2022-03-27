//
// Created by Emy on 3/26/22.
//

#ifndef IL_MALLOC_MYMALLOC_H
#define IL_MALLOC_MYMALLOC_H
    #include "MyHashTable.h"

    class MyMalloc {

    public:

        MyHashTable myHashTable;

        // Constructor & Deconstructor
        MyMalloc();
        ~MyMalloc();

        // my malloc
        void* allocate(size_t bytesToAllocate);

        // my free
        void deallocate(void* ptr);
    };

#endif //IL_MALLOC_MYMALLOC_H
