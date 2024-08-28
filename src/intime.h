
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
    bool _immediately;
    bool _useMillis; 
    uint32_t _time_from;
    uint32_t _time_to;
    uint32_t _tickCnt;
    void _set() {
        if (_useMillis) 
            _time_from = millis();
        else 
            _time_from = micros();
        _time_to = _time_from + _time;
        tmr_on = true;
        _tickCnt = 0;
    }
  public:
    bool tmr_on = false; //false - OFF
    bool expired(void) {
        if (!tmr_on)
            return false;
        uint32_t ticks;
        if (_useMillis)
            ticks = millis();
        else
            ticks = micros();
        if (_immediately) {
            _immediately = false;
            return true;
        }
        if (_time_from <= _time_to || ticks < _time_from)
            if (ticks >= _time_to) {
                tmr_on = false;
                _tickCnt = _time;
                if (_repeat)
                    _set();
                return true;
            }
        if (ticks >= _time_from)
            _tickCnt = ticks - _time_from;
        else
            _tickCnt = UINT32_MAX - _time_from + ticks;
        return false;
    }
    void set(float timeout, bool repeat, bool immediately = false) { //if timeout is integer then use millis else micros 
        _immediately = immediately;
        _repeat = repeat;
        float integerPart_float;
        float fractionPart = modff(timeout, &integerPart_float);
        if (fractionPart == 0) {
            _time = timeout;
            //Serial.println("millis");
            _useMillis = true;
        }
        else {
            _time = timeout * 1000;
            _useMillis = false;
            //Serial.println("micros");
        }
        //Serial.printf("time_to:%d\n", time_to);
        _set();
    }
    uint32_t get_time_from(){
        return _time_from;
    }
    uint32_t get_time_to(){
        return _time_to;
    }
    uint32_t get__tickCnt(){
        return _tickCnt;
    }
};

#endif
