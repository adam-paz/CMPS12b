//Adam Paz
//apa10@ucsc.edu
// $Id: jcal.java,v 1.25 2015-01-20 19:26:59-08 - - $

import java.util.*;
import java.io.*;
import static java.lang.System.*;
import java.text.*;

class jcal {
   static final int MONTHS_IN_YEAR = 12;
   static final int WEEKS_IN_MONTH =  6;
   static final int DAYS_IN_WEEK   =  7;
   static Locale locale;
   static final GregorianCalendar CHANGE_DATE
               = new GregorianCalendar (1752, 9, 14);

   public static void main (String[] args) {
      int[][] month = new int[WEEKS_IN_MONTH][DAYS_IN_WEEK]; 
      int calmonth=13, calyear=10000, k= 0;
      GregorianCalendar cal = new GregorianCalendar();
      cal.setGregorianChange (CHANGE_DATE.getTime());
         try{
            if(args.length>0){
               if (args[0].substring(0,1).equals("-")){
                  locale = new Locale( args[0].substring(1,3));
                  k = 1;
               }
            }
            if (args.length == k+1){
               calyear =  Integer.parseInt(args[k]);
               cal = new GregorianCalendar(calyear, 0, 1);
               make_year(calyear, month, cal); 
            }    
            else if (args.length == k+2){
               calmonth =  Integer.parseInt(args[k])-1;
               calyear=  Integer.parseInt(args[k+1]);
               cal = new GregorianCalendar(calyear, calmonth, 1);
               to_month(calmonth, month, cal);
            }
            else {
              calmonth = cal.get (GregorianCalendar.MONTH);
              calyear  = cal.get (GregorianCalendar.YEAR);
              cal = new GregorianCalendar(calyear, calmonth, 1);
              to_month(calmonth, month, cal);
           }
        }catch (NumberFormatException error) {
               if(calmonth>12 && args.length != 1)
               misclib.die("illegal month value: use 1-12");
               else
               misclib.die("illegal year value: use 1-9999");
            System.exit(1);
        }
        System.exit(0);
   }

   static void make_year (int calyear, int[][] month,
                         GregorianCalendar cal){
        int [][][] year = new int[MONTHS_IN_YEAR][WEEKS_IN_MONTH]
                               [DAYS_IN_WEEK];
        String[] weekdays = new String[7];
        String[] names = new String[12];
        int calmonth = 0, weeks =0;
        out.printf("%35tY%n%n",cal);
        for(int monthOfYear =0; monthOfYear< MONTHS_IN_YEAR;
                                monthOfYear++){
           cal = new GregorianCalendar(calyear, monthOfYear, 1);
           String moname = String.format(locale, "%tB",cal);
           make_month(month, monthOfYear, cal, weekdays);
           names[monthOfYear] = moname;
           for (int week = 0; week< 6; week++) {
              for (int day = 0; day < 7; ++day) {
                 year[monthOfYear][week][day] = month[week][day];
              }
           }
        }
             print_year(year, names ,weekdays, cal);
   }
   static void print_year(int[][][] year, String[] names, 
                          String[] weekdays, GregorianCalendar cal){
      int mo = 0, columns = 3, lines = 4;
      for(int line = 0; line<lines; line++){
         out.printf("%14s%23s%21s%n", names[mo], names[mo+1],
                    names[mo +2]);
            for(int incr =0; incr<columns; incr++){
               for (int i = 0; i<DAYS_IN_WEEK; i++){
                  String dayname = weekdays[i];
                  out.printf(i == 0 ? "%2s": "%3s",
                             twoLetter(dayname, 2));
               }
            out.printf("   ");
         }
         out.printf("%n");
         for(int weeks = 0; weeks<WEEKS_IN_MONTH; weeks++){
            int months = mo;
            for(int column = 0; column<3; column++){
               months++;
               for(int days = 0; days< DAYS_IN_WEEK; days++){
                   if(year[months-1][weeks][days] == 0)
                      out.printf (days == 0 ? "%2s" : "%3s", " ");
                   else
                       out.printf (days == 0 ? "%2d" : "%3d",
                                  year[months-1][weeks][days]); 
                   }
                out.printf(column == 2 ? "%n" : "   ");
                }
             }
       out.printf("%n");
       mo = mo +3;
         }
   out.printf("%n");
   }
 
   static void to_month(int calmonth,int[][] month, 
                           GregorianCalendar cal){
      int i =0;
      String[] weekdays = new String[7];
      String moname = "month name";
      moname = String.format(locale,"%tB",cal);
      make_month(month, calmonth, cal, weekdays); 
      print_month(moname,weekdays,month, cal);
    }

    static void print_month(String moname, String[] weekdays,
                           int[][] month, GregorianCalendar cal){
       out.printf(locale, "%11s%5tY%n", moname, cal );
       //passing in moname becasue %tB would be the next month
       for (int i = 0; i<DAYS_IN_WEEK; i++){
          String dayname = weekdays[i];
          out.printf(i == 0 ? "%2s": "%3s",twoLetter(dayname, 2));
       }
       out.printf("%n");

       for (int[] week: month) {
          for (int day = 0; day < week.length; ++day) {
             if(week[day] == 0)
                 out.printf (day == 0 ? "%2s" : "%3s", " ");
             else
                out.printf (day == 0 ? "%2d" : "%3d", week[day]);
             
          }
          out.printf("%n");
        }
   }

   static String twoLetter (String dayname, int length){
   //taken frommackey's misc/calnames
      return length > dayname.length ()
      ? dayname
      : dayname.substring (0, length);
   }

   static void make_month(int[][] month, int calmonth, 
                          GregorianCalendar cal,String[] weekdays){
      int i =0;

      for(int p = 0; p<WEEKS_IN_MONTH; p++){
         for(int k = 0; k<DAYS_IN_WEEK; k++){
            month[p][k] = 0;
         }
      }

      while (calmonth == cal.get (GregorianCalendar.MONTH)) {
           int calday = cal.get (GregorianCalendar.DAY_OF_MONTH);
           int weekday = cal.get (GregorianCalendar.DAY_OF_WEEK)-1;
           int weekNum = cal.get(GregorianCalendar.WEEK_OF_MONTH);
           String dayname = String.format (locale,"%tA",cal);
        
           if(weekday ==i ) {
              weekdays[i] = twoLetter(dayname, 2);
              i++;
           }
        
           month[weekNum-1][weekday] = calday;
           cal.add(GregorianCalendar.DAY_OF_MONTH, 1);
        }
    }
}
