#include "gui.h"

GUI::GUI() {
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        ElementCache[i] = "$DPEMPTY$";
    }
}

void GUI::Button(int ID, int PosX, int PosY, string ButtonText, int Width, int Height, Color ButtonColor, Font ButtonFont, int FontSize, Color TextColor) {
    ButtonsX1[ID] = PosX;
    ButtonsY1[ID] = PosY;
    ButtonsX2[ID] = PosX+Width;
    ButtonsY2[ID] = PosY+Height;
    ElementType[ID] = ElementTypes::Button;

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
    DrawRectangleRounded(r, 0.5, 4, BoxColor);

    Vector2 textBounds = MeasureTextEx(TextFont, ElementCache[ID].c_str(), FontSize, 1);
    DrawTextEx(TextFont, ElementCache[ID].c_str(),
               (Vector2){PosX+10, PosY+Height/2-textBounds.y/2},
               FontSize, 1, TextColor);
}

int GUI::GetClickedElement() {
    int MouseX = GetMouseX();
    int MouseY = GetMouseY();
    bool MouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (MouseClicked) {
        for (int i = 0; i < MAX_ELEMENTS; i++) {
            if (MouseX > ButtonsX1[i] && MouseX < ButtonsX2[i] && MouseY > ButtonsY1[i] && MouseY < ButtonsY2[i]) {
                // std::cout << "Pressed " << MouseX << " " << MouseY << " " << i << std::endl;
                return i;
            }
        }
    }
    return -1;
}

void GUI::MainEventLoop(string DPATH) {
    int Element = GetClickedElement();

    if (Element != -1) {
        std::cout << Element << std::endl;
        ElementCache[1] = "HELLO WORLD";

    }

}