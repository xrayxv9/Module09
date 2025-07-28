#pragma once

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <map>
#include <ctime>

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
		BitcoinExchange( const std::string & );
		BitcoinExchange( const BitcoinExchange & );

		BitcoinExchange &operator=( const BitcoinExchange & );

		~BitcoinExchange();

		void showData();
		std::string getFileName() const;
		bool checkDate( const std::string & );


	private :
		void getData();
		void removeSpace( std::string & );
		std::string _fileName;
		std::map<std::string, double> _exchangeRate;
		bool _canBeUsed;
};
