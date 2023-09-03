/*
  InTime - Library for asynchronous actions.
 * Copyright (C) 2018  Andrey Karpushin
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses
*/

#include "intime.h"

bool InTime::expired(void) {
  if (!tmr_on)
    return false;
  uint32_t ticks = millis();
  if (_immediately){
    _immediately = false;
    return true;
  }
  if (time_from <= time_to || ticks < time_from)
    if (ticks >= time_to) {
      tmr_on = false;
      tickCnt = _time;
      if (_repeat)
        this->set(_time, _repeat);
      return true;
    }
  if (ticks >= time_from)
    tickCnt = ticks - time_from;
  else
    tickCnt = UINT32_MAX - time_from + ticks;
  return false;
}

void InTime::set(uint32_t timeout, bool repeat, bool immediately) {
  _immediately = immediately;
  _repeat = repeat;
  _time = timeout;
  time_from = millis();
  time_to = time_from + timeout;
  tmr_on = true;
  tickCnt = 0;
}
