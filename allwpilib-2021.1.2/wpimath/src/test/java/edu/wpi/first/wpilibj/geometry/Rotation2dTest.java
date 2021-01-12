// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.wpilibj.geometry;

import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import org.junit.jupiter.api.Test;

class Rotation2dTest {
  private static final double kEpsilon = 1E-9;

  @Test
  void testRadiansToDegrees() {
    var one = new Rotation2d(Math.PI / 3);
    var two = new Rotation2d(Math.PI / 4);

    assertAll(
        () -> assertEquals(one.getDegrees(), 60.0, kEpsilon),
        () -> assertEquals(two.getDegrees(), 45.0, kEpsilon));
  }

  @Test
  void testRadiansAndDegrees() {
    var one = Rotation2d.fromDegrees(45.0);
    var two = Rotation2d.fromDegrees(30.0);

    assertAll(
        () -> assertEquals(one.getRadians(), Math.PI / 4, kEpsilon),
        () -> assertEquals(two.getRadians(), Math.PI / 6, kEpsilon));
  }

  @Test
  void testRotateByFromZero() {
    var zero = new Rotation2d();
    var rotated = zero.rotateBy(Rotation2d.fromDegrees(90.0));

    assertAll(
        () -> assertEquals(rotated.getRadians(), Math.PI / 2.0, kEpsilon),
        () -> assertEquals(rotated.getDegrees(), 90.0, kEpsilon));
  }

  @Test
  void testRotateByNonZero() {
    var rot = Rotation2d.fromDegrees(90.0);
    rot = rot.plus(Rotation2d.fromDegrees(30.0));

    assertEquals(rot.getDegrees(), 120.0, kEpsilon);
  }

  @Test
  void testMinus() {
    var one = Rotation2d.fromDegrees(70.0);
    var two = Rotation2d.fromDegrees(30.0);

    assertEquals(one.minus(two).getDegrees(), 40.0, kEpsilon);
  }

  @Test
  void testEquality() {
    var one = Rotation2d.fromDegrees(43.0);
    var two = Rotation2d.fromDegrees(43.0);
    assertEquals(one, two);
  }

  @Test
  void testInequality() {
    var one = Rotation2d.fromDegrees(43.0);
    var two = Rotation2d.fromDegrees(43.5);
    assertNotEquals(one, two);
  }
}
