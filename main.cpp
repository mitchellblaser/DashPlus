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

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "DashPlus");
    SetTargetFPS(60);

    fonts.Load(argv[1]);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(ColorFromHSV(354, 0.2, 1.0));
        DrawTextEx(fonts.Title(), "DashPlus", (Vector2){20,10}, 80, 2, BLACK);
        DrawTextEx(fonts.Body(), "An FRC Dashboard.", (Vector2){20,90}, 32, 2, BLACK);
        
        EndDrawing();
    }

    fonts.Unload();
    CloseWindow();
    return 0;
}