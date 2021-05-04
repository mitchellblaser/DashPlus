/*
DashPlus
Mitchell Blaser 2021.
http://github.com/mitchellblaser/dashplus
*/

#include <raylib.h>
#include <iostream>
#include "fonts.h"

using namespace std;

#ifndef DP_GUI
#define DP_GUI

class GUI {
    public:
        GUI();
        void Button(int ID, int PosX, int PosY, string ButtonText,
                    int Width, int Height, Color ButtonColor,
                    Font ButtonFont, int FontSize, Color TextColor);
    private:
        int GUIButtonCount = 0;
        Fonts _fonts;
        int ButtonsX1[100] = {};
        int ButtonsY1[100] = {};
        int ButtonsX2[100] = {};
        int ButtonsY2[100] = {};
};

#endif