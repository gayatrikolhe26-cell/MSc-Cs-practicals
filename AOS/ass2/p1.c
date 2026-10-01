#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
  int fd;
  fd=open("holefile.txt",O_CREAT | O_WRONLY | O_TRUNC,0644);
  /*if(fd<0)
  {
     perror("Error opening file");
     exit(1);
  }*/
  write(fd,"Hello",5);
  lseek(fd,100,SEEK_CUR);
  write(fd,"World",5);
  close(fd);
  printf("File created successfully with a hole.\n");
  return 0;
}
