#include <iostream> // error printing
#include <string>

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/lexer.hh"
#include "../../include/eval/operator.hh"
#include "../../include/eval/parser.hh"

int main(int argc, char** argv)
{
  try
  {
    if (argc != 2)
      throw EvalException::BadArgument();
    else
      std::cout << Parser(argv[1]).eval() << "\n";
  }
  catch(const EvalException::BaseException& e)
  {
    std::cerr << e.what() << std::endl;
    return e.code(); // quit the program with appropriate exit code
  }

  return 0;
}
