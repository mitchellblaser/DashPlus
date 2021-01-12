#include "iostream"
#include "ntcore.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "raylib.h"

int main() {
    std::cout << "DashPlus\nMitchell Blaser 2021\n\n";

    InitWindow(800, 480, "DashPlus");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("DashPlus", 20, 20, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}