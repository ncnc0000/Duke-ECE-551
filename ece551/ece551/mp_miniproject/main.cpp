#include <iostream>

#include "command.h"
#include "shell_operating.h"
using namespace std;
const int END = -100;
//clear extra spaces of user input

void print_dragon() {
  cout << "                                 ^    ^"
       << "\n                                / \\  //\\ "
       << "\n                 |\\___/|      /   \\//  .\\"
       << "\n                 /O  O  \\__  /    //  | \\ \\"
       << "\n                /     /  \\/_/    //   |  \\  \\"
       << "\n                @___@'    \\/_   //    |   \\   \\"
       << "\n                  |       \\/_ //     |    \\    \\"
       << "\n                  |        \\///      |     \\     \\"
       << "\n"
       << "\n                 _|_ /   )  //       |      \\     _\\"
       << "\n                '/,_ _ _/  ( ; -.    |    _ _\\.-~        .-~~~^-."
       << "\n                ,-{        _      `-.|.-~-.           .~         `."
       << "\n                 '/\\      /                 ~-. _ .-~      .-~^-.  \\"
       << "\n                    `.   {            }                   /      \\  \\"
       << "\n                  .----~-.\\        \\-'                 .~         \\  `. \\^-."
       << "\n                 ///.----..>    c   \\             _ -~             `.  ^-`   ^-_"
       << "\n                   ///-._ _ _ _ _ _ _}^ - - - - ~                     ~--,   .-~"
       << "\n                                                                         /.-'"
       << "\nSad hacking...                         Quote:(Dragon from https://www.asciiart.eu)"
       << endl;
}

string ClearSpace(string in) {
  int t = 0;
  for (unsigned int i = 0; i < in.size(); i++) {
    if (in[i] == '\\') {
      i += 2;
    }
    if (in[i] == ' ') {
      int j = i + 1, number = 0;
      while (in[j] == ' ') {
        j++;
        number++;
      }
      in.erase(i + 1, number);
      t++;
    }
    if (t == 1) {
      if (in[0] == ' ') {
        in.erase(0, 1);
        t--;
      }
      else {
        if (in.size() >= 4) {
          string u = in.substr(0, 4);
          if (u == "ins ") {
            break;
          }
        }
        else if (in.size() >= 7) {
          string u = in.substr(0, 7);
          if (u == "export ") {
            break;
          }
        }
      }
    }
    if (t == 2 && in.size() >= 4) {
      string u = in.substr(0, 4);
      if (u == "set ")
        break;
    }
  }
  return in;
}

int main() {
  Shell a;
  string in;
  print_dragon();
  //shell loop, only break when user type "exit" or didn't set eofbit/failbit/badbit
  while (1) {
    vector<string> t;
    //shell function--ReadInput(), get user input.
    in = a.ReadInput();
    //if user tpye "enter" or only spaces, back to ReadInput
    size_t found = in.find_first_not_of(" ", 0);
    if (found == string::npos || in == "") {
      continue;
    }
    //handle extra spaces in user input
    in = ClearSpace(in);
    //parse input
    t = ArgvTransform(in);
    //Call constuctor based on the parsed command
    Command com(t, a);
    if (com.RunCommand(a) == END) {
      //only break while loop when user parsed command equal to "exit"
      break;
    }
  }
  return 0;
}
