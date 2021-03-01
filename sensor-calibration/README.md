# We need to make sure that our sensors are working fine and showing correct values

For that we will make a sample node-red application in Raspberry Pi and save the data from sensors.

                            +----------------+
MQ135 -----> Arduino -----> |                |
                            |  Raspberry Pi  | --------> Node-Red App
        DHT-11 -----------> |                |
                            +----------------+

Since MQ135 only sends Analog values and we can not read Analog values in Raspberry pi, therefore an Arduino was used as ADC converter.

## Steps

1. Install Node-Red on raspberry pi
2. Node-Red is installed and can be accessed over : <http://localhost:1880>
3. Connect both the DHT11 sensor to Raspberry Pi via GPIO pins in BCM Mode
4. Connect MQ135 sensor to Arduino and Connect Arduino to Raspberry Pi via Serial (Since MQ135 sends analog output and we can not use analog input in Raspberry Pi)
5. Flash Arduino with AQI application
6. Import Flow into node-red dashboard and deploy the app

You will start to see the logs in Debug window, if there is any discrepancy in values. Then just put that individual sensor and start debugging.
In my case one of the MQ135 was dead and was showing very high values, so I just compared the values individually from 2 sensors and came to conclusion that one is dead.

## Observations

- Give some time to sensors to heat up, after that only they will show correct values.
- Difference of values from DHT11 was +/- 1%
- MQ135 values were within a range of +/- 5%
