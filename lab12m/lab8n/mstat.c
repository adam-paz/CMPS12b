//Adam Paz (apa10@ucsc.edu)
//$Id$

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <libgen.h>
#include <time.h>

#define SEC_PER_DAY (24 * 60 * 60)
#define SEC_PER_YEAR (SEC_PER_DAY * 365 + SEC_PER_DAY / 4)

int exit_status = EXIT_SUCCESS;

void timestamp (char *filename) {
   struct stat buf;
   struct tm tm;
   int stat = lstat(filename, &buf);
   if (stat != 0) {
       fflush(NULL);
       fprintf (stderr, "mstat: %s: %s\n",
           filename, strerror (errno));
       exit_status = EXIT_FAILURE;
       fflush(NULL);
   } else {
      char buffer[64];
      time_t timer = buf.st_mtime;
      time_t now = time(NULL);
      int diff = now > timer ?(now - timer)/SEC_PER_DAY: (timer-now)/SEC_PER_DAY;
      localtime_r(&timer, &tm);
      if(diff < 180)
          strftime(buffer, sizeof buffer, "%b %e %R", &tm );
      else 
          strftime(buffer, sizeof buffer, "%b %e  %Y", &tm );
      mode_t mode =  buf.st_mode;
      int size =  buf.st_size; 
      printf("%06lo %9d %s %s", (unsigned long) mode, size, buffer, filename );
   }
}


int main (int argc, char **argv){
    char *pathname;
    if (argc == 1)
       pathname = ".";
    else{
       for (int argi = 1; argi<argc; argi++){
          pathname = argv[argi];
          char linkname[PATH_MAX +1];
          int retval = readlink(pathname, linkname, sizeof linkname);
          if (retval!= -1 ) {
             timestamp(pathname);
             linkname[retval < PATH_MAX + 1 ? retval : PATH_MAX] = '\0';
             printf (" -> %s\n", linkname);
          } else {  
             if(pathname ==NULL){ 
                fprintf (stderr, "mstat: %s: %s\n",
                    pathname, strerror (errno));
                exit_status = EXIT_FAILURE;
                return exit_status;
           }
           timestamp(pathname);
           printf("\n");
         }
      }
   }
      return exit_status;
}

