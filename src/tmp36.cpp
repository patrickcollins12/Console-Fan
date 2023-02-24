#include <Arduino.h>

const int tmp36  = 4; 

void setup(){
    Serial.begin(9600);
    pinMode(tmp36, INPUT_PULLDOWN);
}

void loop(){
    int tempa = analogRead(tmp36);

    float mV = ( tempa / 4096.0 ) * 3300;
    float celcius = (mV - 500.0) / 10.0;

    // 822/4096, 662/3300mV, 16.2 celcius
    Serial.printf("%d/4096, %0.0f/3300mV, %0.1f celcius\n", tempa, mV, celcius);
}

