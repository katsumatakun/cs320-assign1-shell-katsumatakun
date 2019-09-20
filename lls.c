#include <stdio.h>
#include <unistd.h>
int main(){
  char* ary[3];
  ary[0] = "/bin/ls";
  ary[1] = "-l";
  ary[2] = NULL;
  int rv = execv(ary[0], ary);
}
