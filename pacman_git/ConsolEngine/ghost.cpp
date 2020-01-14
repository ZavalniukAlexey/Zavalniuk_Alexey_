#include "ghost.h"
#include <cmath>
#include "Field.h"
#include "Pacman.h"
#include "BaseApp.h"

bool swapped = true;

//����������� ������� ��� �������� ���������� ����� �������
double ghost::checkDistance(int x1, int y1, int x2, int y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//����������� ������� ��� ������ ����������� ���������
double getMinOfThree(double b, double a, double c)
{
	return fmin(fmin(a, b), c);
}

ghost::ghost()
{
	PosX_ = 20;
	PosY_ = 6;
	PosXOld_ = PosX_;
	PosYOld_ = PosY_;
	health_ = 1;
	displayName_ = 'o';
	startingY_ = 6;
	startingX_ = 20;
	frighten_ = false;
	scatter_ = false;
	chase_ = true;
	direction_ = 'b';
}
ghost::ghost(int x, int y, int hp, char c)
{
	PosX_ = x;
	PosY_ = y;
	PosXOld_ = x;
	PosYOld_ = y;
	health_ = hp;
	displayName_ = c;
	startingY_ = y;
	startingX_ = x;
	frighten_ = false;
	scatter_ = false;
	chase_ = true;
	direction_ = 'b';
}
void ghost::respawn()
{
	PosX_ = startingX_;
	PosY_ = startingY_;
	direction_ = 'b';
}
//�������� �� ����������
//�� ���������� ����������� ������� � ��������, � ����������� �� �������� �����������
void ghost::moveToStop(Field &field, int steps, Pacman pacman)
{
	switch (this->direction_)
	{
		case 't':
		{
			//������ ���� ������������ ���
			if (!swapped)
			{
				if (field.getFieldChar(this->PosY_, this->PosX_ - 1) == ' ' ||
					field.getFieldChar(this->PosY_, this->PosX_ + 1) == ' ' ||
					field.getFieldChar(this->PosY_, this->PosX_ - 1) == '.' ||
					field.getFieldChar(this->PosY_, this->PosX_ + 1) == '.')
				{
					turn('t', pacman, field);
					break;
				}
			}
			swapped = false;
			//��������� �� ����� ��� �� ����������
			while (steps-- && (field.getFieldChar(this->PosY_ - 1, this->PosX_) != '#'))				
			{
				char temp = field.getFieldChar(this->PosY_ - 1, this->PosX_);
				this->PosXOld_ = this->PosX_;
				this->PosYOld_ = this->PosY_;
				this->PosY_--;
				
				field.updateField(this->PosY_, this->PosX_, this->GetDisplayName());
				field.updateField(this->PosYOld_, this->PosXOld_, temp);
			}
			break;
		}

		case 'b':
		{
			if (!swapped)
			{
				if (field.getFieldChar(this->PosY_, this->PosX_ - 1) == ' ' ||
					field.getFieldChar(this->PosY_, this->PosX_ + 1) == ' ' ||
					field.getFieldChar(this->PosY_, this->PosX_ - 1) == '.' ||
					field.getFieldChar(this->PosY_, this->PosX_ + 1) == '.')
				{
					this->direction_ = 'r';
					turn('b', pacman, field);
					break;
				}
			}
			swapped = false;
			while (steps-- && (field.getFieldChar(this->PosY_+ 1, this->PosX_) != '#'))
			{
				char temp = field.getFieldChar(this->PosY_+1, this->PosX_);
				this->PosXOld_ = this->PosX_;
				this->PosYOld_ = this->PosY_;
				this->PosY_++;
				field.updateField(this->PosY_, this->PosX_, this->GetDisplayName());
				field.updateField(this->PosYOld_, this->PosXOld_, temp);
			}
			break;
		}

		case 'l':
		{
			if (!swapped)
			{
				if (field.getFieldChar(this->PosY_ - 1, this->PosX_) == ' ' ||
					field.getFieldChar(this->PosY_ + 1, this->PosX_) == ' ' ||
					field.getFieldChar(this->PosY_ - 1, this->PosX_) == '.' ||
					field.getFieldChar(this->PosY_ + 1, this->PosX_) == '.')
				{
					turn('l', pacman, field);
					break;
				}
			}
			swapped = false;
			while (steps-- && (field.getFieldChar(this->PosY_, this->PosX_ - 1) != '#'))
			{
				char temp = field.getFieldChar(this->PosY_, this->PosX_ - 1);
				this->PosXOld_ = this->PosX_;
				this->PosYOld_ = this->PosY_;
				if (this->PosX_ == 1 && this->PosY_ == 14)
				{
					this->PosX_ = 28;
				}
				else
				{
					this->PosX_--;
				}
				field.updateField(this->PosY_, this->PosX_, this->GetDisplayName());
				field.updateField(this->PosYOld_, this->PosXOld_, temp);
			}
			break;
		}
		
		case 'r':
		{
			if (!swapped) 
			{
					if (field.getFieldChar(this->PosY_ - 1, this->PosX_) == ' ' ||
						field.getFieldChar(this->PosY_ + 1, this->PosX_) == ' ' ||
						field.getFieldChar(this->PosY_ - 1, this->PosX_) == '.' ||
						field.getFieldChar(this->PosY_ + 1, this->PosX_) == '.')
				{
					turn('r', pacman, field);
					break;
				}
			}
			swapped = false;
			while (steps-- && (field.getFieldChar(this->PosY_, this->PosX_+1) != '#' ))
			{

				char temp = field.getFieldChar(this->PosY_, this->PosX_ + 1);
				this->PosXOld_ = this->PosX_;
				this->PosYOld_ = this->PosY_;
				if (this->PosX_ == 28 && this->PosY_ == 14)
				{
					this->PosX_ = 1;
				}
				else
				{
					this->PosX_++;
				}
				field.updateField(this->PosY_, this->PosX_, this->GetDisplayName());
				field.updateField(this->PosYOld_, this->PosXOld_, temp);
			}
			break;
		}
	}
}
//������ ���������
void ghost::turn(char direction, Pacman pacman, Field field)
{
	swapped = true;
	double top = 1000000, bot = 1000000, right = 10000000, left = 1000000;
	switch (direction)
	{
	case 't':
	{
		//�������� ��������� ��� �������� ������, ���� ��� ��������
		if (field.getFieldChar(this->GetY() + 1, this->GetX()) != '#')
			top = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());
		char t = field.getFieldChar(this->GetY() + 1, this->GetX());

		//�������� ��������� ��� �������� �������, ���� ��� ��������
		if (field.getFieldChar( this->GetY(), this->GetX() + 1 ) != '#')
			right = checkDistance(this->GetX() + 1, this->GetY(), pacman.GetX(), pacman.GetY());
		char r = field.getFieldChar(this->GetY(), this->GetX() + 1);

		//�������� ��������� ��� �������� ������, ���� ��� ��������
		if (field.getFieldChar(this->GetY(), this->GetX()-1) != '#')
			left = checkDistance(this->GetX() - 1, this->GetY(), pacman.GetX(), pacman.GetY());
		char l = field.getFieldChar(this->GetY(), this->GetX()-1);

		double temp = getMinOfThree(top, right, left);
		if (top == temp)
		{
			if (field.getFieldChar(this->GetY()+1, this->GetX()) != '#')
			{
				this->direction_ = 't';
				break;
			}
			else
				temp = fmin(left, right);
		}
		if (left == temp)
		{
			if (field.getFieldChar(this->GetY(), this->GetX()+1) != '#')
			{
				this->direction_ = 'l';
				break;
			}
			else
				temp = right;
		}
		if (right == temp)
		{
			this->direction_ = 'r';
			break;
		}


		break;
	}
	case 'b':
	{
		//�������� ��������� ��� �������� �������, ���� ��� ��������
		//char c = field.getFieldChar;
		if (field.getFieldChar(this->GetY(), this->GetX()+1) != '#')
			right = checkDistance(this->GetX() + 1, this->GetY(), pacman.GetX(), pacman.GetY());

		//�������� ��������� ��� �������� ������, ���� ��� ��������
		if (field.getFieldChar(this->GetY(), this->GetX()-1) != '#')
			left = checkDistance(this->GetX() - 1, this->GetY(), pacman.GetX(), pacman.GetY());

		//�������� ��������� ��� �������� ����, ���� ��� ��������
		char s = field.getFieldChar(this->GetY() + 1, this->GetX());
		if (field.getFieldChar( this->GetY() + 1, this->GetX() ) != '#')
			bot = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());

		double temp = getMinOfThree(right, left, bot);

		if (left == temp)
		{
			//char c = field.getFieldChar(this->GetX() - 1, this->GetY());
			if (field.getFieldChar(this->GetY(), this->GetX()-1) != '#')
			{
				this->direction_ = 'l';
				break;
			}
			else
				temp = fmin(bot, right);
		}
		if (bot == temp)
		{
			if (field.getFieldChar(this->GetY()+1, this->GetX()) != '#') {
				this->direction_ = 'b';
				break;
			}
			else
				temp = right;
		}


		if (right == temp)
		{
			this->direction_ = 'r';
			break;
		}
		break;
	}

	case 'r':
	{
		//�������� ��������� ��� �������� ������, ���� ��� ��������
		if (field.getFieldChar(this->GetY()+1, this->GetX()) != '#')
			top = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());

		//�������� ��������� ��� �������� �������, ���� ��� ��������
		if (field.getFieldChar(this->GetY(), this->GetX()+1) != '#')
			right = checkDistance(this->GetX() + 1, this->GetY(), pacman.GetX(), pacman.GetY());

		//�������� ��������� ��� �������� ����, ���� ��� ��������
		if (field.getFieldChar(this->GetY()+1, this->GetX()) != '#')
			bot = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());

		double temp = getMinOfThree(top, right, bot);
		if (top == temp)
		{
			if (field.getFieldChar(this->GetY(), this->GetX()+1) != '#')
			{
				this->direction_ = 't';
				break;
			}
			else
				temp = fmin(bot, right);
		}
		if (right == temp)
		{
			if (field.getFieldChar(this->GetY(), this->GetX()+1) != '#')
			{
				this->direction_ = 'r';
				break;
			}
			else
				temp = bot;
		}
		if (bot == temp)
		{
			this->direction_ = 'b';
			break;
		}

		break;
	}
	case 'l':
	{
		//�������� ��������� ��� �������� ������, ���� ��� ��������
		if (field.getFieldChar(this->GetY()+1, this->GetX()) != '#')
			top = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());
		//�������� ��������� ��� �������� ������, ���� ��� ��������
		if (field.getFieldChar(this->GetY(), this->GetX()-1) != '#')
			left = checkDistance(this->GetX() - 1, this->GetY(), pacman.GetX(), pacman.GetY());
		//�������� ��������� ��� �������� ����, ���� ��� ��������
		if (field.getFieldChar(this->GetY()+1, this->GetX()) != '#')
			bot = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());
		double temp = getMinOfThree(top, bot, left);

		if (bot == temp)
		{
			if (field.getFieldChar(this->GetY()+1, this->GetX()) != '#') 
			{
				this->direction_ = 'b';
				break;
			}
			else
				temp = fmin(left, top);
		}
		if (left == temp)
		{
			if (field.getFieldChar(this->GetY(), this->GetX()-1) != '#')
			{
				this->direction_ = 'l';
				break;
			}
			else
				temp = top;
			if (top == temp)
			{
				this->direction_ = 't';
				break;
			}
			break;
		}
	}
	}
}





void ghost::moveToPoint(int x, int y, Field &field, Pacman pacman)
{
	moveToStop(field, 1, pacman);
}

ghost::~ghost()
{
}
