const int LED = 13;  // pin for LED
int val = 0; // variable for sensor output

void setup() {
	pinMode(LED, OUTPUT); // LED is output
			      // Note Analogue Pins are set with as inputs
}

void loop() {
	val = analogRead(0); // read the value from the sensor
	
	digitalWrite(LED, HIGH); // turn the LED on

	delay(val); // stop the program for some time

	digitalWrite(LED, LOW); // turn the LED off

	delay(val);  // stop the program for some time

}
