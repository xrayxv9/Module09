#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	(void)argc;
	PmergeMe pm = PmergeMe();

	pm.preParse(argv);
}
