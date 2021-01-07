#include <iostream>
#include <fstream>
#include <streambuf>
#include "Markov_chain.h"
int main(int argc, char **argv)
{
	if (argc != 3)
		std::cerr << "ERROR:: Usage: ./program <input_file> <output_file>";
	std::ifstream fin{ argv[1] };
	//if (fin.is_open())
	//	std::cout << "OPEN";
	std::string str((std::istreambuf_iterator<char>(fin)),
		std::istreambuf_iterator<char>());
	fin.close();
	Markov_chain m_chain { str };
	std::ofstream fout{ argv[2] };
	fout << m_chain.Generate_text(500);
	return 0;
}