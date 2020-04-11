// Need to add functionality now to turn on the pump 
// depending on the state of the humidity monitor



// Setup the debug LED
const int LED_1_R = 11;
const int LED_1_G = 12;
const int LED_1_B = 13;

// Setup up the Humidity Monitor
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {

        Serial.begin(9600);

        // setup LEDs
        pinMode(LED_1_R, OUTPUT);
        pinMode(LED_1_G, OUTPUT);
        pinMode(LED_1_B, OUTPUT);

        // setup humidity monitor
        dht.begin();
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
}

void green() {
        digitalWrite(LED_1_R, LOW);
        digitalWrite(LED_1_G, HIGH);
        digitalWrite(LED_1_B, LOW);
}

void yellow() {
        digitalWrite(LED_1_R, LOW);
        digitalWrite(LED_1_G, HIGH);
        digitalWrite(LED_1_B, HIGH);
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
