/*command include

*/
#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED
//--------------------include
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

#include "shell_operating.h"

using namespace std;
class Shell;
//--------------------class
class Command
{
  int argc;
  pid_t childpid, pid;
  int command_number;
  string home_path;
  vector<int> pipe_list;
  vector<vector<string> > command_list;
  vector<string> parameter_list;
  int DoCommand(vector<string> & _command, Shell & shell);
  int Exit();
  int Empty();
  int ChangeDir(vector<string> & _command, Shell & shell);
  int ListDir(string & path, string & command);
  void Execute(vector<string> & _command, Shell & shell);
  void get_env(Shell & shell);
  void check_path(vector<string> & _command, Shell & shell);
  string Check_Program(string & path, Shell & shell);
  void Set_var(vector<string> & _command, Shell & shell);
  void Export(vector<string> & _command, Shell & shell);
  void Inc(vector<string> & _command, Shell & shell);
  void Check_dollar(vector<string> & _command, Shell & shell);

 public:
  int status;
  string ori_str;
  Command(vector<string> command_list_in, Shell & shell);
  int RunCommand(Shell & shell);
};
//--------------------function
vector<string> ArgvTransform(string in);
string ContinueInput();
#endif
