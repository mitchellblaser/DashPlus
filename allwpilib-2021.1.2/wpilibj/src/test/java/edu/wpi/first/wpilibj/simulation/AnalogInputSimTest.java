// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.wpilibj.simulation;

import static org.junit.jupiter.api.Assertions.assertEquals;

import edu.wpi.first.hal.HAL;
import edu.wpi.first.wpilibj.AnalogInput;
import org.junit.jupiter.api.Test;

class AnalogInputSimTest {
  static class DoubleStore {
    public boolean m_wasTriggered;
    public boolean m_wasCorrectType;
    public double m_setValue0;
  }

  @Test
  void setCallbackTest() {
    HAL.initialize(500, 0);

    try (AnalogInput input = new AnalogInput(5)) {
      AnalogInputSim inputSim = new AnalogInputSim(input);

      for (double i = 0; i < 5.0; i += 0.1) {
        inputSim.setVoltage(0);

        assertEquals(input.getVoltage(), 0, 0.001);

        inputSim.setVoltage(i);

        assertEquals(input.getVoltage(), i, 0.001);
      }
    }
  }
}
