// $Id: hello.c,v 1.2 2015-01-22 10:59:46-08 - - $
// Adam Paz
// apa10@ucsc.edu
//    hello - print the "Hello, World!" message.
//
// SYNOPSIS
//    hello
//
// DESCRIPTION
//    Prints the "Hello, World!" message if no operands are
//    present.  Errors out with a Usage message otherwise.

 #include <libgen.h>
 #include <stdio.h>
 #include <stdlib.h>

 int main (int argc, char **argv) {
    int exit_status = EXIT_SUCCESS;
    if(argc == 1){
       printf ("Hello, World!\n");
          return exit_status;
    }
    else{
       fprintf(stderr, "Usage: hello\n");
       exit_status = EXIT_FAILURE;
    }
}
