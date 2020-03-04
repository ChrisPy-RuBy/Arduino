
const int LED_1_R = 9; // pin for the LED
const int LED_1_G = 8;
const int LED_1_B = 13;

int rval = 0;
int gval = 200;
int bval = 0;

void setup() {

        Serial.begin(9600);
        pinMode(LED_1_R, OUTPUT); // tell Arduino LED is an output
        pinMode(LED_1_G, OUTPUT);
        pinMode(LED_1_B, OUTPUT);
}

void loop() {
        while (Serial.available() > 0) {
       //         rval = Serial.parseInt();
        
               gval = Serial.read();
               Serial.println(gval);
       //         bval = Serial.parseInt();

                if (Serial.read() == '\n') {
        //analogWrite(LED_1_R, rval);
        analogWrite(LED_1_G, gval);
        //analogWrite(LED_1_B, bval);
                }

        }
        analogWrite(LED_1_B, 200);
}
