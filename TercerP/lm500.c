#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define READ  0
#define WRITE 1

int main() {

  pid_t pid;
  int   fd[2];
  int N;
  char buf[10];

  if (pipe(fd) == -1) {
    perror("Creating pipe");
    exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {

  case 0:
      
      close(fd[1]);
      read(fd[0],buf,sizeof(buf));
      close(fd[0]);
      int x = buf[0];
      if(x<50)
      printf("%d Menor que 50\n",x);
      else if(x>=50)
      printf("%d mayor o igual a 50\n",x);
      break;

  case -1:

    perror("fork() failed)");
    exit(EXIT_FAILURE);

  default:

      srand(time(NULL));
      N = rand() %99;

        close(fd[0]);
        write(fd[1],&N,sizeof(N));
        close(fd[1]);
        exit(0);
        break;
      
   
  }
}