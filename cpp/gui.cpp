#include "gui.h"

GUI::GUI() {}

void GUI::Button(int ID, int PosX, int PosY, string ButtonText, int Width, int Height, Color ButtonColor, Font ButtonFont, int FontSize, Color TextColor) {
    Rectangle r = {PosX, PosY, Width, Height};
    DrawRectangleRounded(r, 0.5, 4, ButtonColor);

    Vector2 textBounds = MeasureTextEx(ButtonFont, ButtonText.c_str(), FontSize, 1);
    DrawTextEx(ButtonFont, ButtonText.c_str(),
               (Vector2){PosX+Width/2-textBounds.x/2, PosY+Height/2-textBounds.y/2},
               FontSize, 1, TextColor);
    
    ButtonsX1[ID] = PosX;
    ButtonsY1[ID] = PosY;
    ButtonsX2[ID] = PosX+Width;
    ButtonsY2[ID] = PosY+Height;
    
}