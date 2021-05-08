#include <iostream>
#include <raylib.h>

#include "fonts.h"
#include "file.h"
#include "gui.h"

Fonts fonts;
File file;
GUI gui;

string DPATH;

using namespace std;

bool CallExit = false;
int WindowPosX[MAX_ELEMENTS];
int WindowPosY[MAX_ELEMENTS];
int WindowPosX2[MAX_ELEMENTS];
int WindowPosY2[MAX_ELEMENTS];

void SaveSetupValues() {
    file.WriteFile(DPATH + ".dpdata/SETUP", "{ipAddrTarget:"+gui.GetTextFromElement(1)+",updateInterval:"+gui.GetTextFromElement(2)+"}");
    CallExit = true;
}

bool ShowGrid = true;
void ToggleGridVisibility() {
    if (ShowGrid) {
        ShowGrid = false;
    } else {
        ShowGrid = true;
    }
}

/**
* Draw the Setup Window of the application.
*
* @return <int> - 0 for Window Exit or 1 for Window Continued.
*/
int Setup_Draw() {
    //Ensure we don't exit straight away.
    CallExit = false;
    //Call the Raylib BeginDrawing() function.
    BeginDrawing();
    //Draw everything here.
    ClearBackground(ColorFromHSV(232, 0.54, 0.41));
    DrawTextEx(fonts.Title(), "DashPlus", Vector2{20,7}, 80, 2, RAYWHITE);
    DrawTextEx(fonts.Body(), "An FRC Dashboard.", Vector2{23,77}, 32, 2, RAYWHITE);
    gui.TextBox(1, 23, 125, "", 200, 35, WHITE, fonts.BodySmall(), 16, BLACK, true, "Server IP Address:");
    gui.TextBox(2, 23, 165, "", 200, 35, WHITE, fonts.BodySmall(), 16, BLACK, true, "Update Interval:");
    gui.Button(0, GetScreenWidth()-120, 20, "Save Settings", 100, 50, RAYWHITE, fonts.BodySmall(), 15, BLACK, &SaveSetupValues);
    //Call the Event Loop here.
    gui.MainEventLoop(DPATH);
    //Call the Raylib EndDrawing() function.
    EndDrawing();

    //Handle Window Exiting - On Raylib condition or our own
    if (WindowShouldClose() || CallExit) {
        //If window should exit, we return 0.
        return 0;
    }
    //If window should not exit, we return 1.
    return 1;
}
bool Setup_Init = false;
int Setup_GfxLoop() {
    if (!Setup_Init) {
        Setup_Init = true;
    }
    return Setup_Draw();
}

int Main_Draw() {
    //Ensure we don't exit straight away.
    CallExit = false;
    //Call the Raylib BeginDrawing() function.
    BeginDrawing();
    //Draw everything here.
    ClearBackground(ColorFromHSV(232, 0.54, 0.41));
    if (gui.ShouldShowGrid()) {
        gui.Grid(0, 0, GetScreenWidth(), GetScreenHeight(), 25, 1, GRAY, true);
        // gui.Grid(0, 0, GetScreenWidth(), GetScreenHeight(), 50, 1, LIGHTGRAY);
    }

    int WindowMoveCheck = gui.WindowHasMoved();
    if (WindowMoveCheck != -1) {
        int DiffX = gui.GetGridPos(WindowMoveCheck).x - WindowPosX[WindowMoveCheck];
        int DiffY = gui.GetGridPos(WindowMoveCheck).y - WindowPosY[WindowMoveCheck];

        WindowPosX2[WindowMoveCheck] = WindowPosX2[WindowMoveCheck] + DiffX;
        WindowPosY2[WindowMoveCheck] = WindowPosY2[WindowMoveCheck] + DiffY; 

        WindowPosX[WindowMoveCheck] = gui.GetGridPos(WindowMoveCheck).x;
        WindowPosY[WindowMoveCheck] = gui.GetGridPos(WindowMoveCheck).y;
    }

    gui.WindowFromGrid(0, WindowPosX[0], WindowPosY[0], WindowPosX2[0], WindowPosY2[0], "Test Window", fonts.BodySmall());
    gui.WindowFromGrid(1, WindowPosX[1], WindowPosY[1], WindowPosX2[1], WindowPosY2[1], "Settings", fonts.BodySmall());

    gui.Button(2, GetScreenWidth()-120, 20, "Toggle Grid", 100, 50, RAYWHITE, fonts.BodySmall(), 15, BLACK, &ToggleGridVisibility);
    //Call the Event Loop here.
    gui.MainEventLoop(DPATH);
    //Call the Raylib EndDrawing() function.
    EndDrawing();

    //Handle Window Exiting - On Raylib condition or our own
    if (WindowShouldClose() || CallExit) {
        //If window should exit, we return 0.
        return 0;
    }
    //If window should not exit, we return 1.
    return 1;
}

bool Main_Init = false;
int Main_GfxLoop() {
    if (!Main_Init) {
        Main_Init = true;
        WindowPosX[0] = 0;
        WindowPosY[0] = 0;
        WindowPosX2[0] = 16;
        WindowPosY2[0] = 10;
        WindowPosX[1] = 16;
        WindowPosY[1] = 0;
        WindowPosX2[1] = 26;
        WindowPosY2[1] = 12;
        /* We need to do this here so that the GridLayout
           can be generated in the GUI object.*/
        BeginDrawing();
        gui.Grid(0, 0, GetScreenWidth(), GetScreenHeight(), 25, 1, GRAY, true);
        EndDrawing();
    }
    return Main_Draw();
}

int main(int argc, char* argv[]) {
    std::cout << "DashPlus" << std::endl
    << "http://github.com/mitchellblaser" << std::endl;

    std::cout << argc << std::endl;

    if (argc == 1) {
        DPATH = "../";
    } else {
        DPATH = argv[1];
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "DashPlus");
    SetTargetFPS(60);

    fonts.Load(DPATH);

    bool NeedsSetup = false;
    if (!file.FolderExists(DPATH + ".dpdata")) {
        file.MakeFolder(DPATH + ".dpdata");
        NeedsSetup = true;
    } else {
        if (!file.IsFile(DPATH + ".dpdata/SETUP")) {
            NeedsSetup = true;
        }
    }

    while (NeedsSetup) {
        if (Setup_GfxLoop() == 0) { NeedsSetup = false; }
    }
    gui.ResetGUI();

    while (!WindowShouldClose()) {
        if (Main_GfxLoop() == 0) { break; }
    }

    fonts.Unload();
    CloseWindow();
    return 0;
}