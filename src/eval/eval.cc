#include <iostream> // error printing
#include <string>

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/lexer.hh"
#include "../../include/eval/operator.hh"
#include "../../include/eval/parser.hh"
#include "../../include/eval/preprocessor.hh"

int main(int argc, char** argv)
{
  try
  {
    std::string expression = Preprocessor(argc, argv).expression();
    Parser parser(expression); // implicitly declares a lexer
    std::cout << parser.eval() << "\n";
  }
  catch(const EvalException::BaseException& e)
  {
    std::cerr << e.what() << std::endl;
    return e.code(); // quit the program with appropriate exit code
  }

  return 0;
}
