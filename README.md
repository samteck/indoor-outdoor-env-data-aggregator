# Sensor-Arduino-RPi-UI Branch
This was the first working branch which gathered the sensor data onto the Arduino Board (Edge Layer), makes a JSON string of the sensor values, and sends it over UART to Raspberry Pi.

On Raspberry Pi we have a Node-Red instance running along with Dashboard(UI) capabilities. This app reads the JSON data over serial port, calculate the vapour pressure and dew point at the FOG layer. Also, the Data is being Stored in InfluxDB (local instance) and visualized via Grafana Dashboard (local instance).

<img src="https://github.com/samteck/indoor-outdoor-env-data-aggregator/blob/sensor-ardunio-RPi-UI/architectural-diagrams/Sensor-Arduino-RPi-UI.png" width="800">

## InfluxDB
Steps to setup, secure, and configure in Guides Folder. 
We will be creating 6 measurements (temp, humidity, aqi, heat index, dew point and vapour pressure) for each of the environmental parameter and 1 tag: location (indoor/outdoor) and 1 field : value (actual value)

Measurements = Tables\
Fields       = Columns (Value)\
Primary Key  = Timestamp\
Note : tags are optional but helps in better segregation.

## Grafana
Steps to setup and configure in Guides Folder and JSON Dashboard in the src folder
We will display Gauge and Historical Graphs for the 3 values we are getting from the sensors(Temperature, Humidity, and AQI), and for 3 calculated values(Heat Index/Real Feels, Dew Point, and Vapour Pressure) we will be showing only the values.

Note: For Node-Red setup go to guides

### Additional Features Added in this Branch
1. Used Adafruit DHT library (temperature values 1 decimal places)
2. Added Heat Index Parameter in Arduino Code
3. Added delay between reading values from 2 DHT sensors
4. Added Dew Point and Vapour Pressure calculation on Node-Red

### An image of the setup 
Here 1 sensor module is ready and experimentation going on with second sensor module (testing if sensor values are similar).
See sensor-calibration folder

<img src="https://github.com/samteck/indoor-outdoor-env-data-aggregator/blob/sensor-ardunio-RPi-UI/Images/sensor-system-interfacing.JPG" width="800">
