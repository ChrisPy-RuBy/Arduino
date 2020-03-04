const int LED = 9;
int val = 0;

void setup() {
	pinMode(LED, OUTPUT); //LED is OUTPUT
}

void loop() {
	val = analogRead(0);
	analogWrite(LED, val/4);
	delay(10);

}
