//$Id$
//Adam Paz


#include <stdio.h>
#include <stdlib.h>

#include "inssort.h"

int intcmp (const void *obj, const void *obj2) {
    double  *this = (double*) obj;
    double *that = (double*) obj2;
    //return *this < *that ? -1 : *this > *that ? +1 : 0;
    if (*this == *that ) return 0;
    else   return *this > *that ? 1 : -1;
}


int main (int argc, char **argv) {
   (void) argc; (void) argv;
   double number;
   double array[0x1000];
   size_t i = 0;
   for(;;i++){
   int scan = scanf( "%lg", &number);
        if(scan == EOF) break;
        if(scan != 1) break;
    array[i] = number;
    }  
//    const size_t nelem = sizeof array / sizeof *array;
    inssort (array, i, sizeof *array, intcmp);
    for (size_t itor = 0; itor < i ; itor ++)
       printf("%20.15g\n", array[itor]);
    return EXIT_SUCCESS;
}
