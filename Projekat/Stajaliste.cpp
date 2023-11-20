#include "Stajaliste.h"

Stajaliste::Stajaliste(string podaci)
{
	if (podaci[size(podaci)-1]==']' && podaci[size(podaci) - 2] == '!' && podaci[size(podaci) - 3] == '[')
	{
		bitna = true;
		int i = 0;
		string x = "";
		while (podaci[i] != ' ')
		{
			x += podaci[i];
			i++;
		}
		this->sifra = stoi(x);
		string z = "";
		for (i; i < size(podaci) - 4; i++)
		{
			z += podaci[i];
		}
		this->ime = z;
	}
	else
	{
		bitna = false;
		int i = 0;
		string x = "";
		while (podaci[i] != ' ')
		{
			x += podaci[i];
			i++;
		}
		this->sifra = stoi(x);
		string z = "";
		for (i; i < size(podaci); i++)
		{
			z += podaci[i];
		}
		this->ime = z;
	}
	
}

bool Stajaliste::jelBitna()
{
	return bitna;
}

/*void Stajaliste::dodajLinije(vector<Linija*> sveLinije)
{
	
	for (int i = 0; i < size(sveLinije); i++)
	{
		for (int j = 0; j < size(sveLinije[i]->stajalista); j++)
		{
			if (sveLinije[i]->stajalista[j] == sifra)
			{
				linije.push_back(sveLinije[i]->ime);
				brojStajalista.push_back(i);
			}
		}
	}
}

vector<int> Stajaliste::vremenaLinije(Linija* autobus)
{
	vector<int> redVoznje;
	int a;
	for (size_t i = 0; i < size(linije); i++)
	{
		if (linije[i] == autobus->ime)
		{
			a = brojStajalista[i];
			break;
		}
	}
	for (int j = 0; j < size(autobus->vremenaKretanja); j++)
	{
		redVoznje.push_back(a * 3 + autobus->vremenaKretanja[j]);
	}
	return redVoznje;
}*/
