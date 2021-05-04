#include "gui.h"

/**
* Construct a new GUI Class.
*
* Used to create and handle custom Raylib wrappers for 
* easier GUI creation inside the library.
*/
GUI::GUI() {
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        ElementCache[i] = "$DPEMPTY$";
    }
}

/**
* Create a Button and Draw on the Raylib window.
*
* @param <int> ID: Unique ID Number for the element.
* @param <int> PosX: X Position of the Button.
* @param <int> PosY: Y Position of the Button.
* @param <std::string> ButtonText: Text to appear inside the button.
* @param <int> Width: Width of the Button.
* @param <int> Height: Height of the Button.
* @param <raylib::Color> ButtonColor: Background color of the Button.
* @param <raylib::Font> ButtonFont: Font for the Button to use.
* @param <int> FontSize: Font size for the Button to use.
* @param <raylib::Color> TextColor: Foreground color of the Button.
* @param <void(*)()> *onclick: Pointer to a function to run when the button is clicked. Optional.
*/
void GUI::Button(int ID, int PosX, int PosY, string ButtonText, int Width, int Height, Color ButtonColor, Font ButtonFont, int FontSize, Color TextColor, void (*onclick)()) {
    ButtonsX1[ID] = PosX;
    ButtonsY1[ID] = PosY;
    ButtonsX2[ID] = PosX+Width;
    ButtonsY2[ID] = PosY+Height;
    ElementType[ID] = ElementTypes::Button;
    EventsList[ID] = onclick;

    if (ElementCache[ID] == "$DPEMPTY$") {
        ElementCache[ID] = ButtonText;
    }

    Rectangle r = {PosX, PosY, Width, Height};
    DrawRectangleRounded(r, 0.5, 4, ButtonColor);

    Vector2 textBounds = MeasureTextEx(ButtonFont, ElementCache[ID].c_str(), FontSize, 1);
    DrawTextEx(ButtonFont, ElementCache[ID].c_str(),
               (Vector2){PosX+Width/2-textBounds.x/2, PosY+Height/2-textBounds.y/2},
               FontSize, 1, TextColor);
}

/**
* Create a Text Box and Draw on the Raylib window.
*
* @param <int> ID: Unique ID Number for the element.
* @param <int> PosX: X Position of the Text Box.
* @param <int> PosY: Y Position of the Text Box.
* @param <std::string> PlaceholderText: Text to appear inside the text box by default.
* @param <int> Width: Width of the Text Box.
* @param <int> Height: Height of the Text Box.
* @param <raylib::Color> BoxColor: Background color of the Text Box.
* @param <raylib::Font> TextFont: Font for the Text Box to use.
* @param <int> FontSize: Font size for the Text Box to use.
* @param <raylib::Color> TextColor: Foreground color of the Text Box.
*/
void GUI::TextBox(int ID, int PosX, int PosY, string PlaceholderText, int Width, int Height, Color BoxColor, Font TextFont, int FontSize, Color TextColor) {
    ButtonsX1[ID] = PosX;
    ButtonsY1[ID] = PosY;
    ButtonsX2[ID] = PosX+Width;
    ButtonsY2[ID] = PosY+Height;
    ElementType[ID] = ElementTypes::TextBox;

    if (ElementCache[ID] == "$DPEMPTY$") {
        ElementCache[ID] = PlaceholderText;
    }

    Rectangle r = {PosX, PosY, Width, Height};
    // DrawRectangleRounded(r, 0.5, 4, BoxColor);
    DrawRectangle(PosX, PosY, Width, Height, BoxColor);

    Vector2 textBounds = MeasureTextEx(TextFont, ElementCache[ID].c_str(), FontSize, 1);
    DrawTextEx(TextFont, ElementCache[ID].c_str(),
               (Vector2){PosX+10, PosY+Height/2-textBounds.y/2},
               FontSize, 1, TextColor);
}

/**
* Mainly used inside the GUI Class, but can also 
* be used elsewhere. Detects when the mouse clicks an element.
*
* @return <int> Index of Element Clicked.
*/
int GUI::GetClickedElement() {
    int MouseX = GetMouseX();
    int MouseY = GetMouseY();
    bool MouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (MouseClicked) {
        for (int i = 0; i < MAX_ELEMENTS; i++) {
            if (MouseX > ButtonsX1[i] && MouseX < ButtonsX2[i] && MouseY > ButtonsY1[i] && MouseY < ButtonsY2[i]) {
                return i;
            }
        }
    }
    return -1;
}

/**
* Main Event Loop for the Application's GUI Stuff. 
* Also handles running functions when an event (such as OnClick) is met.
*
* @param <std::string> DPATH: Root data path to reference for font loading, etc.
*/
void GUI::MainEventLoop(string DPATH) {
    int Element = GetClickedElement();

    if (Element != -1) {
        SelectedUserInput = -1;
        if (ElementType[Element] == ElementTypes::Button) {
            if (EventsList[Element] != 0) {
                (*EventsList[Element])(); // Run OnClick Command if not NULL.
            }
        }
        else if (ElementType[Element] == ElementTypes::TextBox) {
            UserInputBuffer = ElementCache[Element];
            SelectedUserInput = Element;
        }
    }
    else { //TODO: Add ENTER Key Handles - Defocus Text Box.
        //If we're not handling a click this iteration
        if (SelectedUserInput != -1) {
            int code = GetCharPressed();
            if (code != 0) {
                if (BlinkerState) {
                    UserInputBuffer = UserInputBuffer.substr(0, UserInputBuffer.size()-1) + char(code) + "|";
                } else {
                    UserInputBuffer = UserInputBuffer + char(code);
                }
            } else {
                if (IsKeyDown(KEY_BACKSPACE)) {
                    debounceTimer.Tick();

                    if (debounceTimer.AtTarget()) {
                        if (BlinkerState) {
                            UserInputBuffer = UserInputBuffer.substr(0, UserInputBuffer.size()-2) + "|";
                        } else {
                            UserInputBuffer = UserInputBuffer.substr(0, UserInputBuffer.size()-1);
                        }
                        debounceTimer.RunComplete();
                    }
                }
                else { debounceTimer.Reset(); }
                if (IsKeyDown(KEY_ENTER)) {
                    SelectedUserInput = -1;
                }
            }
            ElementCache[SelectedUserInput] = UserInputBuffer;

            inputBlinker.Tick();
            if (inputBlinker.AtTarget()) {
                if (BlinkerState) {
                    BlinkerState = false;
                    UserInputBuffer = UserInputBuffer.substr(0, UserInputBuffer.size()-1);
                    PreviousBlinkCapture = SelectedUserInput;
                } else {
                    BlinkerState = true;
                    UserInputBuffer = UserInputBuffer + "|";
                    PreviousBlinkCapture = SelectedUserInput;
                }                
                inputBlinker.RunComplete();
            }
        } else {
            if (BlinkerState) {
                UserInputBuffer = UserInputBuffer.substr(0, UserInputBuffer.size()-1);
                ElementCache[PreviousBlinkCapture] = UserInputBuffer;
                PreviousBlinkCapture = -1;
                BlinkerState = false;
            }
        }
    }
}

string GUI::GetTextFromID(int ID) {
    string out = ElementCache[ID];
    if (out.substr(ElementCache[ID].size()-1, ElementCache[ID].size()) == "|") {
        out = out.substr(0, ElementCache[ID].size()-1);
    }
    return out;
}