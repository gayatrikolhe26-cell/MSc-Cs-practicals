#include <stdio.h>
#include <stdlib.h>
void finish(){
    printf("Program terminated\n");}
int main(){
    atexit(finish);
    printf("Program is running\n");
    return 0;}

