#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Node
{
private:
	string data;
	vector<Node> vector_of_child;
public:
	Node()
	{

	};
	Node(string data)
	{
		this->data = data;
		this->vector_of_child.resize(0);
	}
	string& get_data()
	{
		return data;
	}
	vector<Node>& get_vector_of_child()
	{
		return vector_of_child;
	}
	void set_data(string data)
	{
		this->data = data;
	}
	void add_child(string data)
	{
		Node buffer(data);
		this->vector_of_child.push_back(buffer);
	}
	vector<Node>& get_child_vector()
	{
		return vector_of_child;
	}
};
class Tree_of_syntax
{
private:
	Node our_root;
public:
	Tree_of_syntax()
	{
		our_root = Node("Program");
	}
	Tree_of_syntax(string name)
	{
		our_root = Node(name);
	}
	void addSon(string data, string current, Node& our_root);
	void print(ofstream& out, Node root, int level);
	void our_root_info_set(string data);
	void insert_child(Tree_of_syntax& syntax_tree, string need_to_add, Node& current_node);
	void insert_new_subtree(Tree_of_syntax& syntax_tree, string need_to_add, Node& current_node);
	void copy(Node& from, Node& to);
	void clear_childs();
	Node& get_our_root();

};