#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

template<class T>
void printProgram(std::vector<T> program)
{
	int i = 0;
	for(auto& opcode : program)
	{
		if(i%4==0)
			std::cout << "\n";
		std::cout << opcode << " " ;
		i++;
	}
}
bool emulate_program(std::vector<int> &program)
{
	unsigned int position = 0;
	unsigned int program_len = program.size();
	for(;position<program_len;)
	{
		int opcode = program[position];
		switch(opcode)
		{
			case 1:
				{
					if(position+3>program_len)
					{
						std::cout << "Invalid length of program passed...Index error\n";
						return false;
					}
					unsigned int val1 = program[position+1];
					unsigned int val2 = program[position+2];
					unsigned int result_position = program[position+3];
					if(val1 > program_len || val2 > program_len)
					{
						std::cout << "Invalid position opcodes " << val1 << " " << val2 << "\n";
						return false;
					}
					program[result_position] = program[val1] + program[val2] ;
					position = position+4;
					break;
				}
			case 2: 
				{
					if(position+3>program_len)
					{
						std::cout << "Invalid length of program passed...Index error\n";
						return false;
					}
					unsigned int val1 = program[position+1];
					unsigned int val2 = program[position+2];
					unsigned int result_position = program[position+3];
					if(val1 > program_len || val2 > program_len)
					{
						std::cout << "Invalid position opcodes " << val1 << " " << val2 << "\n";
						return false;
					}
					program[result_position] = program[val1] * program[val2] ;
					position = position+4;
					break;
				}
			case 99:
				return true;
			default :
				std::cout << "Invalid opcode " << opcode << " passed in program.. failing..\n";
				return false;
		}
	}
	return true;
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
	std::string opcode_string;
	while(std::getline(line,opcode_string,','))
	{
		std::stringstream data(opcode_string);
		data >> opcode;
		program.push_back(opcode);
	}
	if(program.size()>1)
	{
		program[1] = 12;
		if(program.size()>2)
		{
			program[2] = 2;
		}
		else
		{
			std::cout << "Program does not have more than 2 opcodes. Failing...\n";
			infile.close();
			return -2;
		}
	}
	else
	{
		std::cout << "The program does not have more than 1 opcode. Fialing...\n";
		infile.close();
		return -2;
	}
	if(emulate_program(program))
	{
		std::cout << "The answer is " << program[0] << "\n" ;
	}else
	{
		std::cout << "The emulator failed to emulate the input program\n";
	}
	infile.close();
	return 0;
}
