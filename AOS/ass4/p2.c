#include <stdio.h>
#include <stdlib.h>
int main(){
    int *p;
    p = malloc(5 * sizeof(int));
    if(p == NULL){
        printf("Memory allocation failed\n");
        return 1;}
    for(int i = 0; i < 5; i++) 
        p[i] = i + 1;
    printf("Memory allocated successfully\n");
    free(p);       // release allocated memory
    p = NULL;      // avoid a dangling pointer
    return 0;}
