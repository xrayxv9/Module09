#include "BitcoinExchange.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>

BitcoinExchange::BitcoinExchange(): _fileName("input.txt") 
{
	getData();
}
BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange::BitcoinExchange( const std::string &input ): _fileName(input) 
{
	getData();
}

void BitcoinExchange::removeSpace(std::string &file)
{
	file.erase(std::remove(file.begin(), file.end(), ' '), file.end());
}

bool BitcoinExchange::checkDate( std::string &date )
{
	size_t pos = 0;
	size_t pos2;
	std::string tmp;
	bool bis = false;
	int month = false;

	removeSpace(date);
	pos = date.find("-");
	tmp = date.substr(0, pos);
	if (!(tmp.length() == 4 && tmp < "2025" && tmp > "2008"))
	{
		std::cerr << RED << "Incorrect year" << RESET << std::endl;
		return false;
	}

	int annee = std::atoi(tmp.c_str());
	bis = (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
	pos2 = date.find("-", pos + 1);
	tmp = date.substr(pos + 1, pos2 - (pos + 1));
	int mo = std::atoi(tmp.c_str());
	if (tmp.length() != 2 && (mo >= 12 || mo <= 1))
	{
		std::cerr << RED << "Incorrect months" << RESET << std::endl;
		return false;
	}

	month = std::atoi(tmp.c_str());
	pos = date.find("-", pos2 + 1);
	tmp = date.substr(pos2 + 1, pos);
	int day = std::atoi(tmp.c_str());
	int monthsDate[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (!(tmp.length() == 2 && day <= monthsDate[month] && day > 0))
	{
		if (month == 2 && bis && day == 29)
			return true;
		std::cerr << RED << "Incorrect day" << RESET << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::getData()
{
	std::fstream file;
	std::string line;
	std::string date;
	std::string value;
	size_t pos;
	double val;
	_canBeUsed = true;


	file.open("data.csv");
	if (!file.is_open())
	{
		std::cerr << RED << "The data file couldn't be opened" << RESET << std::endl;
		_canBeUsed = false;
		return ;
	}
	while (std::getline(file, line))
	{
		if (line.empty())
			return ;
		removeSpace(line);
		pos = line.find(",");
		if (pos == std::string::npos)
		{
			std::cerr << RED << "No comma detected" << RESET << std::endl;
			_canBeUsed = false;
			return ;
		}
		date = line.substr(0, pos);
		if (date == "date")
			continue;
		if (!checkDate(date))
		{
			std::cerr << RED << "Invalid date in the data file" << RESET << std::endl;
			_canBeUsed = false;
			return ;
		}
		value = line.substr(pos + 1, line.length());
		char *endptr = NULL;
		val = std::strtod(value.c_str(), &endptr);
		if (endptr == value.c_str())
		{
			_canBeUsed = false;
			std::cerr << RED << "Invalid bitcoin value" << RESET << std::endl;
			return ;
		}
		_exchangeRate[date] = val;
	}
}

void BitcoinExchange::exploitFile()
{
	std::fstream file;
	std::string line;
	std::string date;
	std::string number;
	double num;
	size_t pos;

	if (!_canBeUsed)
	{
		std::cerr << RED << "The data file was determined has invalid, therefore you cannot open it" << RESET << std::endl;
		return ;
	}
	file.open(_fileName.c_str());
	if (!file.is_open())
	{
		std::cerr << RED << "The file couldn't be opened" << RESET << std::endl;
		return ;
	}
	while (getline(file, line))
	{
		if (line.empty())
			return ;
		removeSpace(line);
		pos = line.find('|');
		if (pos == std::string::npos)
		{
			std::cerr << RED << "bad input, missing the pipe => " << line << RESET << std::endl;
			continue ;
		}
		date = line.substr(0, pos);
		if (date == "date")
			continue ;
		if (!checkDate(date))
			continue ;
		number = line.substr(pos + 1, line.length());
		if (number == "")
		{
			std::cerr << RED << "No bitcoin amount found => " << line << RESET << std::endl;
			continue ;
		}
		char *endptr = NULL;
		num = std::strtod(number.c_str(), &endptr);
		if (endptr == number.c_str() || num < 0 || num > 1000)
		{
			std::cerr << RED << "Invalid bitcoin amount => " << number << RESET << std::endl;
			continue ;
		}
		std::map<std::string, double>::iterator it = _exchangeRate.lower_bound(date);
		if (it == _exchangeRate.end() && _exchangeRate.size() != 0)
			it--;
		std::cout << date << " => " << num << " = " << num * it->second << std::endl;
	}
}

