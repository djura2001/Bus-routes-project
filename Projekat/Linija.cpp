#include "Linija.h"

Linija::Linija(string podaci)
{
	string z = "";
	int i = 0;
	while (podaci[i] != ' ')
	{
		z += podaci[i];
		i++;
	}
	this->ime = z;
	i++;
	/*i += 2;
	string x = "";
	while (podaci[i] != '-')
	{
		x += podaci[i];
		i++;
	}
	this->prvoVremeKretanja = x;
	i++;
	string y = "";
	while (podaci[i] != '#')
	{
		y += podaci[i];
		i++;
	}
	i++;
	this->poslednjeVremeKretanja = y;
	*/
	
	string d = "";
	while (podaci[i])
	{
		d += podaci[i];
		i++;
	}
	//i += 2;
	//this->razmak = stoi(d);
	//string c = "";
	/*while (i < size(podaci))
	{
		c += podaci[i];
		i++;
	}*/
	d += ' ';
	string token1; // define a string variable  
	int pos = 0;
	char delim = ' ';
	vector<string> aa;
	while ((pos = d.find(delim)) != std::string::npos)
	{
		token1 = d.substr(0, pos);
		aa.push_back(token1);
		d.erase(0, pos + 1);
	}
	for (int i = 0; i < size(aa); i++)
	{
		stajalista.push_back(stoi(aa[i]));
	}
	for (int j = size(stajalista) - 1; j >=0; j--)
	{
		stajalistaDrugiSmer.push_back(stajalista[j]);
	}
	/*
	int j = 0;
	int prviSat, prviMin, drugiSat, drugiMin;
	string ps = "";
	string pm = "";
	string ds = "";
	string dm = "";
	while (prvoVremeKretanja[j] != ':')
	{
		ps += prvoVremeKretanja[j];
		j++;

	}
	j++;
	prviSat = stoi(ps);
	while (j < size(prvoVremeKretanja))
	{
		pm += prvoVremeKretanja[j];
		j++;

	}
	prviMin = stoi(pm);
	int k = 0;
	while (poslednjeVremeKretanja[k] != ':')
	{
		ds += poslednjeVremeKretanja[k];
		k++;

	}
	k++;
	drugiSat = stoi(ds);
	while (k < size(poslednjeVremeKretanja))
	{
		dm += poslednjeVremeKretanja[k];
		k++;

	}
	drugiMin = stoi(dm);

	int prvoKretanje = prviSat * 60 + prviMin;
	int posldenjeKretanje = drugiSat * 60 + drugiMin;
	int m = 1;
	vremenaKretanja.push_back(prvoKretanje);
	while (vremenaKretanja[m-1] < posldenjeKretanje)
	{
		vremenaKretanja.push_back(prvoKretanje + m * razmak);
		m++;
	}
	if (posldenjeKretanje != vremenaKretanja[size(vremenaKretanja) - 1]) vremenaKretanja.push_back(posldenjeKretanje);*/
}

bool Linija::direktnoPovezane(int sifra1, int sifra2)
{
	int id1 = vratiStajaliste(sifra1);
	int id2 = vratiStajaliste(sifra2);
	return abs(id1 - id2) == 1;
}

int Linija::vratiStajaliste(int sifra)
{
	for (int i = 0; i < size(stajalista); i++)
	{
		if (stajalista[i] == sifra) return i;
	}
	return -1;
}

/*void Linija::nadjiImenaStajalista(vector<Stajaliste*> svaStajalista)
{
	for (int i = 0; i < size(stajalista); i++)
	{
		for (int j = 0; j < size(svaStajalista); j++)
		{
			if (svaStajalista[j]->sifra == stajalista[i])
			{
				imenaStajalista.push_back(svaStajalista[j]->ime);
			}
		}
	}
}*/
