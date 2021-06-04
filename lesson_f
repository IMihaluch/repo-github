#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

void less6::exec() {
  createFile(std::string("Enter name_1: "), &createFirstFile);
  createFile(std::string("Enter name_2: "), &createSecondFile);
  
void less6::createFile(const std::string& promtMessage,less6::CreateFileFunction fcn) {
  std::string file_name;

  std::cout << promtMessage << std::ends;
  std::cin >> file_name;
  if (fcn(file_name)) {
    std::cout << "true" << std::endl;
  } else {
    std::cerr << "false" << std::endl;
  }
}


bool less6::createFirstFile(const std::string& fileName) {
  std::ofstream writer(fileName);
  if (writer.is_open() == false) return false;

  static const int FILE_LINES = 50;
  for (int it(0); it < FILE_LINES; ++it) {
    writer << "First file, line " << it << " ";
  }
  writer.close();
  return true;
}


bool less6::createSecondFile(const std::string& fileName) {
  std::ofstream writer(fileName);
  if (writer.is_open() == false) return false;

  static const int FILE_LINES = 100;
  for (int it(0); it < FILE_LINES; ++it) {
    writer << "Second file, line " << it << std::endl;
  }
  writer.close();
  return true;
}
