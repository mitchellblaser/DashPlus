// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "WSHalProviders.h"

namespace wpilibws {

void HALSimWSHalProvider::OnNetworkConnected(
    std::shared_ptr<HALSimBaseWebSocketConnection> ws) {
  {
    // store a weak reference to the websocket object
    m_ws = ws;
  }

  RegisterCallbacks();
}

void HALSimWSHalProvider::OnNetworkDisconnected() {
  CancelCallbacks();
}

void HALSimWSHalProvider::ProcessHalCallback(const wpi::json& payload) {
  auto ws = m_ws.lock();
  if (ws) {
    wpi::json netValue = {
        {"type", m_type}, {"device", m_deviceId}, {"data", payload}};
    ws->OnSimValueChanged(netValue);
  }
}

HALSimWSHalChanProvider::HALSimWSHalChanProvider(int32_t channel,
                                                 const std::string& key,
                                                 const std::string& type)
    : HALSimWSHalProvider(key, type), m_channel(channel) {
  m_deviceId = std::to_string(channel);
}

}  // namespace wpilibws
