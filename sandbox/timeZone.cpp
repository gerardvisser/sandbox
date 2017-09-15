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

#include <string.h>
#include "Exception.h"
#include "timezones/europeAmsterdam.h"

static const char* const availableZonesIds[] = {
  "Europe/Amsterdam",
  "UTC",
  NULL
};

static int64_t offset (int64_t millisSinceEpoch) {
  return 0;
}

const timeZone::zone_t timeZone::UTC = {"UTC", offset};

const char* const * timeZone::availableZones (void) {
  return availableZonesIds;
}

const timeZone::zone_t* timeZone::zoneFor (const char* zoneId) {
  if (zoneId == NULL) {
    throw Exception ("zoneId is null.");
  }
  /* TODO: Create a map for this.  */
  if (strcmp (zoneId, availableZonesIds[0]) == 0) {
    return &timeZone::amsterdam;
  } else if (strcmp (zoneId, availableZonesIds[1]) == 0) {
    return &timeZone::UTC;
  }
  throw Exception ("Unknown zoneId: %s.", zoneId);
}
