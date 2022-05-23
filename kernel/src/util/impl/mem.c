#include <util/mem.h>

// 2022 Ian Moffett <ian@kesscoin.com>


void memzero(void* ptr, size_t n) {
    char* ptrch = (char*)ptr;

    for (size_t i = 0; i < n; ++i) {
        ptrch[i] = 0;
    }
}
