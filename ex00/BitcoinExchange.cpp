#include "BitcoinExchange.hpp"
#include <fstream>
#include <string>
#include <ctime>

BitcoinExchange::BitcoinExchange(): _fileName("input.txt") {}
BitcoinExchange::BitcoinExchange( std::string input ): _fileName(input) {}
BitcoinExchange::BitcoinExchange( BitcoinExchange &other )
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=( BitcoinExchange &other )
{
	if (this != &other)
		this->_fileName = other.getFileName();
	return *this;
}

std::string BitcoinExchange::getFileName()
{
	return _fileName;
}

const char *BitcoinExchange::ExceptionFileNotOpened::what() const throw()
{
	return ("Couldn't open the file");
}

const char *BitcoinExchange::ExceptionIncorectDate::what() const throw()
{
	return ("Invalid Date received");
}

const char *BitcoinExchange::ExceptionNoPipeDetected::what() const throw()
{
	return ("No pipe was detected");
}

const char *BitcoinExchange::ExceptionInvalidNumberOfBitCoin::what() const throw()
{
	return ("The number of BitCoin is incorrect ");
}

std::fstream BitcoinExchange::openFile( std::string &fileName)
{
	std::fstream file;

	file.open(fileName, std::fstream::in);
	if (!file.is_open())
		throw ExceptionFileNotOpened();	

	return file;
}

void BitcoinExchange::readFile()
{
	std::string tmp;
	std::fstream file;

	int i = 0;
	try
	{
		file= openFile(_fileName);
	}
	catch (std::exception &e)
	{
		std::cout << RED << e.what() << RESET << std::endl;
		return ;
	}

	while (std::getline(file, tmp, '\0'))
	{
		if (tmp.empty())
		{
			file.close();
			return ;
		}
		exploit(tmp);
	}
}

void BitcoinExchange::removeSpace(std::string &file)
{
	for (std::string::iterator it = file.begin(); it != file.end(); it++)
	{
		if (*it == ' ')
			file.erase(it);
	}
}

void BitcoinExchange::lineExploit(std::string &date, bool pipe, std::string &number)
{
	std::string year;
	std::string month;
	std::string day;
	int yearN;
	int monthN;
	int dayN;
	int i = 0;

	for (; date[i] && date[i] != '-'; i++)
		year+= date[i];
	if (date[i] == '-')
		i++;
	else
		throw ExceptionIncorectDate();	

	for (; date[i] && date[i] != '-'; i++)
		month += date[i];
	if (date[i] == '-')
		i++;
	else
		throw ExceptionIncorectDate();	

	for (; date[i] && date[i] != '-'; i++)
		day += date[i];
	if (date[i])
		throw ExceptionIncorectDate();	

	yearN = std::atoi(year.c_str());
	dayN = std::atoi(day.c_str());
	monthN = std::atoi(day.c_str());
	std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int annee = now->tm_year + 1900;
	int months[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


	if (yearN > annee || yearN < 2008)
		throw  ExceptionIncorectDate();

	if (monthN > 12 || monthN <= 0)
		throw  ExceptionIncorectDate();

	if (dayN > months[monthN] || dayN < 0)
		throw  ExceptionIncorectDate();

	if (monthN == 2 && !(yearN % 4 == 0 && yearN % 100 != 0) || (yearN % 400 == 0))
		if (dayN == 29)
			throw  ExceptionIncorectDate();

	if (!pipe)
		throw ExceptionNoPipeDetected();

	if (number.find(".") == std::string::npos)
	{
		if (number.length() > 4)
			ExceptionInvalidNumberOfBitCoin();
		if (number.find("-") == std::string::npos)
			ExceptionInvalidNumberOfBitCoin();

	}
}

void BitcoinExchange::exploit( std::string &file )
{
	int i = 0;
	int x = 0;
	std::string date;
	bool pipe;
	std::string number;

	removeSpace(file);
	while (file[i])
	{
		pipe = false;
		for (; (file[x] && file[x] == '\n') && file[x] != '|'; x++)
			date += file[x];
		if (file[x] == '|')
			pipe = true;
		x++;
		for (; (file[x] && file[x] != '\n') && (file[x] >= '0' && file[x] <= '9'); x++)
		{
			number += file[x];
		}
		lineExploit(date, pipe, number);
		i = x;
	}
}


