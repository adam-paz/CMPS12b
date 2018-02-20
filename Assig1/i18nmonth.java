// $Id: i18nmonth.java,v 1.4 2013-04-11 14:51:27-07 - - $
//
// NAME
//    i18nmonth - print out the days of this month in a language
//
// SYNOPSIS
//    i18nmonth [language]
//
// DESCRIPTION
//    Prints out (in sloppy but easy to program format) one line
//    for each day in the month.  A language code may be specified.
//    The associated program LocaleInfo.java prints out language
//    codes known to Java.
//
//    ISO-639 language codes and ISO-3166 country codes are at:
//    http://www.ics.uci.edu/pub/ietf/http/related/iso639.txt
//    http://userpage.chemie.fu-berlin.de/diverse/doc/ISO_3166.html
//
//    Format string syntax is described at:
//    http://java.sun.com/j2se/1.5.0/docs/api/java/util/Formatter.html
//

import java.util.GregorianCalendar;
import java.util.Locale;
import static java.lang.System.*;

class i18nmonth {

   public static void main (String[] args) {

      // Get the locale from args[0]
      Locale locale = args.length == 0
                    ? Locale.getDefault()
                    : new Locale (args[0]);

      // Get the calendar for the current day.
      GregorianCalendar cal = new GregorianCalendar();

      // Back up to the first day of the month.
      int today = cal.get (GregorianCalendar.DAY_OF_MONTH);
      cal.add (GregorianCalendar.DAY_OF_MONTH, 1 - today);

      // Loop, printing out every day of this month.
      for (int thismonth = cal.get (GregorianCalendar.MONTH);
           thismonth == cal.get (GregorianCalendar.MONTH);
           cal.add (GregorianCalendar.DAY_OF_MONTH, 1)
      ) {
         out.printf (locale, "%s: %tY %<tB %<2te => %<tA (%d).%n",
                     locale.getDisplayLanguage(), cal,
                     cal.get (GregorianCalendar.DAY_OF_WEEK));
      }
   }

}

//TEST// i18nmonth de >i18nmonth.de.out
//TEST// i18nmonth en >i18nmonth.en.out
//TEST// i18nmonth es >i18nmonth.es.out
//TEST// i18nmonth fr >i18nmonth.fr.out
//TEST// mkpspdf i18nmonth.ps i18nmonth.java* i18nmonth.*.out

