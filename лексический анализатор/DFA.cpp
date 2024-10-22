#include <vector>
#include <iostream>
#include <vector>
#include "DFA.h"
#include "Hash.h"
#include "struct_unique_value.h"
using namespace std;

DFA::DFA()//строим таблицу переходов
{

	vector<vector<int>> Transit_Tables(5, vector<int>(127, 4));
	this->Transit_Table = Transit_Tables;
	for (int i = 46; i <= 127; i++)
	{
		if (i >= 48 && i <= 57)
		{
			Transit_Table[0][i] = 1;
			Transit_Table[1][i] = 1;
			Transit_Table[3][i] = 4;
			Transit_Table[2][i] = 2;
		}
		if (i == 46)
		{
			Transit_Table[0][i] = 4;
			Transit_Table[1][i] = 2;
			Transit_Table[3][i] = 4;
			Transit_Table[2][i] = 4;
		}

		//находимся в нулевом состоянии если цифра переходим в 1 состояние буква в 3 состояние
		//если резко после буквы цифра то в 4 состояние тоесть в ошибку 
		//и на оборот
		if (i >= 65 && i <= 90)
		{
			Transit_Table[0][i] = 3;
			Transit_Table[2][i] = 4;
			Transit_Table[1][i] = 4;
			Transit_Table[3][i] = 3;
		}
		if (i >= 97 && i <= 122)
		{
			Transit_Table[0][i] = 3;
			Transit_Table[2][i] = 4;
			Transit_Table[1][i] = 4;
			Transit_Table[3][i] = 3;

		}

	}

}
void check_for_state(string& our_string, int& actual_state, Hash& Values)
{
	if (actual_state == 1)
	{
		unique_value value_new(our_string, "int_num");
		Values.add_new_word_in_table(value_new);
	}
	else if (actual_state == 2)
	{
		unique_value value_new(our_string, "real_num");
		Values.add_new_word_in_table(value_new);
	}
	else if (actual_state == 3)
	{
		bool flag = false;
		DFA buffer;
		for (int i = 0; i < buffer.get_vector_words_key().size(); i++)
		{
			if (our_string == buffer.get_vector_words_key()[i])
				flag = true;
		}
		if (flag)
		{
			unique_value value_new(our_string, "WordsKey");//отправлять сразу в хэш таблицу
			Values.add_new_word_in_table(value_new);
		}
		else
		{
			unique_value value_new(our_string, "Id");
			Values.add_new_word_in_table(value_new);
		}
	}
	else if (actual_state == 4)
	{
		unique_value value_new(our_string, "Error");
		Values.add_new_word_in_table(value_new);
	}
}
bool check_for_separting_symbols(char our_symbol, Hash& Values)
{
	DFA buffer;
	for (int i = 0; i < buffer.get_Symbols_Separating().size(); i++)
	{
		if (our_symbol == buffer.get_Symbols_Separating()[i])
		{
			string name = "";
			name += our_symbol;
			unique_value new_value(name, "Symbols_of_Separating");
			Values.add_new_word_in_table(new_value);
			return true;
		}
	}
	return false;
}
bool check_for_oper_symbols(char our_symbol, Hash& Values)
{
	DFA buffer;
	for (int i = 0; i < buffer.get_Symbols_Operations().size(); i++)
	{
		if (our_symbol == buffer.get_Symbols_Operations()[i])
		{
			string name = "";
			name += our_symbol;
			unique_value new_value(name, "Symbols_of_Operation");
			Values.add_new_word_in_table(new_value);
			return true;
		}
	}
	return false;
}

vector<string> DFA::get_vector_words_key()
{
	return Words_Key;
}
vector<vector<int>> DFA::get_Transit_Table()
{
	return Transit_Table;
}

vector<char> DFA::get_Symbols_Operations()
{
	return Symbols_Operations;
}

vector<char> DFA::get_Symbols_Separating()
{
	return Symbols_Separating;
}

void DFA::vector_for_unique_value(string& line, Hash& Values)
{
	int actual_state = 0;
	string our_string = "";
	for (int i = 0; i < line.size(); i++)
	{
		if (check_for_oper_symbols(line[i], Values))
		{
			actual_state = 0;
			our_string.clear();
			our_string.shrink_to_fit();
		}
		else if (check_for_separting_symbols(line[i], Values))
		{
			actual_state = 0;
			our_string.clear();
			our_string.shrink_to_fit();
		}
		else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		{
			check_for_state(our_string, actual_state, Values);
			actual_state = 0;
			our_string.clear();
			our_string.shrink_to_fit();
		}
		else
		{
			our_string += line[i];
			if (line[i] >= 48 && line[i] <= 57)
			{
				actual_state = Transit_Table[actual_state][line[i]];
			}
			else if (line[i] >= 65 && line[i] <= 90)
			{
				actual_state = Transit_Table[actual_state][line[i]];
			}
			else if (line[i] >= 97 && line[i] <= 122)
			{
				actual_state = Transit_Table[actual_state][line[i]];
			}
			else if (line[i] == 46)
			{
				actual_state = Transit_Table[actual_state][line[i]];
			}
			else
			{
				actual_state = 4;
			}

		}
	}
	check_for_state(our_string, actual_state, Values);
}