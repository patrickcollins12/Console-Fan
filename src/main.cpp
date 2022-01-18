#include <Arduino.h>

//L293D
const int motorPin_A_forward  = 32; //Motor A - Second motor
const int motorPin_B_forward  = 33; //Motor B - First Motor. Pin 15/Input4 of L293
// NodeMCU: on the left rail with usb facing down looking from the top:
// 5th pin is 34, then 35, 32 33 25 26 27 14 12 13
const int tmp36_a  = 25; // Pin 15/Input4 of L293

void setup(){
    Serial.begin(115200);

    pinMode(motorPin_A_forward, OUTPUT);
    pinMode(motorPin_B_forward, OUTPUT);    

    digitalWrite(motorPin_A_forward, HIGH);
    digitalWrite(motorPin_B_forward, HIGH);

    pinMode(tmp36_a, INPUT_PULLDOWN);
}

void loop(){


    int adc_a;
    adc_a = analogRead(tmp36_a);
    adc_a = analogRead(tmp36_a);

    float mV = adc_a * ( 3300.0 / 4096.0 );
    float celcius = (mV - 500.0) / 10.0;

    Serial.printf("%d/4096, %0.0f/3300mV, %0.1f celcius\n", adc_a, mV, celcius);
    delay(100);
}