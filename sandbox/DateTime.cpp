/*
   Author:  Gerard Visser
   e-mail:  visser.gerard(at)gmail.com

   Copyright (C) 2017 Gerard Visser.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <stddef.h>
#include <sys/time.h>
#include "DateTime.h"
#include "Exception.h"

#define MILLIS_IN_DAY 86400000

DateTime::DateTime (const timeZone::zone_t* zone) : m_zone (zone) {
  struct timeval time;
  gettimeofday (&time, NULL);
  m_millisSinceEpoch = (int64_t) time.tv_sec * 1000 + time.tv_usec / 1000;
  initFromTime ();
}

DateTime::DateTime (int64_t millisSinceEpoch, const timeZone::zone_t* zone) : m_zone (zone), m_millisSinceEpoch (millisSinceEpoch) {
  initFromTime ();
}

DateTime::DateTime (int year, int month, int day, const timeZone::zone_t* zone) : m_zone (zone), m_hour (0), m_minute (0), m_second (0) {
  initFromDate (year, month, day);
}

DateTime::DateTime (int year, int month, int day, int hour, int minute, const timeZone::zone_t* zone) : m_zone (zone), m_hour (hour), m_minute (minute), m_second (0) {
  initFromDate (year, month, day);
}

DateTime::DateTime (int year, int month, int day, int hour, int minute, int second, const timeZone::zone_t* zone) : m_zone (zone), m_hour (hour), m_minute (minute), m_second (second) {
  initFromDate (year, month, day);
}

int DateTime::day (void) const {
  return m_date.day ();
}

int DateTime::dayOfWeek (void) const {
  return m_date.dayOfWeek ();
}

int DateTime::hour (void) const {
  return m_hour;
}

void DateTime::initFromDate (int year, int month, int day) {
  m_date.init (year, month, day);
  int64_t time = (int64_t) m_date.daysSinceEpoch () * 24;
  time += m_hour;
  time *= 60;
  time += m_minute;
  time *= 60;
  time += m_second;
  time *= 1000;
  m_millisSinceEpoch = time - m_zone->offset (time);
  int64_t time2 = m_millisSinceEpoch + m_zone->offset (m_millisSinceEpoch);
  if (time2 < time) {
    m_millisSinceEpoch += time - time2;
    time2 = m_millisSinceEpoch + m_zone->offset (m_millisSinceEpoch);
    if (time2 > time) {
      throw Exception ("Illegal date.");
    }
  } else if (time2 > time) {
    m_millisSinceEpoch -= time2 - time;
  }
}

void DateTime::initFromTime (void) {
  int64_t time = m_millisSinceEpoch + m_zone->offset (m_millisSinceEpoch);
  int days = time / MILLIS_IN_DAY;
  time %= MILLIS_IN_DAY;
  if (time < 0) {
    time += MILLIS_IN_DAY;
    --days;
  }
  time /= 1000;
  m_second = time % 60;
  time /= 60;
  m_minute = time % 60;
  time /= 60;
  m_hour = time;
  m_date.init (days);
}

int64_t DateTime::millisSinceEpoch (void) const {
  return m_millisSinceEpoch;
}

int DateTime::minute (void) const {
  return m_minute;
}

int DateTime::month (void) const {
  return m_date.month ();
}

int DateTime::second (void) const {
  return m_second;
}

int DateTime::year (void) const {
  return m_date.year ();
}

const timeZone::zone_t* DateTime::zone (void) const {
  return m_zone;
}
