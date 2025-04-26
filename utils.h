#pragma once

#include <string>

void trim(std::string &trim_me) {
  trim_me.erase(trim_me.begin(), std::find_if(trim_me.begin(), trim_me.end(),
                                              [](unsigned char ch) { return !std::isspace(ch); }));
  trim_me.erase(std::find_if(trim_me.rbegin(), trim_me.rend(),
                             [](unsigned char ch) { return !std::isspace(ch); })
                    .base(),
                trim_me.end());
}

bool isNumber(const std::string &str) {
  for (char c : str) {
    if (!std::isdigit(c))
      return false;
  }
  return true;
}