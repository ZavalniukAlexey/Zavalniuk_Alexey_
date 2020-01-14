#include "ghost.h"
#include <cmath>
#include "Field.h"
#include "Pacman.h"

bool swapped = true;

//утилитарна€ функци€ дл€ рассчЄта рассто€ни€ между точками
double checkDistance(int x1, int y1, int x2, int y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//утилитарна€ функци€ дл€ поиска минимальной дистанции
double getMinOfThree(double b, double a, double c)
{
	return fmin(fmin(a, b), c);
}
ghost::ghost()
{
	PosX_ = 6;
	PosY_ = 20;
	PosXOld_ = PosX_;
	PosYOld_ = PosY_;
	health_ = 1;
	display_name_ = 'o';
	startingY_ = 16;
	startingX_ = 12;
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
	display_name_ = c;
	startingY_ = y;
	startingX_ = x;
	frighten_ = false;
	scatter_ = false;
	chase_ = true;
	direction_ = 't';
}

//движение до перекрЄстка
//на перекрЄстке принимаетс€ решение о повороте, в зависимости от текущего направлени€
void ghost::moveToStop(Field &field, int steps, Pacman pacman)
{
	switch (this->direction_)
	{
		case 't':
		{
			//делаем один об€зательный шаг
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
			//двигаемс€ до стены или до перекрЄстка
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
				if (this->PosX_ = 1 && this->PosY_ == 14)
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
//логика поворотов
void ghost::turn(char direction, Pacman pacman, Field field)
{
	swapped = true;
	double top = 1000000, bot = 1000000, right = 10000000, left = 1000000;
	switch (direction)
	{
	case 't':
	{
		//пересчЄт дистанции при движении наверх, если это возможно
		if (field.getFieldChar(this->GetX(), this->GetY() + 1) != '#')
			top = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());

		//пересчЄт дистанции при движении направо, если это возможно
		if (field.getFieldChar(this->GetX() + 1, this->GetY()) != '#')
			right = checkDistance(this->GetX() + 1, this->GetY(), pacman.GetX(), pacman.GetY());

		//пересчЄт дистанции при движении налево, если это возможно
		if (field.getFieldChar(this->GetX() - 1, this->GetY()) != '#')
			left = checkDistance(this->GetX() - 1, this->GetY(), pacman.GetX(), pacman.GetY());

		double temp = getMinOfThree(top, right, left);
		if (top == temp)
		{
			if (field.getFieldChar(this->GetX(), this->GetY() + 1) != '#')
			{
				this->direction_ = 't';
				break;
			}
			else
				temp = fmin(left, right);
		}
		if (left == temp)
		{
			if (field.getFieldChar(this->GetX() + 1, this->GetY()) != '#')
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
		//пересчЄт дистанции при движении направо, если это возможно
		//char c = field.getFieldChar;
		if (field.getFieldChar(this->GetX() + 1, this->GetY()) != '#')
			right = checkDistance(this->GetX() + 1, this->GetY(), pacman.GetX(), pacman.GetY());

		//пересчЄт дистанции при движении налево, если это возможно
		if (field.getFieldChar(this->GetX() - 1, this->GetY()) != '#')
			left = checkDistance(this->GetX() - 1, this->GetY(), pacman.GetX(), pacman.GetY());

		//пересчЄт дистанции при движении вниз, если это возможно
		char s = field.getFieldChar(this->GetY() + 1, this->GetX());
		if (field.getFieldChar( this->GetY() + 1, this->GetX() ) != '#')
			bot = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());

		double temp = getMinOfThree(right, left, bot);

		if (left == temp)
		{
			char c = field.getFieldChar(this->GetX() - 1, this->GetY());
			if (field.getFieldChar(this->GetX() - 1, this->GetY()) != '#')
			{
				this->direction_ = 'l';
				break;
			}
			else
				temp = fmin(bot, right);
		}
		if (bot == temp)
		{
			if (field.getFieldChar(this->GetX(), this->GetY() + 1) != '#') {
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
		//пересчЄт дистанции при движении наверх, если это возможно
		if (field.getFieldChar(this->GetX(), this->GetY() + 1) != '#')
			top = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());
		//пересчЄт дистанции при движении направо, если это возможно
		if (field.getFieldChar(this->GetX() + 1, this->GetY()) != '#')
			right = checkDistance(this->GetX() + 1, this->GetY(), pacman.GetX(), pacman.GetY());
		//пересчЄт дистанции при движении вниз, если это возможно
		if (field.getFieldChar(this->GetX(), this->GetY() + 1) != '#')
			bot = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());
		double temp = getMinOfThree(top, right, bot);
		if (top == temp)
		{
			if (field.getFieldChar(this->GetX() + 1, this->GetY()) != '#')
			{
				this->direction_ = 't';
				break;
			}
			else
				temp = fmin(bot, right);
		}
		if (right == temp)
		{
			if (field.getFieldChar(this->GetX() + 1, this->GetY()) != '#')
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
		//пересчЄт дистанции при движении наверх, если это возможно
		if (field.getFieldChar(this->GetX(), this->GetY() + 1) != '#')
			top = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());
		//пересчЄт дистанции при движении налево, если это возможно
		if (field.getFieldChar(this->GetX() - 1, this->GetY()) != '#')
			left = checkDistance(this->GetX() - 1, this->GetY(), pacman.GetX(), pacman.GetY());
		//пересчЄт дистанции при движении вниз, если это возможно
		if (field.getFieldChar(this->GetX(), this->GetY() + 1) != '#')
			bot = checkDistance(this->GetX(), this->GetY() + 1, pacman.GetX(), pacman.GetY());
		double temp = getMinOfThree(top, bot, left);

		if (top == temp)
		{
			if (field.getFieldChar(this->GetX(), this->GetY() + 1) != '#') {
				this->direction_ = 't';
				break;
			}
			else
				temp = fmin(left, bot);
		}
		if (left == temp)
		{
			if (field.getFieldChar(this->GetX() - 1, this->GetY()) != '#')
			{
				this->direction_ = 'l';
				break;
			}
			else
				temp = bot;
			if (bot == getMinOfThree(top, right, left))
			{
				this->direction_ = 'b';
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
