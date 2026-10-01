#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
  int fd;
  fd=open("sample.txt",O_RDONLY);
  if(fd<0)
  {
     perror("Error opening file");
     exit(1);
  }
     printf("File opened successfully.\n");
     printf("Program will sleep for 15 seconds.\n");
     sleep(15);
     close(fd);
     printf("15 seconds completed.\n");
     printf("File closed and program terminated.\n");
     return 0;
}
