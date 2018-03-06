#include "worker.h"
#include"sqlite3.h"
#include"menu.h"
#include<iostream>
#include<conio.h>
#include <windows.h>
#include<string>

using namespace std;

//oddzielanie rekordow w tabelce
void dots() {
	for (int o = 0; o < 79; o++) {
		cout << "-";
	}
}


int myCallback(void *pUser, int argc, char **colData, char **colNames) {
	int *flag = (int*)pUser;
	*flag = 1;
	return 1;
}

int worker::callback(void * NotUsed, int argc, char ** argv, char ** azColName)
{
	int i;
		
		for (i = 0; i<argc; i++) {
			printf("%s ", argv[i] ? argv[i] : "NULL");
				if (strlen(argv[i]) <7) {
					cout << "\t";
				}
				cout << "\t";
		}
		dots();
		cout<<"\n";
		return 0;
		cout << "\n";
}

//otwiera baze danych
int worker::open()
{
	/* Open database */
	rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
}


//dodaje rekord do bazy danych
int worker::insert()
{
	string a = "Insert into COMPANY (Imie,Nazwisko,Wiek,Stanowisko,Pensja) Values (";
	cout << "DODAWANIE NOWEGO PRACOWNIKA" << endl << endl;
	cout << "Wprowadz imie:";
	cin >> imie;
	cout << "Nazwisko:";
	cin >> nazwisko;
	cout << "Wiek:";
	cin >> wiek;
	cout << "Stanowisko:";
	cin >> stanowisko;
	cout << "Pensja:";
	cin >> pensja;
	string sql1 = a + g + imie + g + p + g + nazwisko + g + p + wiek + p + g + stanowisko + g + p + pensja + k;
	char * sql = new char[sql1.size() + 1];
	strcpy(sql, sql1.c_str());

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		getch();
	}
	else {
		fprintf(stdout, "Pracownik dodany!\n");
		getch();
	}
	return 0;
}


//usuwa rekord z tabeli
int worker::delet()
{
	cout << "USUWANIE PRACOWNIKA" << endl << endl;
	cout << "Podaj imie:";
	cin >> imie;
	cout << "Podaj nazwisko:";
	cin >> nazwisko;
	cout << "Podaj wiek:";
	cin >> wiek;
	cout << endl;
	string sql1 = a + g + imie + g + i + "Nazwisko=" + g + nazwisko + g + i + "Wiek=" + wiek+";";		 //sklejenie paru stringow w jeden tworzacy zapytanie
	char * sql = new char[sql1.size() + 1];
	strcpy(sql, sql1.c_str());
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, myCallback, &fHasResult, &zErrMsg);		//sprawdza czy pracownik istnieje w bazie
	if (fHasResult) {		 //jesli istnieje to go usuwa
		sql1 = "DELETE from COMPANY where Imie=" + g + imie + g + i + "Nazwisko=" + g + nazwisko + g + i + "Wiek=" + wiek + ";";
		char * sql = new char[sql1.size() + 1];
		strcpy(sql, sql1.c_str());
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			cout << "Pracownik zostal usuniety!";
		}
	}
	else {		//w przypadku braku takiego pracownika
		cout << "Brak takiego pracownika w bazie danych!";
	}
	getch();

	return 0;
}

