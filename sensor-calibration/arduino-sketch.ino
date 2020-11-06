int indoor_gas;
int outdoor_gas;

void setup(){
Serial.begin(9600);                            // sets the serial port to 9600
}
void loop(){
outloor_gas = analogRead(0);       // read analog input pin 0
indoor_gas = analogRead(1);       // read analog input pin 1
//Serial.print("outdoor=");
Serial.print(outdoor_gas, DEC);               // prints the value read
//Serial.println(" PPM");

//Serial.print("indoor=");
//Serial.println(indoor_gas, DEC);               // prints the value read
//Serial.println(" PPM");

delay(10000);                                   // wait 100ms for next reading
}
