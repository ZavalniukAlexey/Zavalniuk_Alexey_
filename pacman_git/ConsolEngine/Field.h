#pragma once


class Field
{
private:
	char field[31][29] = {
	"############################", //0
	"#............##............#", //1
	"#.####.#####.##.#####.####.#", //2
	"#.####.#####.##.#####.####.#", //3
	"#.####.#####.##.#####.####.#", //4
	"#..........................#", //5
	"#.####.##.########.##.####.#", //6
	"#.####.##.########.##.####.#", //7
	"#......##....##....##......#",	//8
	"######.#####.##.#####.######",	//9
	"######.#####.##.#####.######",	//10
	"######.##          ##.######",	//11
	"######.## ######## ## ######", //12
	"######.## #      # ##.######", //13
	"      .   #      #   .      ", //14
	"######.## #      # ##.######", //15
	"######.## ######## ##.######",	//16
	"######.##          ##.######",	//17
	"######.##.########.##.######",	//18
	"######.##.########.##.######",	//19
	"#............##............#",	//20
	"#.####.#####.##.#####.####.#", //21
	"#.####.#####.##.#####.####.#",	//22
	"#...##................##...#",	//23
	"###.##.##.########.##.##.###",	//24
	"###.##.##.########.##.##.###",	//25
	"#......##....##....##......#",	//26
	"#.##########.##.##########.#",	//27
	"#.##########.##.##########.#",	//28
	"#..........................#",	//29
	"############################" 	//30
	};

public:
	Field();
	void updateField(int x, int y, char c);
	void resetField();
	void setCharOnField(int x, int y, char c);
	int countStars();
	int getFieldScore();
	char getFieldChar(int i, int j);
	void setFieldChar(int i, int j, char s);
	~Field();
};

