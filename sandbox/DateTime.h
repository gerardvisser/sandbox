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

#ifndef DATE_TIME_INCLUDED
#define DATE_TIME_INCLUDED

#include <stdint.h>
#include "Date.h"
#include "timeZone.h"

class DateTime {
private:
  const timeZone::zone_t* const m_zone;
  int64_t m_millisSinceEpoch;
  Date m_date;
  int m_hour;
  int m_minute;
  int m_second;

public:
  DateTime (const timeZone::zone_t* zone = &timeZone::UTC);
  DateTime (int64_t millisSinceEpoch, const timeZone::zone_t* zone = &timeZone::UTC);
  DateTime (int year, int month, int day, const timeZone::zone_t* zone = &timeZone::UTC);
  DateTime (int year, int month, int day, int hour, int minute, const timeZone::zone_t* zone = &timeZone::UTC);
  DateTime (int year, int month, int day, int hour, int minute, int second, const timeZone::zone_t* zone = &timeZone::UTC);

  int day (void) const;
  int dayOfWeek (void) const;
  int hour (void) const;
  int64_t millisSinceEpoch (void) const;
  int minute (void) const;
  int month (void) const;
  int second (void) const;
  int year (void) const;
  const timeZone::zone_t* zone (void) const;

private:
  void initFromDate (int year, int month, int day);
  void initFromTime (void);
};

#endif
