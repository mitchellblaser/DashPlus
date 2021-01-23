// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

#include "string"

using namespace std;

class DashPlusServer {
 public:
  DashPlusServer();
  void sendInteger(string key, int value);

 private:
  shared_ptr<NetworkTable> _ntTable;
};
