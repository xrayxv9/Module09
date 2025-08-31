#include "PmergeMe.hpp"
#include <cstddef>
#include <ctime>

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
		this->_vec.push_back(std::atoi(av[i]));
		this->_deq.push_back(std::atoi(av[i]));
		i++;
	}
}

std::vector<int>    PmergeMe::sortVec(std::vector<int> mainParam)
{
    size_t    n = mainParam.size();

    if (n <= 1)
        return mainParam;
    std::vector<int>    main, pend;
    for (size_t i = 0; i + 1 < n; i += 2) {
        if (mainParam[i] > mainParam[i + 1]) {
            main.push_back(mainParam[i]);
            pend.push_back(mainParam[i + 1]);
        }
        else {
            main.push_back(mainParam[i + 1]);
            pend.push_back(mainParam[i]);
        }
    }
    main = this->sortVec(main);
    for (std::vector<int>::iterator it = pend.begin(); it != pend.end(); it++) {
        std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), *it);
        main.insert(pos, *it);
    }
    if (n % 2) {
        std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), mainParam[n - 1]);
        main.insert(pos, mainParam[n - 1]);
    }
    return main;
}

std::deque<int>    PmergeMe::sortDec(std::deque<int> mainParam)
{
    size_t    n = mainParam.size();

    if (n <= 1)
        return mainParam;
    std::deque<int>    main, pend;
    for (size_t i = 0; i + 1 < n; i += 2) {
        if (mainParam[i] > mainParam[i + 1]) {
            main.push_back(mainParam[i]);
            pend.push_back(mainParam[i + 1]);
        }
        else {
            main.push_back(mainParam[i + 1]);
            pend.push_back(mainParam[i]);
        }
    }
    main = this->sortDec(main);
    for (std::deque<int>::iterator it = pend.begin(); it != pend.end(); it++) {
        std::deque<int>::iterator pos = std::lower_bound(main.begin(), main.end(), *it);
        main.insert(pos, *it);
    }
    if (n % 2) {
        std::deque<int>::iterator pos = std::lower_bound(main.begin(), main.end(), mainParam[n - 1]);
        main.insert(pos, mainParam[n - 1]);
    }
    return main;
}

void PmergeMe::sort( char **av )
{
	this->preParse(av);

	std::clock_t start = std::clock();
	this->_vec = this->sortVec(this->_vec);
	std::clock_t end = std::clock();
	double time = end - start;
	std::cout << BLUE << "Vector : " << time <<  "us" << std::endl;

	start = std::clock();
	this->_deq = this->sortDec(this->_deq);
	end = std::clock();
	time = end - start;
	std::cout << BLUE << "Deque : " << time <<  "us" << std::endl;
}
