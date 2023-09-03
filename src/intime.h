
#ifndef INTIME_H
#define INTIME_H

/*
  interval - Library for asynchronous actions.
 * Copyright (C) 2018  Andrey Karpushin
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses
*/

#include <arduino.h>
class InTime {
  private:
    uint32_t _time;
    bool _repeat;
    bool _immediately; //check!!!

  public:
    uint32_t time_from;
    uint32_t time_to;
    uint32_t tickCnt;
    bool tmr_on = false;
    bool expired(void);
    void set(uint32_t timeout, bool repeat, bool immediately = false);
};

#endif
