#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main(){
    int p1[2], p2[2];
    char msg[] = "Hello Child";
    char reply[] = "Hello Parent";
    char buf[50];
    pipe(p1);                  // Create parent-to-child pipe
    pipe(p2);                  // Create child-to-parent pipe
    if(fork() == 0){
        close(p1[1]);          // Child does not write to p1
        close(p2[0]);          // Child does not read from p2
        read(p1[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        write(p2[1], reply, strlen(reply) + 1);
        close(p1[0]);
        close(p2[1]);
    }else{
        close(p1[0]);          // Parent does not read from p1
        close(p2[1]);          // Parent does not write to p2
        write(p1[1], msg, strlen(msg) + 1);
        read(p2[0], buf, sizeof(buf));
        printf("Parent received: %s\n", buf);
        close(p1[1]);
        close(p2[0]);
        wait(NULL);            // Wait for child
    }
    return 0;
}
