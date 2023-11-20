#pragma once
#include <vector>
#include <string>
#include "Linija.h"
using namespace std;

class Stajaliste
{
public:
	int sifra;
	string ime;
	vector<string> linije;
	vector<int> brojStajalista;//za svaku liniju redom cuva koja po redu mu je ova trenutna stanica
	vector<int> brojStajalistaDrugiSmer;
	Stajaliste();
	Stajaliste(string podaci);
	bool jelBitna();
	/*void dodajLinije(vector < Linija* > sveLinije);
	vector<int> vremenaLinije(Linija* autobus);*/

private:
	bool bitna;
};

