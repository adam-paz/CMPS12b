//$Id: environ.c,v 1.4 2015-02-10 16:19:40-08 - - $
//Adam Paz (apa10@ucsc.edu)

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    extern char **environ;
    for(int i = 0; environ[i]!=NULL; i++)
          printf("%s\n", environ[i]);
}
