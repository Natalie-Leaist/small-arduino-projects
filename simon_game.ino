/*
Name: Natalie Leaist
Email: nleaist@student.ubc.ca
Lab section: L1B
Date: June 18 2024
Purpose: Implement the Simon Game in arduino.
*/

//pin numbers corresponding to won/lost LEDs
#define WON_LED 9
#define LOST_LED 8

//pin numbers corresponding to sequence display LEDs
#define RED_LED 13
#define YELLOW_LED 12
#define BLUE_LED 11
#define GREEN_LED 10

//pin numbers corresponding to buttons
#define RED_BUTTON 7
#define YELLOW_BUTTON 6
#define BLUE_BUTTON 5
#define GREEN_BUTTON 4

#define NUM_COLOURS 4
#define NUM_FLASHES 5

#define ONE_SEC 1000

#define MAX_SEQUENCE 5

//conversions
#define LED_BUTTON_CONVERSION 6
#define EQUAL_CONVERSION 8

#define TRUE 1
#define FALSE 0

void setup()
{
  // variable declaration
  int ledColours[] = {RED_LED, YELLOW_LED, BLUE_LED, GREEN_LED};
  int buttonColours[] = {RED_BUTTON, YELLOW_BUTTON, BLUE_BUTTON, GREEN_BUTTON};
  
  // set the sequence display leds as output
  setPinGroup(ledColours, OUTPUT);
  
  // set the buttons as input
  setPinGroup(buttonColours, INPUT);
  
  // set the won and lost leds are output
  pinMode(WON_LED, OUTPUT);
  pinMode(LOST_LED, OUTPUT);
  
  //set up random generator
  randomSeed(analogRead(0));
}

void loop()
{
  //variable declaration 
  int sequence[MAX_SEQUENCE], userInput[MAX_SEQUENCE];
  int num, round, numInputs, equal, count;
 
  //start the game by turning on all LEDs for two seconds
  startGame();
  
  //generate a random set of numbers
  generateSequence(sequence);
  
  /*Play for five rounds, increasing the sequence given to the
  user each time */
  for(round = 0; round <= MAX_SEQUENCE - 1; round++)
  {
    
    //flash each led in the current sequence once
    for(num = 0; num <= round; num++)
      flash(sequence[num]);
    
    //get input sequence from the user
    getUserInput(userInput, round);
    
    //check if the sequence entered by the user is correct
    equal = compareSequences(sequence, userInput, round);
    
    /*if the sequences are not equal, break out of the for loop
    because the user has lost the game */
    if(equal == FALSE)
      break;
    
    //wait one second if proceeding to next round
    if(round < MAX_SEQUENCE - 1)
    	delay(ONE_SEC);
  }
  
  //flash the result of the game
  for(count = 1; count <= NUM_FLASHES; count++)
  	flash(equal + EQUAL_CONVERSION);
  
  //wait one second before starting a new game
  delay(ONE_SEC);
}
     
    
    
  
/*
Function to set a group of pins as input or output
Parameters:
colours[] - the group of pins
type - input or output
Assumptions:
- array is of size NUM_COLOURS
- type must be input or output
*/
void setPinGroup(int colours[], int type)
{
  //variable declaration
  int i;
  
  //set each pin in the group to input or output
  for(i = 0; i <= NUM_COLOURS - 1; i++)
    pinMode(colours[i], type);
}

/*
Function to turn on all LEDs for two seconds, and turn off all 
LEDs, then wait two seconds before proceeding with the game
*/
void startGame()
{
  // variable declaration 
  int ledColours[] = {RED_LED, YELLOW_LED, BLUE_LED, GREEN_LED};
  int buttonColours[] = {RED_BUTTON, YELLOW_BUTTON, BLUE_BUTTON, GREEN_BUTTON};
  int i;
  
  //turn on all sequence display leds
  for(i = 0; i <= NUM_COLOURS - 1; i++)
    digitalWrite(ledColours[i], HIGH);
  
  //turn on the win/lose leds
  digitalWrite(WON_LED, HIGH);
  digitalWrite(LOST_LED, HIGH);
  
  //wait two seconds
  delay(2*ONE_SEC);
  
  //turn off all sequence display leds
  for(i = 0; i <= NUM_COLOURS - 1; i++)
    digitalWrite(ledColours[i], LOW);
  
  //turn off the win/lose leds
  digitalWrite(WON_LED, LOW);
  digitalWrite(LOST_LED, LOW);
  
  //wait two seconds before proceeding with the game
  delay(2*ONE_SEC);
} 

