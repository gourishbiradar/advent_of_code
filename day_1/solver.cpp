#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char** argv)
{
	if(argc < 2 )
	{
		std::cout << "Usage solver <inputfile.txt> \n" ;
		return -1;
	}
	std::string inputfile(argv[1]);
	std::cout << "File to read: " << inputfile << "\n" ;
	unsigned int answer = 0;
	unsigned int readval = 0;
	std::ifstream infile(inputfile.c_str());
	if(!infile)
	{
		std::cout << "Failed to load the file : " << inputfile << "\n" ;
		return -2;
	}
	while(infile >> readval)
	{
		answer += (readval/3) - 2;
	}
	std::cout << "The answer is " << answer << "\n" ;
	infile.close();
	return 0;
}
