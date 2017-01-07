/*************************************************************************

    Arduino Twinkle Lights
    by John M. Wargo (www.johnwargo.com)
    November, 2016

    This project is an Arduino variant of the Pimoroni Firefly Light
    (https://learn.pimoroni.com/tutorial/sandyj/firefly-light) project.
 ************************************************************************/

//Compiler constant representing max analog voltage output, 
//Do not change this value.
#define maxAnalog 255

//Analog output pin assignments
//Populate this array with the lst of pins you've connected
//LED strands to.
int ledPins[] = { 9, 10, 11 };
//Then update the numPins constant to match the number of 
//elements in the array
const int numPins = 3;

//Specifies how long the application delays between changes to output voltage
//Decrease this value to speed up the fade
//Increase this value to slow down the fade
const int delayVal = 10;  //in milliseconds

//Used internally to track which output pin is going up and which down
int upPin, downPin;

void setup() {
  //Initialize the up and down pin designators
  //In loop(), we'll start by incrementing the pins, so start this one 
  //at -1 so it will be incremented to 0 at the start
  downPin = -1;
  upPin = 0;

  //We need one of the strands to be illuminated to start, 
  //so start by winding the first strand up to full illumination
  for (int i = 0; i <= maxAnalog; i++) {
    //Write the voltage value
    analogWrite(ledPins[0], i);
    //Pause for a little while
    delay(delayVal);
  }
  //Wait a second before continuing
  delay(1000);
}

void loop() {
  //Increment our pin designators
  downPin = getNextPin(downPin);
  upPin = getNextPin(upPin);
  
  //Loop through the voltage output values (ranging from 0 to 255)
  //incrementing by 1
  for (int i = 0; i <= maxAnalog; i++) {
    //Drive the upPin up to maxAnalog
    analogWrite(upPin, i);
    //While simultaneously driving downPin down to 0
    analogWrite(downPin, maxAnalog - i);
    //Pause for a little while
    delay(delayVal);
  }
  //Wait a second before continuing
  delay(1000);
}

int getNextPin(int currentPin) {
  //Get the next array pointer
  //start by incrementing the current pin
  int pin = ++currentPin;
  //does pin exceed the bounds of the array?
  //I could use a == comparison here as pin should never go above numPins, 
  //unless I have a logic error in the code, but I'm going to check anyway  
  if (pin >= numPins) {
    //Then reset to the beginning of the array
    pin = 0;
  }
  return pin;
}

