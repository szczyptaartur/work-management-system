#pragma once
class menu
{

public:
	int wybor;
	int poprzedniWybor;
	bool wykonujPetle;

	void gotoxy(const int x, const int y);

	void HideCursor();

	void draw();
	void show();
};

