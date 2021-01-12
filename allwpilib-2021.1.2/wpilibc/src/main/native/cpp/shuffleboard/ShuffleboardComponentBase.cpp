// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/shuffleboard/ShuffleboardComponentBase.h"

#include <wpi/SmallVector.h>

using namespace frc;

ShuffleboardComponentBase::ShuffleboardComponentBase(
    ShuffleboardContainer& parent, const wpi::Twine& title,
    const wpi::Twine& type)
    : ShuffleboardValue(title), m_parent(parent) {
  wpi::SmallVector<char, 16> storage;
  m_type = type.toStringRef(storage);
}

void ShuffleboardComponentBase::SetType(const wpi::Twine& type) {
  wpi::SmallVector<char, 16> storage;
  m_type = type.toStringRef(storage);
  m_metadataDirty = true;
}

void ShuffleboardComponentBase::BuildMetadata(
    std::shared_ptr<nt::NetworkTable> metaTable) {
  if (!m_metadataDirty) {
    return;
  }
  // Component type
  if (GetType() == "") {
    metaTable->GetEntry("PreferredComponent").Delete();
  } else {
    metaTable->GetEntry("PreferredComponent").ForceSetString(GetType());
  }

  // Tile size
  if (m_width <= 0 || m_height <= 0) {
    metaTable->GetEntry("Size").Delete();
  } else {
    metaTable->GetEntry("Size").SetDoubleArray(
        {static_cast<double>(m_width), static_cast<double>(m_height)});
  }

  // Tile position
  if (m_column < 0 || m_row < 0) {
    metaTable->GetEntry("Position").Delete();
  } else {
    metaTable->GetEntry("Position")
        .SetDoubleArray(
            {static_cast<double>(m_column), static_cast<double>(m_row)});
  }

  // Custom properties
  if (GetProperties().size() > 0) {
    auto propTable = metaTable->GetSubTable("Properties");
    for (auto& entry : GetProperties()) {
      propTable->GetEntry(entry.first()).SetValue(entry.second);
    }
  }
  m_metadataDirty = false;
}

ShuffleboardContainer& ShuffleboardComponentBase::GetParent() {
  return m_parent;
}

const std::string& ShuffleboardComponentBase::GetType() const {
  return m_type;
}

const wpi::StringMap<std::shared_ptr<nt::Value>>&
ShuffleboardComponentBase::GetProperties() const {
  return m_properties;
}
