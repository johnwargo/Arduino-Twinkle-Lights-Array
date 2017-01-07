# Arduino Twinkle Lights in a Jar (Array Version)

This is an alternative approach to the code for the [Arduino Twinkle Lights](https://github.com/johnwargo/Arduino-Twinkle-Lights) project. For the original project, I used two strands of lights, so the code was pretty simple. If you want to expand the number of LED Strands, to implement a US 4th of July twinkle light jar with Red, White and Blue LEDs for example, then you'll need the array-based approach which is implemented here.

The hardware implementation is the same; the core difference in this version is in the following code:

Instead of defining a variable for each output pin:

	//Analog output pin assignments
	const int pin0 = 9;
	const int pin1 = 10;

The application uses an array to hold the output pin values:

	//Analog output pin assignments
	//Populate this array with the lst of pins you've connected
	//LED strands to.
	int ledPins[] = { 9, 10, 11 };
	//Update the numPins constant to match the number of 
	//elements in the array
	const int numPins = 3; 

Plus a function to use to get the next pin array element:

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

The loop is greatly simplified as well:

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


***

If you find this code useful, and feel like thanking me for providing it, please consider making a purchase from [my Amazon Wish List](https://amzn.com/w/1WI6AAUKPT5P9). You can find information on many different topics on my [personal blog](http://www.johnwargo.com). Learn about all of my publications at [John Wargo Books](http://www.johnwargobooks.com). 
