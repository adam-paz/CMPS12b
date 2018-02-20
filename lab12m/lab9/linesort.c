//$Id$
//Adam Paz


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inssort.h"

int strstrcmp (const void *this, const void *that) {
   char **thisstr = (char**) this;
   char **thatstr = (char**) that;
   return strcmp (*thisstr, *thatstr);
}

int main (int argc, char **argv){
   (void)argc; (void)argv;
   char *array[0X1000];
   char buffer[88];
   int linenr = 1;
   int i = 0;
   for(;;i++){
      linenr ++;
      char *gotline = fgets (buffer, sizeof buffer, stdin);
      if (gotline == NULL) break;
      if(buffer[strlen(buffer) - 1] == '\n'){
        buffer[strlen(buffer) - 1] = '\0';
      }
      array[i] = strdup(buffer);
   }
   inssort (array, i, sizeof *array, strstrcmp);
   printf("\n");
   for (int ind = 0; ind < i; ind ++){
   printf("%s", array[ind]);
   free(array[ind]);
   }
   return EXIT_SUCCESS;      
}