//aktualizuje rekord w tabeli
int worker::update() {
	cout << "Podaj imie, nazwisko oraz wiek pracownika, ktorego dane chcesz zaaktualizowac w podanej kolejnosci \n \n";
	cin >> imie >> nazwisko >> wiek1;
	string sql1 = a + g + imie + g + i + "Nazwisko=" + g + nazwisko + g + i + "Wiek=" + wiek1 + ";";		 //sklejenie paru stringow w jeden tworzacy zapytanie
	char * sql = new char[sql1.size() + 1];
	strcpy(sql, sql1.c_str());
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, myCallback, &fHasResult, &zErrMsg);		//sprawdza czy pracownik istnieje w bazie
	if (fHasResult) {		 //jesli istnieje to go "uaktualnia"
		cout << "\nCo chcesz zmienic?";
		int wybor;
		int poprzedniWybor;
		bool wykonujPetle;
		menu gotox;
		while (1)
		{
			wybor = 0;
			poprzedniWybor = wybor;
			wykonujPetle = true;
			//rysowanie dwoch opcji
			int wysokosc = 7;
			gotox.gotoxy(3, wysokosc);
			cout << "Wiek";
			gotox.gotoxy(3, wysokosc+2);
			cout << "Pensje";
			//przesuwanie strza³ki
			while (wykonujPetle)
			{
				//rysowanie strza³ki wyboru
				gotox.gotoxy(1, wybor * 2 + wysokosc);
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
						else wybor = 1;

						break;

					case 80: //strza³ka w dó³
						if (wybor < 1) wybor++;
						else wybor = 0;

						break;
					}
					break;
				case 13: //enter
						 //je¿eli wciœniêto enter, sprawdŸ wybran¹ opcjê i wykonaj odpowiedni¹ akcjê
					switch (wybor)
					{
						case 0:
						gotox.gotoxy(1, wybor * 2 + wysokosc+4);
						cout << "Podaj nowy wiek:";
						cin >> wiek;
						sql1 = UpdateQuestion1 +wiek+" where imie=" + g + imie + g + i + "Nazwisko=" + g + nazwisko + g + i + "Wiek=" + wiek1 + ";";		 //sklejenie paru stringow w jeden tworzacy zapytanie
						sql = new char[sql1.size() + 1];
						strcpy(sql, sql1.c_str());

						/* Execute SQL statement */
						rc = sqlite3_exec(db, sql, callback, &fHasResult, &zErrMsg);
						if (rc != SQLITE_OK) {
							fprintf(stderr, "SQL error: %s\n", zErrMsg);
							sqlite3_free(zErrMsg);
							getch();
						}
						else {
							fprintf(stdout, "\nWiek zmieniony pomyslnie!");
							getch();
						}
						goto end;

					case 1:
						gotox.gotoxy(1, wybor * 2 + wysokosc + 4);
						cout << "Podaj nowapensje:";
						cin >> pensja;
						sql1 = UpdateQuestion2 + pensja + " where imie=" + g + imie + g + i + "Nazwisko=" + g + nazwisko + g + i + "Wiek=" + wiek1 + ";";		 //sklejenie paru stringow w jeden tworzacy zapytanie
						cout << sql1;
						getch();
						sql = new char[sql1.size() + 1];
						strcpy(sql, sql1.c_str());

						/* Execute SQL statement */
						rc = sqlite3_exec(db, sql, callback, &fHasResult, &zErrMsg);
						if (rc != SQLITE_OK) {
							fprintf(stderr, "SQL error: %s\n", zErrMsg);
							sqlite3_free(zErrMsg);
							getch();
						}
						else {
							fprintf(stdout, "\nWysokosc pensji zmieniona pomyslnie!");
							getch();
						}
						goto end;
					}
					break;
				}
				//czyszczenie strza³ki wyboru
				gotox.gotoxy(1, poprzedniWybor * 2 + wysokosc);
				cout << " ";
				
			}
		}
	}
	else {		//w przypadku braku takiego pracownika
		cout << "Brak takiego pracownika!";
		getch();
	}
	end:
	return 0;
}


//wyswietla baze danych
int worker::select()
{
	const char* data = "Callback function called";
	/* Create SQL statement */
	sql = "SELECT * from COMPANY";

	/* Execute SQL statement */	
	HANDLE hOut;		//Kolorowanie poczatku tabeli
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 12);
	for (int i = 0; i < __argc; i++) {
		cout <<"Imie\t\tNazwisko\tWiek\t\tStanowisko\tPensja\n";
	}
	dots();
	SetConsoleTextAttribute(hOut, 7);
	cout << endl;
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) { //zabezpieczenie na wypadek gdyby baza danych nie zostala otworzona
		fprintf(stderr, "Tabela jest pusta!\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	return 0;
}


//zamyka baze danych
int worker::close() {
	sqlite3_close(db);
	return 0;
}

int worker::create() {
	sql = "CREATE TABLE COMPANY("  \
		"Imie			TEXT     NOT NULL," \
		"Nazwisko           TEXT    NOT NULL," \
		"Wiek            INT     NOT NULL," \
		"Stanowisko        CHAR(50)," \
		"Pensja         REAL );";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	return 1;
	}

worker::worker()
{
}


worker::~worker()
{
}
