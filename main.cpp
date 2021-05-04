#include <iostream>
#include <raylib.h>

#include "fonts.h"
#include "file.h"

Fonts fonts;
File file;

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

        ClearBackground(ColorFromHSV(354, 0.2, 1.0));
        DrawTextEx(fonts.Title(), "DashPlus", (Vector2){20,10}, 80, 2, BLACK);
        DrawTextEx(fonts.Body(), "An FRC Dashboard.", (Vector2){20,90}, 32, 2, BLACK);

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