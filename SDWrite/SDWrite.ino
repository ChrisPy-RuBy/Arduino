/*
BASED ON
https://create.arduino.cc/projecthub/electropeak/sd-card-module-with-arduino-how-to-read-write-data-37f390

const int POW_PIN = 8;
 Set by default for the SD lib
 MOSI = pin 11
 MISO = pin 12
 SCLK = pin 13
 We always need to set the CS pin
 CS = pin 10
 VCC = 5V
*/


#include <SPI.h>
#include <SD.h>
File myFile;
void setup() {
        // Open serial communications and wait for port to open:
        Serial.begin(9600);
        while (!Serial) {
                ; // wait for serial port to connect. Needed for native USB port only
        }
        Serial.print("Initializing SD card...");
        if (!SD.begin(10)) {
                Serial.println("initialization failed!");
                while (1);
        }
        Serial.println("initialization done.");
        // open the file. note that only one file can be open at a time,
        // so you have to close this one before opening another.
        myFile = SD.open("test.txt", FILE_WRITE);
        // if the file opened okay, write to it:
        if (myFile) {
                Serial.print("Writing to test.txt...");
                myFile.println("This is a test file :)");
                myFile.println("testing 1, 2, 3.");
                for (int i = 0; i < 20; i++) {
                        myFile.println(i);
                }
                // close the file:
                myFile.close();
                Serial.println("done.");
        } else {
                // if the file didn't open, print an error:
                Serial.println("error opening test.txt");
        }
}
void loop() {
        // nothing happens after setup
}
