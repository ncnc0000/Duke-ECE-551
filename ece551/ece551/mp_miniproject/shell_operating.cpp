#include "shell_operating.h"

#include <dirent.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "command.h"

using namespace std;
//print shell promption "myShell:/current working path $:"
void Shell::PrintMyshell() {
  char * p = get_current_dir_name();
  path = p;
  free(p);
  cout << "myShell:";
  int pos = path.find(home_path.c_str(), 0);
  if (pos == -1)
    cout << path;
  else {
    cout << "~";
    if (home_path.size() != path.size())
      for (size_t i = home_path.size(); i < path.size(); i++)
        cout << path[i];
  }
  cout << "$ ";
}
Shell::Shell() {
  //get current working path
  char * p = get_current_dir_name();
  path = p;
  free(p);
  //get home path
  home_path = GetHome();
}
string Shell::GetHome() {
  string home;
  int num = 0;
  for (unsigned int i = 0; i < path.size(); i++) {
    if (path[i] == '/')
      num++;
    if (num == 3) {
      home = path.substr(0, i);
      break;
    }
  }
  return home;
}
string Shell::ReadInput() {
  string in;
  PrintMyshell();
  if (!getline(cin, in))
    in = "exit";
  else
    history_command.push_back(in);
  return in;
}
