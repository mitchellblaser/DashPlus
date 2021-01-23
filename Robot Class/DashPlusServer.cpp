// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "DashPlusServer.h"

#include "ntcore.h"
#include "string"

using namespace std;

DashPlusServer::DashPlusServer() {
  nt::NetworkTableInstance ntInst = nt::NetworkTableInstance::GetDefault();
  
  shared_ptr<NetworkTable> ntTable(ntInst.GetTable("DashPlus"));
  
  _ntTable = ntTable;
  
  _ntTable->PutBoolean("RIO_CONNECTED", 1);

}

void DashPlusServer::sendInteger(string key, int value) {
    _ntTable->PutNumber(key, value);
}