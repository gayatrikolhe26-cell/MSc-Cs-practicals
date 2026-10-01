#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
void handler(int sig){
    if(sig == SIGHUP)
        printf("Child: SIGHUP received\n");
    else if(sig == SIGINT)
        printf("Child: SIGINT received\n");
    else if(sig == SIGQUIT){
        printf("My DADDY has Killed me!!!\n");
        exit(0);
    }
}
int main(){
    pid_t child;
    int i;
    child = fork();
        printf("Child: SIGINT received\n");
    else if(sig == SIGQUIT){
        printf("My DADDY has Killed me!!!\n");
        exit(0);
    }
}
int main(){
    if(child == 0){
        signal(SIGHUP, handler);
        signal(SIGINT, handler);
        signal(SIGQUIT, handler);
        while(1)
            pause();
    }else{
        for(i = 3; i <= 30; i += 3){
            sleep(3);
            if(i == 30)
                kill(child, SIGQUIT);
            else if((i / 3) % 2 == 1)
                kill(child, SIGHUP);
            else
                kill(child, SIGINT);
        }
        wait(NULL);
    }
    return 0;
}
