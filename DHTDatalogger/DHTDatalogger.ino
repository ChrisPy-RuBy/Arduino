// Script to Read a DHT Sensor and write to an SD card
// [x] Read from DHT sensor
// [x] Write to SD Card
// [] Add timestamp to DHT output

/*
Physical setup (What pins connect to what?)
---> SENSOR
DHTPIN = 2
---> SD CARD
MISO = 13
MOSI = 12
SCK = 11
CS = 10
---> RTC
*/

// setup DHT
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// setup SSD
#include <SPI.h>
#include <SD.h>
File myFile;

// setup RTC
//#include <Wire.h>
//#include <RTClib.h>
//RTC_DS1307 rtc;

void setup() {
	Serial.begin(9600);
	Serial.print("Initializing SD card...");
	if (!SD.begin(10)) {
		Serial.println("Initialisation failed!");
		while (1);
	}

	dht.begin();
	Serial.println("End of setup");
}

void loop() {

    // Reading the sensor	
	delay(2000);
	Serial.println("In loop");

    float h = dht.readHumidity();
    float t = dht.readTemperature();
	serialWrite(h, t);
	saveData(h, t);
}

void saveData(float h, float t) {
	myFile = SD.open("data.txt", FILE_WRITE);
	myFile.print(h);
	myFile.print(",");
	myFile.print(t);
	myFile.print(",");
	myFile.close();
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
