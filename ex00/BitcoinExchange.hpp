#pragma once

#include <iostream>
#include <map>

class BitcoinExchange
{
	public :
		BitcoinExchange();
		BitcoinExchange( std::string );
		BitcoinExchange( BitcoinExchange & );

		BitcoinExchange operator=( BitcoinExchange & );

		~BitcoinExchange();

		void readFile( std::string );

	private :
		std::map<std::string, unsigned int> _exchangeRate;
		std::map<std::string, unsigned int> _inputs;
};
