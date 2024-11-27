#include <iostream>
#include <vector>
#include "string"
#include"Hash.h"
#include "struct_unique_value.h"
using namespace std;
class DFA
{
protected:
	vector<char> Symbols_Operations{ '=', '+', '-' };
	vector<char> Symbols_Separating{ '(', ')', ',' };
	vector<char> Symbols_of_Separating{ '\n', '\t', ' ' };
	vector<string> Words_Key{ "PROGRAM", "INTEGER", "REAL", "CALL", "END" };
	vector<vector<int>> Transit_Table;
public:
	DFA();
	unique_value vector_for_unique_value(string& line);
	vector<string>get_vector_words_key();
	vector<vector<int>> get_Transit_Table();
	vector<char> get_Symbols_Operations();
	vector<char> get_Symbols_of_Separating();
	vector<char> get_Symbols_Separating();
};