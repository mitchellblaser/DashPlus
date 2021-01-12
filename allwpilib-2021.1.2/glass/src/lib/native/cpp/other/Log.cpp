// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "glass/other/Log.h"

#include <imgui.h>
#include <wpi/raw_ostream.h>

using namespace glass;

LogData::LogData(size_t maxLines) : m_maxLines{maxLines} {}

void LogData::Clear() {
  m_buf.clear();
  m_lineOffsets.clear();
  m_lineOffsets.push_back(0);
}

void LogData::Append(const wpi::Twine& msg) {
  if (m_lineOffsets.size() >= m_maxLines) {
    Clear();
  }

  size_t oldSize = m_buf.size();
  wpi::raw_vector_ostream os{m_buf};
  msg.print(os);
  for (size_t newSize = m_buf.size(); oldSize < newSize; ++oldSize) {
    if (m_buf[oldSize] == '\n') {
      m_lineOffsets.push_back(oldSize + 1);
    }
  }
}

void glass::DisplayLog(LogData* data, bool autoScroll) {
  if (data->m_buf.empty()) {
    return;
  }
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
  const char* buf = data->m_buf.data();
  const char* bufEnd = buf + data->m_buf.size();
  ImGuiListClipper clipper;
  clipper.Begin(data->m_lineOffsets.size());
  while (clipper.Step()) {
    for (size_t lineNum = clipper.DisplayStart;
         lineNum < static_cast<size_t>(clipper.DisplayEnd); lineNum++) {
      const char* lineStart = buf + data->m_lineOffsets[lineNum];
      const char* lineEnd = (lineNum + 1 < data->m_lineOffsets.size())
                                ? (buf + data->m_lineOffsets[lineNum + 1] - 1)
                                : bufEnd;
      ImGui::TextUnformatted(lineStart, lineEnd);
    }
  }
  clipper.End();
  ImGui::PopStyleVar();

  if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
    ImGui::SetScrollHereY(1.0f);
  }
}

void LogView::Display() {
  if (ImGui::BeginPopupContextItem()) {
    ImGui::Checkbox("Auto-scroll", &m_autoScroll);
    if (ImGui::Selectable("Clear")) {
      m_data->Clear();
    }
    ImGui::EndPopup();
  }

  DisplayLog(m_data, m_autoScroll);
}
