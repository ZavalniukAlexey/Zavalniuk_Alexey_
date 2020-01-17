#pragma once
#include "Field.hpp"
class FactoryField
{
private: 
	Field fField;
public:
	FactoryField();
	FactoryField(Field factoryField);
	~FactoryField();
};

