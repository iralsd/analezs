#pragma once
#include "Hash.h"
#include "syntax_analis.h"
#include "Tree.h"
#include <iostream>


class semantic_analyzer
{
private:
	ofstream out;
	Tree_of_syntax Tree;
	Hash hash_table;
public:
	semantic_analyzer(string filename, Tree_of_syntax tree, Hash hash_table);
	bool flag = true;
	bool Program(Tree_of_syntax& Tree);
	bool Begin(Node& node);
	bool Descriptions(Node& node);
	bool Varlist(Node& node, int& count_deti, string type);
	bool Operators(Node& node);
	bool Expr(Node& node, string type_num);
	bool S1mpleExpr(Node& node, string type_num);
	bool End(Node& node);
};
