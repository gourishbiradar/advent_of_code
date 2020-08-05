#include "solver.h"
#define MAGIC_SOLUTION 19690720
template<class T>
bool fuzzer(std::vector<T> program, unsigned int &noun, unsigned int &verb)
{
	for(int i=0;i<=99;i++)
	{
		for(int j=0;j<=99;j++)
		{
			std::vector<T> temporary_prg(program.begin(),program.end());
			temporary_prg[1] = i;
			temporary_prg[2] = j;
			if(emulate_program(temporary_prg) && temporary_prg[0] == MAGIC_SOLUTION)
			{
				noun = i;
				verb = j;
				return true;
			}
		}
	}
	return false;
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
	std::vector<int> program;
	std::ifstream infile(inputfile.c_str());
	if(!infile)
	{
		std::cout << "Failed to load the file : " << inputfile << "\n" ;
		return -2;
	}
	int opcode;
	std::stringstream line;
	line << infile.rdbuf();
	infile.close();
	std::string opcode_string;
	while(std::getline(line,opcode_string,','))
	{
		std::stringstream data(opcode_string);
		data >> opcode;
		program.push_back(opcode);
	}
	unsigned int noun = 0;
	unsigned int verb = 0;
	if(fuzzer(program,noun,verb))
	{
		std::cout << "Noun: " << noun << " Verb: " << verb << "\n";
		std::cout << "The answer is " << 100*noun+verb << " \n" ;
	}
	else
	{
		std::cout << "The answer cannot be found for given program \n";
	}
	return 0;
}
