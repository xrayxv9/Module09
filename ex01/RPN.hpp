#pragma once

#include <exception>
#include <stack>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

class RPN 
{
	public :
		RPN();
		RPN( const std::string & );
		RPN( const RPN & );

		RPN &operator=( const RPN & );
		~RPN();

		std::stack<double> getStack() const;
		// void makeCalcul();
		void calcul( std::string );
		void makeCalcul();
		void printStack();

		class ExceptionNotEnoughNumbers : public std::exception
		{
			public:
				const char *what() const throw();
		};

		class ExceptionDivisionByZero : public std::exception
		{
			public:
				const char *what() const throw();
		};


		class ExceptionTooManyNumbers : public std::exception
		{
			public:
				const char *what() const throw();
		};

	private:
		std::stack< double > _queue;
		std::string _calcul;
};
