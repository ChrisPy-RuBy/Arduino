// Date and time functions using a DS1307 RTC connected via
// I2C and wire lib

#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday", "Saturday"};
void setup() {
        pinMode(A3, OUTPUT);
        pinMode(A2, OUTPUT);
        digitalWrite(A3, HIGH);
        digitalWrite(A2, LOW);
        while (!Serial); //for Leonardo/Mirco/Zero
        Serial.begin(57600);
        if (! rtc.begin()) {
                Serial.println("Couldn't find RTC");
                while (1);
        }
        if (! rtc.isrunning()) {
                Serial.println("RTC is not running!");
                // following line sets the RTC to the date & time this sketch was complied
                rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
                // This line sets the RTC with an explicit date & time, for example to set
                // jan 21, 2014, at 3 am you would call
                // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
        }
}


void loop() {
        DateTime now = rtc.now();
        Serial.print(now.year(), DEC);
        Serial.print('/');
        Serial.print(now.month(), DEC);
        Serial.print('/');
        Serial.print(now.day(), DEC);
        Serial.print(" (");
        Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.second(), DEC);
        Serial.println();
        Serial.print(" since midnight 1/1/1970 = ");
        Serial.print(now.unixtime());
        Serial.print("s = ");
        Serial.print(now.unixtime() / 86400L);
        Serial.println("d");
}
