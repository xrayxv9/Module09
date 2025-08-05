#include "PmergeMe.hpp"
#include <vector>

PmergeMe::PmergeMe(): _numbers("") {}
PmergeMe::PmergeMe( std::string &num): _numbers(num) {}
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
