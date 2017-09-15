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

#include "offsetInfo.h"

int64_t timeZone::findOffsetForTime (int64_t time, const offsetInfo_t* offsetInfos, int offsetInfoCount) {
  int start = 0;
  int end = offsetInfoCount;

  int index = (start + end) / 2;
  while (index != start) {
    if (time >= offsetInfos[index].startTime) {
      start = index;
    } else {
      end = index;
    }
    index = (start + end) / 2;
  }
  return offsetInfos[index].offset;
}
