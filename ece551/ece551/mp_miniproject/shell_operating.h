#ifndef SHELL_OPERATING_H_INCLUDED
#define SHELL_OPERATING_H_INCLUDED
//----------------------include
#include <map>
#include <string>
#include <vector>

#include "command.h"
using namespace std;
//---------------------class
class Shell
{
  string path, adv_path, home_path;
  vector<string> history_command;
  map<string, string> var;
  map<string, string> env;
  string GetHome();
  void PrintMyshell();

 public:
  Shell();
  string ReadInput();
  void PrintStatus();
  // void Check_dollar();
  friend class Command;
};
//----------------------function

#endif
