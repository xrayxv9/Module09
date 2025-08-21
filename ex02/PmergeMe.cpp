#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe( const PmergeMe &cpy )
{
	*this = cpy;
}

PmergeMe &PmergeMe::operator=( const PmergeMe &cpy )
{
	if (this != &cpy)
	{
		this->_deq = cpy.getQueu();
		this->_vec = cpy.getVector();
	}
	return *this;
}

std::vector<int> PmergeMe::getVector() const
{
	return _vec;
}

std::deque<int> PmergeMe::getQueu() const
{
	return _deq;
}

PmergeMe::~PmergeMe() {}

const char *PmergeMe::ExceptionParsingError::what() const throw()
{
	return "Error while parsing the numbers given";
}

void PmergeMe::preParse( char **av )
{
	int i = 1;
	int j;

	while(av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				throw ExceptionParsingError();
			j++;
		}
		i++;
	}
	i = 1;
	while (av[i])
	{
		_vec.push_back(std::atoi(av[i]));
		i++;
	}
	doubles();
}


void PmergeMe::doubles()
{
	int size = _vec.size();

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (_vec[i] == _vec[j])
				throw ExceptionParsingError();
		}
	}
}
