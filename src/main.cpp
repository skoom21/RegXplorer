#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "regex_search_engine.h"
#include <QApplication>
#include "mainwindow.h"
using namespace std;

// Function to search for pattern in text
void search(string text, const string &pattern)
{
    RegexSearchEngine engine(pattern);
    engine.search(text);
}

int main()
{
    // // Read file path and regular expression from user
    // string file_path, regex_pattern;
    // cout << "Enter file path: ";
    // cin >> file_path;
    // cout << "Enter regular expression: ";
    // cin >> regex_pattern;

    // // Read text from file
    // ifstream file(file_path);
    // if (file.is_open())
    // {
    //     string text((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    //     file.close();

    //     // Call search function with text and pattern
    //     search(text, regex_pattern);
    // }
    // else
    // {
    //     cerr << "Error: Unable to open file" << endl;
    // }



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}


    return 0;
}