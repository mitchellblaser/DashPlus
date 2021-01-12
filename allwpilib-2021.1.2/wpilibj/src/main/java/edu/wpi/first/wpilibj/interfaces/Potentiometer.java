// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.wpilibj.interfaces;

import edu.wpi.first.wpilibj.PIDSource;

/** Interface for a Potentiometer. */
public interface Potentiometer extends PIDSource {
  double get();
}
