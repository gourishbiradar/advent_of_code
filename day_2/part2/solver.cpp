#include "solver.h"
	
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

