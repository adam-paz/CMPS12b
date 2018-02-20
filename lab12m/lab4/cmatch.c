//$Id$
//Adam Paz (apa10)
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"

typedef struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
} options;

void scan_options(int argc, char **argv, options *opts){
    opts->ignore_case = false;
    opts->filenames_only = false;
    opts->number_lines = false;
    opterr = false;
    for(;;){
        int opt = getopt (argc, argv, "iln");
        if(opt == EOF)break;
        switch(opt){
            case 'i':
                opts->ignore_case = true;
                break;
            case 'l':
                opts->filenames_only = true;
                break;
            case 'n':
                opts->number_lines = true;
                break;
            default:
                exit_status = EXIT_FAILURE;
                fflush (NULL);
                fprintf (stderr, "%s: -%c: invalid option\n",
                             program_name, optopt);
                break;
        }
    }
}

int main (int argc, char **argv){
    program_name = basename(argv[0]);
    char *theword = "word";
    options opts;
    scan_options(argc, argv, &opts);
    int place = 1;
    if(opts.ignore_case == true ||opts.number_lines == true||
                                   opts.filenames_only == true )
    place =2;
    theword = argv[place];
    if(argc == 1){
       fflush(NULL);
       fprintf(stderr, "Usage: %s [-iln] string [filename...]\n",
                                                    program_name);
       fflush(NULL);
       exit_status = EXIT_FAILURE;
    }
    for (int argi = place +1 ; argi < argc; ++argi) {
       char *filename = argv[argi];
       if (strcmp (filename, STDIN_NAME) == 0) {
            printf("%s\n", "standard in");
       }else {
          FILE *input = fopen(filename, "r");
          if(input!= NULL){
              findword(input, theword, filename, opts);
              fclose(input);
          }else {
              exit_status = EXIT_FAILURE;
              fflush (NULL);
              fprintf (stderr, "%s: %s: %s\n", program_name,
                       filename, strerror (errno));
              fflush (NULL); 
          }
       }
    }
    return exit_status;
}
void findword(FILE *input, char *theword, char *filename, options opts){
   char buffer[1024];
   char *word = "hello\n";
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL) break;
      if (opts.ignore_case)
          word = strcasestr(buf, theword);
                    else word = strstr(buf, theword);
      if(word!=NULL && opts.filenames_only == false){
          if(opts.number_lines == true) printf("%d:", linenr);
          printf("%s", buf );
      }
      else if(word!=NULL){
           printf("%s\n", filename);
      }
   } 
}
