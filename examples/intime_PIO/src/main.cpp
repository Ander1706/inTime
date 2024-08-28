#include <Arduino.h>
#include <intime.h>
uint16_t cnt = 0;
InTime intime_Cont, intime_Once, intime_Simple, intime_Imm;
uint32_t t;
void setup() {
    Serial.begin(115200);
    while (!Serial)
        delay(1); // Wait until the serial port has opened
    delay(1000);
    Serial.println("Serial connect");
    intime_Cont.set(0.50, true);
    intime_Simple.set(2000, true);
    intime_Once.set(2000, false);
    intime_Imm.set(1000, false, true);
    t = micros();
}

void loop() {
    if (intime_Imm.expired()) {
        Serial.println("int_Imm completed");
    }
    if (intime_Once.expired()) {
        intime_Cont.tmr_on = false;
        Serial.println("int_Once completed");
    }
    if (intime_Simple.expired()) {
        uint32_t tt = micros();
        Serial.print(" dt=");
        Serial.println(tt - t);
        t = tt;
    }
    delay(500);
    Serial.print("tCnt=");
    Serial.println(intime_Simple.get__tickCnt());

    if (intime_Cont.expired()) {
        // Serial.print("int_Cont completed");
        cnt++;
        // Serial.print(" cnt =");
        // Serial.println(cnt);
        uint32_t tt = micros();
        if (tt - t > 10000) {
            // Serial.print(" dt=");
            Serial.print(cnt);
            Serial.print(" ");
            Serial.println(tt - t);
        }
        else
            Serial.println(tt - t);
        t = tt;
    }
}