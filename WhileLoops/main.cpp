//While Loops
//CSIS 111-BO2
//

//Include statements
#include <iostream>
#include <fstream>
#include "macros.h"
#include <math.h>



//Global declarations: Constants and type definitions only -- no variables
const int maxSongs = 1 << 5; //**Maximum of 32 songs can be stored**
const int dataBufferSize = 1 << 11; //Maximum of 2048 characters in data buffer output table
const int maxMinutesCD = 80;

//Function prototypes
///I came up with my own function using Desmos, I am really happy it works!
char* intToCharArray(int a) {//Avoid std::string by converting the base10 integer to ascii
	char parsed[1 << 4]; //Maximum of 16 digits in char array
	char n = (char)floor((float)log10(a)); //Calculate number of digits in the integer
	for (char i = 0; i <= n; i++) { //solve every digit in it's place, turn to ascii
		int b = (floor((float)(a / pow(10, n - i))) - (10*floor((float)(a / pow(10, n - i + 1)))));
		parsed[i] = b + 0x30; //formula
	}
	parsed[n + 1] = '\0'; //Apply a null character for null-terminate convenience
	return parsed;
}
///Write to a character array to another character array and specify a position
int writeCharArray(char* dest, char* toWrite, int pos) {
	int i = 0;
	while (toWrite[i]) { //terminate if data to write is a 0
		dest[i + pos] = toWrite[i++];
	}
	return i; //Return the number of characters written for spacing position
}

int main()
{
	//In cout statement below SUBSTITUTE your name and lab number
	sayl("Alexander Weight -- Lab 4");

	//Variable declarations

	int songDuration[maxSongs]; //= { 310, 462, 627, 273, 300, 535, 259, 625, 736, 122 }; //Used for debug purposes
	int durationSum = 0; //Total duration of song files in seconds
	char data[dataBufferSize]; //Define fixed data buffer size for output characters
	for (int i = 0; i < sizeof(data); i++) data[i] = '\0';
	//memset(data, 0, sizeof(data)); //Set null characters in data buffer
	int dataPos = 0; //Used to index through the character array buffer
	char numSongs = 10; //Determine number of songs opened for convenience
	int numSecondsRemaining = maxMinutesCD * 60; //Use seconds total seconds available for convenience
	char header[] = "Song\t\tSong Time\t\tTotal Time\nNumber\t\tMinutes\tSeconds\t\tMinutes\tSeconds\n------\t\t-------\t-------\t\t-------\t-------\n"; //Define header
	char header0[] = " minutes and "; //Used for ending sentence
	char header1[] = " seconds remaining.";
	std::ifstream inFile; //Call ifstream for file reading
	std::ofstream output; //Call ofstream for data output

	//Program logic
	dataPos += writeCharArray(data, header, dataPos); //Write the header to the data output buffer

	inFile.open("songs.txt"); //Open the songs.txt file

	char i = '\0'; //Use char instead of int because there will never be more than 127 songs
	do {
		inFile >> songDuration[i++]; //Parse song second's duration to song duration integer array
	} while ((!inFile.eof()) && inFile); //null terminate
	numSongs = i; //index equals the number of songs discovered
	for (int i = 0; i < numSongs; i++) { //Apply each row with the song duration details
		durationSum += songDuration[i]; //Keep track of duration of each song for solving the remaining time
		dataPos += writeCharArray(data, intToCharArray(i + 1), dataPos);
		data[dataPos++] = '\t'; //Use \t for tabbing forward to next column
		data[dataPos++] = '\t';
		dataPos += writeCharArray(data, intToCharArray(songDuration[i] / 60), dataPos);
		data[dataPos++] = '\t';
		dataPos += writeCharArray(data, intToCharArray(songDuration[i] % 60), dataPos);

		data[dataPos++] = '\t';
		data[dataPos++] = '\t';
		dataPos += writeCharArray(data, intToCharArray(durationSum / 60), dataPos);
		data[dataPos++] = '\t';
		dataPos += writeCharArray(data, intToCharArray(durationSum % 60), dataPos);

		data[dataPos++] = '\n';
	}
	data[dataPos++] = '\n';
	numSecondsRemaining -= durationSum; //Calculate the number of seconds remaining for convenience

	//Write the minutes and seconds remaining
	dataPos += writeCharArray(data, intToCharArray(numSecondsRemaining / 60), dataPos);
	dataPos += writeCharArray(data, header0, dataPos);
	dataPos += writeCharArray(data, intToCharArray(numSecondsRemaining % 60), dataPos);
	dataPos += writeCharArray(data, header1, dataPos);

	sayl(data); //Output the full text to the screen
	output.open("details.txt"); //Open the details file for writing
	output.write(data, sizeof(data)); //Copy contents of the data char array to the output file
	output.close(); //Very important, always remember to close the stream!

	//Closing program statements
	system("pause");
	return 0;
}