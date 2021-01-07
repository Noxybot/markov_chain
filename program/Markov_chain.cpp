#include "Markov_chain.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>

Markov_chain::Markov_chain(const std::string &str)
{
	auto splited_str = Split_string(str);
	int counter = 1; // 0 - START word
	
	for (const auto &str : splited_str) {
		if (uniq_words.find(str) == uniq_words.end())
			uniq_words.emplace(str, counter++);
	}
		

	probability_matrix.reserve(counter + 1); // two additional rows for START(0) and END word
	for (int i = 0; i < counter + 1; ++i){
		probability_matrix.emplace_back(counter + 1);
		std::fill(probability_matrix[i].begin(), probability_matrix[i].end(), 0.0);
	}
		
	for (auto word_p = splited_str.begin(); word_p != splited_str.end(); ++word_p) {
		std::string prev_word;
		if (word_p != splited_str.begin())
			prev_word = *std::prev(word_p);
		if (*word_p == "." || *word_p == "!" || *word_p == "?")
			*std::prev(probability_matrix[uniq_words[prev_word]].end()) += 1;
		else if (prev_word == "." || prev_word == "!" || prev_word == "?")
			(*probability_matrix.begin())[uniq_words[*word_p]] += 1;
		else if (!prev_word.empty())
			probability_matrix[uniq_words[prev_word]][uniq_words[*word_p]] += 1;
	
		prev_word.clear();
	}
	for (auto &row : probability_matrix) {
		double sum = std::accumulate(row.begin(), row.end(), 0.0);
		for (auto &elem : row)
			if (sum != 0.0)
				elem /= sum;
	}
	index_word_map.emplace(0, "START_WORD");
	for (const auto &elem : uniq_words)
		index_word_map.emplace(elem.second, elem.first);
	index_word_map.emplace(uniq_words.size() + 1, "END_WORD");

}

Markov_chain::~Markov_chain()
{
}
//TODO: Add proper splits cases for I`m, don`t , etc. shorcuts
std::vector<std::string> Markov_chain::Split_string(const std::string & str) //const
{
	std::vector<std::string> res;
	std::stringstream str_strm{ str };
	std::string word;
	while (str_strm >> word) {

		if (char last = word[word.size() - 1]; last == '!' || last == '?' || last == '.' || last == ',') {
			res.push_back(word.replace(word.find_first_of(last), word.size() - 1, ""));
			res.push_back(std::string(1, last));
		}
		else
			res.push_back(word);			
	}
	return res;
}

std::string Markov_chain::Generate_text(int words_count) const
{
	std::string res;
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);
	std::string word = Pick_random_word(probability_matrix[0], dis(gen)); // get a first word
	if (word.empty()) {
		std::cerr << "ERORR::TOO FEW WORDS TO BUILD MARKOV CHAIN\n";
		return std::string();
	}
		
	res += word;
	res += " ";
	while (words_count - 1) {
		std::string next_word = Pick_random_word(probability_matrix[uniq_words.at(word)], dis(gen));
		if (next_word == "END_WORD") {
			res.pop_back();
			res += ". "; // TODO: add difference end-symbols choices
			word =  Pick_random_word(probability_matrix[0], dis(gen));
			res += word;
			res += " ";
		}
		else {
			if (next_word == ",")
				res.pop_back();
			res += next_word;
			res += " ";
			word = next_word;
		}
		
		--words_count;
	}
	return res;
}

std::string Markov_chain::Pick_random_word(const std::vector<double>& vec, double random_num) const
{
	for (int i = 0; i < vec.size(); ++i) {
		if (random_num < vec[i])
			return   index_word_map.at(i);
		random_num -= vec[i];
	}
	return std::string();
}
