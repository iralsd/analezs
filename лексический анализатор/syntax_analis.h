#pragma once
#include "lex_analis.h"
#include "Hash.h"
#include "Tree.h"
//#include "pos_error.h"

class syntax_analis
{
private:
	Pos_Error Error;
public:
	lex_analis lex;
	Hash table;
	Tree_of_syntax Tree;
	ifstream in;
	syntax_analis(string input_name) :in(input_name) { };
	bool Program(Tree_of_syntax& Tree);
	bool Begin(Tree_of_syntax& Tree);
	bool Descriptions(Tree_of_syntax& Tree);
	bool Descr(Tree_of_syntax& Tree);
	bool Type(Tree_of_syntax& Tree);
	bool Varlist(Tree_of_syntax& Tree);
	bool Operators(Tree_of_syntax& Tree);
	bool Op(Tree_of_syntax& Tree);
	bool SimpleExpr(Tree_of_syntax& Tree);
	bool Expr(Tree_of_syntax& Tree);
	bool End(Tree_of_syntax& Tree);
};

