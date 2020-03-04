const int LED = 9; // pin for the LED
int i = 0; // counter

void setup() {
  pinMode(LED, OUTPUT); // tell Arduino LED is an output
}

void loop() {
  // we have 2 for loops here the first ramps up. The second 
  // ramps down.
  for (i=0; i<255; i++) {
    analogWrite(LED, i); 
    delay(10);
  }
  for (i=255; i > 0; i--) {
    analogWrite(LED, i);
    delay(10);
  }
}
