#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "regex_search_engine.h"

using namespace std;

// Function to search for pattern in text
void search(const string& text, const string& pattern) {
    RegexSearchEngine regex_pattern(pattern);
    vector<string> matches = regex_pattern.search(text);
    // Search for matches in the text
    if(!matches.empty())
    {
        cout << "Matches found:" << endl;
        for (const string& match : matches) {
            cout << match << endl;
        }
    } else {
        cout << "No matches found" << endl;
    }
}

int main() {
    // Read file path and regular expression from user
    string file_path, regex_pattern;
    cout << "Enter file path: ";
    cin >> file_path;
    cout << "Enter regular expression: ";
    cin >> regex_pattern;

    // Read text from file
    ifstream file(file_path);
    if (file.is_open()) {
        string text((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
        file.close();

        // Call search function with text and pattern
        search(text, regex_pattern);
    } else {
        cerr << "Error: Unable to open file" << endl;
    }

    return 0;
}