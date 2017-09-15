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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Exception.h"

Exception::Exception (const char* message, ...) {
  if (message == NULL) {
    message = "(null)";
  }
  va_list argp;
  int defaultSize = 64;
  va_start (argp, message);
  m_message = (char*) malloc (defaultSize);
  int size = vsnprintf (m_message, defaultSize, message, argp) + 1;
  if (size > defaultSize) {
    va_end (argp);
    va_start (argp, message);
    m_message = (char*) realloc (m_message, size);
    vsnprintf (m_message, size, message, argp);
  }
  va_end (argp);
}

Exception::Exception (const Exception& exception) {
  int len = strlen (exception.m_message) + 1;
  m_message = (char*) malloc (len);
  memcpy (m_message, exception.m_message, len);
}

Exception::~Exception (void) {
  free (m_message);
}

const char* Exception::message (void) const {
  return m_message;
}
