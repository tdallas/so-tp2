#include <stdio.h>

#define MAX_ALLOC_LOG2 29
#define MAX_ALLOC ((size_t)1 << MAX_ALLOC_LOG2)

int main() {
    printf("MAX_LOG : %d , MAX : %d \n", MAX_ALLOC_LOG2, MAX_ALLOC);
}