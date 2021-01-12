// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/buttons/PressedButtonScheduler.h"

#include "frc/buttons/Button.h"
#include "frc/commands/Command.h"

using namespace frc;

PressedButtonScheduler::PressedButtonScheduler(bool last, Trigger* button,
                                               Command* orders)
    : ButtonScheduler(last, button, orders) {}

void PressedButtonScheduler::Execute() {
  bool pressed = m_button->Grab();

  if (!m_pressedLast && pressed) {
    m_command->Start();
  }

  m_pressedLast = pressed;
}
