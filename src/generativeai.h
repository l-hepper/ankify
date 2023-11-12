#ifndef _CHATGPTFUNCTIONS_H_
#define _CHATGPTFUNCTIONS_H_

#include <iostream>
#include <fstream>
#include <curl/curl.h>


using namespace std;

namespace generativeai {

    // Callback function to handle response data - solution found on stack overflow (this is not provided with libcurl??)
    size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t totalSize = size * nmemb;
        output->append((char*)contents, totalSize);
        return totalSize;
    }

    void createFlashcards() {

        CURL *curl = curl_easy_init();
        CURLcode res;

        // Initialize the curl session
        curl_global_init(CURL_GLOBAL_DEFAULT);

        // header list
        struct curl_slist *list = NULL;

        string prompt;
        cout << "Enter prompt:";
        getline(cin, prompt);

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

        cout << "=== PRINTING RESPONSE ===" << endl << response << endl;

        ofstream outputFile("output.txt");
        outputFile << response;
        outputFile.close();
    }

}

#endif