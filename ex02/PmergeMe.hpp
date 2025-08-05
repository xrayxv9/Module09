#pragma once

#include <deque>
#include <iostream>
#include <vector>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe( std::string & );
		PmergeMe( const PmergeMe &);
		~PmergeMe();
		PmergeMe &operator=( const PmergeMe & );

		std::vector<int> getVector() const;
		std::deque<int> getQueu() const;

		void preParse();

	private:
		std::vector<int> _vec;
		std::deque<int> _deq;
		std::string _numbers;
};
