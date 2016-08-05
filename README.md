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
