#pragma once

#include "utils.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using string = std::string;

class Command {
public:
  Command() = default;
  virtual ~Command() = default;

  virtual void execute(const string &user_input = "") = 0;
};

class HelpCommand : public Command {
public:
  HelpCommand() = default;
  virtual ~HelpCommand() = default;

  void execute(const string &user_input = "") override {
    std::cout << ":Help Command:" << std::endl;
    std::cout << "Aviable Commands: " << std::endl
              << "time" << std::endl
              << "exit" << std::endl
              << "time" << std::endl
              << "echo" << std::endl
              << "add" << std::endl
              << "mult" << std::endl;
  }
};

class EchoCommand : public Command {
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

    std::vector<std::string> argums = splitString(std::move(user_input));

    if (argums.size() != 2) {
      std::cout << "ERROR: function \'Add\' expects exactly two positive arguments!" << std::endl;
      return;
    }

    long long result = 0;

    for (const auto &argum : argums) {
      try {
        if (!isNumber(argum)) {
          throw std::invalid_argument("'" + argum + "' not a number!");
        }

        long long number = std::stoll(argum);

        if (number > std::numeric_limits<long long>::max() - result) {
          throw std::overflow_error("Overflow during operation. \n(max: 9223372036854775807)");
        }

        result += number;

      } catch (const std::invalid_argument &e) {
        std::cerr << "ERROR!: " << e.what() << std::endl;
        return;
      } catch (const std::out_of_range &e) {
        std::cerr << "ERROR!: Overflow value " + argum + ".\n(max: 9223372036854775807)"
                  << std::endl;
        return;
      } catch (const std::overflow_error &e) {
        std::cout << "ERROR!: " << e.what() << std::endl;
        return;
      } catch (...) {
        std::cerr << "ERROR!: Undefined error!" << std::endl;
        return;
      }
    }

    std::cout << "Result: " << result << std::endl;
  }
};

class MultCommand : public Command {
public:
  MultCommand() = default;
  virtual ~MultCommand() = default;

  void execute(const string &user_input = "") override {
    std::cout << ":Mult Command:" << std::endl;

    std::vector<std::string> argums = splitString(std::move(user_input));

    if (argums.size() != 2) {
      std::cout << "ERROR: function \'Mult\' expects exactly two positive arguments!" << std::endl;
      return;
    }

    long long result = 1;

    for (const auto &argum : argums) {
      try {
        if (!isNumber(argum)) {
          throw std::invalid_argument("'" + argum + "' not a number!");
        }

        long long number = std::stoll(argum);

        if (number > std::numeric_limits<long long>::max() / result) {
          throw std::overflow_error("Overflow during operation. \n(max: 9223372036854775807)");
        }

        result *= number;

      } catch (const std::invalid_argument &e) {
        std::cerr << "ERROR!: " << e.what() << std::endl;
        return;
      } catch (const std::out_of_range &e) {
        std::cerr << "ERROR!: Overflow value " + argum + ".\n(max: 9223372036854775807)"
                  << std::endl;
        return;
      } catch (const std::overflow_error &e) {
        std::cout << "ERROR!: " << e.what() << std::endl;
        return;
      } catch (...) {
        std::cerr << "ERROR!: Undefined error!" << std::endl;
        return;
      }
    }

    std::cout << "Result: " << result << std::endl;
  };
};