#pragma once
#include <string>
#include <vector>
#include "struct_unique_value.h"
using namespace std;

class List
{
public:
	List* predNode = NULL;
	List* nextNode = NULL;
	unique_value value_actual_state;
	
};