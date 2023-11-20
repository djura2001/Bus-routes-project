#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include "Linija.h"
#include "Stajaliste.h"

using namespace std;

class Mreza
{
public:
	vector<Linija*> linije;
	vector<Stajaliste*> stajalista;
	int brojStajalista;
	int trenutnoVreme;
	Mreza(const string& staniceTxt,const string& linijeTxt);
	Mreza();
	void ucitajFajlove(const string& staniceTxt, const string& linijeTxt);
	void linijeStajalistima();
	void imenaStajalistaLinijama();
	void stajalisteInfo(int sifra);
	void linijaInfo(string ime);
	//void linijaStatistika(string ime);
	//void postaviVreme(string vreme);

	vector<int> dist;
	int pocetak;
	int kraj;
	vector<int> roditelj;
	vector<bool> prosao;
	vector<int> vremeStanice;


	vector<vector<int>> praviGraf();
	vector<vector<int>> praviPresedanjaGraf();
	void sveBitne(int prvaSifra, int poslednjaSifra);
	void najbrziPut(int prva, int poslednja, string vreme);
	void najmanjePresedanja(int prvaSifra, int poslednjaSifra);
	void terminal();
	
private:
	bool povezanaStajalista(Stajaliste* stajaliste1, Stajaliste* stajaliste2);
	bool povezanaStajalista2(Stajaliste* stajaliste1, Stajaliste* stajaliste2);
	int udaljenost(Stajaliste* stajaliste1, Stajaliste* stajaliste2);
	vector<int> dodajNenulte(int i, vector<vector<int>> g);
	vector<vector<int>> sortirajApsolutne(vector<int> v1, vector<int> v2);
	vector<int> direktanPut(Stajaliste* s1,Stajaliste* s2);
	string linijaVeze(Stajaliste* s1, Stajaliste* s2);
	
	vector<Linija*> zajdenickeLinije(Stajaliste* stajaliste1, Stajaliste* stajaliste2);
	Linija* nadjiLiniju(string ime);
	Stajaliste* nadjiStanicu(int sifra);
	int prviDolazak(vector<int> vremena);
	
	int minimum(vector<int> x);
	int minIndex(vector<int> x);
	
	int redniStajalista(Stajaliste * s);
	int dajBrojStajalista(Stajaliste* stajaliste, Linija* linija);
	int dajBrojStajalistaDrugiSmer(Stajaliste* stajaliste, Linija* linija);
	int vremeCekanja(Stajaliste* stajaliste1, Stajaliste* stajaliste2);
	string najkracaLinija(int sifra1, int sifra2);
	vector<int> bitniSusedi(Stajaliste* s);
	
	
	int stanica(int sifra);
	
	void inicijalizacija();
	int najbliza();
	void djikstra();
	void prikaziPut();
	vector<int> najmanjePresedanjaRuta(int prva, int poslednja);
	
};

