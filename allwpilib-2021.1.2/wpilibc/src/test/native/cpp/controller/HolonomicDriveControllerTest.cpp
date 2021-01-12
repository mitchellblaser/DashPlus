// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <units/math.h>
#include <units/time.h>
#include <wpi/math>

#include "frc/MathUtil.h"
#include "frc/controller/HolonomicDriveController.h"
#include "frc/trajectory/TrajectoryGenerator.h"
#include "gtest/gtest.h"

#define EXPECT_NEAR_UNITS(val1, val2, eps) \
  EXPECT_LE(units::math::abs(val1 - val2), eps)

static constexpr units::meter_t kTolerance{1 / 12.0};
static constexpr units::radian_t kAngularTolerance{2.0 * wpi::math::pi / 180.0};

TEST(HolonomicDriveControllerTest, ReachesReference) {
  frc::HolonomicDriveController controller{
      frc2::PIDController{1.0, 0.0, 0.0}, frc2::PIDController{1.0, 0.0, 0.0},
      frc::ProfiledPIDController<units::radian>{
          1.0, 0.0, 0.0,
          frc::TrapezoidProfile<units::radian>::Constraints{
              6.28_rad_per_s, 3.14_rad_per_s / 1_s}}};

  frc::Pose2d robotPose{2.7_m, 23_m, frc::Rotation2d{0_deg}};

  auto waypoints = std::vector{frc::Pose2d{2.75_m, 22.521_m, 0_rad},
                               frc::Pose2d{24.73_m, 19.68_m, 5.846_rad}};
  auto trajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      waypoints, {8.0_mps, 4.0_mps_sq});

  constexpr auto kDt = 0.02_s;
  auto totalTime = trajectory.TotalTime();
  for (size_t i = 0; i < (totalTime / kDt).to<double>(); ++i) {
    auto state = trajectory.Sample(kDt * i);
    auto [vx, vy, omega] = controller.Calculate(robotPose, state, 0_rad);

    robotPose = robotPose.Exp(frc::Twist2d{vx * kDt, vy * kDt, omega * kDt});
  }

  auto& endPose = trajectory.States().back().pose;
  EXPECT_NEAR_UNITS(endPose.X(), robotPose.X(), kTolerance);
  EXPECT_NEAR_UNITS(endPose.Y(), robotPose.Y(), kTolerance);
  EXPECT_NEAR_UNITS(frc::AngleModulus(robotPose.Rotation().Radians()), 0_rad,
                    kAngularTolerance);
}
