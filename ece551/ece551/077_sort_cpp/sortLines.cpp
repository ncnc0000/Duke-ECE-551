#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
//#include <string.h>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
bool sort(string i, string j) {
  return (i < j);
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & v) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    s << *it << endl;
  }
  return s;
}

void read_cin(std::istream & s) {
  string word;
  vector<string> v1;
  while (getline(s, word)) {
    v1.push_back(word);
  }
  if (!s.eof() && !s) {
    std::cerr << "failed to read file" << std::endl;
    exit(EXIT_FAILURE);
  }
  sort(v1.begin(), v1.end());
  cout << v1 << endl;
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    read_cin(cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream s(argv[i]);
      if (!s) {
        cerr << "fail to open files!" << endl;
        return EXIT_FAILURE;
      }
      read_cin(s);
    }
  }
  return EXIT_SUCCESS;
}
