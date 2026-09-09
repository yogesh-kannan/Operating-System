#include <stdlib.h>

typedef struct {
    int n;
    int *mem;
} Allocator;

// Constructor
Allocator* allocatorCreate(int n) {
    Allocator* obj = (Allocator*)malloc(sizeof(Allocator));
    obj->n = n;
    obj->mem = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        obj->mem[i] = -1;
    }
    return obj;
}

// Map your allocation logic here
int allocatorAllocate(Allocator* obj, int size, int mID) {
    int l = 0;
    for (int r = 0; r < obj->n; ++r) {
        if (obj->mem[r] == -1) {
            if (r - l + 1 == size) {
                for (int i = l; i <= r; ++i) {
                    obj->mem[i] = mID;
                }
                return l;
            }
        } else {
            l = r + 1;
        }
    }
    return -1;
}

// FIX: LeetCode expects the logical free function to be called 'allocatorFreeMemory' 
// to avoid overlapping with the internal instance destructor.
int allocatorFreeMemory(Allocator* obj, int mID) {
    int cnt = 0;
    for (int i = 0; i < obj->n; ++i) {
        if (obj->mem[i] == mID) {
            obj->mem[i] = -1;
            cnt++;
        }
    }
    return cnt;
}

// Destructor (Internal judge boilerplate code calls this to wipe the structure)
void allocatorFree(Allocator* obj) {
    if (obj) {
        free(obj->mem);
        free(obj);
    }
}
