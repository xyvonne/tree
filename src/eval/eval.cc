#include <iostream> // error printing
#include <string>

#include "../../include/eval/eval_error.hh"
#include "../../include/eval/lexer.hh"
#include "../../include/eval/operator.hh"
#include "../../include/eval/parser.hh"
#include "../../include/eval/preprocessor.hh"

//TODO
#if 0
* Tester l evaluation des operateurs.
* Surcharger dans Operator l operateur >, en disant que o1 > o2 si :
  1) o2 est un vrai operateur (pas un nombre, ni (), ni STOP),
& 2) - ou bien priorite(o1) > priorite(o2),
     - ou bien priorite(o1)==priorite(o2) et binding(o1)==right.
#endif

int main(int argc, char** argv)
{
  try
  {
	  std::string default_expression = "123 \t  +  2 \n\r\t - 42";
    Preprocessor preprocessor(argc, argv, default_expression);
    std::string expression = preprocessor.expression();
    Parser parser(expression);
  }
  catch(const EvalException& e)
  {
    std::cerr << e.what() << std::endl;
    return e.code(); // quit the program with appropriate exit code
  }

  return EXIT_SUCCESS;
}

#if 0
Operator::Type type = Operator::NUMBER;
while(type != Operator::STOP)
{
  Operator token = lexer.next_token();
  std::cout << token;
  type = token.type();
}
std::cout << std::endl;
#endif
