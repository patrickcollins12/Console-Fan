#include <Arduino.h>
#include <neotimer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN1 21
#define DHTPIN2 19

DHT_Unified dht1(DHTPIN1, DHT11);
DHT_Unified dht2(DHTPIN2, DHT11);

uint32_t delayMS;

Neotimer fanTimer = Neotimer(5*1000); //  timer
Neotimer tempTimer1 = Neotimer(); //  timer
Neotimer tempTimer2 = Neotimer(); //  timer

const int freq = 5000;
const int pwmChannel = 0;
const int resolution = 8;

//L293D - Final configuration
const int motorPin_A_forward  = 32; //Motor A - 1st motor on/off
const int motorPin_A_speed    = 13; //Motor A - 1st motor speed
// const int motorPin_A_forward  = 33; //Motor A - 1st motor on/off
// const int motorPin_A_speed    = 14; //Motor A - 1st motor speed


// const int motorPin_B_forward  = 33; //Motor B - 2nd Motor. Pin 15/Input4 of L293
// const int motorPin_B_speed    = 14; //Motor B - 2nd motor speed

  const int tmp36_a  = 4; 

void printDHTReading(DHT_Unified dht);
void printDHTSetup(DHT_Unified dht, Neotimer timer);


void setup(){
    Serial.begin(9600);

    pinMode(motorPin_A_forward, OUTPUT);
    // pinMode(motorPin_B_forward, OUTPUT);    

    digitalWrite(motorPin_A_forward, HIGH);
    // digitalWrite(motorPin_B_forward, LOW);

    Serial.println("Fan A on");

    // setting PWM properties
      // configure LED PWM functionalitites
    ledcSetup(pwmChannel, freq, resolution);
    
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(motorPin_A_speed, pwmChannel);

    pinMode(tmp36_a, INPUT_PULLDOWN);
    // 829/4096, 668/3300mV, 16.8 celcius
    // fanTimer.start();

    // // Initialize temp devices.
    // dht1.begin();
    // dht2.begin();

    // printDHTSetup(dht1,tempTimer1);
    // printDHTSetup(dht2,tempTimer2);
    
    // delayMS = sensor.min_delay / 1000;

}

bool fanA=0;

void loop(){

    int adc_a;
    adc_a = analogRead(tmp36_a);
    adc_a = analogRead(tmp36_a);

    float mV = ( adc_a / 4096.0 ) * 3300;
    float celcius = (mV - 500.0) / 10.0;

    Serial.printf("%d/4096, %0.0f/3300mV, %0.1f celcius\n", adc_a, mV, celcius);


    // digitalWrite(motorPin_A_forward, HIGH);

    // ledcWrite(pwmChannel, 255);
    // delay(6000);
    // ledcWrite(pwmChannel, 40);
    // delay(6000);

    // ledcWrite(pwmChannel, 35);
    // delay(3000000);

    // for(int dutyCycle = 40; dutyCycle >= 0; dutyCycle--   ){
    //     // changing the LED brightness with PWM
    //     ledcWrite(pwmChannel, dutyCycle);
    //     delay(2000);
    //     Serial.println(dutyCycle);
    // }
    // ledcWrite(pwmChannel, 0);
    // delay(5000);

    // if(fanTimer.repeat() ){
    //     if (fanA) {
    //         digitalWrite(motorPin_A_forward, HIGH);
    //         Serial.println("Fan A on");
    //     } else {
    //         digitalWrite(motorPin_A_forward, LOW);
    //         Serial.println("Fan B on");
    //     }
    //     fanA = ! fanA;
    // }

    // if(tempTimer1.repeat() ){
    //     printDHTReading(dht1);
    // }
    // if(tempTimer2.repeat() ){
    //     printDHTReading(dht2);
    // }

    // delay(100)
}

// void printDHTReading(DHT_Unified dht) {
//     sensors_event_t event;
//     dht.temperature().getEvent(&event);
//     if (isnan(event.temperature)) {
//         Serial.println(F("Error reading temperature!"));
//     }
//     else {
//         Serial.print(F("Temperature: "));
//         Serial.print(event.temperature);
//         Serial.println(F("°C"));
//     }
//     // Get humidity event and print its value.
//     dht.humidity().getEvent(&event);
//     if (isnan(event.relative_humidity)) {
//         Serial.println(F("Error reading humidity!"));
//     }
//     else {
//         Serial.print(F("Humidity: "));
//         Serial.print(event.relative_humidity);
//         Serial.println(F("%"));
//     }
// }

// void printDHTSetup(DHT_Unified dht, Neotimer timer) {
//   sensor_t sensor;
//   dht.temperature().getSensor(&sensor);
//   Serial.println(F("------------------------------------"));
//   Serial.println(F("Temperature Sensor"));
//   Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
//   Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
//   Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
//   Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
//   Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
//   Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
//   Serial.println(F(""));
//   // Print humidity sensor details.
//   dht.humidity().getSensor(&sensor);
//   Serial.println(F("Humidity Sensor"));
//   Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
//   Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
//   Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
//   Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
//   Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
//   Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
//   Serial.println(F("------------------------------------"));
//   // Set delay between sensor readings based on sensor details.

//   timer.set(sensor.min_delay);
// }

