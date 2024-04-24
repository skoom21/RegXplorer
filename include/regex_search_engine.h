#ifndef REGEX_SEARCH_ENGINE_H
#define REGEX_SEARCH_ENGINE_H

#include <regex>
#include <string>
#include <vector>

using namespace std; // Add this line

class RegexSearchEngine {
public:
    RegexSearchEngine(const string& pattern);
    vector<string> search(const string& text);

private:
    regex regexPattern;
};

RegexSearchEngine::RegexSearchEngine(const string& pattern) : regexPattern(pattern) {}

vector<string> RegexSearchEngine::search(const string& text) {
    vector<string> matches;
    smatch match;

    string::const_iterator searchStart(text.cbegin());
    string::const_iterator searchEnd(text.cend());

    while (regex_search(searchStart, searchEnd, match, regexPattern)) {
        matches.push_back(match.str());
        searchStart = match.suffix().first;
    }

    return matches;
}

#endif