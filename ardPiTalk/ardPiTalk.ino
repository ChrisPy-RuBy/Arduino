// Getting ardiuino and pi to talk to
// one another

const int ledPinB = 11;
const int ledPinG = 9;
const int ledPinR = 6;

int r = 0;
int g = 0;
int b = 0;

void setup() {
        pinMode(ledPinB, OUTPUT);
        pinMode(ledPinG, OUTPUT);
        pinMode(ledPinR, OUTPUT);
        Serial.begin(9600);
}

void loop() {
        {
                Serial.println("Hello Pi");
                if (Serial.available()) {
                        //flash(Serial.read()- '0');
                        color(Serial.parseInt(), Serial.parseInt(), Serial.parseInt());
                }
                delay(1000);
        }
}

void color(int r, int g, int b) {
        analogWrite(ledPinR, r);
        analogWrite(ledPinG, g);
        analogWrite(ledPinB, b);
}


void flash(int n) {
        for (int i = 0; i < n; i++)
        {
                digitalWrite(ledPinR, HIGH);
                digitalWrite(ledPinG, HIGH);
                digitalWrite(ledPinB, HIGH);
                delay(100);
                digitalWrite(ledPinR, LOW);
                digitalWrite(ledPinG, LOW);
                digitalWrite(ledPinB, LOW);
                delay(100);
        }
}
