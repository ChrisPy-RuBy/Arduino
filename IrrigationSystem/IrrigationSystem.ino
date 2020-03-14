#include <Wire.h>
#include "RTClib.h"
#include "DHT.h"

// Analogue pin
const int RTC_5V_PIN = A3;
const int RTC_GND_PIN = A2;

// Digital pins
const int DHT_pin = 2;
const int WATER_VALVE_0_PIN = 8;
const int WATER_VALVE_1_PIN = 7;
const int WATER_VALVE_2_PIN = 4;

const int NUMBEROFVALVES = 3;
const int NUMBEROFTIMES = 2;

int onOffTimes [NUMBEROFVALVES][NUMBEROFTIMES];
int valvePinNumbers[NUMBEROFVALVES];

const int ONTIME = 0;
const int OFFTIME = 1;

#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

RTC_DS1307 rtc;

DateTime dateTimeNow;

float HumidityNow;

void setup {

        // Power annd ground to RTC
        pinMode(RTC_5V_PIN, OUTPUT);
        pinMode(RTC_GND_PIN, OUTPUT);
        digitalWrite(RTC_5V_PIN, HIGH);
        digitalWrite(RTC_GND_PIN, LOW);

#ifdef AVR
        Wire.begin();
#else
        Wire1.begin();
#endif

        rtc.begin();
        dht.begin();
        Serial.begin(9600);

        valvePinNumbers[0] = WATER_VALVE_0_PIN;

        for (int valve = 0; valve < NUMBEROFVALVES; valve++) {
                pinMode(valvePinNumbers[valve], OUTPUT);
        }

}

void loop() {

        Serial.print("Type 'P' to print settings or ");
        Serial.println(" 'S2N13:45' to set valve 2 OIN time time to 13:34 ");

        getTimeTempHumidity();
        
        checkUserInteraction();

        checkTimeControlValves();

        delay(5000);
}

void getTimeTempHumidity() {

        dateTimeNow = rtc.now();

        if (! rtc.isrunning()) {
        Serial.println("RTC is not running!");
        return;
        }

        Serial.print(dateTimeNow.hour(), DEC);
        Serial.print(':');
        Serial.print(dateTimeNow.minute(), DEC);
        Serial.print(':');
        Serial.print(dateTimeNow.second(), DEC);

        humidityNow = dht.readHumidity();
        float t = dht.readTemperature();
        float f = dht.readTemperature(true);

        if (isnan(humidityNow) || isnan(t) || isnan(f)) {
                Serial.println("Failed to read from DHT sensor!");
                return;
        }

        Serial.print(" Humidity ");
        Serial.print(humidityNow);
        Serial.print("% ");
        Serial.print("Temp ");
        Serial.print(t);
        Serial.print("C ");
        Serial.print(f);
        Serial.print("F");
        Serial.println();
}

void checkUserInteraction() {
        // Check for user interaction
        while (Serial.available() > 0) {

                // The first character tells us what to expect for
                // the rest of the line.
                char temp = Serial.read();

                // If the first character is 'P' then print the
                // current settings and break out of the while()
                // loop.
                if ( temp == 'P' ) {
                        printSettings();
                        Serial.flush();
                        break;
                } // end of printing the current settings

                // If first character is 'S' then the rest will be a setting
                else if (temp == 'S') {
                        expectValveSetting();
                }

                // Otherwise its an error. Remind the user what the choices
                // are and break out of the while() loop
                else
                {
                        printMenu();
                        Serial.flush();
                        break;
                }

        } // End of processing user interaction.
}

// Read a string of the form "2N13:45" and seperate it into the
// valve number, the letter indicating ON or OFF, and the time.

void expectValveSetting() {
        // The first integer should be the valve number
        int valveNumber = Serial.parseInt();

        // the next character should be either N or F
        char onOff = serial.read();

        int desiredHour = Serial.parseInt(); // the hour

        // the next character should be ':'
        if (Serial.read() != ':') {
                Serial.println("no : found"); // sanity check
                Serial.flush();
                return;
        }

        int desiredMinutes = Serial.parseInt(); // the minutes

        // finally expect a newline which is the end of the sentence:
        if (Serial.read() != '\n') {
                Serial.println(
                                "Make sure ot end your request with a Newline"
                              );
                Serial.flush();
                return;
        }

        // Convert the desired hour and minute time
        // to the number of minutes since midnight
        int desiredMinutesSinceMidnight
                = (desiredHour*60 + desiredMinutes);

        // Put time into the array in the correct row/column
        if ( onOff = 'N') { //  its an ON time
                onOffTimes[valveNumber][ONTIME]
                        = desiredMinutesSinceMidnight;
        }
        else if ( onOff == 'F') { // its an OFF time
                onOffTimes[valveNumber][OFFTIME]
                        = desiredMinutesSinceMidnight;
        }
        else { // user didnt use N or F
                Serial.print("You must use upper case N or F ");$
                        Serial.println("to indicate ON time or OFF time");$
                        Serial.flush();
                return;
        }

        printSettings(); // print the array so user can confirm settings
} // end of expectValveSetting()

void checkTimeControlValves() {

        // First, figure out how many minutes have passed since
        // midnight, since we store ON and OFF time as the number of
        // minutes since midnight. The biggest number will be at
        // 2359 which is 23 * 60 + 59 = 1159 which is less tham the max
        // that can be stored in an integer so an int is big enough.
        int nowMinutesSinceMidnight =
                (dateTimeNow.hour() * 60) + dateTimeNow.minute();

        // Now check the array for each valve
        for (int valve = 0; valve < NUMBEROFVALVES; valve++) {
                Serial.print("Valve ");
                Serial.print(valve);

                Serial.print(" is now ");
                if (( nowMiniutesSinceMidnight >=
                                        onOffTimes[valve][ONTIME])) &&
                        ( nowMinutesSinceMidnight <
                          onOffTimes[valve][OFFTIME]) {

                                // Before we turn a valve on make sure that its not raining
                                if ( humidityNow > 70 ) {
                                        // its raining; turn the valve OFF
                                        Serial.print(" OFF ");
                                        digitalWrite(valvePinNumbers[valve], LOW);
                                }
                                else {
                                        //No rain and its time ot turn the valve ON
                                        Serial.print(" ON ");
                                        digitalWrite(valvePinNumbers[valve][, HIGH]);
                                } // end of checking for rain
                        } // end of checking for time to turn valve ON
                else {
                        Serial.print(" OFF ");
                        digitalWrite(valvePinNumbers[valve], LOW);
                }
                Serial.println();
        } // end of looping over each valve
        Serial.println();
}

void printMenu() {
        Serial.println(
                        "Please enter P to print the current settings"
                      );
        Serial.println(
                        "Please enter S2N13:45 to set valve 2 ON time to 13:34"
                      );
}

void printSettings() {
        Serial.println();
        for (int valve = 0; valve < NUMBEROFVALVES; valve++) {
                Serial.print("Valve ");
                Serial.print(valve);
                Serial.print(" will turn ON at ");


                Serial.print((onOffTimes[valve][ONTIME])/60);
                Serial.print(":");

                Serial.print((onOffTimes[valve][ONTIME])%60);

                Serial.print(" and will turn OFF at ");
                Serial.print((onOffTimes[valve][OFFTIME])/60);
                Serial.print(":");
                Serial.print((onOffTimes[valve][OFFTIME])%(60));
                Serial.println();
        }
}
