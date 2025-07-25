#pragma once

#include <fstream>
#include <iostream>
#include <map>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


class BitcoinExchange
{
	public :
		BitcoinExchange();
		BitcoinExchange( std::string );
		BitcoinExchange( BitcoinExchange & );

		BitcoinExchange &operator=( BitcoinExchange & );

		~BitcoinExchange();

		std::string getFileName();

		void readFile();
		void exploit( std::string & );
		void removeSpace( std::string & );
		void lineExploit( std::string &, bool, std::string &);

		class ExceptionFileNotOpened : public std::exception
		{
			public :
				const char *what() const throw();
		};

		class ExceptionNoPipeDetected : public std::exception
		{
			public :
				const char *what() const throw();
		};

		class ExceptionIncorectDate: public std::exception
		{
			public :
				const char *what() const throw();
		};

		class ExceptionInvalidNumberOfBitCoin: public std::exception
		{
			public :
				const char *what() const throw();
		};

	private :
		bool checkDate( std::string & );
		std::fstream openFile( std::string & );
		std::string _fileName;
		std::map<std::string, unsigned int> _exchangeRate;
		std::map<std::string, unsigned int> _inputs;
};
