#include "string"
#include "lex_analis.h"
#include "struct_unique_value.h"
#include <fstream>
using namespace std;
lex_analis::lex_analis()
{

}

bool lex_analis::check_for_Symbols_Operations(char c)
{
    DFA buffer;
    for (char tmp_c : buffer.get_Symbols_Operations())
    {
        if (tmp_c == c)
        {
            return 1;
        }
    }

    return 0;
}
//(,)
bool lex_analis::check_for_Symbols_Separating(char c)
{
    DFA buffer;
    for (char tmp_c : buffer.get_Symbols_Separating())
    {
        if (tmp_c == c)
        {
            return 1;
        }
    }

    return 0;
}
//'\t''\n'
bool lex_analis::check_for_Symbols_of_Separators(char c)
{
    DFA buffer;
    for (char tmp_c :buffer.get_Symbols_of_Separating())
    {
        if (tmp_c == c)
        {
            return 1;
        }
    }

    return 0;
}

string lex_analis::get_word(ifstream& in)
{
    string buffer = "";
    while (true)
    {
        char symb = in.get();//читает из потока символ
        if (symb < 0 && !buffer.empty())
        {
            return buffer;
        }
        if (symb < 0 && buffer.empty())
        {
            return "";
        }
        if (in.eof())//возврачает False пока не достигнут конец файла
        {
            break;
        }
        Positoin.Check_Position(symb);
        if (check_for_Symbols_of_Separators(symb))
        {
            if (!buffer.empty())
            {
                Positoin.position--;
                in.unget();//помещает символ обратно в поток и удаляет индикатор конца файла 
                return buffer;
            }
            else
            {
                continue;
            }
        }
        else if (check_for_Symbols_Separating(symb))
        {
            if (!buffer.empty())
            {
                Positoin.position--;
                in.unget();
                return buffer;
            }
            else
            {
                buffer += symb;
                return buffer;
            }
        }
        else if (check_for_Symbols_Operations(symb))
        {
            if (!buffer.empty())
            {
                Positoin.position--;
                in.unget();
                return buffer;
            }
            else
            {
                buffer += symb;
                return buffer;
            }
        }

        buffer += symb;
    }
    return buffer;
}
Hash lex_analis::get_our_hash_table()
{
	return our_hash_table;
}
unique_value lex_analis::add_new_unique_value(ifstream& in, Hash& our_hash_table)
{
    DFA df;
    string word = get_word(in);
    unique_value buffer = df.vector_for_unique_value(word);
    our_hash_table.add_new_word_in_table(buffer);
    return buffer;
}
vector<unique_value> lex_analis::get_our_unique_value()
{
    return our_unique_value;
}

void lex_analis::back_word(ifstream& in, string word)
{
    reverse(word.begin(), word.end());
    for (auto symb : word)
    {
        in.putback(symb);//Возвращаем в поток
    }
}