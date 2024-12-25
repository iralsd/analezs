#include "struct_unique_value.h"

unique_value::unique_value(string name, string type)
{
	this->type = type;
	this->name = name;
}

unique_value::unique_value()
{

}
unique_value::unique_value(string name)
{
    bool get_space = false;
    string type_of_token = "";
    string name_of_token = "";
    for (auto elem : name) {
        if (elem == ' ') {
            get_space = true;
        }
        if (!get_space && elem!=' ' && elem != ':') {
            type_of_token += elem;
        }
        else if (elem != ' ' && elem != ':'){
            name_of_token += elem;
        }
    }
    this->type = type_of_token;
    this->name = name_of_token;
}
//*******
unique_value::unique_value(int number)
{
    if (number == -1)
    {
        this->type = "Bad";
        this->name = "Bad";
    }
}