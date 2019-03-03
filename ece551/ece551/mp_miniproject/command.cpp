#include "command.h"

#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>

#include "shell_operating.h"
using namespace std;
//Command constructor
Command::Command(vector<string> command_list_in, Shell & shell) {
  //deal with "\"
  get_env(shell);
  for (vector<string>::iterator i = command_list_in.begin(); i != command_list_in.end(); i++) {
    if (*i == "\\") {
      command_list_in.erase(i);
    }
  }
  //deal with "\0"
  for (vector<string>::iterator i = command_list_in.begin(); i != command_list_in.end(); i++)
    if (*i == "\0")
      command_list_in.erase(i--);
  //deal with pipe "|"
  vector<string> str;
  for (vector<string>::iterator i = command_list_in.begin(); i != command_list_in.end(); i++) {
    str.push_back(*i);
    if (*i == "|") {
      str.pop_back();
      command_list.push_back(str);
      str.clear();
    }
  }
  command_list.push_back(str);
  str.clear();
  command_number = command_list.size();
}
//set ECE551path enviroment variable and add it to env map
void Command::get_env(Shell & shell) {
  char * path;
  path = getenv("PATH");
  string str2(path);
  string str1("ECE551PATH");
  shell.env[str1] = str2;
}
//parse input
vector<string> ArgvTransform(string in) {
  vector<string> out;
  const char SPACE = ' ', PIPE = '|', LINE = '\\';
  if (in[in.size() - 1] == ' ')
    in.erase(in.size() - 1, 1);
  unsigned int pos = 0, init = 0;
  while (1) {
    if (pos >= in.size()) {
      string s = in.substr(init, pos - init);
      out.push_back(s);
      break;
    }
    else if (in[pos] == SPACE) {
      if (!out.empty() &&
          (out.front() == "set" || out.front() == "export" || out.front() == "inc")) {
        if (out.front() == "set" || out.front() == "export" || out.front() == "inc") {
          string s = in.substr(init, pos - init);
          out.push_back(s);
          init = pos + 1;
        }
        if (in[in.size() - 1] == ' ') {
          for (size_t i = in.size() - 1; i > pos; i--) {
            if (in[i] == ' ' && in[i - 1] != ' ') {
              pos = i;
            }
          }
        }
        else {
          pos = in.size();
        }
        string s = in.substr(init, pos - init);
        out.push_back(s);
        break;
      }
      string s = in.substr(init, pos - init);
      out.push_back(s);
      init = pos + 1;
    }
    else if (in[pos] == PIPE) {
      string s = in.substr(init, pos - init);
      out.push_back(s);
      out.push_back("|");
      init = pos + 1;
    }
    else if (in[pos] == LINE) {
      in.erase(pos, 1);
    }
    pos++;
  }
  return out;
}
//run different command, run one and get rid of it
int Command::RunCommand(Shell & shell) {
  int res;
  while (!command_list.empty()) {
    res = DoCommand(command_list.front(), shell);
    command_list.erase(command_list.begin());
  }
  return res;
}
//for each command(vector<string>), run different function according to the first element of the vector
int Command::DoCommand(vector<string> & _command, Shell & shell) {
  int res = 0;
  string command_get = _command.front();
  if (_command.empty())
    res = Empty();
  else if (command_get == "exit")
    res = Exit();
  else if (command_get == "cd")
    res = ChangeDir(_command, shell);
  else if (command_get == "set") {
    Set_var(_command, shell);
  }
  else if (command_get == "export") {
    Export(_command, shell);
  }
  else if (command_get == "inc") {
    Inc(_command, shell);
  }
  else {
    //if the command is not set/export/inc/cd/exit, we need to find if the input is a execteable program
    check_path(_command, shell);
  }
  shell.adv_path = shell.path;
  return res;
}
//-----------------command
int Command::Exit() {
  //cout << "Program exited with status " << status << endl;
  return -100;
}
int Command::Empty() {
  //do nothing
  return 100;
}
//if the command is cd, then change the DIRectory
int Command::ChangeDir(vector<string> & _command, Shell & shell) {
  if (_command.size() == 1) {
    chdir(shell.home_path.c_str());
    return 1;
  }
  if (_command[1][0] == '~') {
    _command[1].erase(_command[1].begin());
    _command[1] = shell.home_path + _command[1];
  }
  if (_command[1] == "-") {
    cout << shell.adv_path << endl;
    chdir(shell.adv_path.c_str());
  }
  else if (_command[1] == ".")
    ;
  else if (chdir(_command[1].c_str()) == -1)
    cout << "Error: No such file or directory" << endl;
  return 1;
}
//get all the file of the current path and find the executable program
int Command::ListDir(string & path, string & command) {
  vector<string> dir_name;
  DIR * dir = opendir(path.c_str());
  struct dirent * dir_read;
  while ((dir_read = readdir(dir)) != NULL) {
    dir_name.push_back(dir_read->d_name);
  }
  closedir(dir);
  sort(dir_name.begin(), dir_name.end());
  for (unsigned int i = 0; i < dir_name.size(); i++) {
    if (dir_name[i].compare(command) == 0) {
      return 1;
    }
  }
  return 0;
}
//set all parameters of execve, create child process.
void Command::Execute(vector<string> & _command, Shell & shell) {
  //first parameter of execve
  vector<string> v1;
  const char * __path = _command.front().c_str();
  int id, envpc = 0, argc = 0;
  //second parameter of execve
  char ** argv = NULL;
  //third parameter of execve
  char ** envp = NULL;
  status = 0;
  size_t found = _command[0].find_last_of('/');
  string str = _command[0].substr(found + 1);
  //put all arguments in argv
  argv = (char **)realloc(argv, (argc + 1) * sizeof(*argv));
  argv[argc] = const_cast<char *>(str.c_str());
  argc++;
  for (std::size_t i = 1; i < _command.size(); ++i) {
    argv = (char **)realloc(argv, (argc + 1) * sizeof(*argv));
    argv[argc] = const_cast<char *>(_command[i].c_str());
    argc++;
  }
  //add NULL at the end of argv;
  argv = (char **)realloc(argv, (argc + 1) * sizeof(*argv));
  argv[argc] = NULL;
  argc++;
  //put env virables in envp
  for (map<string, string>::iterator it = shell.env.begin(); it != shell.env.end(); ++it) {
    string str(it->first);
    str.append(" = ");
    str.append(it->second);
    v1.push_back(str);
  }
  for (vector<string>::iterator it = v1.begin(); it != v1.end(); ++it) {
    envp = (char **)realloc(envp, (envpc + 1) * sizeof(*envp));
    envp[envpc] = const_cast<char *>(it->c_str());
    envpc++;
  }
  //add NULL at the end of envp
  envp = (char **)realloc(envp, (envpc + 1) * sizeof(*envp));
  envp[envpc] = NULL;
  envpc++;
  //create child process
  childpid = fork();
  if (childpid < 0) {
    cout << "Fork Error!" << endl;
    exit(EXIT_FAILURE);
  }
  if (childpid == 0) {
    execve(__path, argv, envp);
    //wouldn't be here unless execve fail, free argv and envp;
    //fprintf(stderr, "%s: no such file or directory\n", __path);
    perror("execve");
    free(argv);
    free(envp);
    int i = kill(getpid(), SIGKILL);
    if (i != 0) {
      cout << "kill: fail" << endl;
    }
  }
  else {
    do {
      //call waitpid and let parent process wait until child process finished. free argv and envp;
      id = waitpid(childpid, &status, 0);
      free(argv);
      free(envp);
      if (id == -1) {
        cout << "waitpid" << endl;
        exit(EXIT_FAILURE);
      }
      /*if (id == 0) {
        int i = kill(childpid, SIGKILL);
        if (i != 0) {
          cout << "kill: fail" << endl;
        }
	}*/
      if (WIFEXITED(status)) {
        cout << "Program exited with status " << WEXITSTATUS(status) << endl;
      }
      else if (WIFSIGNALED(status)) {
        cout << "Program was killed by signal " << WTERMSIG(status) << endl;
      }
      else if (WIFSTOPPED(status)) {
        cout << "stopped by signal " << WSTOPSIG(status) << endl;
      }
      else if (WIFCONTINUED(status)) {
        cout << "continued " << WIFCONTINUED(status) << endl;
      }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
}
//check executable program under syetem path
string Command::Check_Program(string & path, Shell & shell) {
  string final_path("nothing");
  vector<string> temp;
  //for (map<string, string>::iterator i = shell.env.begin(); i != shell.env.end(); ++i) {
  map<string, string>::iterator it = shell.env.find("ECE551PATH");
  if (it != shell.env.end()) {
    string str = it->second;
    size_t pos = str.find_first_of(":");
    while (pos != string::npos) {
      temp.push_back(str.substr(0, pos));
      str = str.substr(pos + 1);
      pos = str.find_first_of(":");
    }
    temp.push_back(str);
  }
  for (vector<string>::iterator i = temp.begin(); i != temp.end(); ++i) {
    if (ListDir(*i, path)) {
      *i += "/";
      *i += path;
      final_path = *i;
      return final_path;
    }
  }
  cout << path << ":command not found" << endl;
  return final_path;
}
//check if the command is strat from / or ./, otherwise go to find the program under system path
void Command::check_path(vector<string> & _command, Shell & shell) {
  Check_dollar(_command, shell);
  vector<string> new_command;
  if (_command.front()[0] == '/' || (_command.front()[0] == '.' && _command.front()[1] == '/')) {
    Execute(_command, shell);
  }
  else {
    string str = Check_Program(_command.front(), shell);
    if (str.compare("nothing") != 0) {
      new_command.push_back(str);
      for (size_t i = 1; i < _command.size(); ++i) {
        new_command.push_back(_command[i]);
      }
      Execute(new_command, shell);
    }
  }
}
//set varible, and varible name can only contain letter, number and '_'
void Command::Set_var(vector<string> & _command, Shell & shell) {
  if (_command.size() == 1 && _command[0] == "set") {
    for (map<string, string>::iterator it = shell.var.begin(); it != shell.var.end(); ++it) {
      cout << it->first << " = " << it->second << endl;
    }
  }
  else if (_command.size() != 3) {
    cout << "set: Invild set command, try set Varname Value" << endl;
  }
  else {
    size_t found = _command[1].find_first_not_of(
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_");
    if (found == string::npos) {
      shell.var[_command[1]] = _command[2];
    }
    else {
      cout << "set: Invaild var name" << endl;
    }
  }
}
//export varible from var to env
void Command::Export(vector<string> & _command, Shell & shell) {
  if (_command.size() == 1 && _command[0] == "export") {
    for (map<string, string>::iterator it = shell.env.begin(); it != shell.env.end(); ++it) {
      cout << it->first << " = " << it->second << endl;
    }
  }
  else if (_command.size() != 2) {
    cout << "export: Invild export command, try export Varname " << endl;
  }
  else {
    Check_dollar(_command, shell);
    map<string, string>::iterator it = shell.var.find(_command[1]);
    if (it == shell.var.end()) {
      cout << "export: no such varible " << endl;
    }
    else {
      shell.env[it->first] = it->second;
    }
  }
}
//inc command, set varible value to number
void Command::Inc(vector<string> & _command, Shell & shell) {
  if (_command.size() == 1 && _command[0] == "inc") {
    for (map<string, string>::iterator it = shell.var.begin(); it != shell.var.end(); ++it) {
      cout << it->first << " = " << it->second << endl;
    }
  }
  else if (_command.size() != 2) {
    cout << "inc: Invild inc command, try inc Varname" << endl;
  }
  else if (_command[1].find_first_not_of(
               "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_") != string::npos) {
    cout << "inc: Invild var name" << endl;
  }
  else {
    map<string, string>::iterator it = shell.var.find(_command[1]);
    size_t found = it->second.find_first_not_of("1234567890");
    if (it == shell.var.end() || (found != string::npos)) {
      shell.var[_command[1]] = "1";
    }
    else {
      unsigned long int i;
      istringstream(it->second) >> i;
      i++;
      stringstream ss;
      ss << i;
      string str = ss.str();
      shell.var[_command[1]] = str;
    }
  }
}
//check if the command contain $ sign and search for the content in var, if find it, exchange it to corrsponding value.
void Command::Check_dollar(vector<string> & _command, Shell & shell) {
  size_t found;
  for (size_t i = 0; i < _command.size(); ++i) {
    string str;
    found = _command[i].find_first_of('$', 0);
    //don't find $ in ith element of vector , don't need to change it.
    if (found == string::npos) {
      continue;
    }  //find $
    else if (found != string::npos && _command[i].size() == 1) {
      str = "$";
    }
    else {
      string temp;
      string str1 = _command[i].substr(0, found);
      str += str1;
      string sub_str = _command[i].substr(found);
      found = sub_str.find_first_of('$', 1);
      if (found == string::npos) {
        for (size_t i = sub_str.size() - 1; i > 0; --i) {
          temp = sub_str;
          map<string, string>::iterator it = shell.var.find(sub_str.substr(1, i));
          if (it != shell.var.end()) {
            temp = it->second;
            temp += sub_str.substr(1 + i, sub_str.size() - i - 1);
            break;
          }
        }
        str += temp;
      }
      else {
        while (found != string::npos) {
          str1 = sub_str.substr(0, found);
          temp = str1;
          for (size_t i = str1.size() - 1; i > 0; --i) {
            map<string, string>::iterator it = shell.var.find(str1.substr(1, i));
            if (it != shell.var.end()) {
              temp = it->second;
              temp += str1.substr(1 + i, str1.size() - i - 1);
              break;
            }
          }
          str += temp;
          sub_str = sub_str.substr(found);
          found = sub_str.find_first_of('$', 1);
        }
        temp = sub_str;
        for (size_t i = sub_str.size() - 1; i > 0; --i) {
          map<string, string>::iterator it = shell.var.find(sub_str.substr(1, i));
          if (it != shell.var.end()) {
            temp = it->second;
            temp += sub_str.substr(1 + i, sub_str.size() - i - 1);
            break;
          }
        }
        str += temp;
      }
    }
    _command[i] = str;
  }
}
