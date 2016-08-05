/**
   The MySensors Arduino library handles the wireless radio link and protocol
   between your home built sensors/actuators and HA controller of choice.
   The sensors forms a self healing radio network with optional repeaters. Each
   repeater and gateway builds a routing tables in EEPROM which keeps track of the
   network topology allowing messages to be routed to nodes.
   
   Created by mboyer85 / 
   Modified by sincze
   
   Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
   
   Documentation: http://www.mysensors.org
   Support Forum: http://forum.mysensors.org
   
   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   version 2 as published by the Free Software Foundation.
 *******************************
   DESCRIPTION
   
   Example sketch showing how to send HUMIDITY AND TEMPERATURE readings back to the controller
   
   Based upon KY015 / DHT11 / DHT21 / DHT22

   Wiring:
   For regular DHT11 / DHT21 / DHT22
   Connect pin 1 (on the left) of the sensor to +5V
   NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
   to 3.3V instead of 5V!
   Connect pin 2 of the sensor to whatever your D3
   Connect pin 4 (on the right) of the sensor to GROUND
   Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

   For KY015 Sensor DHT11
   Arduino pin D3 --> Pin S module
   Arduino GND --> Pin - module
   Arduino +5 --> Pin Middle
*/

// Enable debug prints to serial monitor
#define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_NRF24
//#define MY_RADIO_RFM69

#include <SPI.h>
#include <MySensors.h>
#include "DHT.h"

#define CHILD_ID_HUM 0
#define CHILD_ID_TEMP 1

#define COMPARE_TEMP 0                // Send Humid and Temperature only if changed? 1 = Yes 0 = No
#define HUMIDITY_SENSOR_DIGITAL_PIN 3 // what digital pin we're connected to Digital Pin 3

// Uncomment whatever type you're using!
#define DHTTYPE DHT11                 // DHT 11
//#define DHTTYPE DHT22               // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21               // DHT 21 (AM2301)

float temp_calibration = 2.3;       // My Sensor was not that accurate so I had to deduct this value from reading
float humid_calibration = 9;        // My Sensor was not that accurate so I had to add this value to the reading
float lastTemperature;

unsigned long SLEEP_TIME = 60000;   // Sleep time between reads (in milliseconds)

// boolean receivedConfig = false;
// boolean metric = true;

// Initialize DHT sensor.
DHT dht(HUMIDITY_SENSOR_DIGITAL_PIN, DHTTYPE);

MyMessage msgHum(CHILD_ID_HUM, V_HUM);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);

void setup()
{
  //Setup your PH sensor here (I2C,Serial,Phidget...)
  dht.begin();
}

void presentation() {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Humidity / Temperature ", "1.0");
  // Register all sensors to gw (they will be created as child devices)
  present(CHILD_ID_HUM, S_HUM);
  present(CHILD_ID_TEMP, S_TEMP);
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

  // Only send data if temperature has changed and no error (before calibration)
  #if COMPARE_TEMP == 1
  if (lastTemperature != temperature && temperature != -127.00 && temperature != 85.00) {
    #else
    if (t != -127.00 && t != 85.00) {
    #endif
  lastTemperature=t;

    // Calculate calibrated values
    t = t-temp_calibration;
    h = h+9;
    Serial.print("Calibrated Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Calibrated Temperature: ");
    Serial.print(t);
    Serial.println(" *C ");
  
    send(msgHum.set(h,1));        // Calibrated Values will be presented
    send(msgTemp.set(t,1));     // Calibrated Values will be presented
    }
    
  sleep(SLEEP_TIME);
}
