#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main() {

    while(1){
      char command[255];
      printf("$: ");
      char* buffer; long unsigned int len;
      int read = getline(&buffer, &len, stdin);
      int rc = fork();
      // printf("%d\n",rc );
      if (rc < 0) {
      // fork failed
      fprintf(stderr, "fork failed\n");
      exit(1);
      }
      else if (rc == 0) { // child (new process)
        char path[] = "/bin/";
        printf("buffer: %lu \n",strlen(buffer));
        printf("path: %s \n",path);
        int len_bin = strlen(path);
        int len_buf = strlen(buffer);
        char* loc = malloc(len_bin+len_buf-1);

        for (int i=0; i< len_bin; i++){
          loc[i] = path[i];
        }
        printf("%s\n",loc );
        int count = 0;
        while(buffer[count] != '\0')
        {
          printf("%d\n", count+len_bin);
          loc[len_bin+count] = buffer[count];
          count++;
        }
        loc[len_bin+len_buf-1] = '\0';
        char *args[2];

        args[0] = loc;
        args[1] = NULL;
        // printf("%d\n",strcmp(loc,"/bin/ps");
        int rv = execv(args[0], args);
        printf("program not found \n");
      exit(1);
      }
      else {
      // parent goes down this path (main)
      wait(NULL);
      printf("parent finished\n");
      }
   }
    return 0;
}
