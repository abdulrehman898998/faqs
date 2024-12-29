#ifndef FAQ_LOADER_H
#define FAQ_LOADER_H

#include <vector>
#include <string>

using namespace std; // Simplify all type declarations

// Function declarations
vector<pair<string, string>> loadFAQs(const string &filename);
string findAnswer(const string& userInput, const vector<pair<string, string>>& faqs);

#endif // FAQ_LOADER_H
