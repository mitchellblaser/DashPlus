#include <iostream>
#include <raylib.h>

int main() {
    std::cout << "DashPlus" << std::endl
    << "http://github.com/mitchellblaser" << std::endl;

    InitWindow(800, 450, "DashPlus");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Welcome To DashPlus!", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}