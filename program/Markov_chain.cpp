#include "Markov_chain.h"
#include <map>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <iterator>
#include <numeric>

Markov_chain::Markov_chain(const std::string &str)
{
	std::map<std::string, int> word_freq;
	
	auto splited_str = Split_string(str);
	int counter = 1; // 0 - START word
	std::unordered_map<std::string, int> uniq_words;
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
}

Markov_chain::~Markov_chain()
{
}

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
