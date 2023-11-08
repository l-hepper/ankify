#ifndef _VALIDATE_H_
#define _VALIDATE_H_

#include <fstream>
#include <iostream>

using namespace std;


// these functions validate the user input (filename, flags, argument number) etc
namespace validate {

    string filePath {};

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
    bool validateAll() {

        if (!fileFound()) {
            return false;
        }

        if (!correctNumberOfLines()) {
            return false;
        }

        return true;
    }
}



#endif