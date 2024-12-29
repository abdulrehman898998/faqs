#include "faq_loader.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std; // Simplify usage of standard types and functions

// Function to convert a string to lowercase
string toLowerCase(const string& input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to tokenize a string into words
vector<string> tokenize(const string& text) {
    vector<string> tokens;
    istringstream stream(text);
    string word;

    while (stream >> word) {
        tokens.push_back(word);
    }
    return tokens;
}

// Function to compute match score between user query and FAQ question
int computeMatchScore(const vector<string>& userTokens, const vector<string>& faqTokens) {
    set<string> uniqueTokens(faqTokens.begin(), faqTokens.end());
    int score = 0;

    for (const auto& token : userTokens) {
        if (uniqueTokens.find(token) != uniqueTokens.end()) {
            score += 2; // Boost exact matches
        } else {
            for (const auto& faqToken : faqTokens) {
                if (faqToken.find(token) != string::npos) {
                    score += 1; // Partial match
                }
            }
        }
    }
    return score;
}

// Function to load FAQs from a file
vector<pair<string, string>> loadFAQs(const string &filename) {
    vector<pair<string, string>> faqs;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        istringstream stream(line);
        string question, answer;

        if (getline(stream, question, '|') && getline(stream, answer)) {
            faqs.emplace_back(question, answer);
        }
    }
    file.close();
    return faqs;
}

// Function to find the best-matching FAQ answer
string findAnswer(const string& userInput, const vector<pair<string, string>>& faqs) {
    string lowerInput = toLowerCase(userInput);
    vector<string> userTokens = tokenize(lowerInput);

    int bestScore = 0;
    string bestAnswer = "I'm sorry, I couldn't find an answer to your question. Please visit https://nust.edu.pk/admissions/ for assistance.";

    // Handle short queries (e.g., single-word queries)
    if (userTokens.size() == 1) {
        for (const auto& faq : faqs) {
            if (toLowerCase(faq.first).find(userTokens[0]) != string::npos) {
                return faq.second; // Return the FAQ answer directly
            }
        }
    }

    // Standard query matching logic
    for (const auto& faq : faqs) {
        string lowerQuestion = toLowerCase(faq.first);
        vector<string> faqTokens = tokenize(lowerQuestion);

        int score = computeMatchScore(userTokens, faqTokens);

        if (score > bestScore) {
            bestScore = score;
            bestAnswer = faq.second;
        }
    }

    return bestAnswer;
}
