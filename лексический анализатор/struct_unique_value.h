#pragma once
#include <string>
using namespace std;
struct unique_value
{
	string type = "None", name = "None";
	unique_value(string name, string type);
	unique_value();
};