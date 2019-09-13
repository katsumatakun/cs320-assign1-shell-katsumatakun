#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {

    while(1){
      char command[255];
      printf("$: ");
      scanf("%s", command);
      int rc = fork();
      if (rc < 0) {
      // fork failed
      fprintf(stderr, "fork failed\n");
      exit(1);
      }
      else if (rc == 0) { // child (new process)
      printf("%s\n", command);
      // printf("child finished\n");
      exit(1);
        }
      else {
      // parent goes down this path (main)
      wait(NULL);
      // printf("parent finished\n");
      }
   }
    return 0;
}
