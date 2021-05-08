#include "gui.h"

/**
* Construct a new GUI Class.
*
* Used to create and handle custom Raylib wrappers for 
* easier GUI creation inside the library.
*/
GUI::GUI() {
    ResetGUI();
    ShowGrid = false;
}

void GUI::ResetGUI() {
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        Elements[i] = Element{};
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
    Elements[ID].X1Pos = PosX;
    Elements[ID].Y1Pos = PosY;
    Elements[ID].X2Pos = PosX+Width;
    Elements[ID].Y2Pos = PosY+Height;
    Elements[ID].Type = ElementTypes::Button;
    Elements[ID].Event = onclick;
    Elements[ID].Initialized = true;

    if (Elements[ID].Cache == "$DPEMPTY$") {
        Elements[ID].Cache = ButtonText;
    }

    Rectangle r = {PosX, PosY, Width, Height};
    DrawRectangleRounded(r, 0.5, 4, ButtonColor);

    Vector2 textBounds = MeasureTextEx(ButtonFont, Elements[ID].Cache.c_str(), FontSize, 1);
    DrawTextEx(ButtonFont, Elements[ID].Cache.c_str(),
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
* @param <bool> ShowLabel: Show a label alongside the Text Box (optional)
* @param <std::string> LabelText: Text to show in the label (optional)
* @param <int> LabelPadding: How much space to leave between the label and Text Box. (default=120)
*/
void GUI::TextBox(int ID, int PosX, int PosY, string PlaceholderText, int Width, int Height,
                  Color BoxColor, Font TextFont, int FontSize, Color TextColor,
                  bool ShowLabel, string LabelText, int LabelPadding) {

    int _PosX = PosX;

    if (ShowLabel) {
        Vector2 labelBounds = MeasureTextEx(TextFont, LabelText.c_str(), FontSize, 1);
        DrawTextEx(TextFont, LabelText.c_str(), (Vector2){PosX,PosY+Height/2-labelBounds.y/2}, 16, 1, RAYWHITE);
        _PosX = PosX+LabelPadding;
    }

    Elements[ID].X1Pos = _PosX;
    Elements[ID].Y1Pos = PosY;
    Elements[ID].X2Pos = _PosX+Width;
    Elements[ID].Y2Pos = PosY+Height;
    Elements[ID].Type = ElementTypes::TextBox;
    Elements[ID].Initialized = true;

    if (Elements[ID].Cache == "$DPEMPTY$") {
        Elements[ID].Cache = PlaceholderText;
    }

    if (SelectedUserInput == ID) {
        DrawRectangle(_PosX-HighlightBorderSize, PosY-HighlightBorderSize, Width+HighlightBorderSize*2, Height+HighlightBorderSize*2, BLUE);
    }

    DrawRectangle(_PosX, PosY, Width, Height, BoxColor);

    Vector2 textBounds = MeasureTextEx(TextFont, Elements[ID].Cache.c_str(), FontSize, 1);
    DrawTextEx(TextFont, Elements[ID].Cache.c_str(),
               (Vector2){_PosX+10, PosY+Height/2-textBounds.y/2},
               FontSize, 1, TextColor);
}

//TODO: Make docstring for this function.
/**
* Draw a Grid on the Screen.
*
* @param <param> Description of the parameter
* @return Description of the return value
*/
void GUI::Grid(double PosX, double PosY, double Width, double Height, double Spacing, double Radius, Color GridColor, bool GenerateLayoutFromGrid) {
    if (GenerateLayoutFromGrid) {
        CurrentGridLayout.PosX = PosX;
        CurrentGridLayout.PosY = PosY;
        CurrentGridLayout.Width = Width;
        CurrentGridLayout.Height = Height;
        CurrentGridLayout.Spacing = Spacing;
    }
    for (int x = PosX; x < PosX+Width; x = x + Spacing) {
        for (int y = PosY; y < PosY+Height; y = y + Spacing) {
            DrawCircle(x+Spacing/2, y+Spacing/2, Radius, GridColor);
        }
    }
}

Vector2 GUI::FromGridLayout(int x, int y) {
    Vector2 GL;
    GL.x = (CurrentGridLayout.Spacing)*x + CurrentGridLayout.PosX + CurrentGridLayout.Spacing/2;
    GL.y = (CurrentGridLayout.Spacing)*y + CurrentGridLayout.PosY + CurrentGridLayout.Spacing/2;
    return GL;
}

void GUI::Window(int ID, double PosX, double PosY, double Width, double Height, string Title, Font TitleFont, float FontSize) {
    Rectangle Rec;
    Rec.x = PosX;
    Rec.y = PosY;
    Rec.width = Width;
    Rec.height = CurrentGridLayout.Spacing;
    
    Elements[ID].X1Pos = PosX;
    Elements[ID].Y1Pos = PosY;
    Elements[ID].X2Pos = PosX+Width;
    Elements[ID].Y2Pos = PosY+Height;
    Elements[ID].Initialized = true;
    Elements[ID].Type = ElementTypes::Window;
    Elements[ID].Cache = Title;

    DrawRectangleRounded(Rec, 0.5, 4, TitleBarColor);
    Rec.y = Rec.y+10;
    Rec.height = Rec.height-10;
    DrawRectangleRec(Rec, TitleBarColor);
    Rec.y = PosY+CurrentGridLayout.Spacing;
    Rec.height = Height-CurrentGridLayout.Spacing;
    DrawRectangleRec(Rec, BackgroundColor);
    DrawTextEx(TitleFont, Title.c_str(), (Vector2){PosX+10, PosY+CurrentGridLayout.Spacing/2-MeasureTextEx(TitleFont, Title.c_str(), FontSize, 1).y/2}, FontSize, 1, TitleTextColor);
}

void GUI::WindowFromGrid(int ID, int X1, int Y1, int X2, int Y2, string Title, Font TitleFont, float fontSize) {
    Vector2 WinS = FromGridLayout(X1, Y1);
    Vector2 WinE = FromGridLayout(X2, Y2);
    Window(ID, WinS.x, WinS.y, WinE.x-WinS.x-CurrentGridLayout.Spacing/2, WinE.y-WinS.y-CurrentGridLayout.Spacing/2, Title, TitleFont, fontSize);
}

/**
* Mainly used inside the GUI Class, but can also 
* be used elsewhere. Detects when the mouse clicks an element.
*
* @return <int> Index of Element Clicked.
*/
int GUI::GetClickedElement() {
    MouseX = GetMouseX();
    MouseY = GetMouseY();
    bool MouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (MouseClicked) {
        for (int i = 0; i < MAX_ELEMENTS; i++) {
            if (MouseX > Elements[i].X1Pos && MouseX < Elements[i].X2Pos && MouseY > Elements[i].Y1Pos && MouseY < Elements[i].Y2Pos) {
                
                if (Elements[i].Type == ElementTypes::Window) {
                    if (MouseY < Elements[i].Y1Pos+CurrentGridLayout.Spacing) {
                        return i;
                    }
                } else {
                    return i;
                }
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
    //TODO: Click away from element to stop capturing input
    //TODO: Add OnFocusLost and OnFocusCaptured Events.
    int Element = GetClickedElement(); 
    if (Element != -1) {
        int _SelectedUserInput = SelectedUserInput;
        SelectedUserInput = -1;
        if (Elements[Element].Type == ElementTypes::Button) {
            if (Elements[Element].Event != 0) {
                (*Elements[Element].Event)();
            }
        }
        else if (Elements[Element].Type == ElementTypes::TextBox) {
            if (Elements[_SelectedUserInput].Cache != "") {
                if (Elements[_SelectedUserInput].Cache.substr(UserInputBuffer.size()-1, UserInputBuffer.size()) == "|") {
                    Elements[_SelectedUserInput].Cache = Elements[_SelectedUserInput].Cache.substr(0, UserInputBuffer.size()-1);
                }
            }
            UserInputBuffer = Elements[Element].Cache;
            SelectedUserInput = Element;
        }
        else if (Elements[Element].Type == ElementTypes::Window) {
            SelectedUserInput = Element;
        }
    }
    else {
        //If we're not handling a click this iteration we run this
        if (SelectedUserInput != -1) {
            int code = GetCharPressed();
            if (code != 0) {
                if (BlinkerState) { //TODO: Check if string exceeds length of text box (get string x + 10 + 10 and box x)
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
                if (IsKeyDown(KEY_TAB)) {
                    //TODO: TAB Switches Elements.
                }
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    if (WasMouseButtonDown > 0) {
                        if (Elements[SelectedUserInput].Type == ElementTypes::Window) {
                            //TODO: Add checks for overlapping windows, change box to red and leave pos as old pos.
                            ShowGrid = true;
                            GUI::Element win = Elements[SelectedUserInput];

                            if (InitialMouseX == 0 && InitialMouseY == 0) {
                                InitialMouseX = GetMouseX();
                                InitialMouseY = GetMouseY();
                            }

                            double OffsetX = InitialMouseX-win.X1Pos;
                            double OffsetY = InitialMouseY-win.Y1Pos;

                            if (InitialMouseY < win.Y1Pos+CurrentGridLayout.Spacing) {
                                double X = GetMouseX()-OffsetX-CurrentGridLayout.Spacing*0.5;
                                double Y = GetMouseY()-OffsetY-CurrentGridLayout.Spacing*0.5;

                                // DrawRectangleLines(GetMouseX()-OffsetX, GetMouseY()-OffsetY, win.X2Pos-win.X1Pos, win.Y2Pos-win.Y1Pos, LIGHTGRAY);

                                rX = round(X/CurrentGridLayout.Spacing)*CurrentGridLayout.Spacing;
                                rY = round(Y/CurrentGridLayout.Spacing)*CurrentGridLayout.Spacing;
                                Rectangle r{rX+CurrentGridLayout.Spacing*0.5, rY+CurrentGridLayout.Spacing*0.5, win.X2Pos-win.X1Pos, win.Y2Pos-win.Y1Pos};

                                ValidWindowPosition = true;

                                for (int i = 0; i < MAX_ELEMENTS; i++) {
                                    if (!Elements[i].Initialized) {
                                        break;
                                    }
                                    if(i != SelectedUserInput) { //FIXME: This only checks corners, not in between - so collisions are not detected sometimes.
                                        if (r.x > Elements[i].X1Pos && r.x < Elements[i].X2Pos && r.y > Elements[i].Y1Pos && r.y < Elements[i].Y2Pos ||
                                            r.x+r.width > Elements[i].X1Pos && r.x+r.width < Elements[i].X2Pos && r.y+r.height > Elements[i].Y1Pos && r.y+r.height < Elements[i].Y2Pos) {
                                            ValidWindowPosition = false;
                                        }
                                    }

                                }
                                
                                if (ValidWindowPosition) {
                                    DrawRectangleLinesEx(r, 3, PINK);
                                } else {
                                    DrawRectangleLinesEx(r, 3, RED);
                                }
                            }
                        }
                    }
                    WasMouseButtonDown++;
                } else {
                    if (WasMouseButtonDown > 0) {
                        //Handle Release Here.
                        InitialMouseX = 0;
                        InitialMouseY = 0;
                        if (ValidWindowPosition) {
                            WinMoved = SelectedUserInput;
                        } else {
                            WinMoved = -1;
                        }
                        ShowGrid = false;
                        SelectedUserInput = -1;
                    }
                    WasMouseButtonDown = 0;
                }
            }
            Elements[SelectedUserInput].Cache = UserInputBuffer;

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
                Elements[PreviousBlinkCapture].Cache = UserInputBuffer;
                PreviousBlinkCapture = -1;
                BlinkerState = false;
            }
        }
    }
}

string GUI::GetTextFromElement(int ID) {
    string out = Elements[ID].Cache;
    if (out != "") {
        if (out.substr(Elements[ID].Cache.size()-1, Elements[ID].Cache.size()) == "|") {
            out = out.substr(0, Elements[ID].Cache.size()-1);
        }
    }
    return out;
}

int GUI::GetEmptyElementID() {
    for (int i = 1; i < MAX_ELEMENTS; i++) {
        if (!Elements[i].Initialized) {
            return i;
        }
    }
}

int GUI::WindowHasMoved() {
    int w = WinMoved;
    WinMoved = -1;
    return w;
}

Vector2 GUI::GetGridPos(int ID) {
    Vector2 Pos;
    Pos.x = rX/CurrentGridLayout.Spacing;
    Pos.y = rY/CurrentGridLayout.Spacing;
    return Pos;
}

bool GUI::ShouldShowGrid() {
    return ShowGrid;
}