#pragma once

#include <deque>
#include <iostream>
#include <cstdlib>
#include <vector>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe( const PmergeMe &);
		~PmergeMe();
		PmergeMe &operator=( const PmergeMe & );

		std::vector<int> getVector() const;
		std::deque<int> getQueu() const;

		class ExceptionParsingError : public std::exception
		{
			const char *what() const throw();
		};

		void preParse( char ** );
		std::vector<int> sortVec( std::vector<int> );
		std::deque<int> sortDec( std::deque<int> );
		void sort( char ** );

	private:
		std::vector<int> _vec;
		std::deque<int> _deq;
};
