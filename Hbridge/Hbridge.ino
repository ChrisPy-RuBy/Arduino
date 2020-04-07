// HBridge motor control
const int EN=9;     // Half bridge ! enable
const int MC1=3;    // Motor control 1
const int MC2=2;    // Motor control 2
const int POT=0;    // POT on Analog Pin 0

int val = 0;
int velocity = 0;

void setup() {
}

void loop() 
{
        val = analogRead(POT);

        // go forward
        if (val > 562)
        {
                velocity = map(val, 563, 1023, 0, 255);
                forward(velocity);
        }

        // go backward
        else if (val < 462)
        {
                velocity = map(val, 461, 0, 0, 255);
                reverse(velocity);
        }

        // break 
        else 
        {
                brake();
        }

}

// Motor goes forward at given rate (0-255)
void forward (int rate) 
{
        digitalWrite(EN, LOW);
        digitalWrite(MC1, HIGH);
        digitalWrite(MC2, LOW);
        analogWrite(EN, rate);
}

// Motor goes backward at given rate (0-255)
void reverse (int rate)
{
        digitalWrite(EN, LOW);
        digitalWrite(MC1, LOW);
        digitalWrite(MC2, HIGH);
        analogWrite(EN, rate);
}

// Stop motor
void brake ()
{
        digitalWrite(EN, LOW);
        digitalWrite(MC1, LOW);
        digitalWrite(MC2, LOW);
        analogWrite(EN, HIGH);
}

