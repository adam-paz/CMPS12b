// $Id: uninit.c,v 1.1 2015-02-09 15:04:22-08 - - $

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   int *pointer;
   printf ("pointer=%p\n", pointer);
   printf ("*pointer=%d\n", *pointer);
   int foo;
   printf ("foo=%d\n", foo);
}
