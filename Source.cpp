#include<iostream>
#include"sqlite3.h"
#include"worker.h"
#include"menu.h"
#include<conio.h>

using namespace std;



int main(int argc, char* argv[]) 
{

	menu f1;
	worker p1;
	f1.HideCursor(); //hidding cursor
	const int n = 5;
	string *FunctionNames = new string[n];
	FunctionNames[0] = "Wyswietl pracownikow firmy";
	FunctionNames[1] = "Dodaj pracownika";
	FunctionNames[2] = "Zaaktualizuj dane o pracowniku";
	FunctionNames[3] = "Usun pracownika z firmy";
	FunctionNames[4] = "Wyjscie";
	

	int (worker::*Functions[n])();

	//p1.Functions[0] = p1.select;
	Functions[0] = &worker::select;
	Functions[1] = &worker::insert;
	Functions[2] = &worker::update;
	Functions[3] = &worker::delet;
	Functions[4] = &worker::close;
	
	
	f1.menu1(p1, n, 3, 3, FunctionNames, Functions);


	return 0;
}