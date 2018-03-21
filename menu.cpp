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
	start:
	draw();
	while (wykonujPetle)
	{
		//rysowanie strzałki wyboru
		gotoxy(1, wybor * 2 + 1);
		cout << static_cast < char >(16);
				
		//obsługa klawiatury
		poprzedniWybor = wybor;
		switch (_getch())
		{
		case 224: //STRZAŁKI
			switch (_getch())
			{
			case 72: //strzałka w górę
				if (0 < wybor) wybor--;
				else wybor = 4;

				break;

			case 80: //strzałka w dół
				if (wybor < 4) wybor++;
				else wybor = 0;

				break;
			}
			break;
		case 13: //enter
				 //jeżeli wciśnięto enter, sprawdź wybraną opcję i wykonaj odpowiednią akcję
			switch (wybor)
			{
			case 0:
				system("cls");
				p1.select(); //wyswietla baze danych
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

		//czyszczenie strzałki wyboru
		gotoxy(1, poprzedniWybor * 2 + 1);
		cout << " ";
	}
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
