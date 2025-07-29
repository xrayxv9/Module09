#include "BitcoinExchange.hpp"

int main( int argc, char **argv )
{
	if (argc != 2)
	{
		std::cerr << "Error : could not oppen the file" << std::endl;
		return 1;
	}
	std::string fileName(argv[1]);
	BitcoinExchange bc = BitcoinExchange(fileName);
	bc.exploitFile();
}
