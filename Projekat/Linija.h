#pragma once
#include <vector>
#include <string>
#include "Stajaliste.h"
using namespace std;
class Linija
{
public:
	
	string ime; //prvoVremeKretanja, poslednjeVremeKretanja;
	int razmak; 
	vector<int> stajalista;
	vector<int> stajalistaDrugiSmer;
	vector<string> imenaStajalista;
	//vector<int> vremenaKretanja;
	Linija();
	Linija(string podaci);
	/*void nadjiImenaStajalista(vector< Stajaliste* > svaStajalista);*/
	bool direktnoPovezane(int sifra1, int sifra2);
	

	

private:
	int vratiStajaliste(int sifra);

};

