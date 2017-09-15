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

#include "Date.h"
#include "Exception.h"

#define MEAN_YEAR_LENGTH 365.2425

static const int yearMonthEnd[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
static const int leapYearMonthEnd[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

static int daysSince1970AtStartOfYear (int year);
static int leapCountSince1970AtStartOfYear (int year);

Date::Date (void) {
  /* Does not initialize.  */
}

Date::Date (int daysSinceEpoch) {
  init (daysSinceEpoch);
}

Date::Date (int year, int month, int day) {
  init (year, month, day);
}

int Date::day (void) const {
  return m_day;
}

/* 1: Monday, ..., 7: Sunday.  */
int Date::dayOfWeek (void) const {
  int d = (m_daysSinceEpoch + 3) % 7;
  if (d < 0)
    d += 7;
  return d + 1;
}

int Date::daysSinceEpoch (void) const {
  return m_daysSinceEpoch;
}

void Date::init (int daysSinceEpoch) {
  m_daysSinceEpoch = daysSinceEpoch;
  m_year = (int) (1970.003 + daysSinceEpoch / MEAN_YEAR_LENGTH);
  int daysSinceYearStart = daysSinceEpoch - daysSince1970AtStartOfYear (m_year);
  if (daysSinceYearStart >= 0) {
    const int* monthEnd = Date::isLeapYear (m_year) ? leapYearMonthEnd : yearMonthEnd;
    m_month = 1;
    while (daysSinceYearStart >= monthEnd[m_month]) {
      ++m_month;
    }
    m_day = daysSinceYearStart - monthEnd[m_month - 1] + 1;
  } else {
    --m_year;
    m_month = 12;
    m_day = 32 + daysSinceYearStart;
  }
}

void Date::init (int year, int month, int day) {
  const int* monthEnd = Date::isLeapYear (year) ? leapYearMonthEnd : yearMonthEnd;
  if (month < 1 || month > 12) {
    throw Exception ("month out of range.");
  }
  if (day < 1 || day > monthEnd[month] - monthEnd[month - 1]) {
    throw Exception ("day out of range.");
  }
  m_daysSinceEpoch = daysSince1970AtStartOfYear (year) + monthEnd[month - 1] + day - 1;
  m_year = year;
  m_month = month;
  m_day = day;
}

bool Date::isLeapYear (int year) {
  return year % 4 == 0 ^ year % 100 == 0 ^ year % 400 == 0;
}

int Date::month (void) const {
  return m_month;
}

int Date::year (void) const {
  return m_year;
}

static int daysSince1970AtStartOfYear (int year) {
  int leapCount = leapCountSince1970AtStartOfYear (year);
  int nonleapCount = year - 1970 - leapCount;
  return 365 * nonleapCount + 366 * leapCount;
}

static int leapCountSince1970AtStartOfYear (int year) {
  year -= 1970;
  if (year < 0)
    return (year - 2) / 4 - (year - 30) / 100 + (year - 30) / 400;
  else
    return (year + 1) / 4 - (year + 69) / 100 + (year + 369) / 400;
}
