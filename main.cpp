#include <iostream>
#include <raylib.h>

#include "fonts.h"
#include "file.h"
#include "gui.h"

Fonts fonts;
File file;
GUI gui;

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "DashPlus" << std::endl
    << "http://github.com/mitchellblaser" << std::endl;

    string DPATH = argv[1];

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "DashPlus");
    SetTargetFPS(60);

    fonts.Load(argv[1]);

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
        BeginDrawing();
        gui.MainEventLoop(DPATH);

        ClearBackground(ColorFromHSV(232, 0.54, 0.41));
        DrawTextEx(fonts.Title(), "DashPlus", (Vector2){20,7}, 80, 2, RAYWHITE);
        DrawTextEx(fonts.Body(), "An FRC Dashboard.", (Vector2){23,77}, 32, 2, RAYWHITE);

        gui.Button(0, 200, 200, "Update Settings", 100, 50, RAYWHITE, fonts.BodySmall(), 15, BLACK);
        gui.TextBox(1, 280, 250, "Hello World|", 200, 35, WHITE, fonts.BodySmall(), 15, BLACK);


        EndDrawing();

        if (WindowShouldClose()) {
            CloseWindow();
            return 0;
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();

        //Main Event Loop
        
        EndDrawing();
    }

    fonts.Unload();
    CloseWindow();
    return 0;
}