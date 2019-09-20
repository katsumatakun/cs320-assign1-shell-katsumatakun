#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define GENERIC_MIN(x, y) ((x) < (y) ? (x) : (y))
int history(char**,int);

int main() {
   char fullpath[] = "/bin/;/home/cs320/bin/";
   char* path_array[20];
   path_array[0] = "/bin/";
   path_array[1] = "/home/cs320/bin/";
   int num_path = 2;
   int nonexit = 1;
   int command_count = 0;
   char* command_ary[20];
    while(nonexit){
      char command[255];
      printf("$: ");
      char* buffer; long unsigned int len;
      int read = getline(&buffer, &len, stdin);
      command_ary[command_count%20]=(char*)(malloc(strlen(buffer)));
      strcpy(command_ary[command_count%20],buffer);
      printf("command count %d\n",command_count%20 );
      printf("command inserted %s\n", command_ary[command_count%20]);
      command_count++;
      int bikkuri = strncmp(buffer,"!\n",1);
      printf("bikkuri %d\n",bikkuri);
      int bikkuri2 = strcmp(buffer,"!!\n");
      printf("bikkuri2 %d\n",bikkuri2);
      if(!strcmp("exit\n",buffer)){
        nonexit = 1;
        exit(1);
      }
      if(bikkuri == 0){
        if(bikkuri2 == 0){
          strcpy(command_ary[(command_count-1)%20],command_ary[(command_count-2)%20]);
        }
        else{
          buffer=buffer+1;
          int num_go_back=0;
          int mini = GENERIC_MIN(20,command_count);
          num_go_back = strtol(buffer,NULL,10);
          printf("%d\n", num_go_back);
          if(0<num_go_back && mini >num_go_back){
            strcpy(command_ary[(command_count-1)%20],command_ary[(command_count-1-num_go_back)%20]);
            printf("next command %s\n", command_ary[(command_count-1)%20]);
          }
        }
      }
      if(!strcmp("history\n", command_ary[(command_count-1)%20])){
        history(command_ary,command_count);
      }

      else{
        int rc = fork();
        if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
        else if (rc == 0) { // child (new process)

          // char path[] = "/bin/";
          char *args[20];
          int num = 0;
          printf("most recent command %s\n", command_ary[(command_count-1)%20]);
          char*p = strtok(command_ary[(command_count-1)%20], " ");
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
          int len_pro = strlen(args[0]);
          // printf("what is the program name length?%lu\n", strlen(args[0]));
          // printf("is second null? %d\n",args[1]==NULL);
          // printf("program: %s \n",args[0]);
          for (int x=0; x<num_path; x++){
            int len_bin = strlen(path_array[x]);
            // printf("lenpro %d\n", len_pro);
            char* loc = malloc(len_bin+len_pro);

            printf("len loc %d\n",len_bin+len_pro );
            for (int i=0; i< len_bin; i++){
              loc[i] = path_array[x][i];
            }
            int count = 0;
            printf("args %s\n", args[0]);
            printf("len %ld\n",strlen(args[0]));
            while(args[0][count] != '\0')
            {
              loc[len_bin+count] = args[0][count];
              count++;
            }
            loc[len_bin+len_pro] = '\0';
            if (strcmp("getPATH",args[0]) == 0){
              printf("%s\n", fullpath);
            }
            else if(strcmp("setPATH",args[0]) == 0){
            }
            else if(!strcmp("lls",args[0])){
              int rv = execv("./lls", args);
              free(loc);
            }
            else{
            printf("loc: %s\n",loc );
            // printf("loc size: %lu\n",strlen(loc) );
            // printf("%d\n",strcmp(loc,""));
            // args[0] = loc;
            int rv = execv(loc, args);
            free(loc);
          }
          }
          printf("program not found \n");
          exit(1);
        }
        else {
        // parent goes down this path (main)
        wait(NULL);
        printf("parent finished\n");
      }
     }
  }
return 0;
}

int history(char** ary, int count){
  if(count>=20){
    int a = count%20;
    for(int i=0; i<20; i++){
      printf("%d %s\n",i,ary[a%20]);
      a++;
    }
  }
  else{
    for(int j=0; j<count; j++){
      printf("%d %s\n",j,ary[j]);
    }
  }
}
