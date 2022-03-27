//
// Created by Emy on 3/26/22.
//

#include "myMalloc.h"
#include <sys/mman.h>

MyMalloc::MyMalloc() {
}

MyMalloc::~MyMalloc() {

    auto table = myHashTable.getTable();
    for (int i = 0; i < myHashTable.getCapacity(); i++) {
        if (table[i].first != nullptr) {
            munmap(table[i].first, table[i].second);
        }
    }
}



/*round up the allocation size to the next multiple of the page size
allocate memory with mmap
insert the returned pointer and the allocation size in the hash tableround up the allocation size to the next multiple of the page size
allocate memory with mmap
insert the returned pointer and the allocation size in the hash table
*/
void *MyMalloc::allocate(size_t bytesToAllocate) {
    size_t pagesToAllocate = bytesToAllocate / 4096;
    if (bytesToAllocate % 4096 != 0) {
        pagesToAllocate++;
    }
    size_t bytesSize = pagesToAllocate * 4096;

    void* memory = mmap(NULL, bytesSize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
    myHashTable.insert(memory, bytesSize);

    return memory;
}

void MyMalloc::deallocate(void *ptr) {
    size_t sizeBytes = myHashTable.deleteAdd(ptr);
    munmap(ptr, sizeBytes);
}

