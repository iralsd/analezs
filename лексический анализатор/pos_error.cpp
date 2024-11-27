#include "pos_error.h"

Pos_Error::Pos_Error()
{
	line_number = 1;
	position = 1;
}

void Pos_Error::Check_Position(char symb)
{
	position++;
	if (symb == '\n')
	{
		line_number++;
		position = 1;
	}
}
