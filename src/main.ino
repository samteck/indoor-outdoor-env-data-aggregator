/*
 * indoor-outdoor-env-data-aggregator
 * Author: Samarth Gupta
 * Started Date: 19/11/20
 * Version: 1.0
 */

/////////////////////////////////////////////////////////////////////////


// Including the libraries
#include <dht.h>

// Object creation for DHT sensors
dht indoor_Sensor;
dht outdoor_Sensor;

// Pinout define on Arduino Board
//// Digital Pins
#define DHT_INDOOR_PIN 7
#define DHT_OUTDOOR_PIN 8
//// Analog Pins
#define MQ_INDOOR_PIN 0
#define MQ_OUTDOOR_PIN 1

// Variables to hold sensor values
int indoor_Temp;
int indoor_Humidity;
int indoor_Aqi;
int outdoor_Temp;
int outdoor_Humidity;
int outdoor_Aqi;

void setup()
{
  Serial.begin(9600);  //serial port data write speed
}

void loop()
{
  // Object initialization for DHT sensors
  indoor_Sensor.read11(DHT_INDOOR_PIN);
  outdoor_Sensor.read11(DHT_OUTDOOR_PIN);
  
  // Reading the actual sensor value (DHT values from DHT objects and MQ values directly from Analog pins)
  indoor_Temp = indoor_Sensor.temperature;
  indoor_Humidity = indoor_Sensor.humidity;
  indoor_Aqi = analogRead(MQ_INDOOR_PIN);
  //delay(2000);
  outdoor_Temp = outdoor_Sensor.temperature;
  outdoor_Humidity = outdoor_Sensor.humidity;
  outdoor_Aqi = analogRead(MQ_OUTDOOR_PIN);
  
  // Creating a JSON string to send
  String json = String("{\"indoor_Temp\":\"") + String(indoor_Temp) + String("\",\"indoor_Humidity\":\"") + String(indoor_Humidity) + String("\",\"indoor_Aqi\":\"") + String(indoor_Aqi) + String("\",\"outdoor_Temp\":\"") + String(outdoor_Temp) + String("\",\"outdoor_Humidity\":\"") + String(outdoor_Humidity) + String("\",\"outdoor_Aqi\":\"") + String(outdoor_Aqi) + String("\"}");

  // For debugging
//  Serial.print(indoor_Temp);
//  Serial.print(",\t");
//  Serial.print(indoor_Humidity);
//  Serial.print(",\t");
//  Serial.print(indoor_Aqi, DEC);
//  Serial.print(",\t");
//  Serial.print(outdoor_Temp);
//  Serial.print(",\t");
//  Serial.print(outdoor_Humidity);
//  Serial.print(",\t");
//  Serial.print(outdoor_Aqi, DEC);
//  Serial.print(",\t");
  
  // Send value to the serial Port
  Serial.println(json);
  
  delay(2000);
}
