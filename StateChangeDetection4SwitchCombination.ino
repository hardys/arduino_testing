/*
  This example shows how to detect when buttons change from off to on
  and on to off, checking against a pre-defined combination to 'unlock'
  a green LED when the expected sequence is observed.

  The circuit:
  - pushbutton attached to pin 2/3/4/5 from +5V
  - 10 kilohm resistors attached to pins 2/3/4/5 from ground
  - Blue LED attached from pin 8/9/10/11 to ground via 220ohm resistors
  - Red LED attached from pin 12 to ground via 220ohm resistor
  - Green LED attached from pin 7 to ground via 220ohm resistor
  This example is derived from the following example:

  http://www.arduino.cc/en/Tutorial/ButtonStateChange
*/

const int numButtons = 4;
const int buttonPins[numButtons] = {2, 3, 4, 5};  // the pins that the pushbuttons are attached to
const int ledPins[numButtons] = {8, 9, 10, 11};   // the pins that the LEDs are attached to
const int redPin = 12;
const int greenPin = 7;
const int buttonCode[numButtons] = {2, 3, 4, 5};  // Buttons must be pressed in this order to set the pin LEDs

// Variables will change:
int buttonCodeIndex = 0;
int buttonCodePushed[numButtons] = {0, 0, 0, 0};   // The input code to compare
int buttonState[numButtons] = {0, 0, 0, 0};        // current state of the button
int lastButtonState[numButtons] = {0, 0, 0, 0};    // previous state of the button
bool mismatch = false;

void setup() {
  for (int ii=0; ii < numButtons; ii++) {
      // initialize the button pin as a input:
      pinMode(buttonPins[ii], INPUT);
      // initialize the LED as an output:
      pinMode(ledPins[ii], OUTPUT);
  }
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  for (int ii=0; ii < numButtons; ii++) {
    // read the pushbutton input pin:
    buttonState[ii] = digitalRead(buttonPins[ii]);
    mismatch = false;

    // compare the buttonState to its previous state
    if (buttonState[ii] != lastButtonState[ii]) {
      // if the state has changed, increment the counter
      if (buttonState[ii] == HIGH) {
        // if the current state is HIGH then the button went from off to on:
        Serial.print("Pin on : "); 
        Serial.println(buttonPins[ii]);
        buttonCodePushed[buttonCodeIndex] = buttonPins[ii];
        // If the button matches the combination, we set one of the per-button LEDs as a clue
        if (buttonCodePushed[buttonCodeIndex] == buttonCode[buttonCodeIndex]) {
          Serial.print("Pushed equals code : ");
          for (int jj=0; jj < numButtons; jj++) {
            Serial.print(buttonCodePushed[jj]);   
          }
          Serial.println(".");
          digitalWrite(redPin, LOW);
          digitalWrite(ledPins[ii], HIGH);
        } else {
          mismatch = true;
        }
        buttonCodeIndex++;
        Serial.print("buttonCodeIndex : "); 
        Serial.println(buttonCodeIndex);
        Serial.print("numButtons : "); 
        Serial.println(numButtons);
        Serial.print("mismatch : "); 
        Serial.println(mismatch);        
        if ( mismatch == true || buttonCodeIndex > numButtons) {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
          for (int jj=0; jj < numButtons; jj++) {
            digitalWrite(ledPins[jj], LOW);   
          }
          buttonCodeIndex=0;
          Serial.print("Bad code input, reset buttonCodeIndex : "); 
          Serial.println(buttonCodeIndex);
        }
      } else {
        // if the current state is LOW then the button went from on to off:
        Serial.print("Pin off : "); 
        Serial.println(buttonPins[ii]);
        if (buttonCodeIndex == numButtons) {
          Serial.println("Unlocked!");
          digitalWrite(greenPin, HIGH);
        }
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state, for next time through the loop
    lastButtonState[ii] = buttonState[ii];

  }
}
