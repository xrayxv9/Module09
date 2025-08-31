#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe pm = PmergeMe();

	if (argc <= 2)
	{
		std::cout << "nothing to sort" << std::endl;
		return 1;
	}
	try
	{
		pm.preParse(argv);
	}
	catch( std::exception &e )
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	pm.sort(argv);
}
