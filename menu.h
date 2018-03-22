#pragma once
#include <iostream>
#include "worker.h"
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;


class menu
{

public:
	int wybor;
	int poprzedniWybor;
	bool wykonujPetle;
	void gotoxy(const int x, const int y);
	void HideCursor();
	int menu1(worker & p1,int n, int wysokosc, int szerokosc, string FunctionNames[], int(worker::*Functions[])());
};

