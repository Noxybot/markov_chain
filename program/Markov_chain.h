#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class Markov_chain
{
private:
	std::vector<std::vector<double>> probability_matrix;
	std::unordered_map<std::string, int> uniq_words;
	std::unordered_map<int, std::string> index_word_map;
public:
	Markov_chain(const std::string &str);
	~Markov_chain();

public:
    static std::vector<std::string> Split_string(const std::string &str); //const;
	std::string Generate_text(int words_count) const;
private:
	std::string Pick_random_word(const std::vector<double> &vec, double random_num) const;
};

