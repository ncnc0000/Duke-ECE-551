#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>

int main(void) {
  std::hash<std::string> h1;
  size_t a = h1("a");
  size_t b = h1("b");
  std::cout << a << "," << b << std::endl;
}
