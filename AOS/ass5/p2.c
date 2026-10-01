#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
    pid_t child;
    int i;
    child = fork();
    if(child < 0)
    {
        printf("Fork failed\n");
        return 1;
    }
    if(child == 0)
    {
        printf("Child: Running\n");

        for(i = 1; i <= 10; i++)
        {
            printf("Child: Working %d\n", i);
            sleep(1);
        }
        printf("Child: Finished\n");
        exit(0);
    }
    else
    {
        sleep(2);

        kill(child, SIGSTOP);
        printf("Parent: Child suspended\n");
        sleep(3);
        kill(child, SIGCONT);
        printf("Parent: Child resumed\n");
        wait(NULL);
    }
    return 0;
}
