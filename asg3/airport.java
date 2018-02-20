// $Id: airport.java,v 1.59 2015-02-17 14:46:20-08 - - $

//Adam Paz (apa10@ucsc.edu)
//Kevin Cai (kcai2@ucsc.edu)

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class airport {
   private static final String STDIN_FILENAME = "-";

   public static treemap load_database (String database_name) {
      treemap tree = new treemap ();
      int nothing;//arbitrary for the else statement
      try {
         Scanner database = new Scanner (new File (database_name));
         for (int linenr = 1; database.hasNextLine(); ++linenr) {
            String line = database.nextLine();
            while(line.substring(0,1).equals('#')){
                line = database.nextLine();
                ++linenr;
            }     
                if (line.matches ("^\\s*(#.*)?$")) continue;
                String[] keyvalue = line.split (":");
                if (keyvalue.length != 2) {
                    misc.warn (database_name, linenr, "invalid line");
                    continue;
            }
            tree.put (keyvalue[0], keyvalue[1]);
         }
         database.close();
      }catch (IOException error) {
         misc.warn (error.getMessage());
         exit(misc.exit_status);
      }
      return tree;
   } 

   public static void main (String[] args) {
       if(args.length < 1){
          err.printf("Usage: airport [-d] database%n");
          exit(1);
      }

      int pos = 0;
      boolean dbg = false;
      if(args[0].substring(0,1).equals("-")){
           pos = 1;
           if(args[0].substring(1,2).equals("d"))
                dbg = true;
                       else {
                         err.printf("Usage: airport [-d] database%n");
                         exit(1);
                       } 
      }   
                       
      if(args.length > pos+1){
          err.printf("Usage: airport [-d] database%n");
          exit(1);
      }

      treemap tree = load_database (args[pos]);
      Scanner stdin = new Scanner (in);
      if(dbg ==true)
           tree.debug_tree();
      while (stdin.hasNextLine()) {
         String airport = stdin.nextLine().toUpperCase().trim();
         String airport_name = tree.get (airport);
         if (airport_name == null) {
            misc.warn(airport,"no such airport");
         }else {
            out.printf ("%s = %s%n", airport, airport_name);
         }
      }
      //tree.debug_tree ();
      exit (misc.exit_status);
   }

}
