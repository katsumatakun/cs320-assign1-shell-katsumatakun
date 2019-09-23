#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define GENERIC_MIN(x, y) ((x) < (y) ? (x) : (y))
int history(char**,int);

//shell program
int main() {
   char fullpath[] = "/bin/;/home/cs320/bin/";
   int nonexit = 1;
   int command_count = 0;
   char* command_ary[20];
    while(nonexit){
      char command[255];
      printf("myshell$: ");
      char* buffer; long unsigned int len;
      int read = getline(&buffer, &len, stdin); //read input
      command_ary[command_count%20]=(char*)(malloc(strlen(buffer)));
      strcpy(command_ary[command_count%20],buffer);
      // printf("command count %d\n",command_count%20 );
      // printf("command inserted %s\n", command_ary[command_count%20]);
      command_count++;
      int bikkuri = strncmp(buffer,"!\n",1); //check if input begins with !
      int bikkuri2 = strcmp(buffer,"!!\n");
      if(!strcmp("exit\n",buffer)){
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
          if(0<num_go_back && mini >num_go_back){
            strcpy(command_ary[(command_count-1)%20],command_ary[(command_count-1-num_go_back)%20]);
            // printf("next command %s\n", command_ary[(command_count-1)%20]);
          }
        }
      }

      //shell programs -> not fork
      if(!strcmp("history\n", command_ary[(command_count-1)%20])){
        history(command_ary,command_count);
      }
      else if (!strcmp("getPATH\n",command_ary[(command_count-1)%20])){
        printf("%s\n", fullpath);
      }
      else if(!strncmp("setPATH ",command_ary[(command_count-1)%20],8)){
        char* new_path = (char*)malloc(len-7);
        for (int i=0;i<len-7;i++){
          new_path[i] = buffer[i+8];
        }
        new_path[strlen(new_path)-1] = '\0';
        // printf("new path %s\n", new_path);
        strcpy(fullpath,new_path);
        }
      //system command -> fork
      else{
        int rc = fork();
        if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
        else if (rc == 0) { // child (new process)

          //figuing out input arguments
          char *args[20];
          int num = 0;
          char*p = strtok(command_ary[(command_count-1)%20], " ");
          while (p)
          {
            if(p[strlen(p)-1] == '\n'){
             p[strlen(p)-1]  = '\0';
           }
             args[num] = p;
             p = strtok(NULL, " ");
             num++;
          }
          args[num] = NULL;
          int len_pro = strlen(args[0]);

          //loop each diretory of PATH
          char*path = strtok(fullpath, ";");
          while(path){
            int len_bin = strlen(path);
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

            //special command
            if(!strcmp("lls",args[0])){
              int rv = execv("./lls", args);
              free(loc);
            }
            else{
            int rv = execv(loc, args);
            free(loc);
            path = strtok(NULL, ";");
          }
          }
          printf("program not found \n");
          exit(1);
        }
        else {
        // parent goes down this path (main)
        wait(NULL);
        // printf("parent finished\n");
      }
     }
  }
return 0;
}

//history command
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
