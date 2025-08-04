#include "RPN.hpp"
#include <exception>

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "I want one argument" << std::endl;
		return 1;
	}

	RPN a = RPN(static_cast<std::string>(argv[1]));
	try
	{
		a.makeCalcul();
		a.printStack();
	}
	catch ( std::exception &e )
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
}
