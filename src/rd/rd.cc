#include <iostream>
#include <system_error> // std::error_condition

#include "../../include/rd/reader.hh"

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Usage: ./rd <path>" << std::endl;
    return 2;
  }

  const String path = (argc == 1) ? "." : argv[1];
  try
  {
    std::cout << DirectoryReader(path).read_directory();
  }
  catch(const std::error_condition& econd)
  {
    std::cerr << path + " [error opening dir]\n\n0 directories" << std::endl;
    return 1;
  }

  return 0;
}
