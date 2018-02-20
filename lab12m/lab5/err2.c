// $Id: err2.c,v 1.1 2015-02-09 15:29:25-08 - - $

#include <stdio.h>
#include <string.h>
int main (void) {
   char *p = 20;
   int c = strcmp (p, "foo");
   printf ("%d\n", c);
   return 0;
}
