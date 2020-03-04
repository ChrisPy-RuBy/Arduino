

const int LED_1_R = 9; // pin for the LED
const int LED_1_G = 8;
const int LED_1_B = 13;

const int LED_2_R = 7;
const int LED_2_G = 6;
const int LED_2_B = 5;
int i = 0; // counter

void setup() {
  pinMode(LED_1_R, OUTPUT); // tell Arduino LED is an output
  pinMode(LED_1_G, OUTPUT);
  pinMode(LED_1_B, OUTPUT);
  pinMode(LED_2_R, OUTPUT); // tell Arduino LED is an output
  pinMode(LED_2_G, OUTPUT);
  pinMode(LED_2_B, OUTPUT);

}

void loop() {
  // we have 2 for loops here the first ramps up. The second 
  // ramps down.

  analogWrite(LED_2_R,255);
  analogWrite(LED_2_G, 105);
  for (i=0; i<255; i++) {
    analogWrite(LED_1_R, i); 
    delay(10);
  }
  for (i=255; i > 0; i--) {
    analogWrite(LED_1_R, i);
    delay(10);
  }
}
