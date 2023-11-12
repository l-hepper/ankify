#ifndef _VALIDATE_H_
#define _VALIDATE_H_

#include <fstream>
#include <iostream>

using namespace std;

// Validates the user input (filename, flags, argument number) etc
namespace validate {

    string filePath {}; // filename passed to the command
    string option {};
    char validOptions[] {'r', 'p', 'x', 'a'};


    // ensures that ankify command consists of three arguments
    bool correctNumberOfArguments(int argc) {

        if (argc != 3) {
            cerr << "Incorrect number of arguments. Usage: ankify [-option] [-filepath]" << endl;
            return false;
        }

        return true;
    }


    // validates the option the user has specified in the command
    bool correctOption() {

        if (option.length() != 2) {
            cerr << "The option '" << option << "' is not valid. See ankify -h for help" << endl;
            return false;
        }

        for (auto o : validOptions) {
            if (o == option[1]) {
                return true;
            }
        }

        cerr << "The option '" << option << "' is not valid. See ankify -h for help" << endl;
        return false;
    }


    // ensures that the passed file can be found
    bool fileFound() {
        fstream file(filePath);

        if (!file.is_open()) {
            cerr << "The file '" << filePath << "' could not be found." << endl;
            return false;
        }

        return true;
    }


    // ensures an even number of lines in the text file (necessary for creating a whole number of flashcards each with a front and back)
    bool correctNumberOfLines() {
        fstream file(filePath);

        int count {0};
        string line {};

        while(getline(file, line)) {
            if (line == "") {
                continue;
            }
            count++;
        }

        if (count == 0) {
            cerr << "The content of the text file provided is empty." << endl;
            return false;
        }

        if (count % 2 != 0) {
            cerr << "There are an odd number of lines in the text file - an even number of lines is required to create a whole number of flashcards with FRONT and BACK" << endl;
            return false;
        }

        return true;
    }


    // all checks must pass for the application to continue
    bool validateFile() {

        if (!correctOption())
            return false;

        if (!fileFound())
            return false;

        if (!correctNumberOfLines()) 
            return false;

        return true;
    }
}

#endif