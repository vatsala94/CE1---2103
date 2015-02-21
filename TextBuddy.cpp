#pragma once
#include "TextBuddy.h"

const int CORRECT_NO_OF_INPUTS=2;
const int DEFAULT_LINE_NUMBER=1;
const string DISPLAY_WELCOME_MESSAGE="Welcome to TextBuddy. ";
const string DISPLAY_READY_MSG="is ready for use";

// These are the static variables to display error that cannot be initialized in header file.
const string TextBuddy::ERROR_INCORRECT_COMMAND="Please enter a valid command";
const string TextBuddy::ERROR_INPUT_FORMAT="Please enter TextBuddy.exe followed by FILE NAME.txt";

TextBuddy::TextBuddy(char* nameOfFile) {
	fileName=nameOfFile;
}

TextBuddy::~TextBuddy() {
}
	
void TextBuddy::printWelcomeMessage() {
	cout << DISPLAY_WELCOME_MESSAGE << fileName << DISPLAY_READY_MSG << endl << endl;
}

void TextBuddy::errorInputFormat() {
	cout << ERROR_INPUT_FORMAT << endl << endl;
}

void TextBuddy::getInputLine() {
	cout << "command: ";
	getline(cin,inputLine);
}

int TextBuddy::startIndex(string input) {
	return input.find_first_not_of(".,!? ");
}

int TextBuddy::endIndex(string input) {
	return input.find_first_of(".,!? ");
}

void TextBuddy::extractUserCommand() {
	int start;
	start = startIndex(inputLine);
	int end;
	end = endIndex(inputLine);
	userCommand = inputLine.substr(start,end-start);
	userInput = inputLine.substr(end+1); 
}	


void TextBuddy::add() {	
	ofstream writefile;
	writefile.open(fileName,ios::app);
	writefile << userInput <<endl; 
	writefile.close();
	cout<<"added to " << fileName << ": \"" << userInput << "\"" << endl << endl;
}

//This function deletes a specific line from the file. A queue is used to temporarily store the file data
//while deletion takes place. 
void TextBuddy::deleteFromFile() {
	ifstream readfile(fileName);
	queue <string> fileData;  
	string lineFromFile;
	int lineNumber=DEFAULT_LINE_NUMBER;
	while(!readfile.eof()) {
 		getline(readfile,lineFromFile);	
		if(atoi(userInput.c_str())!=lineNumber) {
			fileData.push(lineFromFile);
		}
		else { 
			cout <<  "deleted from " << fileName << ": \"" << lineFromFile <<"\""<< endl << endl;
		}
		lineNumber++;
	}
	readfile.close();
	ofstream writefile;
	writefile.open(fileName,ios::trunc);
	while(!fileData.empty()) {
		writefile << fileData.front() <<endl;
		fileData.pop();
	}
	writefile.close();
}

void TextBuddy::displayFile() {
	ifstream readfile(fileName);
	if(readfile.peek()==std::ifstream::traits_type::eof()) {
		cout << fileName << " is empty" << endl <<endl;
	}
	else {
		int lineNumber=DEFAULT_LINE_NUMBER;
		while(!readfile.eof()) {
			string line;
			getline(readfile,line);
			//To ensure the last blank line of the file is not read and displayed.
			if(!line.empty()) { 
				cout << lineNumber << ". " << line << endl;
				lineNumber++;
			}
		}
	}
	readfile.close();
}

void TextBuddy::clearFile() {
	ofstream writefile;
	writefile.open(fileName,ios::trunc);
	writefile.close();
	cout<<"all content deleted from "<<fileName<<endl<<endl;
}

void TextBuddy::processCommand() {
	if(userCommand=="add") {
		add();
	}
	else if(userCommand=="delete") {
		deleteFromFile();
	}
	else if(userCommand=="clear") {
		clearFile();
	}
	else if(userCommand=="display") {
		displayFile();
	}
	else if(userCommand=="exit") {
		exit(0);
	}
	else {
		cout << ERROR_INCORRECT_COMMAND << endl;
	}
}

int main(int argc, char* argv[]) {
    TextBuddy newBuddy(argv[1]);
	if (argc!=CORRECT_NO_OF_INPUTS) { 
        newBuddy.errorInputFormat();
        return 1;
    }
	else {
		newBuddy.printWelcomeMessage();
	}
	while(cin) {
		newBuddy.getInputLine();
		newBuddy.extractUserCommand();
		newBuddy.processCommand();
	}
return 0;
}

