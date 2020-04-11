// Setup the debug LED
const int LED_1_R = 11;
const int LED_1_G = 12;
const int LED_1_B = 13;

// Setup up the Humidity Monitor
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Setup the pump
const int PUMP_PIN = 6;

// Setup the POT
const int POT = A0;
int c1 = 0;
int c2 = 0;

void setup() {

        Serial.begin(9600);

        // setup LEDs
        pinMode(LED_1_R, OUTPUT);
        pinMode(LED_1_G, OUTPUT);
        pinMode(LED_1_B, OUTPUT);

        // setup pump
        pinMode(PUMP_PIN, OUTPUT);

        // setup humidity monitor
        dht.begin();

        // setup POT
        //pinMode(POT, INPUT);
}       

void loop() {

        // Reading the sensor
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        Serial.println(t);
        serialWrite(h, t);
        
        if (h > 80.0) {
                green();
        }
        else if (h > 50) {
                yellow();
        }
        else {
                red();
        }

}

void red() {
        digitalWrite(LED_1_R, HIGH);
        digitalWrite(LED_1_G, LOW);
        digitalWrite(LED_1_B, LOW);
        //analogWrite(PUMP_PIN, 125);  // Can vary the motor speed using PWM between 100 and 250
        pumpRate();
}

void green() {
        digitalWrite(LED_1_R, LOW);
        digitalWrite(LED_1_G, HIGH);
        digitalWrite(LED_1_B, LOW);
        digitalWrite(PUMP_PIN, LOW);
}

void yellow() {
        digitalWrite(LED_1_R, LOW);
        digitalWrite(LED_1_G, HIGH);
        digitalWrite(LED_1_B, HIGH);
        digitalWrite(PUMP_PIN, LOW);
}

void serialWrite(float h, float t) {
  // Function for debug of humidity sensor

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
}

void pumpRate() {
        c2 = analogRead(POT);
        // need to get the number 1024 to 0 down to 100 to 250
        c1 = 1024-c2;
        analogWrite(PUMP_PIN, c1 / 4);
}


