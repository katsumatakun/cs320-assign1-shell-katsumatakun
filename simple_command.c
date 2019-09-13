#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main() {
   int nonexit = 1;
    while(nonexit){
      char command[255];
      printf("$: ");
      char* buffer; long unsigned int len;
      int read = getline(&buffer, &len, stdin);
      // printf("%d\n", buffer[0]=='e');
      // printf("%d\n", buffer[1]=='x');
      // printf("%d\n", buffer[2]=='i');
      // printf("%d\n", buffer[3]=='t');
      // printf("%d\n", buffer[4]=='\n');
      if(strcmp("exit\n",buffer) == 0){
        nonexit = 1;
        exit(1);
      }
      int rc = fork();
      if (rc < 0) {
      // fork failed
      fprintf(stderr, "fork failed\n");
      exit(1);
      }
      else if (rc == 0) { // child (new process)
        char path[] = "/bin/";
        char *args[20];
        int num = 0;
        char*p = strtok(buffer, " ");
        while (p)
        {
          // printf("%s\n", p);
          // printf("%lu\n",strlen(p));
          if(p[strlen(p)-1] == '\n'){
           p[strlen(p)-1]  = '\0';
         }
           args[num] = p;
           // printf("new len %lu\n",strlen(args[num]));
           p = strtok(NULL, " ");
           num++;
        }
        args[num] = NULL;
        // printf("what is the program name length?%lu\n", strlen(args[0]));
        // printf("is second null? %d\n",args[1]==NULL);
        // printf("program: %s \n",args[0]);
        int len_bin = strlen(path);
        int len_pro = strlen(args[0]);
        // printf("lenpro %d\n", len_pro);
        char* loc = malloc(len_bin+len_pro);

        for (int i=0; i< len_bin; i++){
          loc[i] = path[i];
        }
        int count = 0;
        while(args[0][count] != '\0')
        {
          loc[len_bin+count] = args[0][count];
          count++;
        }
        loc[len_bin+len_pro] = '\0';
        args[0] = loc;
        // printf("loc: %s\n",loc );
        // printf("loc size: %lu\n",strlen(loc) );
        //
        // printf("%d\n",strcmp(loc,"/bin/ps"));

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
