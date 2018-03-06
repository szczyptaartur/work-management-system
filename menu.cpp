#include <iostream>
#include "menu.h"
#include "worker.h"
#include <windows.h>
#include <conio.h>


using namespace std;

//funkcja, kt�ra przestawia kursor konsoli w dowolne miejsce
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

//rysowanie menu
void menu::draw()
{
	system("cls");
	HideCursor();
	wybor = 0;
	poprzedniWybor = wybor;
	wykonujPetle = true;

	//rysowanie menu
	system("cls");
	gotoxy(3, 1);
	cout << "Wyswietl pracownikow firmy";
	gotoxy(3, 3);
	cout << "Dodaj pracownika";
	gotoxy(3, 5);
	cout << "Zaaktualizuj dane o pracowniku";
	gotoxy(3, 7);
	cout << "Usun pracownika z firmy";
	gotoxy(3, 9);
	cout << "Wyjscie";
	gotoxy(46, 10);
	cout << "Artur Szczypta " << char(1);
	gotoxy(46, 11);
	cout << "Kontakt: szczypta.artur@gmail.com";
}

//wykonywanie akcji w menu
void menu::show()
{
	worker p1;
	p1.open();
	p1.create();
	start:
	draw();
	while (wykonujPetle)
	{
		//rysowanie strza�ki wyboru
		gotoxy(1, wybor * 2 + 1);
		cout << static_cast < char >(16);

		//obs�uga klawiatury
		poprzedniWybor = wybor;
		switch (_getch())
		{
		case 224: //STRZA�KI
			switch (_getch())
			{
			case 72: //strza�ka w g�r�
				if (0 < wybor) wybor--;
				else wybor = 4;

				break;

			case 80: //strza�ka w d�
				if (wybor < 4) wybor++;
				else wybor = 0;

				break;
			}
			break;
		case 13: //enter
				 //je�eli wci�ni�to enter, sprawd� wybran� opcj� i wykonaj odpowiedni� akcj�
			switch (wybor)
			{
			case 0:
				system("cls");
				p1.select(); //wyswietla baze danych
				_getch();
				goto start;
			case 1:
				system("cls");
				p1.insert(); //dodaje nowy wiersz
				goto start;
			case 2:
				system("cls");
				p1.update(); //aktualizuje wiersz
				goto start;
			case 3:
				system("cls");
				p1.delet(); //usuwa wiersz
				goto start;
			case 4:
				p1.close();
				exit(0); //wyjscie
			}
		}

		//czyszczenie strza�ki wyboru
		gotoxy(1, poprzedniWybor * 2 + 1);
		cout << " ";
	}
}