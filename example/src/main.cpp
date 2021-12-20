#include <Arduino.h>
#include <intime.h>
uint16_t cnt = 0;
InTime intime_Cont, intime_Once, intime_getTick;

void setup() {
    Serial.begin(115200);
    while (!Serial)
        delay(1); // Wait until the serial port has opened
    delay(1000);
    Serial.println("Serial connect");
    intime_Cont.set(2000, true);
    intime_getTick.set(600, true);
    intime_Once.set(10000, false);
}

void loop() {
    if (intime_Once.expired()) {
        intime_Cont.tmr_on = false;
        Serial.println("int_Once completed");
        intime_getTick.tmr_on = false;
        Serial.println("int_getTick completed");
    }
    if (intime_getTick.expired()) {
        Serial.print("int_Cont cnt=");
        Serial.println(intime_Cont.tickCnt);
    }
    if (intime_Cont.expired()) {
        Serial.println("int_Cont completed");
        cnt++;
        Serial.print("cnt =");
        Serial.println(cnt);
    }
}