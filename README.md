# Sensor-Arduino-RPi-UI Branch
This branch gathers the sensor data onto the Arduino Board, makes a JSON string of the sensor values, and sends it over UART to Raspberry Pi.
On Raspberry Pi we have a Node-Red instance running along with Dashboard(UI) capabilities to show the Data over the Local Network. Also, the Data is being Stored in InfluxDB (local instance) and visualized via Grafana Dashboard (local instance).

<img src="https://github.com/samteck/indoor-outdoor-env-data-aggregator/blob/sensor-ardunio-RPi-UI/architectural-diagrams/Sensor-Arduino-RPi-UI.png" width="800">

## InfluxDB
Steps to setup, secure, and configure in Guides Folder
We will be creating 6 measurements for each of the parameter and 1 tag: location (indoor/outdoor) and 1 value: value (actual value)

## Grafana
Steps to setup and configure in Guides Folder and JSON Dashboard in the src folder
We will display Gauge and Graph for the 3 values we are getting from the sensors(temperature, humidity, and AQI), and for 3 calculated values(Heat Index/Real Feels, Dew Point, and Vapour Pressure) we will be showing only the values.

### Additional Features Added in this Branch
1. Used Adafruit DHT library (temperature values 1 decimal places)
2. Added Heat Index Parameter in Arduino Code
3. Added delay between reading values from 2 DHT sensors
4. Added Dew Point and Vapour Pressure calculation on Node-Red

Note: For Node-Red setup go to guides
