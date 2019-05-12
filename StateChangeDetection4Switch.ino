/*
  State change detection (edge detection)

  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.

  This example shows how to detect when a button or button changes from off to on
  and on to off.

  The circuit:
  - pushbutton attached to pin 2/3/4/5 from +5V
  - 10 kilohm resistors attached to pins 2/3/4/5 from ground
  - LED attached from pin 8/9/10/11 to ground via 220ohm resistors
  - 

  This example is derived from the following example:

  http://www.arduino.cc/en/Tutorial/ButtonStateChange
*/

const int numButtons = 4;
const int buttonPins[numButtons] = {2, 3, 4, 5};    // the pins that the pushbuttons are attached to
const int ledPins[numButtons] = {8, 9, 10, 11};   // the pins that the LEDs are attached to

// Variables will change:
int buttonPushCounter[numButtons] = {0, 0, 0, 0};   // counter for the number of button presses
int buttonState[numButtons] = {0, 0, 0, 0};         // current state of the button
int lastButtonState[numButtons] = {0, 0, 0, 0};     // previous state of the button

void setup() {
  for (int ii=0; ii < numButtons; ii++) {
      // initialize the button pin as a input:
      pinMode(buttonPins[ii], INPUT);
      // initialize the LED as an output:
      pinMode(ledPins[ii], OUTPUT);
  }
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  for (int ii=0; ii < numButtons; ii++) {
    // read the pushbutton input pin:
    buttonState[ii] = digitalRead(buttonPins[ii]);

    // compare the buttonState to its previous state
    if (buttonState[ii] != lastButtonState[ii]) {
      // if the state has changed, increment the counter
      if (buttonState[ii] == HIGH) {
        // if the current state is HIGH then the button went from off to on:
        buttonPushCounter[ii]++;
        Serial.println("on");
        Serial.print("number of button pushes: ");
        Serial.println(buttonPushCounter[ii]);
      } else {
        // if the current state is LOW then the button went from on to off:
        Serial.println("off");
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state, for next time through the loop
    lastButtonState[ii] = buttonState[ii];


    // turns on the LED every four button pushes by checking the modulo of the
    // button push counter. the modulo function gives you the remainder of the
    // division of two numbers:
    if (buttonPushCounter[ii] % 4 == 0) {
      digitalWrite(ledPins[ii], HIGH);
    } else {
      digitalWrite(ledPins[ii], LOW);
    }
  }
}
