#include "RPN.hpp"
#include <cstdlib>
#include <string>

RPN::RPN(): _calcul("") {}
RPN::~RPN() {}
RPN::RPN( const std::string &calcul ): _calcul(calcul){}

RPN::RPN( const RPN &other )
{
	*this = other;
}

RPN &RPN::operator=( const RPN &other )
{
	if (this != &other)
		this->_queue = other.getStack();
	return *this;
}

std::stack<int> RPN::getStack() const
{
	return _queue;
}

bool isValid( std::string value )
{
	if (value.length() > 1)
		return false;
	else if (value[0] >= '0' && value[0] <= '9')
		return true;
	if (value[0] != '+' && value[0] != '/' && value[0] != '-' && value[0] != '*')
		return false;
	else
		return true;
	return false;
}

void RPN::makeCalcul()
{
	std::stringstream stream(_calcul);
	std::string tmp;

	while (stream >> tmp)
	{
		if (!isValid(tmp))
		{
			std::cerr << RED << "ERROR : the character entered as input is invalid" << RESET << std::endl;
			return ;
		}
		if (tmp[0] == '+' || tmp[0] == '-' || tmp[0] == '/' || tmp[0] == '*')
			calcul(tmp);
		else
			_queue.push(std::atoi(tmp.c_str()));
	}
	if (_queue.size() > 1)
		throw ExceptionTooManyNumbers();
}

void RPN::printStack()
{
	while (!_queue.empty())
	{
		std::cout << _queue.top() << std::endl;
		_queue.pop();
	}
}

const char *RPN::ExceptionNotEnoughNumbers::what() const throw()
{
	return "You do not have enough number to make a calcul";
}

const char *RPN::ExceptionTooManyNumbers::what() const throw()
{
	return "you have a remaining number in your stack";
}

void RPN::calcul( std::string symbole )
{
	int nu;
	int num;
	int result;

	if (_queue.size() < 2)
		throw ExceptionNotEnoughNumbers();
	nu = _queue.top();
	_queue.pop();
	num = _queue.top();
	_queue.pop();
	switch (symbole.c_str()[0])
	{
		case '+':
			result = num + nu;
			break;
		case '-':
			result = num - nu;
			break;
		case '*':
			result = num * nu;
			break ;
		case '/':
			result = num / nu;
	}
	_queue.push(result);
}
