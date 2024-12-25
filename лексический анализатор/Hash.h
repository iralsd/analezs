#pragma once
#include "List.h"
#include <iostream>
#include <string>
#include <vector>
#include "struct_unique_value.h"
using namespace std;

class Hash
{
private:

public:
	List hash_table[1000];
	Hash();
	void get_hash_table_index(string& actual_line, long long& index);
	void add_new_word_in_table(unique_value& our_value);
	List* get_hash_table();
	void put_new_atribute(string name_unique_value, string new_name_atribute);
	unique_value get_unique_value(unique_value uv);
};
