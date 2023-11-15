#ifndef _CHATGPTFUNCTIONS_H_
#define _CHATGPTFUNCTIONS_H_

#include <iostream>
#include <fstream>
#include <regex>
#include <limits>
#include <fstream>
#include <curl/curl.h>
#include <algorithm>

// #include "json.h"

using namespace std;

namespace generativeai {


    // Callback function to handle response data
    size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t totalSize = size * nmemb;
        output->append((char*)contents, totalSize);
        return totalSize;
    }


    // string getGPTResponseContentFromJSON(string jsonResponse) {

    //     // Parse the JSON string
    //     nlohmann::json json_data = nlohmann::json::parse(jsonResponse);

    //     // get 'content' value
    //     string value = json_data["choices"][0]["message"]["content"];

    //     return value;
    // }


    // Constructs the gpt prompt with a combination of hard-coded text instructing the creation of flashcards and the textfile input by the user
    string generatePromptToFormatCards(string fileName) {

        string promptToFormatProse = "Generate question and answer pairs based on the provided prose text. "
                                "Ensure that all main points of the text are covered in a question/answer pair. "
                                 "Ensure the format of the pairs is as follows: "
                                 "<Question on a single line i.e., within a carriage return> "
                                 "<Answer on a single line i.e., within a carriage return> "
                                 "Text for question and answer pairs: ";

        fstream inputFile(fileName);

        string line {};
        while (getline(inputFile, line)) {
            if (line == "") {
                continue;
            }
            promptToFormatProse += line;
        }

        // double quotes will throw off the parsing of the JSON file so - for a simple solution - they are replaced with single quotes
        std::replace(promptToFormatProse.begin(), promptToFormatProse.end(), '"', '\'');
        
        inputFile.close();

        return promptToFormatProse;
    }

    // Make an API request to gpt-3.5 with the provided string as a prompt - JSON response is written to 'output.txt'
    void apiRequestToGPT(string prompt, string filename) {

        CURL *curl = curl_easy_init();
        CURLcode res;

        // Initialize the curl session
        curl_global_init(CURL_GLOBAL_DEFAULT);

        // header list
        struct curl_slist *list = NULL;

        string api_key = getenv("OPENAI_API_KEY"); // environment variable must be set - add functionality for user to set their environment variable otherwise this function will not work
        string authorization_header = "Authorization: Bearer " + api_key;

        // JSON data boilerplate to which prompt is added
        string json = "{\"model\": \"gpt-3.5-turbo\", " 
                        "\"messages\": [{\"role\": \"user\", "
                        "\"content\": \"" + prompt + "\"}], \"temperature\": 0.7}";

        string response;

        if (curl) {
            // Set the URL you want to request
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
            curl_easy_setopt(curl, CURLOPT_POST, 1);

            list = curl_slist_append(list, "Content-Type: application/json");
            list = curl_slist_append(list, authorization_header.c_str());

            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            // Perform the request
            res = curl_easy_perform(curl);

            // Check for errors
            if(res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

            // Clean up
            curl_easy_cleanup(curl);
        }

        // Clean up global state
        curl_global_cleanup();

        filename = regex_replace(filename, regex(".txt"), ""); // solution for this form of replace found on stack overflow 
        ofstream outputFile(filename + "_gptflashcards.txt");
        
        // outputFile << getGPTResponseContentFromJSON(response);
        outputFile << endl;
        outputFile.close();
    }

}

#endif