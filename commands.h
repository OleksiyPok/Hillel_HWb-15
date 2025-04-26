#pragma once

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "utils.h"

using string = std::string;

class Command {
public:
  Command() = default;
  virtual ~Command() = default;

  virtual void execute(const string &user_input = "") = 0;
};

class EchoCommand : public Command {
private:
  std::string input_string;

public:
  EchoCommand() = default;
  virtual ~EchoCommand() = default;

  void execute(const string &user_input = "") override {
    std::cout << ":Echo Command:" << std::endl;
    if (user_input == "") {
      std::cout << "ERROR: Empty string!" << std::endl;
    } else {
      std::cout << user_input << std::endl;
    }
  }
};

class ExitCommand : public Command {
public:
  ExitCommand() = default;
  virtual ~ExitCommand() = default;

  void execute(const string &user_input = "") override {
    std::cout << ":Exit Command:" << std::endl;
    std::cout << "Thanks for using our REPL! Bye ^_^" << std::endl;
    getchar();

    std::exit(0);
  }
};

class UnknownCommand : public Command {
public:
  UnknownCommand() = default;
  virtual ~UnknownCommand() = default;

  void execute(const string &user_input = "") override {
    std::cout << ":Unknown Command:" << std::endl;
    // std::cout << "ERROR: no such command!" << std::endl;
  }
};

class EmptyCommand : public Command {
public:
  EmptyCommand() = default;
  virtual ~EmptyCommand() = default;

  void execute(const string &user_input = "") override {
    std::cout << ":Empty Command:" << std::endl;
  }
};

class TimeCommand : public Command {
public:
  TimeCommand() = default;
  virtual ~TimeCommand() = default;

  void execute(const string &user_input = "") override {
    std::cout << ":Time Command:" << std::endl;
    auto timestamp = std::chrono::system_clock::now();
    std::time_t now_tt = std::chrono::system_clock::to_time_t(timestamp);
    std::tm tm = *std::localtime(&now_tt);

    std::cout << "Current time: " << std::put_time(&tm, "%c") << std::endl;
  }
};

class AddCommand : public Command {
public:
  AddCommand() = default;
  virtual ~AddCommand() = default;

  void execute(const string &user_input = "") override {
    std::cout << ":Add Command:" << std::endl;

    std::stringstream ss(user_input);
    std::string tempStr;

    int result = 0;
    int count = 0;

    while (ss >> tempStr) {
      count++;
      if (!isNumber(tempStr)) {
        std::cout << "ERROR: '" << tempStr << "' not a number!" << std::endl;
        return;
      }
      result += std::stoi(tempStr);
    }

    if (count != 2) {
      std::cout << "ERROR: function \'Add\' expects exactly two arguments!" << std::endl;
      return;
    }

    std::cout << "Result: " << result << std::endl;
  };
};
