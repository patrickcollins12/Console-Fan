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
//L293D
const int motorPin_A_forward  = 32; //Motor A - Second motor
const int motorPin_B_forward  = 33; //Motor B - First Motor. Pin 15/Input4 of L293
// NodeMCU: on the left rail with usb facing down looking from the top:
// 5th pin is 34, then 35, 32 33 25 26 27 14 12 13
const int tmp36_a  = 25; // Pin 15/Input4 of L293

void printDHTReading(DHT_Unified dht);
void printDHTSetup(DHT_Unified dht, Neotimer timer);


void setup(){
    Serial.begin(115200);

    pinMode(motorPin_A_forward, OUTPUT);
    pinMode(motorPin_B_forward, OUTPUT);    

    digitalWrite(motorPin_A_forward, HIGH);
    digitalWrite(motorPin_B_forward, LOW);
    Serial.println("Fan A on");

    pinMode(tmp36_a, INPUT_PULLDOWN);

    fanTimer.start();

    // Initialize temp devices.
    dht1.begin();
    dht2.begin();

    printDHTSetup(dht1,tempTimer1);
    printDHTSetup(dht2,tempTimer2);
    
    // delayMS = sensor.min_delay / 1000;

}

bool fanA=0;
void loop(){

    if(fanTimer.repeat() ){
        if (fanA) {
            digitalWrite(motorPin_A_forward, HIGH);
            digitalWrite(motorPin_B_forward, LOW);
            Serial.println("Fan A on");
        } else {
            digitalWrite(motorPin_A_forward, LOW);
            digitalWrite(motorPin_B_forward, HIGH);
            Serial.println("Fan B on");
        }
        fanA = ! fanA;
    }

    if(tempTimer1.repeat() ){
        printDHTReading(dht1);
    }
    if(tempTimer2.repeat() ){
        printDHTReading(dht2);
    }

    // delay(100)
}
void printDHTReading(DHT_Unified dht) {
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.println(F("Error reading temperature!"));
    }
    else {
        Serial.print(F("Temperature: "));
        Serial.print(event.temperature);
        Serial.println(F("°C"));
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
    }
    else {
        Serial.print(F("Humidity: "));
        Serial.print(event.relative_humidity);
        Serial.println(F("%"));
    }
}

void printDHTSetup(DHT_Unified dht, Neotimer timer) {
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F(""));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.

  timer.set(sensor.min_delay);
}

