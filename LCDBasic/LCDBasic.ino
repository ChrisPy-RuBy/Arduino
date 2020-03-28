// LCD text with incremental number

//Wiring details are based on 'Exploring Arduino by J.Blum'


//Include the lib code
// Install lib with 'arduino-cli lib install LiquidCrystal'
#include <LiquidCrystal.h>

//Start the time at 0
int time = 0;

//Init the lib with the numbers of the interface pins
LiquidCrystal lcd (2,3,4,5,6,7);

void setup() {
        //Set up the LCD's number of columns and rows;
        lcd.begin(16, 2);
        //Print the message to the display
        lcd.print("Chris Display");
}

void loop() {
        //Move cursor ot second line, first position
        lcd.setCursor(0, 1);
        //Print current time
        lcd.print(time);
        //Wait 1 second
        delay(1000);
        //Increment the time
        time++;
}
