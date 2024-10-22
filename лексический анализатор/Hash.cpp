#include "list.h"
#include "Hash.h"

Hash::Hash()
{
	this->hash_table;
}
void Hash::get_hash_table_index(string& actual_line, long long& index)
{
	int sizee = 1000;
	for (int i = 0; i < actual_line.size(); i++)
	{
		index = (index * 31 + actual_line[i]) % sizee;
	}
}
void Hash::add_new_word_in_table(unique_value& our_value)
{
	long long index = 0;
	get_hash_table_index(our_value.name, index);

	if (hash_table[index].value_actual_state.name == "None" && hash_table[index].value_actual_state.type == "None")
	{
		hash_table[index].value_actual_state = our_value;
	}
	else
	{
		List* buffer = new List;

		buffer->value_actual_state = hash_table[index].value_actual_state;

		buffer->nextNode = hash_table[index].nextNode;

		hash_table[index].value_actual_state = our_value;//новое значение становится текущим, прошлое паследником, добавляем к наследнику предка в качестве текущего 

		hash_table[index].nextNode = buffer;

		buffer->predNode = hash_table[index].predNode;
	}
}

List* Hash::get_hash_table()
{
	return hash_table;
}