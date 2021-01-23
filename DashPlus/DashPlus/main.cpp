#include <iostream>
#include <stdlib.h>
#include "ntcore.h"
#include "NetworkTables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "raylib.h"
using namespace std;


//Set this here for now.
int _teamNumber = 5584;



int main() {
	
	//Set up networktables and get the DashPlus table
	nt::NetworkTableInstance ntInst = nt::NetworkTableInstance::GetDefault();
	ntInst.StartClientTeam(_teamNumber);
	ntInst.SetServer("localhost");
	ntInst.StartClient();
	shared_ptr<NetworkTable> ntTable(ntInst.GetTable("DashPlus"));

	//Set up raylib window stuff
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 480, "DashPlus");
	SetTargetFPS(60);
	//SetWindowPosition(0, 0);

	system("CLS");

	std::cout << "DashPlus Initialized." << "\n";

	if (ntTable->GetBoolean("RIO_CONNECTED", 0) == 0) {
		std::cout << "[WARNING] No Connection to RoboRio! (RIO_CONNECTED=" << ntTable->GetBoolean("RIO_CONNECTED", 0) << ")\n";
	}

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("DashPlus", 10, 10, 20, BLACK);

		EndDrawing();
	}

}