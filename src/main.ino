/*
 * indoor-outdoor-env-data-aggregator
 * Author: Samarth Gupta
 * Started Date: 24/11/20
 * Version: 2.0
 * Additions : Using Adafruit Library, Temparature 1 decimal point, Added Heat Index, delay between 2 DHT reads
 */

/////////////////////////////////////////////////////////////////////////


// Including the libraries
#include "DHT.h"

#define DHTTYPE    DHT11

// Pinout define on Arduino Board
//// Digital Pins
#define DHT_INDOOR_PIN 7
#define DHT_OUTDOOR_PIN 8
//// Analog Pins
#define MQ_INDOOR_PIN 0
#define MQ_OUTDOOR_PIN 1

// Object creation for DHT sensors
DHT indoor_Sensor(DHT_INDOOR_PIN, DHTTYPE);
DHT outdoor_Sensor(DHT_OUTDOOR_PIN, DHTTYPE);

// Variables to hold sensor values
float indoor_Temp;
float indoor_Humidity;
int indoor_Aqi;
float outdoor_Temp;
float outdoor_Humidity;
int outdoor_Aqi;

void setup()
{
  Serial.begin(9600);  //serial port data write speed
  
  // Initialize device.
  indoor_Sensor.begin();
  outdoor_Sensor.begin();
}

void loop()
{  
  // Reading the actual sensor value (DHT values from DHT objects and MQ values directly from Analog pins)
  indoor_Temp = indoor_Sensor.readTemperature();
  indoor_Humidity = indoor_Sensor.readHumidity();
  indoor_Aqi = analogRead(MQ_INDOOR_PIN);
  delay(2000); //delay between 2 DHT reads
  outdoor_Temp = outdoor_Sensor.readTemperature();
  outdoor_Humidity = outdoor_Sensor.readHumidity();
  outdoor_Aqi = analogRead(MQ_OUTDOOR_PIN);

  // Check if any reads failed and exit early (to try again)
  if (isnan(indoor_Temp) || isnan(indoor_Humidity) || isnan(outdoor_Temp) || isnan(outdoor_Humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(1000);
    return;
  }

  // Heat Index Calculation (Real Feel Temperature)
  float indoor_HI = indoor_Sensor.computeHeatIndex(indoor_Temp, indoor_Humidity, false);
  float outdoor_HI = outdoor_Sensor.computeHeatIndex(outdoor_Temp, outdoor_Humidity, false);
  
  // Creating a JSON string to send
  String json = String(F("{\"indoor_Temp\":\"")) + String(indoor_Temp) + String(F("\",\"indoor_Humidity\":\"")) + String(indoor_Humidity) + String(F("\",\"indoor_Aqi\":\"")) + String(indoor_Aqi) + String(F("\",\"indoor_HI\":\"")) + String(indoor_HI) + String(F("\",\"outdoor_Temp\":\"")) + String(outdoor_Temp) + String(F("\",\"outdoor_Humidity\":\"")) + String(outdoor_Humidity) + String(F("\",\"outdoor_Aqi\":\"")) + String(outdoor_Aqi) + String(F("\",\"outdoor_HI\":\"")) + String(outdoor_HI) + String(F("\"}"));

  // For debugging
//  Serial.print(indoor_Temp);
//  Serial.print(",\t");
//  Serial.print(indoor_Humidity);
//  Serial.print(",\t");
//  Serial.print(indoor_Aqi, DEC);
//  Serial.print(",\t");
//  Serial.print(indoor_HI);
//  Serial.print(",\t");
//  Serial.print(outdoor_Temp);
//  Serial.print(",\t");
//  Serial.print(outdoor_Humidity);
//  Serial.print(",\t");
//  Serial.print(outdoor_Aqi, DEC);
//  Serial.print(",\t");
//  Serial.print(outdoor_Hi);
//  Serial.print(",\t");
  
  // Send value to the serial Port
  Serial.println(json);
  
  delay(8000);
}
