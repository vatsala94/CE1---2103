#ifndef TEXTBUDDY_H_
#define TEXTBUDDY_H_

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <queue>

using namespace std;

//This class is used to store and retrieve the data stored by the user in a text file. 
//If the user specified text file does not exist, a new file is automatically created.


class TextBuddy {

private:
	char* fileName;
	string inputLine; //Stores the entire user input 
	string userCommand; //Stores only the command required to be executed
	string userInput; //Stores the data to be added to the file.
	
	//Constant strings to store error messages for invalid commands or invalid input format.
	static const string ERROR_INCORRECT_COMMAND;
	static const string ERROR_INPUT_FORMAT;


public:
	
	//This constructor stores the file name given by the user(command line parameter) in fileName.
	TextBuddy(char*); 
	~TextBuddy();

	void printWelcomeMessage();
	void errorInputFormat();
	void getInputLine();

	//These functions are used when extracting the first word from a sentence. 
	//The startIndex() returns the starting index of the word.
	//The endIndex() returns the last index of the word. 
	int startIndex(string);
	int endIndex(string);
	
	//This function identifies the command from the user input.
	void extractUserCommand();

	//This function performs the tasks required depending on the command.
	void processCommand();
	
	//These functions perform the basic tasks required by the user.
	void add();
	void display();
	void deleteFromFile();
	void displayFile();
	void clearFile();
};
#endif