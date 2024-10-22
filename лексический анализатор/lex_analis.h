#pragma once
#include <vector>
#include"DFA.h"
#include"Hash.h"
class lex_analis
{
private:
	DFA DFA;
public:
	Hash our_hash_table;
	lex_analis();
	void add_new_unique_value(string& name_value);
	Hash get_our_hash_table();
};