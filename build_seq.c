#include <stdio.h>
#include <stdlib.h>

int* buildSequence(int length, int first, int step){
    int* P_intArr = malloc(length * sizeof(int));

    if (P_intArr == NULL) 
    {
        printf("MEMORY ALLOCATION FAILED :(");
        return NULL;
    }

    for (int i = 0; i < length; i++) 
         P_intArr[i] = first + i * step;

    return P_intArr;
}

int main(){
    int length = 9, first = 5, step = 2;
    int* arr = buildSequence(length, first, step);

    if (arr != NULL) {
        for (int i = 0; i < length; i++) 
             printf("%d ", arr[i]);
    }
    
    free(arr);
    arr = NULL;

    return 0;
}
