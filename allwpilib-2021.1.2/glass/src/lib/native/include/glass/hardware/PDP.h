// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <wpi/STLExtras.h>
#include <wpi/StringRef.h>

#include "glass/Model.h"

namespace glass {

class DataSource;

class PDPModel : public Model {
 public:
  virtual int GetNumChannels() const = 0;

  virtual DataSource* GetTemperatureData() = 0;
  virtual DataSource* GetVoltageData() = 0;
  virtual DataSource* GetCurrentData(int channel) = 0;

  virtual void SetTemperature(double val) = 0;
  virtual void SetVoltage(double val) = 0;
  virtual void SetCurrent(int channel, double val) = 0;
};

class PDPsModel : public Model {
 public:
  virtual void ForEachPDP(
      wpi::function_ref<void(PDPModel& model, int index)> func) = 0;
};

void DisplayPDP(PDPModel* model, int index);
void DisplayPDPs(PDPsModel* model, wpi::StringRef noneMsg = "No PDPs");

}  // namespace glass
