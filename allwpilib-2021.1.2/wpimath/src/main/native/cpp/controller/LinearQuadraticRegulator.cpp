// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/controller/LinearQuadraticRegulator.h"

namespace frc {

LinearQuadraticRegulator<1, 1>::LinearQuadraticRegulator(
    const Eigen::Matrix<double, 1, 1>& A, const Eigen::Matrix<double, 1, 1>& B,
    const std::array<double, 1>& Qelems, const std::array<double, 1>& Relems,
    units::second_t dt)
    : LinearQuadraticRegulator(A, B, MakeCostMatrix(Qelems),
                               MakeCostMatrix(Relems), dt) {}

LinearQuadraticRegulator<1, 1>::LinearQuadraticRegulator(
    const Eigen::Matrix<double, 1, 1>& A, const Eigen::Matrix<double, 1, 1>& B,
    const Eigen::Matrix<double, 1, 1>& Q, const Eigen::Matrix<double, 1, 1>& R,
    units::second_t dt)
    : detail::LinearQuadraticRegulatorImpl<1, 1>(A, B, Q, R, dt) {}

LinearQuadraticRegulator<2, 1>::LinearQuadraticRegulator(
    const Eigen::Matrix<double, 2, 2>& A, const Eigen::Matrix<double, 2, 1>& B,
    const std::array<double, 2>& Qelems, const std::array<double, 1>& Relems,
    units::second_t dt)
    : LinearQuadraticRegulator(A, B, MakeCostMatrix(Qelems),
                               MakeCostMatrix(Relems), dt) {}

LinearQuadraticRegulator<2, 1>::LinearQuadraticRegulator(
    const Eigen::Matrix<double, 2, 2>& A, const Eigen::Matrix<double, 2, 1>& B,
    const Eigen::Matrix<double, 2, 2>& Q, const Eigen::Matrix<double, 1, 1>& R,
    units::second_t dt)
    : detail::LinearQuadraticRegulatorImpl<2, 1>(A, B, Q, R, dt) {}

}  // namespace frc
