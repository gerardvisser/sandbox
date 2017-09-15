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

#ifndef DATE_INCLUDED
#define DATE_INCLUDED

class Date {
private:
  int m_daysSinceEpoch;
  int m_year;
  int m_month;
  int m_day;

public:
  Date (int daysSinceEpoch);
  Date (int year, int month, int day);

  int day (void) const;
  int dayOfWeek (void) const;
  int daysSinceEpoch (void) const;
  int month (void) const;
  int year (void) const;

  static bool isLeapYear (int year);

private:
  Date (void);
  void init (int daysSinceEpoch);
  void init (int year, int month, int day);

  friend class DateTime;
};

#endif