/*
Function to generate a random sequence of numbers in the range
(10, 13) inclusive (minimum pin to maximum pin for the LEDs)
*/
void generateSequence(int sequence[])
{
  //variable declaration
  int index;
  int minInt = GREEN_LED, maxInt = RED_LED + 1;
  
  /* generate a random integer in the specified range for each 
  value in the array */
  for(index = 0; index <= MAX_SEQUENCE - 1; index++)
    sequence[index] = random(minInt, maxInt);

}


/*
Function to flash an LED
Parameters:
led - the pin number that corresponds to the LED to be flashed
*/
void flash(int led)
{
  digitalWrite(led, HIGH);
  delay(ONE_SEC);
  digitalWrite(led, LOW);
  delay(ONE_SEC);
}

/* Function to check if a particular button is pressed
 Parameters:
 button - the pin number corresponding to the button we are checking
 Returns:
  - true if the button was pressed and false if it was not pressed
 Assumptions:
 - button corresponds to a valid button on the board
*/
int checkButton(int button)
{
  	//variable declaration
    int wasOn = FALSE;
  	int led = button + LED_BUTTON_CONVERSION;
    
  	//while the button is pressed, turn on the corresponding LED
    while(digitalRead(button) == HIGH)
    {
        wasOn = TRUE;
        digitalWrite(led, HIGH);
    }
  	
  	//if the led was turned on, turn it off
  	if(wasOn == TRUE)
      digitalWrite(led, LOW);
      
    return wasOn;
}

/* Function to check if two arrays are about up to a specified index
Parameters:
sequence - an array containing the randomly generated sequence
userInput - the leds corresponding to the buttons pressed by the user
maxIndex - the max index to which the arrays will be compared
Return:
- 1 (TRUE) if the arrays are equal and 0 (FALSE) if they are not
Assumptions:
- the maximum valid index of both arrays is >= maxIndex
*/
int compareSequences(int sequence[], int userInput[], int maxIndex)
{
  	//variable declaration
    int index, equal = TRUE;
    
  	//check if each element is equal until the desired index
    for(index = 0; index <= maxIndex; index++)
    {
        if(sequence[index] != userInput[index])
        {
            equal = FALSE;
            break;
        }
    }
    
    return equal;
}

/* Function to get an array of the users choices
Parameters:
userInput - array of the values entered by the user
maxIndex - the number of inputs required from the user minus 1
Assumptions:
- the maximum valid index of UserInput is >= round
*/
void getUserInput(int userInput[], int maxIndex)
{
  	//variable declaration
    int buttonList[] = {RED_BUTTON, YELLOW_BUTTON, BLUE_BUTTON, GREEN_BUTTON};
    int index, led, numInputs = 0;
  
 	
  	/* execute outer loop until the user has entered the correct 
    number of colours */
  	while(numInputs <= maxIndex)
    {
      	//go through each colour in button list
    	for(index = 0; index <= NUM_COLOURS - 1; index++)
    	{
        	if(checkButton(buttonList[index]) == TRUE) //if the colour was turned on
        	{
            	userInput[numInputs] = buttonList[index] + LED_BUTTON_CONVERSION; //store the led that was turned on in userInputs
            	numInputs++;
              	if(numInputs > maxIndex) //check that there is still room for more input before executing the for loop again
                  break;
        	}
    	}
   	}
}





  
  

 
  
  
    