// $Id: nsort.c,v 1.1 2011-04-29 19:46:42-07 - - $
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
typedef struct node node;
struct node{
       double num;
       node *link;
};

int main (int argc, char **argv) {
    char *progname = basename (argv[0]);
    node *head = NULL;
    double number;
    int opt = getopt (argc, argv, "d");
    for(;;){
       int scan = scanf( "%lg", &number);
            if(scan == EOF) break;
            if(scan == 0){
               fflush(NULL);
               fprintf(stderr, "Invalid argument\n");
               fflush(NULL);
               break;
             }      
 
       node *curr = head; 
       node *prev = NULL;      

       for(curr = head; curr != NULL; curr = curr->link) {
            if (curr->num > number) break;
            prev = curr;
       }
        
       node *tmp = malloc(sizeof(struct node));
       tmp->num = number;
       assert(tmp != NULL);
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
              "    string= %p->\"%g\",\n"
              "    link= %p}\n",
              progname, old, old->num, old->num, old->link);
        free(old);
   }; 
   
   } else {
       while(head != NULL){
          node *old = head;
          printf("%24.15g\n", old->num);
          head = head->link;
          free(old);
       }
   }
   return EXIT_SUCCESS;
}
  
