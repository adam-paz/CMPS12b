// $Id: err.c,v 1.1 2015-02-09 15:29:25-08 - - $

#include <stdio.h>
void foo() {
   int x = 20;
   int *p = &x;
}
void bar() {
   int a;
   int *p;
   printf ("%d %p\n", a, p);
}
int main() {
   foo();
   bar();
}
