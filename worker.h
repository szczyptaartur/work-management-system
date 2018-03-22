#pragma once
#include"sqlite3.h"
#include<string>


using namespace std;

class worker
{
public:
	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
	int open();
	int create();
	int insert();
	int AgeChange();
	int SalaryChange();
	int delet();
	int update();
	int select();                             
	int close();
	//int(*Functions[4])();

	worker();
	~worker();

	//int wybor, wysokosc;
	string imie, nazwisko, stanowisko, wiek,wiek1, pensja;
	string p = ",";
	string k = ");";
	string g = "'";
	string i = " and ";
	string a = "SELECT * from COMPANY where Imie=";
	string UpdateQuestion1 = "UPDATE COMPANY set Wiek=";
	string UpdateQuestion2 = "UPDATE COMPANY set Pensja=";
	string sql1;

	sqlite3 *db;
	char *zErrMsg = 0;
	int fHasResult = 0;
	int rc;
	char *sql;

	string *FunctionNames = new string[5];

};

