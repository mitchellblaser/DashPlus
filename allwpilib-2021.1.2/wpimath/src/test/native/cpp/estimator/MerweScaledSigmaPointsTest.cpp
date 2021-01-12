// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <gtest/gtest.h>

#include "frc/StateSpaceUtil.h"
#include "frc/estimator/MerweScaledSigmaPoints.h"

namespace drake::math {
namespace {
TEST(MerweScaledSigmaPointsTest, TestZeroMean) {
  frc::MerweScaledSigmaPoints<2> sigmaPoints;
  auto points =
      sigmaPoints.SigmaPoints(frc::MakeMatrix<2, 1>(0.0, 0.0),
                              frc::MakeMatrix<2, 2>(1.0, 0.0, 0.0, 1.0));

  EXPECT_TRUE(
      (points - frc::MakeMatrix<2, 5>(0.0, 0.00173205, 0.0, -0.00173205, 0.0,
                                      0.0, 0.0, 0.00173205, 0.0, -0.00173205))
          .norm() < 1e-3);
}

TEST(MerweScaledSigmaPointsTest, TestNonzeroMean) {
  frc::MerweScaledSigmaPoints<2> sigmaPoints;
  auto points =
      sigmaPoints.SigmaPoints(frc::MakeMatrix<2, 1>(1.0, 2.0),
                              frc::MakeMatrix<2, 2>(1.0, 0.0, 0.0, 10.0));

  EXPECT_TRUE(
      (points - frc::MakeMatrix<2, 5>(1.0, 1.00173205, 1.0, 0.998268, 1.0, 2.0,
                                      2.0, 2.00548, 2.0, 1.99452))
          .norm() < 1e-3);
}
}  // namespace
}  // namespace drake::math
