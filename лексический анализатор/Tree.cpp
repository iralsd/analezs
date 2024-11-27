#include "Tree.h"

void Tree_of_syntax::addSon(string data, string current, Node& our_root)
{
	if (our_root.get_data() == current)
	{
		our_root.add_child(data);
	}
	else
	{
		for (int i = 0; i < our_root.get_vector_of_child().size(); i++)
		{
			addSon(data, current, our_root.get_vector_of_child()[i]);
		}
	}
}

void Tree_of_syntax::print(ofstream& out, Node root, int level)
{
	for (int i = 0; i < level; i++)
	{
		out << "\t";
	}
	out << root.get_data() << "\n";
	for (auto item : root.get_vector_of_child())
	{
		print(out, item, level + 1);
	}
}

void Tree_of_syntax::our_root_info_set(string data)
{
	our_root.set_data(data);
}

void Tree_of_syntax::insert_child(Tree_of_syntax& syntax_tree, string need_to_add, Node& current_node)
{
	if (current_node.get_data().empty())
	{
		return;
	}
	bool flag = false;
	for (auto symbols : current_node.get_data())
	{
		if (symbols == ' ')
			flag = true;
	}
	if (!flag && current_node.get_vector_of_child().empty())
	{
		if (current_node.get_data() == need_to_add)
		{
			current_node.get_vector_of_child().push_back(Node());
			copy(syntax_tree.our_root, *current_node.get_vector_of_child().begin());
			return;
		}
	}
	for (auto& item : current_node.get_vector_of_child())
	{
		insert_child(syntax_tree, need_to_add, item);
	}

}

void Tree_of_syntax::insert_new_subtree(Tree_of_syntax& syntax_tree, string need_to_add, Node& current_node)
{
	if (current_node.get_data().empty())
	{
		return;
	}
	bool flag = false;
	for (auto symbols : current_node.get_data())
	{
		if (symbols == ' ')
			flag = true;
	}
	if (!flag && current_node.get_vector_of_child().empty())
	{
		if (current_node.get_data() == need_to_add)
		{
			current_node.set_data("");
			current_node.get_vector_of_child().clear();
			copy(syntax_tree.our_root, current_node);
			return;
		}
	}
	for (auto& item : current_node.get_vector_of_child())
	{
		insert_new_subtree(syntax_tree, need_to_add, item);
	}
}

void Tree_of_syntax::copy(Node& from, Node& to)
{
	to = from;
	for (int i = 0; i < from.get_vector_of_child().size(); i++)
	{
		copy(from.get_vector_of_child()[i], to.get_vector_of_child()[i]);
	}
}

void Tree_of_syntax::clear_childs()
{
	this->our_root.get_vector_of_child().clear();
}

Node& Tree_of_syntax::get_our_root()
{
	return this->our_root;
}
