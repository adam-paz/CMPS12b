// $Id: nsort.c,v 1.1 2011-04-29 19:46:42-07 - - $
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct node node;
struct node{
       char* str;
       node *link;
};

int main (int argc, char **argv) {
    char *progname = basename (argv[0]);
    node *head = NULL;
    char buffer[82];
    int opt = getopt (argc, argv, "d");
    int linenr = 1;
    for(;;){
       linenr ++;
       char *gotline = fgets (buffer, sizeof buffer, stdin);
       if (gotline == NULL) break;
       char *nlpos = strchr (buffer, '\n');
       if (nlpos != NULL) {
           *nlpos = '\0'; 
       }else {
           fflush(NULL);
           fprintf (stderr, "%s: %d: unterminated line: %s\n",
                  progname, linenr, buffer);
           fflush(NULL);
       };
 
       
       node *curr = head; 
       node *prev = NULL;      
       for(curr = head; curr != NULL; curr = curr->link) {
            char *currstring = curr->str;
            int comp = strcmp(gotline, currstring);
            if (comp < 0) break;
            prev = curr;
       }
        
       node *tmp = malloc(sizeof(struct node));
       tmp->str = strdup (buffer);
       assert(tmp->str != NULL);
       tmp->link = curr;
       if(prev == NULL) head = tmp;
               else prev->link = tmp;
                             
   }
   if (opt == 'd'){
      printf ("%s: head= %p\n", argv[0], head);
      while (head != NULL) {
         node *old = head;
         head = head->link;
         printf ("%s: %p-> node {\n"
              "    string= %p->\"%s\",\n"
              "    link= %p}\n",
              progname, old, old->str, old->str, old->link);
         free(old);
   };

 
   } else {
       while(head != NULL){
          node *old = head;
          printf("%24.15s\n", old->str);
          head = head->link;
          free(old);
       }
   }
   return EXIT_SUCCESS;
}
 

