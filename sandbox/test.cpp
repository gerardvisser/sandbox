#include <stdio.h>
#include <stdlib.h>
#include "Exception.h"
#include "DateTime.h"

static void printDate (const DateTime& date);
static void printTime (int hour, int minute, int second, int milli = -1);

int main (int argc, char** args, char** env) {
  try {
    //const DateTime date (timeZone::zoneFor ("Europe/Amsterdam"));
    const DateTime date (2017, 10, 29, 1, 59, 59, timeZone::zoneFor ("Europe/Amsterdam"));
    //const DateTime date (1937, 7, 1, 0, 0, timeZone::zoneFor ("Europe/Amsterdam"));
    //const DateTime date (-935022000000, timeZone::zoneFor ("Europe/Amsterdam"));
    //const DateTime date (-1025745572130L);

    printDate (date);


  } catch (Exception x) {
    printf ("Error: %s\n", x.message ());
  }
  return 0;
}

static void printDate (const DateTime& date) {
  int64_t offset = date.zone ()->offset (date.millisSinceEpoch ());
  char offsetSign;
  if (offset < 0) {
    offset = -offset;
    offsetSign = '-';
  } else {
    offsetSign = '+';
  }
  int offsetMilli = offset % 1000;
  offset /= 1000;
  int offsetSecond = offset % 60;
  offset /= 60;
  int offsetMinute = offset % 60;
  offset /= 60;
  int offsetHour = offset;

  printf ("%04d-%02d-%02d ", date.year (), date.month (), date.day ());
  printTime (date.hour (), date.minute (), date.second ());
  printf (" (tz=%c", offsetSign);
  printTime (offsetHour, offsetMinute, offsetSecond, offsetMilli);
  printf ("[%s], t=%ld)\n", date.zone ()->id, date.millisSinceEpoch ());
}

static void printTime (int hour, int minute, int second, int milli) {
  if (milli == -1)
    printf ("%02d:%02d:%02d", hour, minute, second);
  else
    printf ("%02d:%02d:%02d.%03d", hour, minute, second, milli);
}
