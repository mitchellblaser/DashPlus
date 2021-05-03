#include <iostream>
#include <raylib.h>

#include "fonts.h"

Fonts fonts;

using namespace std;

int main() {
    std::cout << "DashPlus" << std::endl
    << "http://github.com/mitchellblaser" << std::endl;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "DashPlus");
    SetTargetFPS(60);

    fonts.Load();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextEx(fonts.Title(), "DashPlus", (Vector2){20,10}, 80, 2, BLACK);
        DrawTextEx(fonts.Body(), "An FRC Dashboard.", (Vector2){20,90}, 32, 2, BLACK);
        EndDrawing();
    }

    fonts.Unload();
    CloseWindow();
    return 0;
}