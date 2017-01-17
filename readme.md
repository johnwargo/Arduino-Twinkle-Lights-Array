# Arduino Twinkle Lights in a Jar (Array Version)

This is an alternative approach to the code for the [Arduino Twinkle Lights](https://github.com/johnwargo/Arduino-Twinkle-Lights) project. You can find a complete project write-up at [johnwargo.com](http://johnwargo.com/microcontrollers-single-board-computers/arduino-twinkle-lights.html). For the original project, I used two strands of lights, and the code was pretty simple. When you add a third (or more) strand, you need a different approach. To demonstrate this, I built a project that implements a US 4th of July twinkle light jar with Red, White and Blue LEDs. This repository contains the code for that project.

Here's a video of the project in action:

<iframe src="https://player.vimeo.com/video/199841714" width="640" height="480" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>
<p><a href="https://vimeo.com/199841714">Arduino Twinkle Lights: Red, White, &amp; Blue</a> from <a href="https://vimeo.com/user39135142">John Wargo</a> on <a href="https://vimeo.com">Vimeo</a>.</p>

The hardware implementation is basically the same; the core differences in this version are the following:

Instead of defining a variable for each output pin as I did for the [Arduino Twinkle Lights](https://github.com/johnwargo/Arduino-Twinkle-Lights):

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

Populate the `ledPins` array with the list of Arduino analog output pins the strands are connected to (the strand's positive wires). The pins don't have to be in sequence like the example shown there. Connect the strands to whichever analog pins you want, just make sure to populate the array in the order in which you want the pins used. Next, update the `numPins` constant with the number of strands (or pins - same thing) you're using.  
 
I added a function to use to get the next array index:

	int getNextIndex(int currentIndex) {
	  //Get the next array index
	  //start by incrementing the current pin
	  int idx = ++currentIndex;
	  //does pin exceed the bounds of the array?
	  //I could use a == comparison here as pin should never go above numPins,
	  //unless I have a logic error in the code, but I'm going to check anyway
	  if (idx >= numPins) {
	    //Then reset to the beginning of the array
	    idx = 0;
	  }
	  return idx;
	}

Before starting each loop iteration, the `upPin` and `downPin` variables are updated to point to the next elements in the `ledPins` array. This enables the application to maintain a sliding window into the array - pointing to two sequential analog output pins as it iterates through the array.

The loop is greatly simplified as well:

	void loop() {
	  //Increment our pin designators
	  downPin = getNextIndex(downPin);
	  upPin = getNextIndex(upPin);
	
	  //Loop through the voltage output values (ranging from 0 to 255)
	  //incrementing by 1
	  for (int i = 0; i <= maxAnalog; i++) {
	    //Drive the upPin up to maxAnalog
	    analogWrite(ledPins[upPin], i);
	    //While simultaneously driving downPin down to 0
	    analogWrite(ledPins[downPin], maxAnalog - i);
	    //Pause for a little while
	    delay(delayVal);
	  }
	  //Wait a second before continuing
	  delay(1000);
	}

That's it, you can find the complete hardware assembly instructions on [johnwargo.com](http://johnwargo.com/microcontrollers-single-board-computers/arduino-twinkle-lights.html). 

***

If you find this code useful, and feel like thanking me for providing it, please consider making a purchase from [my Amazon Wish List](https://amzn.com/w/1WI6AAUKPT5P9). You can find information on many different topics on my [personal blog](http://www.johnwargo.com). Learn about all of my publications at [John Wargo Books](http://www.johnwargobooks.com). 
