#include "Markov_chain.h"
#include <map>
#include <sstream>

Markov_chain::Markov_chain(const std::string &str)
{
	std::map<std::string, int> word_freq;
	
	auto splited_str = Split_string(str);
	int count_words = 0;
	
	probability_matrix.reserve(count_words + 2); // two additional rows for START and END word
 	for (auto &row : probability_matrix)
		row.reserve(count_words);

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

		if (char last = word[word.size() - 1]; last == '!' || last == '?' || last == '.') {
			res.push_back(word.replace(word.find_first_of(last), word.size() - 1, ""));
			res.push_back(std::string(1, last));
		}
		else
			res.push_back(word);			
	}
	return res;
}
