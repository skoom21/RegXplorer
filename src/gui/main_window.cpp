#include "main_window.h"
#include "regex_search_engine.h" // Include the header file for RegexSearchEngine
#include <fstream>
#include <FL/fl_draw.H>  
#include <FL/Fl_PNG_Image.H>

MainWindow::MainWindow(int w, int h, const char* title) 
    : Fl_Window(w, h, title),
      regexInput(new Fl_Input(w * 0.2, h * 0.05, w * 0.4, h * 0.07, "Regex:")),
      searchButton(new Fl_Button(w * 0.2, h * 0.15, w * 0.2, h * 0.07, "Search")),
      browseButton(new Fl_Button(w * 0.6, h * 0.05, w * 0.15, h * 0.07, "Browse")),
      textBuffer(new Fl_Text_Buffer()),
      textDisplay(new Fl_Text_Display(w * 0.1, h * 0.3, w * 0.8, h * 0.5, "File Contents")),
      logoBox(new Fl_Box(0, 0, w, h)) {

    // Set background color to black
    color(FL_BLACK);

    // Load and display your logo image
    logoBox->image(new Fl_PNG_Image("logo.png"));

    // Set text color to white
    int fontSize = h * 0.03;
    browseButton->labelcolor(FL_WHITE);
    searchButton->labelcolor(FL_WHITE);
    regexInput->labelcolor(FL_WHITE);
    textDisplay->color(FL_WHITE);

    // Set font size and style
    browseButton->labelfont(FL_HELVETICA);
    browseButton->labelsize(fontSize);
    searchButton->labelfont(FL_HELVETICA);
    searchButton->labelsize(fontSize);
    regexInput->labelfont(FL_HELVETICA);
    regexInput->labelsize(fontSize);
    textDisplay->textsize(fontSize);

    // Set button colors
    browseButton->color(0x4A90E2); // Blue color
    searchButton->color(0x4A90E2); // Blue color

    // Set button shape to rounded
    browseButton->box(FL_ROUND_UP_BOX);
    searchButton->box(FL_ROUND_UP_BOX);

    // Attach text buffer to text display widgetw
    textDisplay->buffer(textBuffer);  

    // Schedule transition to main page after a delay (e.g., 3 seconds)
    Fl::add_timeout(3, &MainWindow::timeoutCallback, this);

    // Set callbacks for buttons
    browseButton->callback(&MainWindow::browseButtonCallback, this);
    searchButton->callback(&MainWindow::searchButtonCallback, this);
    resizable(this);
    show();
    end();
}



void MainWindow::searchButtonCallback(Fl_Widget* widget, void* data) {
    MainWindow* mainWindow = static_cast<MainWindow*>(data);
    std::string pattern = mainWindow->regexInput->value(); // Get the regex pattern from input field
    std::string text = mainWindow->textBuffer->text(); // Get the text to search from the text buffer
    // Filter the text: remove new lines and periods
    // text.erase(std::remove(text.begin(), text.end(), '.'), text.end());
    // text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());

    // Create an instance of RegexSearchEngine with the pattern
    Regex regexEngine(pattern);
    // Search for matches in the text
    std::vector<int> matches = regexEngine.get_matches(text);

    //replace the buffer text with the matches found by adding [] at the indexes that are in the matches and then highlight_style(FL_RED, '[');
    std::string newText = text;
    for (int matchIndex : matches) {
        newText.insert(matchIndex, "[");
        newText.insert(matchIndex + pattern.size() + 1, "]");
    }
    mainWindow->textBuffer->text(newText.c_str());
}


void MainWindow::browseButtonCallback(Fl_Widget* widget, void* data) {
    MainWindow* mainWindow = static_cast<MainWindow*>(data);
    Fl_File_Chooser fileChooser(".", "*", Fl_File_Chooser::SINGLE, "Select a file");
    fileChooser.show();
    while (fileChooser.shown()) {
        Fl::wait();
    }
    const char* filePath = fileChooser.value();
    if (filePath != nullptr) {
        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            mainWindow->textBuffer->text(fileContent.c_str()); // Set text buffer content
            file.close();
        }
    }
}

void MainWindow::timeoutCallback(void* data) {
    MainWindow* mainWindow = static_cast<MainWindow*>(data);
    mainWindow->logoBox->show(); // Show the logo
    Fl::wait(3); // Wait for 3 seconds
    mainWindow->logoBox->hide(); // Hide the logo

    // Fade out the logo by changing the opacity gradually
    for (int i = 255; i >= 0; i -= 5) {
        mainWindow->logoBox->color(FL_BLACK, i); // Set the opacity
        Fl::wait(0.5); // Wait for a small amount of time
        Fl::check(); // Process pending events
    }

    mainWindow->show(); // Show the main window
}
