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
SCL -> A5
SDA -> A4
DS -> 4

LIBRARIES REQUIRED
-> DHT
-> SPI
-> SD
-> Wire
-> RTClib
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
#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 rtc;

// setup RTC thermo DS!8B20
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
	Serial.begin(9600);
	Serial.println("Initializing SD card...");
	if (!SD.begin(10)) {
		Serial.println("Initialisation failed!");
		while (1);
	}

	Serial.println("Initializing RTC...");
	if (!rtc.begin()) {
		Serial.println("Couldn't find RTC");
		while (1);
	}
	if (!rtc.isrunning()) {
		Serial.println("RTC is not running!");
			// following line sets the RTC to the date & time this sketch was complied
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
		}

	Serial.print("Initializing DHT...");
	dht.begin();
	sensors.begin();
	Serial.println("End of setup");
}

void loop() {

    // Reading the sensor	
	delay(2000);
	Serial.println("In loop");
	sensors.requestTemperatures();

	Serial.print(sensors.getTempCByIndex(0));
	DateTime now = rtc.now();
	long time = now.unixtime();
    float h = dht.readHumidity();
    float temp = dht.readTemperature();
	serialWrite(time, h, temp);
	saveData(time, h, temp);
}

void saveData(int time, float h, float temp) {
	myFile = SD.open("data.txt", FILE_WRITE);
	myFile.print(time);
	myFile.print(",");
	myFile.print(h);
	myFile.print(",");
	myFile.print(temp);
	myFile.print(",");
	myFile.close();
}

void serialWrite(int time, float h, float temp) {
  // Function for debug of humidity sensor

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Time: "));
  Serial.print(time);
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(temp);
  Serial.print(F("°C "));
}
