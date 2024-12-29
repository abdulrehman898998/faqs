#include <iostream>
#include <string>
#include "faq_loader.h"

using namespace std; // Simplify usage of standard types and functions

int main() {
    string filename = "faqs.txt";  // Path to your FAQ file
    auto faqs = loadFAQs(filename);  // Load FAQs from the file

    cout << "Welcome to the NUST Admission Chatbot! How can I assist you today?\n";
    string userInput;

    while (true) {
        cout << "> ";
        getline(cin, userInput);

        if (userInput == "exit") {
            cout << "Goodbye! Feel free to reach out if you have more questions.\n";
            break;
        }

        string answer = findAnswer(userInput, faqs);
        cout << answer << "\n";
    }

    return 0;
}
