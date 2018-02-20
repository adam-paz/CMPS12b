//Adam Paz
//apa10@ucsc.edu
// $Id: jcal.java,v 1.2 2013-03-27 21:24:26-07 - - $

import java.util.*;
import java.io.*;
import static java.lang.System.*;
import java.text.*;

class newcal {
   static final int MONTHS_IN_YEAR = 12;
   static final int WEEKS_IN_MONTH =  6;
   static final int DAYS_IN_WEEK   =  7;
   static boolean fullyear = false;
   static final GregorianCalendar CHANGE_DATE
               = new GregorianCalendar (1752, Calendar.SEPTEMBER, 14);


   public static void main (String[] args) {
      int[][] month = new int[WEEKS_IN_MONTH][DAYS_IN_WEEK]; 
      int calmonth, calyear,ui0 = 0, ui1=0, ui2=0 ;
      GregorianCalendar cal = new GregorianCalendar();
      cal.setGregorianChange (CHANGE_DATE.getTime());
      
      /*for(int argi = 0; argi < args.length; ++argi) {
         try{
             ui0 = Integer.parseInt(args[0]);
             ui1 = Integer.parseInt(args[1]);
             ui2 = Integer.parseInt(args[2]);
         } catch (NumberFormatException error) {
             if(args.length == 1)
                err.printf("cal: illegal year value: use 1-9999");
             if(args.length ==2)
                err.printf("cal: illegal month value: use 1-12");
         }
      }
      userIn(ui0, ui1, ui2);
   }
   static void userIn(int ui0, int ui1, int ui2){*/
      if (args.length == 1){
          calyear =  Integer.parseInt(args[0]);
          cal = new GregorianCalendar(calyear, 0, 1);
          make_year(calyear, month, cal); 
          }    
      else if(args.length >1 && args.length<= 2){
          calmonth =  Integer.parseInt(args[0])-1;
          calyear =  Integer.parseInt(args[1]);
          cal = new GregorianCalendar(calyear, calmonth, 1);
          to_month(calmonth, month, cal);
      }
      else if(args.length>2){
         Locale locale = args.length == 0//taken from mackey i18nmonth
         ? Locale.getDefault()
         : new Locale (args[0]);
      }
      else{
          calmonth = cal.get (GregorianCalendar.MONTH);
          calyear  = cal.get (GregorianCalendar.YEAR);
          cal = new GregorianCalendar(calyear, calmonth, 1);
          to_month(calmonth, month, cal);
       }
   System.exit(0);
   }
   static void make_year(int calyear, int[][] month,
                         GregorianCalendar cal){
        int [][][] year = new int[MONTHS_IN_YEAR][WEEKS_IN_MONTH]
                               [DAYS_IN_WEEK];
          String[] weekdays = new String[7];
          String moname = "month name";
          String[] names = new String[12];
        int calmonth = 0, weeks =0;
        for(int monthOfYear =0; monthOfYear< MONTHS_IN_YEAR; monthOfYear++){
           cal = new GregorianCalendar(calyear, monthOfYear, 1);
           moname = String.format("%tB",cal);
           //make_month(calmonth, month, cal);
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
      int mo = 0;
      out.printf("%35tY%n%n",cal);
      for(int line = 0; line<4; line++){
         out.printf("%14s%23s%21s%n", names[mo], names[mo+1],names[mo +2]);
            for(int incr =0; incr<3; incr++){
               for (int i = 0; i<7; i++){
                  String dayname = weekdays[i];
                  out.printf(i == 0 ? "%2s": "%3s",twoLetter(dayname, 2));
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
                       out.printf (days == 0 ? "%2d" : "%3d",year[months-1][weeks][days]); 
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
      moname = String.format("%tB",cal);
      make_month(month, calmonth, cal, weekdays); 
      print_month(moname,weekdays,month, cal);
}
    static void print_month(String moname, String[] weekdays,
                           int[][] month, GregorianCalendar cal){
       out.printf("%11s%5tY%n", moname, cal );
       for (int i = 0; i<7; i++){
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
   static String twoLetter(String dayname, int length){
   //taken frommackey's misc/calnames
      return length > dayname.length ()
      ? dayname
      : dayname.substring (0, length);
   }		
   static void make_month(int[][] month, int calmonth, GregorianCalendar cal, String[] weekdays){
      int i =0;
      for(int p = 0; p<6; p++){
         for(int k = 0; k<7; k++){
            month[p][k] = 0;
}
}
      while (calmonth == cal.get (GregorianCalendar.MONTH)) {
           int calday = cal.get (GregorianCalendar.DAY_OF_MONTH);
           int weekday = cal.get (GregorianCalendar.DAY_OF_WEEK)-1;
           int weekNum = cal.get(GregorianCalendar.WEEK_OF_MONTH);
           String dayname = String.format ("%tA",cal);
              if(weekday ==i ) 
                 weekdays[i++] = twoLetter(dayname, 2);
                 month[weekNum-1][weekday] = calday;
                 cal.add(GregorianCalendar.DAY_OF_MONTH, 1);
              }
                 }
}
