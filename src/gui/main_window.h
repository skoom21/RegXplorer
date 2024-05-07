#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Chooser.H> // Include Fl_File_Chooser header

class MainWindow : public Fl_Window {
public:
    MainWindow(int w, int h, const char* title);

private:
    Fl_Input* regexInput;
    Fl_Button* searchButton;
    Fl_Button* browseButton;
    Fl_Text_Buffer* textBuffer;
    Fl_Text_Display* textDisplay;
    Fl_Box* logoBox;

    static void searchButtonCallback(Fl_Widget* widget, void* data);
    static void browseButtonCallback(Fl_Widget* widget, void* data);
    static void timeoutCallback(void* data);
    static void fadeOutCallback(void* data);

};

#endif // MAIN_WINDOW_H
