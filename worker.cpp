#include "worker.h"
#include"sqlite3.h"
#include"menu.h"
#include<iostream>
#include<conio.h>
#include <windows.h>
#include<string>

using namespace std;
worker p1;
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
	create();
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

menu gotox,f1;


int worker::AgeChange() {
	
	//system("cls");
	gotox.gotoxy(29, 10);
	cout << "Podaj nowy wiek:";
	cin >> wiek;
	sql1 = UpdateQuestion1 + wiek + " where imie=" + g + p1.imie + g + i + "Nazwisko=" + g + p1.nazwisko + g + i + "Wiek=" + p1.wiek1 + ";";		 //sklejenie paru stringow w jeden tworzacy zapytanie
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
		cout << "\n\n\n Wiek zmieniony pomyslnie!";
		getch();
	}

	const int n = 5;
	int (worker::*Functions[n])();

	Functions[0] = &worker::select;
	Functions[1] = &worker::insert;
	Functions[2] = &worker::update;
	Functions[3] = &worker::delet;
	Functions[4] = &worker::close;

	string *FunctionNames = new string[n];
	FunctionNames[0] = "Wyswietl pracownikow firmy";
	FunctionNames[1] = "Dodaj pracownika";
	FunctionNames[2] = "Zaaktualizuj dane o pracowniku";
	FunctionNames[3] = "Usun pracownika z firmy";
	FunctionNames[4] = "Wyjscie";

	f1.menu1(p1, 5, 3, 3, FunctionNames, Functions);

	return 0;
}

int worker::SalaryChange() {
	gotox.gotoxy(29, 12);
	cout << "Podaj nowa pensje:";
	cin >> pensja;
	sql1 = UpdateQuestion2 + pensja + " where imie=" + g + p1.imie + g + i + "Nazwisko=" + g + p1.nazwisko + g + i + "Wiek=" + p1.wiek1 + ";";		 //sklejenie paru stringow w jeden tworzacy zapytanie
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

	const int n = 5;
	int (worker::*Functions[n])();

	Functions[0] = &worker::select;
	Functions[1] = &worker::insert;
	Functions[2] = &worker::update;
	Functions[3] = &worker::delet;
	Functions[4] = &worker::close;

	string *FunctionNames = new string[n];
	FunctionNames[0] = "Wyswietl pracownikow firmy";
	FunctionNames[1] = "Dodaj pracownika";
	FunctionNames[2] = "Zaaktualizuj dane o pracowniku";
	FunctionNames[3] = "Usun pracownika z firmy";
	FunctionNames[4] = "Wyjscie";

	f1.menu1(p1, 5, 3, 3, FunctionNames, Functions);

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
	cout << "Podaj pracownika, ktorego dane chcesz zaaktualizowac: \n \n";
	cout << "Imie: ";
	cin >> p1.imie; 
	cout << "Nazwisko: ";
	cin >> p1.nazwisko;
	cout << "Wiek: ";
	cin >> p1.wiek1;
	string sql1 = a + g + p1.imie + g + i + "Nazwisko=" + g + p1.nazwisko + g + i + "Wiek=" + p1.wiek1 + ";";		 //sklejenie paru stringow w jeden tworzacy zapytanie
	char * sql = new char[sql1.size() + 1];
	strcpy(sql, sql1.c_str());
	// Execute SQL statement 
	rc = sqlite3_exec(db, sql, myCallback, &fHasResult, &zErrMsg);		//sprawdza czy pracownik istnieje w bazie
	if (fHasResult) {
		menu f1;
		//worker p1;
		const int n = 2;
		
		string *FunctionNames = new string[n];
		FunctionNames[0] = "Wiek";
		FunctionNames[1] = "Pensje";

		int (worker::*Functions[n])();
		Functions[0] = &worker::AgeChange;
		Functions[1] = &worker::SalaryChange;
		gotox.gotoxy(10,7);
		cout << "Co chcesz zmienic?";
		f1.menu1(p1, n, 9,10 , FunctionNames, Functions);
	}

	else {		//w przypadku braku takiego pracownika
		cout << "Brak takiego pracownika!";
		getch();
	}




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
	_getch();
	return 0;
}


//zamyka baze danych
int worker::close() {
	sqlite3_close(db);
	exit(0);
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

