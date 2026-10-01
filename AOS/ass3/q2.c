#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void message1()
{
  printf("atexit function 1 executed.\n");
}

void message2()
{
  printf("atexit function 2 executed.\n");
}

void message3()
{
  printf("atexit function 3 executed.\n");
}

int main()
{
  printf("Program started.\n");
  atexit(message1);
  atexit(message2);
  atexit(message3);

  printf("Main function is executing.\n");
  printf("Program is terminating...\n");
  exit(0);
}
