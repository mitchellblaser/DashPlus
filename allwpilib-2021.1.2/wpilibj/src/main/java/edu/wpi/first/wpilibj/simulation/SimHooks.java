// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.wpilibj.simulation;

import edu.wpi.first.hal.simulation.SimulatorJNI;

public final class SimHooks {
  private SimHooks() {}

  public static void setHALRuntimeType(int type) {
    SimulatorJNI.setRuntimeType(type);
  }

  public static void waitForProgramStart() {
    SimulatorJNI.waitForProgramStart();
  }

  public static void setProgramStarted() {
    SimulatorJNI.setProgramStarted();
  }

  public static boolean getProgramStarted() {
    return SimulatorJNI.getProgramStarted();
  }

  public static void restartTiming() {
    SimulatorJNI.restartTiming();
  }

  public static void pauseTiming() {
    SimulatorJNI.pauseTiming();
  }

  public static void resumeTiming() {
    SimulatorJNI.resumeTiming();
  }

  public static boolean isTimingPaused() {
    return SimulatorJNI.isTimingPaused();
  }

  public static void stepTiming(double deltaSeconds) {
    SimulatorJNI.stepTiming((long) (deltaSeconds * 1e6));
  }

  public static void stepTimingAsync(double deltaSeconds) {
    SimulatorJNI.stepTimingAsync((long) (deltaSeconds * 1e6));
  }
}
