// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "Game.h"
#include <string>
#include <iostream>
#include <fstream>
void main()
{
	int choose = 0;
	while (true)
	{
		std::cout << "Pacman game" << std::endl;
		std::cout << "Menu" << std::endl;
		std::cout << "Choose option:" << std::endl;
		std::cout << "1: Start game" << std::endl;
		std::cout << "2: View leaderboard" << std::endl;
		std::cout << "3: Close game" << std::endl;
		std::cin >> choose;
		if (choose == 1)
		{
			Game app;
			app.Run();
			system("cls");
		}
		else if (choose == 2)
		{
			std::string line;
			std::ifstream in;
			in.open("leaderboard.txt");
			if (in.is_open())
			{
				while (std::getline(in, line))
				{
					std::cout << line << std::endl;
				}
				in.close();
			}
			else 
			{
				std::cout << "Failed to open leaderboard" << std::endl;
			}
			std::cout << "Returning into menu..." << std::endl;
			Sleep(2000);
			system("cls");
		}
		else if (choose == 3)
		{
			break;
		}
		else
		{
			std::cout << "Wrong number inputed! Try again" << std::endl;
			Sleep(2000);
			system("cls");
		}
	}
	std::cout << "Good luck!" << std::endl;
	Sleep(2000);
}
