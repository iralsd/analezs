#pragma once
class Pos_Error
{
public:
	int line_number, position;
	Pos_Error();
	void Check_Position(char symb);
};

