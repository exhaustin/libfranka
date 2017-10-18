// Copyright (c) 2017 Franka Emika GmbH
// Use of this source code is governed by the Apache-2.0 license, see LICENSE
#pragma once

#include <stdexcept>
#include <string>

/**
 * @file exception.h
 * Contains exception definitions.
 */

namespace franka {

/**
 * Base class for all exceptions used by `libfranka`.
 */
struct Exception : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

/**
 * ModelException is thrown if an error occurs when loading the model library.
 */
struct ModelException : public Exception {
  using Exception::Exception;
};

/**
 * NetworkException is thrown if a connection to the robot cannot be established, or when a timeout
 * occurs.
 */
struct NetworkException : public Exception {
  using Exception::Exception;
};

/**
 * ProtocolException is thrown if the robot returns an incorrect message.
 */
struct ProtocolException : public Exception {
  using Exception::Exception;
};

/**
 * IncompatibleVersionException is thrown if the robot does not support this version of libfranka.
 */
struct IncompatibleVersionException : public Exception {
  using Exception::Exception;
};

/**
 * ControlException is thrown if an error occurs during motion generation or torque control.
 * The exception holds a path to a temporary log file if one was created.
 */
struct ControlException : public Exception {
  /**
   * Creates the exception with an explanatory string and a path to the log file.
   * @param[in] what Explanatory string.
   * @param[in] log_file_path Path to the temporary log file or an empty string.
   */
  explicit ControlException(const std::string& what, const std::string& log_file_path = "")
      : Exception(what), log_file_path_(log_file_path){};

  /**
  * Returns the path to a temporary file containing the log or an empty string if a log was not
  * written.
  * @return Full file path or an empty string.
  */
  std::string logFilePath() const { return log_file_path_; }

 private:
  std::string log_file_path_;
};

/**
 * CommandException is thrown if an error occurs during command execution.
 */
struct CommandException : public Exception {
  using Exception::Exception;
};

/**
 * RealtimeException is thrown if realtime priority cannot be set.
 */
struct RealtimeException : public Exception {
  using Exception::Exception;
};

/**
 * InvalidOperationException is thrown if an operation cannot be performed.
 */
struct InvalidOperationException : public Exception {
  using Exception::Exception;
};

}  // namespace franka
