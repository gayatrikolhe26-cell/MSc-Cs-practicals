#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <stdlib.h>
int main()
{
    int n, i;
    struct rusage r;
    printf("Enter number of children: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        if(fork() == 0)
        {
            for(long j = 0; j < 10000000; j++);
            exit(0);
        }
    }
    for(i = 0; i < n; i++)
        wait(NULL);
    getrusage(RUSAGE_CHILDREN, &r);
    printf("User time   : %ld.%06ld seconds\n",
           r.ru_utime.tv_sec, r.ru_utime.tv_usec);
    printf("System time : %ld.%06ld seconds\n",
           r.ru_stime.tv_sec, r.ru_stime.tv_usec);
    return 0;
}

