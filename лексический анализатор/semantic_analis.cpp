#include "semantic_analis.h"


semantic_analyzer::semantic_analyzer(string filename,
	Tree_of_syntax tree, Hash hash_table) :
	out(filename), Tree(tree), hash_table(hash_table) {};

string take_new_world_from_vertex(string& name_vertex)
{
	string buffer = "";
	bool flag = false;
	for (auto x : name_vertex)
	{
		if (x == ' ')
		{
			flag = true;
		}
		if (flag && x != ':' && x != ' ')
		{
			buffer += x;
		}
	}
	return buffer;
}

bool semantic_analyzer::Program(Tree_of_syntax& Tree)
{
	Begin(Tree.get_our_root().get_vector_of_child()[0]);
	Descriptions(Tree.get_our_root().get_vector_of_child()[1]);
	Operators(Tree.get_our_root().get_vector_of_child()[2]);
	End(Tree.get_our_root().get_vector_of_child()[3]);
	Tree.get_our_root().get_polskay() += (Tree.get_our_root().get_vector_of_child()[0].get_polskay()) +
		Tree.get_our_root().get_vector_of_child()[1].get_polskay() +
		Tree.get_our_root().get_vector_of_child()[2].get_polskay() +
		Tree.get_our_root().get_vector_of_child()[3].get_polskay();
	if (flag)
		out << Tree.get_our_root().get_polskay();
	return 1;

}

bool semantic_analyzer::Begin(Node& node)
{
	node.get_polskay() += take_new_world_from_vertex(node.get_vector_of_child()[1].get_data()) + " ";
	node.get_polskay() += take_new_world_from_vertex(node.get_vector_of_child()[0].get_data()) + " ";
	node.get_polskay() += " 2 PROGRAM\n";

	hash_table.put_new_atribute(take_new_world_from_vertex(node.get_vector_of_child()[1].get_data()), node.get_vector_of_child()[0].get_data());

	return 1;
}

bool semantic_analyzer::Descriptions(Node& node)
{
	for (int i = 0; i < node.get_vector_of_child().size(); i++)
	{
		if (!node.get_vector_of_child()[i].get_data().empty())
		{
			auto type = take_new_world_from_vertex(node.get_vector_of_child()[i].get_vector_of_child()[0].get_vector_of_child()[0].get_data());
			
			if (type == "")
			{
				Descriptions(node.get_vector_of_child()[i]);
			}
			int count_deti = 1;
			if (Varlist(node.get_vector_of_child()[i].get_vector_of_child()[1], count_deti, type))
			{
				if (i != 1) {
					node.get_polskay() += node.get_vector_of_child()[i].get_vector_of_child()[1].get_polskay();
					node.get_polskay() += type + " " + to_string(count_deti) + " Decralation\n";
				}
				else {
					node.get_polskay() += node.get_vector_of_child()[i].get_polskay();
					
				}
			}
		}
		else
		{
			return 1;
		}
	}
	return 1;
}


bool semantic_analyzer::Varlist(Node& node, int& count_deti, string type)
{
	if (type != "call") {
		for (int i = 0; i < node.get_vector_of_child().size(); i += 2)
		{
			auto buf = node.get_vector_of_child()[i];
			if (buf.get_data() == "Varlist")
			{
				Varlist(buf, count_deti, type);
				node.get_polskay() += buf.get_polskay();
			}
			else
			{
				unique_value uv(buf.get_data());
				if (hash_table.get_unique_value(uv).atribute == "INTEGER" || hash_table.get_unique_value(uv).atribute == "REAL")
				{
					out << "Переменная была создана ранее\n";
					flag = false;
					return 0;
				}
				count_deti++;
				node.get_polskay() = uv.name + " " + node.get_polskay();
				hash_table.put_new_atribute(take_new_world_from_vertex(buf.get_data()), type);

			}
		}
	}
	else {
		for (int i = 0; i < node.get_vector_of_child().size(); i += 2)
		{
			auto buf = node.get_vector_of_child()[i];
			if (buf.get_data() == "Varlist")
			{
				Varlist(buf, count_deti, type);
				node.get_polskay() += buf.get_polskay();
			}
			else
			{
				unique_value uv(buf.get_data());
				if (hash_table.get_unique_value(uv).atribute != "INTEGER" && hash_table.get_unique_value(uv).atribute != "REAL")
				{
					out << "Переменная не создана ранее\n";
					flag = false;
					return 0;
				}
				count_deti++;
				node.get_polskay() = uv.name + " " + node.get_polskay();

			}
		}
	}
	return 1;
}

