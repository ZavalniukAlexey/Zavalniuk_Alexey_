#include "FactoryField.hpp"



FactoryField::FactoryField()
{
}

FactoryField::FactoryField(Field factoryField)
{
	for (int i = 0; i < 31; i++)
		for (int j = 0; j < 29; j++)
			fField.setFieldChar(i, j, factoryField.getFieldChar(i, j));
}


FactoryField::~FactoryField()
{
}
