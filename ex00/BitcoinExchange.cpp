#include "BitcoinExchange.hpp"
#include <fstream>
#include <string>

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

lineExploit BitcoinExchange::lineExploit()

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


