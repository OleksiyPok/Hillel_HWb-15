#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "commands.h"
#include "utils.h"

using string = std::string;

int main(int argc, char **argv) {

  string user_input;

  std::map<std::string, std::unique_ptr<Command>> commands;
  commands.emplace("exit", std::make_unique<ExitCommand>());
  commands.emplace("", std::make_unique<EmptyCommand>());
  commands.emplace("time", std::make_unique<TimeCommand>());
  commands.emplace("echo", std::make_unique<EchoCommand>());
  commands.emplace("add", std::make_unique<AddCommand>());
  commands.emplace("mult", std::make_unique<MultCommand>());
  commands.emplace("help", std::make_unique<HelpCommand>());

  do {
    std::cout << "==>> ";
    std::getline(std::cin, user_input);
    trim(user_input);

    size_t space_pos = user_input.find(' ');
    bool isArgum = space_pos != std::string::npos;

    std::string inp_command = isArgum ? user_input.substr(0, space_pos) : user_input;
    std::string inp_argum = isArgum ? user_input.substr(space_pos + 1) : "";

    trim(inp_command);
    trim(inp_argum);

    if (commands.contains(inp_command)) {
      commands[inp_command]->execute(inp_argum);
    } else {
      UnknownCommand().execute();
    }

  } while (true);

  return 0;
}
