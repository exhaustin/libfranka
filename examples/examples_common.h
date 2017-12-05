// Copyright (c) 2017 Franka Emika GmbH
// Use of this source code is governed by the Apache-2.0 license, see LICENSE
#pragma once

#include <array>

#include <franka/duration.h>
#include <franka/robot_state.h>

/**
 * @file examples_common.h
 * Contains common types and functions for the examples.
 */

/**
 * Limits the rate of an input vector of per-joint commands considering the maximum allowed time
 * derivatives.
 *
 * @param[in] max_derivatives Per-joint maximum allowed time derivative.
 * @param[in] desired_values Desired values of the current time step.
 * @param[in] last_desired_values Desired values of the previous time step.
 *
 * @return Rate-limited vector of desired values.
 */
std::array<double, 7> limitRate(const std::array<double, 7>& max_derivatives,
                                const std::array<double, 7>& desired_values,
                                const std::array<double, 7>& last_desired_values);

/**
 * An example showing how to generate a joint pose motion to a goal position. Adapted from:
 * Wisama Khalil and Etienne Dombre. 2002. Modeling, Identification and Control of Robots
 * (Kogan Page Science Paper edition).
 */
class MotionGenerator {
 public:
  /**
   * Creates a new MotionGenerator instance for a target q.
   *
   * @param[in] speed_factor General speed factor in range [0, 1].
   * @param[in] q_goal Target joint positions.
   */
  MotionGenerator(double speed_factor, const std::array<double, 7> q_goal);

  /**
   * Sends joint position calculations
   *
   * @param[in] robot_state Current state of the robot.
   * @param[in] time_step Duration of execution.
   *
   * @return Joint positions for use inside a control loop.
   */
  franka::JointPositions operator()(const franka::RobotState& robot_state,
                                    franka::Duration time_step);

 private:
  bool calculateDesiredValues(double t, std::array<double, 7>* delta_q_d) const;
  void calculateSynchronizedValues();

  static constexpr double kDeltaQMotionFinished = 1e-6;
  const std::array<double, 7> q_goal_;

  std::array<double, 7> q_start_;
  std::array<double, 7> delta_q_;

  std::array<double, 7> dq_max_sync_;
  std::array<double, 7> t_1_sync_;
  std::array<double, 7> t_2_sync_;
  std::array<double, 7> t_f_sync_;
  std::array<double, 7> q_1_;

  double time_ = 0.0;

  std::array<double, 7> dq_max_ = {{2.0, 2.0, 2.0, 2.0, 2.5, 2.5, 2.5}};
  std::array<double, 7> ddq_max_start_ = {{5, 5, 5, 5, 5, 5, 5}};
  std::array<double, 7> ddq_max_goal_ = {{5, 5, 5, 5, 5, 5, 5}};
};
