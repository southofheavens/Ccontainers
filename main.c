#include <stdio.h>
#include <stdlib.h>
#include <vector.h>


int main() {
    vector vec;
    vector_init(&vec, sizeof(int));
    
    int push_elem;
    push_elem = 5;
    vpush_back(&vec,push_elem);
    push_elem = 3;
    vpush_back(&vec,push_elem);
    push_elem = 6;
    vpush_back(&vec,push_elem);
    push_elem = -4;
    vpush_back(&vec,push_elem);

    {}

    // int arr[5] = {5,4,3,2,1};
    // qsort(arr,5,sizeof(int),comp_asc_int);
    // for (i = 0; i < 5; ++i)
    // {
    //     printf("%d\n",arr[i]);
    // }

    vector_destroy(&vec);
    return 0;
}