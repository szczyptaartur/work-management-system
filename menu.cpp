#include <iostream>
#include "menu.h"
#include "worker.h"
#include <windows.h>
#include <conio.h>
#include <string>


using namespace std;

//funkcja, która przestawia kursor konsoli w dowolne miejsce
void menu::gotoxy(const int x, const int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//funkcja, ktora ukrywa kursor
void menu::HideCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

int menu::menu1(worker & p1, int n, int wysokosc, int szerokosc, string FunctionNames[], int(worker::*Functions[])()) {
	//worker p2;
	p1.open();
	int wybor;
	int poprzedniWybor;
	bool wykonujPetle;
	start:

	//pêtla glówna programu
	while (1)
	{
		wybor = 0;
		poprzedniWybor = wybor;
		wykonujPetle = true;
		//rysowanie menu
		if (n > 3) {
			system("cls");
		}

		HANDLE hOut;		//Kolorowanie poczatku tabeli
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i<5; i++) {
			for (int j = 0; j<10; j += 2) {
				for (int k = 0; k<10; k += 2) {
					SetConsoleTextAttribute(hOut, i + 11);
					gotoxy(j + i + 50, k + i + 1);
					cout << static_cast < char >(177);
				}
			}

		}
		SetConsoleTextAttribute(hOut, 7);

		gotoxy(46, 16);
		cout << "Artur Szczypta " << char(1);
		gotoxy(46, 17);
		cout << "Kontakt: szczypta.artur@gmail.com";
		for (int i = 0; i < n; i++) {
			gotoxy(szerokosc, wysokosc + 1 + 2 * i);
			cout << FunctionNames[i];
		}

		//przesuwanie strza³ki
		while (wykonujPetle)
		{
			//rysowanie strza³ki wyboru
			gotoxy(szerokosc - 2, wybor * 2 + wysokosc + 1);
			cout << static_cast < char >(16);

			//obs³uga klawiatury
			poprzedniWybor = wybor;
			switch (_getch())
			{
			case 224: //STRZA£KI
				switch (_getch())
				{
				case 72: //strza³ka w górê
					if (0 < wybor) wybor--;
					else wybor = n - 1;

					break;

				case 80: //strza³ka w dó³
					if (wybor < n - 1) wybor++;
					else wybor = 0;

					break;
				}
				break;
			case 13: //enter
					 //je¿eli wciœniêto enter, sprawdŸ wybran¹ opcjê i wykonaj odpowiedni¹ akcjê
				if (n > 3) {
					system("cls");
				}
				(p1.*Functions[wybor])();
				goto start;
				break;

			}

			//czyszczenie strza³ki wyboru
			gotoxy(szerokosc - 2, wysokosc + poprzedniWybor * 2 + 1);
			cout << " ";
		}
	}
	return 0;
}
