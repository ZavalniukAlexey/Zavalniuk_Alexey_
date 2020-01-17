#pragma once


class Field
{
private:
	char field[31][28]; 
public:
	Field();
	void updateField(const int x, const int y, const char c);
	void resetField();
	int countStars()const;
	int getFieldScore()const;
	char getFieldChar(const int i, const int j);
	void setFieldChar(const int i, const int j, const char s);
	~Field();
};

