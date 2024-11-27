#pragma once
#include <vector>
#include"DFA.h"
#include"Hash.h"
#include "pos_error.h"
class lex_analis
{
private:
	DFA DFAA;
	vector<unique_value> our_unique_value;
public:
	Hash our_hash_table;
	lex_analis();
	unique_value add_new_unique_value(ifstream& in, Hash& our_hash_table);
	vector<unique_value> get_our_unique_value();
	Hash get_our_hash_table();
	Pos_Error Positoin;
	bool check_for_Symbols_Operations(char c);
	bool check_for_Symbols_Separating(char c);
	bool check_for_Symbols_of_Separators(char c);
	string get_word(ifstream& in);
	void back_word(ifstream& in, string word);
};