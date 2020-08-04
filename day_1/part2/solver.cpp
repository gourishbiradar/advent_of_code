#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

void find_fuel(std::vector<unsigned int> masses, unsigned int& answer)
{
	if(masses.size()==0)
	{
		std::cout << "No more masses to find fuel for...\n" ;
		return ;
	}
	std::vector<unsigned int> next_masses;
	for(auto& mass : masses)
	{
		int fuel_required = std::floor(mass/3) - 2;
		if(fuel_required>0)
		{
			answer += fuel_required;
			next_masses.push_back(fuel_required);
		}
	}
	find_fuel(next_masses,answer);
}
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
	std::vector<unsigned int> masses;
	std::ifstream infile(inputfile.c_str());
	if(!infile)
	{
		std::cout << "Failed to load the file : " << inputfile << "\n" ;
		return -2;
	}
	while(infile >> readval)
	{
		masses.push_back(readval);
	}
	find_fuel(masses,answer);
	std::cout << "The answer is " << answer << "\n" ;
	infile.close();
	return 0;
}
