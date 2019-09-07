#pragma once
#include <vector>
#include <string>

class Markov_chain
{
private:
	std::vector<std::vector<double>> probability_matrix;
public:
	Markov_chain(const std::string &str);
	~Markov_chain();

public:
    static std::vector<std::string> Split_string(const std::string &str); //const;
};

