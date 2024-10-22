#include "string"
#include "lex_analis.h"
#include "struct_unique_value.h"
using namespace std;
lex_analis::lex_analis()
{

}

void lex_analis::add_new_unique_value(string& name_value)
{
	Hash buffer;//имя тип
	buffer = this->our_hash_table;
	DFA.vector_for_unique_value(name_value, buffer);
	this->our_hash_table = buffer;
}
Hash lex_analis::get_our_hash_table()
{
	return our_hash_table;
}