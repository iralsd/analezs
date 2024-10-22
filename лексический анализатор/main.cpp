#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "lex_analis.h"
#include "Hash.h"
using namespace std;

void input_text(string& text,lex_analis& lex_a)
{
	ifstream in("input.txt");
	while (getline(in, text))
	{
		lex_a.add_new_unique_value(text);
	}
	in.close();
}

void right_output(lex_analis& lex_a)
{
	ofstream out("output.txt");
	for (int i = 0; i < 1000; i++)
	{
		List* actual_list = &lex_a.our_hash_table.hash_table[i];
		if (actual_list->value_actual_state.name != "None" && actual_list->value_actual_state.type != "None")
		{
			if (actual_list->nextNode == NULL)
			{
				out << actual_list->value_actual_state.type;
				for (int j = 0; j < 23 - actual_list->value_actual_state.type.size(); j++)
				{
					out << " ";
				}
				out << "{'" << actual_list->value_actual_state.name << "'}";
				for (int j = 0; j < 36 - actual_list->value_actual_state.name.size(); j++)
				{
					out << " ";
				}
			}
			else
			{
				out << actual_list->value_actual_state.type;
				for (int j = 0; j < 23 - actual_list->value_actual_state.type.size();j++)
				{
					out << " ";
				}
				out	<< "{'" << actual_list->value_actual_state.name << "'}";
				for (int j = 0; j < 36 - actual_list->value_actual_state.name.size(); j++)
				{
					out << " ";
				}
			}
			out << "|  Hash Index = " << i << '\n';
		}
	}
}


int main()
{
	string text = "";

	lex_analis lex_a;

	input_text(text, lex_a);

	right_output(lex_a);
}