#pragma once

#include <deque>
#include <iostream>
#include <cstdlib>
#include <vector>

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

		void doubles();
		void preParse( char **av );

	private:
		std::vector<int> _vec;
		std::deque<int> _deq;
};
