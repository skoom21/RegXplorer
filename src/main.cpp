#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "gui/main_window.h"

using namespace std;
// Function to search for pattern in text

int main()
{
    MainWindow mainWindow(1024, 1024, "Regex Search Engine");
    // Read file path and regular expression from user

    return Fl::run();
}