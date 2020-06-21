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

---> Ext Thermo
DS -> 4

--->  Debug LED
RED -> 5
BLUE -> 6
GREEn -> 7

LIBRARIES REQUIRED
-> DHT
-> SPI
-> SD
-> Wire
-> RTClib
-> OneWire
-> dallasTemperature
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

const int RED = 5;
const int GREEN = 6;
const int BLUE = 7;

void setup() {

	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(GREEN, OUTPUT);

	digitalWrite(RED, HIGH);
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
	delay(120000);
	
	digitalWrite(RED, LOW);
	digitalWrite(GREEN, HIGH);
	delay(100);
	digitalWrite(GREEN, LOW);
	sensors.requestTemperatures();

	float externalTemp = sensors.getTempCByIndex(0);
	DateTime now = rtc.now();
	String time = now.timestamp();
    float h = dht.readHumidity();
    float temp = dht.readTemperature();

	if (isnan(now.unixtime()) || isnan(externalTemp) || isnan(h) || isnan(temp)) {
		digitalWrite(BLUE, HIGH);
		digitalWrite(GREEN, LOW);
	}

	serialWrite(time, externalTemp, h, temp);
	saveData(time, externalTemp, h, temp);
}

void saveData(String time, float externalTemp, float dhth, float dhttemp) {
	myFile = SD.open("data.txt", FILE_WRITE);
	myFile.print(time);
	myFile.print(",");
	myFile.print(externalTemp);
	myFile.print(",");
	myFile.print(dhth);
	myFile.print(",");
	myFile.print(dhttemp);
	myFile.print(",\n");
	myFile.close();
}

void serialWrite(String time, float externalTemp, float dhth, float dhttemp) {
  // Function for debug of humidity sensor

  // Check if any reads failed and exit early (to try again).
  //if (isnan(dhth) || isnan(dhttemp)) {
  //  Serial.println(F("Failed to read from DHT sensor!"));
  // return;
  //}
  Serial.print(F("Time: "));
  Serial.print(time);
  Serial.print(F(" Ext Temp: "));
  Serial.print(externalTemp);
  Serial.print(F(" Humidity: "));
  Serial.print(dhth);
  Serial.print(F("%  Temperature: "));
  Serial.print(dhttemp);
  Serial.print(F("°C "));
}