bool semantic_analyzer::Operators(Node& node)
{
	for (auto elem : node.get_vector_of_child())
	{
		if (!elem.get_data().empty())
		{
			unique_value uv(elem.get_vector_of_child()[0].get_data());
			if (uv.type == "Op")
			{
				Operators(elem);
				node.get_polskay() += elem.get_polskay();
			}
			if (uv.type == "WordsKey")//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
			{
				unique_value bf(elem.get_vector_of_child()[1].get_data());
				if (hash_table.get_unique_value(bf).atribute == "INTEGER" || hash_table.get_unique_value(bf).atribute == "REAL")
				{
					out << "Переменная используется \n";
					flag = false;
					return 0;
				}
				string buffer = bf.name + " ";// fun
				
				
				if (!node.get_vector_of_child()[0].get_data().empty())
				{
					int count_deti = 1;
					if (Varlist(node.get_vector_of_child()[0].get_vector_of_child()[3], count_deti, "call"))
					{
						buffer += node.get_vector_of_child()[0].get_vector_of_child()[3].get_polskay();
						node.get_polskay() += buffer + to_string(count_deti) + " " + uv.name + '\n';
					}
				}
			}
			else if (uv.type == "Id")
			{
				if (hash_table.get_unique_value(uv).atribute != "INTEGER" && hash_table.get_unique_value(uv).atribute != "REAL")
				{
					out << "Переменная не объявлена\n";
					flag = false;
					return 0;
				}
				if (!Expr(elem.get_vector_of_child()[2], hash_table.get_unique_value(uv).atribute))
				{
					flag = false;
					return 0;
				}
				node.get_polskay() += elem.get_vector_of_child()[2].get_polskay() + uv.name + " = \n";
			}
		}
		else
		{
			return 1;
		}
	}
	return 1;
}

bool semantic_analyzer::Expr(Node& node,string type_num)
{
	for (int i = 0; i < node.get_vector_of_child().size(); i += 2)
	{
		if (!S1mpleExpr(node.get_vector_of_child()[i],type_num))//int: 1
		{
			flag = false;
			return 0;
		}
		node.get_polskay() = node.get_vector_of_child()[i].get_polskay() + " " + node.get_polskay();
		if (i + 1 < node.get_vector_of_child().size())
		{
			string oper = take_new_world_from_vertex(node.get_vector_of_child()[i + 1].get_data());
			node.get_polskay() += oper + " ";

		}
	}
	return 1;

}

bool semantic_analyzer::S1mpleExpr(Node& node, string type_num)
{
	unique_value uv(node.get_vector_of_child()[0].get_data());
	if (type_num == "None")
	{
		if (uv.type == "int_num")
		{
			type_num = "INTEGER";
		}
		else if(uv.type == "real_num")
		{
			type_num = "REAL";
		

		}
	}
	if ((uv.type == "int_num" && type_num != "INTEGER") || (uv.type == "real_num" && type_num != "REAL"))
	{
		out << "неявное преобразование\n";
		flag = false;
		return 0;
	}
	if (uv.type == "int_num" || uv.type == "real_num")////////////////////////////////////////////////////////////////////////////////
	{
		node.get_polskay() += uv.name;
		return 1;
	}
	else if (uv.type == "Id")
	{
		if (hash_table.get_unique_value(uv).atribute != "INTEGER" && hash_table.get_unique_value(uv).atribute != "REAL")///
		{
			out << "Переменная не объявлена\n";
			flag = false;
			return 0;
		}
		else if (hash_table.get_unique_value(uv).atribute == type_num )
		{
			node.get_polskay() += uv.name;
			return 1;
		}
		else
		{
			out << "неявное преобразование\n";
			flag = false;
			return 0;
		}

	}
	else
	{
		if (!Expr(node.get_vector_of_child()[1], hash_table.get_unique_value(uv).atribute))
		{
			out << "Ошибка выражения\n";
			flag = false;
			return 0;
		}

	}
	if (flag)
	{
		node.get_polskay() += node.get_vector_of_child()[1].get_polskay();
	}
	return 1;
}

bool semantic_analyzer::End(Node& node)
{
	auto derevo_nachalo = Tree.get_our_root().get_vector_of_child()[0];
	auto derevo_konec = Tree.get_our_root().get_vector_of_child()[3];

	unique_value nachalo(derevo_nachalo.get_vector_of_child()[1].get_data()), konec(derevo_konec.get_vector_of_child()[1].get_data());

	if (hash_table.get_unique_value(nachalo).atribute != hash_table.get_unique_value(konec).atribute)
	{
		out << "Разные название начало программы и конца\n";
		flag = false;
		return 0;
	}

	node.get_polskay() += konec.name + " END\n";

	return 1;


}



