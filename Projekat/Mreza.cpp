#include "Mreza.h"

Mreza::Mreza(const string& staniceTxt, const string& linijeTxt)
{
	ifstream staniceFajl;
	ifstream linijeFajl;
	string tekst1, tekst2;
	staniceFajl.open(staniceTxt);
	linijeFajl.open(linijeTxt);
	while (getline(staniceFajl, tekst1))
	{
		Stajaliste* stanica = new Stajaliste(tekst1);
		stajalista.push_back(stanica);
	}
	while (getline(linijeFajl, tekst2))
	{
		Linija* bus = new Linija(tekst2);
		linije.push_back(bus);
	}
	this->brojStajalista = size(stajalista);
	staniceFajl.close();
	linijeFajl.close();
	linijeStajalistima();
	imenaStajalistaLinijama();


}

Mreza::Mreza()
{
}

void Mreza::ucitajFajlove(const string& staniceTxt, const string& linijeTxt)
{
	ifstream staniceFajl;
	ifstream linijeFajl;
	string tekst1, tekst2;
	staniceFajl.open(staniceTxt);
	linijeFajl.open(linijeTxt);
	while (getline(staniceFajl, tekst1))
	{
		Stajaliste* stanica = new Stajaliste(tekst1);
		stajalista.push_back(stanica);
	}
	while (getline(linijeFajl, tekst2))
	{
		Linija* bus = new Linija(tekst2);
		linije.push_back(bus);
	}
	this->brojStajalista = size(stajalista);
	staniceFajl.close();
	linijeFajl.close();
	linijeStajalistima();
	imenaStajalistaLinijama();
}

void Mreza::linijeStajalistima()
{
	for ( int k = 0; k <size(stajalista); k++)
	{
		for (int i = 0; i < size(linije); i++)
		{
			for (int j = 0; j < size(linije[i]->stajalista); j++)
			{
				if (linije[i]->stajalista[j] == stajalista[k]->sifra)
				{
					stajalista[k]->linije.push_back(linije[i]->ime); //napravi dodajLiniju zbog enkapsulacije
					stajalista[k]->brojStajalista.push_back(j+1);
					stajalista[k]->brojStajalistaDrugiSmer.push_back(size(linije[i]->stajalista)-j);
				}
			}
		}
	}

}

void Mreza::imenaStajalistaLinijama()
{
	for (int k = 0; k < size(linije); k++)
	{
		for (int i = 0; i < size(linije[k]->stajalista); i++)
		{
			for (int j = 0; j < size(stajalista); j++)
			{
				if (stajalista[j]->sifra == linije[k]->stajalista[i])
				{
					linije[k]->imenaStajalista.push_back(stajalista[j]->ime); //napravi dodajStajaliste zbog enksapsulacije
				}
			}
		}
	}
}
void Mreza::stajalisteInfo(int sifra)
{
	string ime = "stajaliste_";
	string x = to_string(sifra);
	ime += x;
	ofstream fajlStanica(ime);
	for (int i = 0; i < size(stajalista); i++)
	{
		if (sifra == stajalista[i]->sifra)
		{
			fajlStanica << stajalista[i]->sifra << " " << stajalista[i]->ime << " " << "[";
			for (int j = 0; j < size(stajalista[i]->linije); j++)
			{
				fajlStanica << stajalista[i]->linije[j] << " ";
			}
			fajlStanica << "]" << " ";
			vector<int> susedi = bitniSusedi(stajalista[i]);
			if (size(susedi)>0)
			{
				fajlStanica << "{!" << " ";
				for (size_t i = 0; i < size(susedi); i++)
				{
					fajlStanica << susedi[i] << " ";
				}
				fajlStanica << "!}";
			}
		}
		
	}
	fajlStanica.close();
}

void Mreza::linijaInfo(string ime)
{
	string fajl = "linija_";
	fajl += ime;
	ofstream fajlLinija(fajl);
	
	for (int i = 0; i < size(linije); i++)
	{
		if (ime == linije[i]->ime)
		{
			fajlLinija << ime << " " << linije[i]->imenaStajalista[0] << "->" << linije[i]->imenaStajalista[size(linije[i]->imenaStajalista)-1]<<'\n';
			for (int j = 0; j < size(linije[i]->stajalista); j++)
			{
				fajlLinija << linije[i]->stajalista[j] << " " << nadjiStanicu(linije[i]->stajalista[j])->ime;
				if (nadjiStanicu(linije[i]->stajalista[j])->jelBitna())
				{
					fajlLinija << " [!]";
				}
				fajlLinija << '\n';
			}
		}
		
	}
	

	fajlLinija.close();
}

/*void Mreza::linijaStatistika(string ime)
{
	string fajl = "statistika_";
	fajl += ime;
	ofstream fajlStatistika(fajl);
	fajlStatistika << ime << "\n";
	vector<string> zajednicke;
	Linija* ova = nadjiLiniju(ime);
	for (int i = 0; i < size(linije); i++)
	{
		for (int j = 0; j < size(ova->stajalista); j++)
		{
			for (int k = 0; k < size(linije[i]->stajalista); k++)
			{
				if (ova->stajalista[j] == linije[i]->stajalista[k] && linije[i]!=ova)
				{
					zajednicke.push_back(linije[i]->ime);
					break;
				}
			}
		}
	}
	fajlStatistika << zajednicke[0] << " ";
	for (int i = 1; i < size(zajednicke); i++)
	{
		if (zajednicke[i-1]!=zajednicke[i])
		{
			fajlStatistika << zajednicke[i] << " ";
		}
	}
	fajlStatistika << "\n";
	//fajlStatistika << size(ova->vremenaKretanja);
}*/

/*void Mreza::postaviVreme(string vreme)
{
	int i = 0;
	string s = "";
	while (vreme[i] != ':') 
	{
		s += vreme[i];
		i++;
	}
	i++;
	int sat = stoi(s);	
	string m = "";
	while (i<size(vreme))
	{
		m += vreme[i];
		i++;
	}
	int minut = stoi(m);
	trenutnoVreme = 60 * sat + minut;
}*/




vector<vector<int>> Mreza::praviGraf()
{
	
	vector<vector<int>> graf;
	
	for (int i = 0; i < brojStajalista; i++)
	{
		
		vector<int> v;
		for (int j = 0; j < brojStajalista; j++)
		{
			if (povezanaStajalista(stajalista[i], stajalista[j]))
			{
				v.push_back(1);
			}
			else
			{
				v.push_back(0);
			}
		}
		graf.push_back(v);
		v.clear();
	}
	return graf;
}

vector<vector<int>> Mreza::praviPresedanjaGraf()
{
	vector<vector<int>> graf;
	for (int i = 0; i < brojStajalista; i++)
	{

		vector<int> v;
		for (int j = 0; j < brojStajalista; j++)
		{
			if (povezanaStajalista2(stajalista[i], stajalista[j]))
			{
				v.push_back(1);
			}
			else
			{
				v.push_back(0);
			}
		}
		graf.push_back(v);
		v.clear();
	}
	return graf;
}

void Mreza::sveBitne(int prvaSifra, int poslednjaSifra)
{
	roditelj.clear();
	int prva = redniStajalista(nadjiStanicu(prvaSifra));
	int poslednja = redniStajalista(nadjiStanicu(poslednjaSifra));

	
	
	
	vector<int> bitna;
	for (int i = 0; i < size(stajalista); i++)
	{
		if (stajalista[i]->jelBitna())
		{
			bitna.push_back(i);
		}
	}
	
	
	
	
	
	
	
	stack<int> putanja;
	vector<int> ruta;
	int start = prva;
	for (int i = 0; i < size(bitna); i++)
	{
		/*putanja.push(poslednja);
		int j = bitna[i];
		while (roditelj[j] != start)
		{
			putanja.push(roditelj[i]);
			j = roditelj[j];
		}
		putanja.push(start);
		start = bitna[i];*/
		for (int j = 0; j < size(najmanjePresedanjaRuta(start, bitna[i])); j++)
		{
			ruta.push_back(najmanjePresedanjaRuta(start, bitna[i])[j]);
		}
		//najmanjePresedanja(stajalista[start]->sifra, stajalista[bitna[i]]->sifra);
		start = bitna[i];
	}
	for (int j = 0; j < size(najmanjePresedanjaRuta(start, poslednja)); j++)
	{
		ruta.push_back(najmanjePresedanjaRuta(start, poslednja)[j]);
	}
	ruta.push_back(stajalista[poslednja]->sifra);
	string imeFajla = "putanja_";
	imeFajla += to_string(prvaSifra);
	imeFajla += "_";
	imeFajla += to_string(poslednjaSifra);
	ofstream fajl(imeFajla);
	vector<int> r;
	for (int i = 1; i < size(ruta); i++)
	{
		if (ruta[i] != ruta[i - 1]) r.push_back(ruta[i - 1]);
	}
	r.push_back(ruta[size(ruta) - 1]);
	vector<string> linije;
	for (int i = 1; i < size(r); i++)
	{
		linije.push_back(linijaVeze(nadjiStanicu(r[i - 1]), nadjiStanicu(r[i])));
	}
	string l = linije[0];
	fajl << "->" << l << '\n';
	fajl << r[0];
	for (int i = 0; i < size(linije); i++)
	{
		if (l == linije[i]) 
		{
			fajl << "->" << r[i+1];
		}
		else
		{
			fajl << '\n';
			fajl << l << "->" << linije[i] << '\n';
			fajl << r[i] << "->" << r[i + 1];
			l = linije[i];
		}

	}
	fajl.close();
	

}




bool Mreza::povezanaStajalista(Stajaliste* stajaliste1, Stajaliste* stajaliste2)
{
	bool povezane = false;
	for (int i = 0; i < size(stajaliste1->linije); i++)
	{
		for (int j = 0; j < size(stajaliste2->linije); j++)
		{
			if (stajaliste1->linije[i] == stajaliste2->linije[j] &&  abs(stajaliste1->brojStajalista[i] - stajaliste2->brojStajalista[j]) == 1)
			{
				povezane = true;
			}
		}
	}
	return povezane;
}
bool Mreza::povezanaStajalista2(Stajaliste* stajaliste1, Stajaliste* stajaliste2)
{
	//bool povezane = false;
	for (int i = 0; i < size(stajaliste1->linije); i++)
	{
		for (int j = 0; j < size(stajaliste2->linije); j++)
		{
			if (stajaliste1->linije[i] == stajaliste2->linije[j])
			{
				return true;
			}
		}
	}
	return false;
}
int Mreza::udaljenost(Stajaliste* stajaliste1, Stajaliste* stajaliste2)
{
	for (int i = 0; i < size(stajaliste1->linije); i++)
	{
		for (int j = 0; j < size(stajaliste2->linije); j++)
		{
			if (stajaliste1->linije[i] == stajaliste2->linije[j])
			{
				return stajaliste1->brojStajalista[i] - stajaliste2->brojStajalista[j];
			}
		}
	}
	return 0;
}
vector<int> Mreza::dodajNenulte(int i, vector<vector<int>> g)
{
	vector<int> v;
	for (int j = 0; j < size(g[i]); j++)
	{
		if (g[i][j]!=0 && i!=j)
		{
			v.push_back(j);
		}
	}
	return v;
}
vector<vector<int>> Mreza::sortirajApsolutne(vector<int> v1, vector<int> v2)
{
	vector<vector<int>> v;
	for (int i = 0; i < size(v1); i++)
	{
		for (int j = i+1; j < size(v1); j++)
		{
			if (abs(v1[j])<abs(v1[i]))
			{
				int x = v1[i];
				v1[i] = v1[j];
				v1[j] = x;
				int c = v2[i];
				v2[i] = v2[j];
				v2[j] = c;
			}
		}
	}
	v.push_back(v1);
	v.push_back(v2);
	return v;
}
vector<int> Mreza::direktanPut(Stajaliste* s1, Stajaliste* s2)
{
	vector<int> v;
	for (int i = 0; i < size(s1->linije); i++)
	{
		for (int j = 0; j < size(s2->linije); j++)
		{
			if (s1->linije[i] == s2->linije[j])
			{
				if (s1->brojStajalista[i] < s2->brojStajalista[j])
				{
					Linija* l = nadjiLiniju(s1->linije[i]);
					for (int k = s1->brojStajalista[i] - 1; k < s2->brojStajalista[j]; k++)
					{
						v.push_back(l->stajalista[k]);
					}
					return v;
				}
				else
				{
					Linija* l = nadjiLiniju(s1->linije[i]);
					for (int k = s1->brojStajalistaDrugiSmer[i] - 1; k < s2->brojStajalistaDrugiSmer[j]; k++)
					{
						v.push_back(l->stajalistaDrugiSmer[k]);
					}
					return v;
				}
				
			}
		}
	}
	
	
}
string Mreza::linijaVeze(Stajaliste* s1, Stajaliste* s2)
{
	for (int i = 0; i < size(s1->linije); i++)
	{
		for (int j = 0; j < size(s2->linije); j++)
		{
			if (s1->linije[i] == s2->linije[j])
			{
				return s1->linije[i];
			}
		}
	}
}
vector<Linija*> Mreza::zajdenickeLinije(Stajaliste* stajaliste1, Stajaliste* stajaliste2)
{
	vector<Linija*> v;
	for (int i = 0; i < size(stajaliste1->linije); i++)
	{
		for (int j = 0; j < size(stajaliste2->linije); j++)
		{
			if (stajaliste1->linije[i] == stajaliste2->linije[j])
			{
				Linija* l = nadjiLiniju(stajaliste1->linije[i]);
				if (l->direktnoPovezane(stajaliste1->sifra, stajaliste2->sifra)) {
					v.push_back(nadjiLiniju(stajaliste1->linije[i]));
				}
			}
		}
	}
	return v;
}
Linija* Mreza::nadjiLiniju(string ime)
{
	for (int i = 0; i < size(linije); i++)
	{
		if (linije[i]->ime == ime) return linije[i];
	}
}

Stajaliste* Mreza::nadjiStanicu(int sifra)
{
	for (int i = 0; i < size(stajalista); i++)
	{
		if (stajalista[i]->sifra == sifra) return stajalista[i];
	}
}

/*int Mreza::prviDolazak(vector<int> vremena)
{
	int i = 0;
	while (vremena[i] < trenutnoVreme) i++;
	return vremena[i];
}*/

int Mreza::minimum(vector<int> x)
{
	int min = x[0];
	for (int i = 0; i < size(x); i++)
	{
		if (x[i] < min) min = x[i];
	}
	return min;
}

int Mreza::minIndex(vector<int> x)
{
	int min = x[0];
	int id = 0;
	for (int i = 0; i < size(x); i++)
	{
		if (x[i] < min) 
		{
			min = x[i];
			id = i;
		}
	}
	return id;
}

int Mreza::redniStajalista(Stajaliste* s)
{
	for (int i = 0; i < size(stajalista); i++)
	{
		if (stajalista[i] == s) return i;
	}
	return -1;
}

int Mreza::dajBrojStajalista(Stajaliste* stajaliste, Linija* linija)
{
	for (int i = 0; i < size(linija->stajalista); i++)
	{
		if (stajaliste->sifra == linija->stajalista[i]) return i ;
	}
}

int Mreza::dajBrojStajalistaDrugiSmer(Stajaliste* stajaliste, Linija* linija)
{
	for (int i = 0; i < size(linija->stajalistaDrugiSmer); i++)
	{
		if (stajaliste->sifra == linija->stajalistaDrugiSmer[i]) return i ;
	}
}

int Mreza::vremeCekanja(Stajaliste* stajaliste1, Stajaliste* stajaliste2)
{
	vector<Linija*> zajednicke = zajdenickeLinije(stajaliste1, stajaliste2);
	vector<int> v;
	vector<int> a;
	vector<int> v1;
	for (int i = 0; i < size(zajednicke); i++)
	{
		v.push_back(dajBrojStajalista(stajaliste1, zajednicke[i]));
	}
	for (int l = 0; l < size(zajednicke); l++)
	{
		a.push_back(dajBrojStajalista(stajaliste2, zajednicke[l]));
	}
	for (int i = 0; i < size(zajednicke); i++)
	{
		v1.push_back(dajBrojStajalistaDrugiSmer(stajaliste1, zajednicke[i]));
	}
	vector<int> vremenaPristizanja;
	/*for (int k = 0; k <size(zajednicke); k++)
	{
		if (v[k]<a[k])
		{
			int j = 0;
			while (zajednicke[k]->vremenaKretanja[j] + v[k] * 3 < vremeStanice[stanica(stajaliste1->sifra)])
			{
				j++;
			}
			vremenaPristizanja.push_back(zajednicke[k]->vremenaKretanja[j] + v[k] * 3 - vremeStanice[stanica(stajaliste1->sifra)]);
		}
		else
		{
			int j = 0;
			while (zajednicke[k]->vremenaKretanja[j] + v1[k] * 3 < vremeStanice[stanica(stajaliste1->sifra)])
			{
				j++;
			}
			vremenaPristizanja.push_back(zajednicke[k]->vremenaKretanja[j] + v1[k] * 3 - vremeStanice[stanica(stajaliste1->sifra)]);
		}
	}*/
	return minimum(vremenaPristizanja);
	
}

string Mreza::najkracaLinija(int sifra1, int sifra2)
{
	Stajaliste* stajaliste1 = nadjiStanicu(sifra1);
	Stajaliste* stajaliste2 = nadjiStanicu(sifra2);
	vector<Linija*> zajednicke = zajdenickeLinije(stajaliste1, stajaliste2);
	vector<int> v;
	vector<int> a;
	vector<int> v1;
	for (int i = 0; i < size(zajednicke); i++)
	{
		v.push_back(dajBrojStajalista(stajaliste1, zajednicke[i]));
	}
	for (int l = 0; l < size(zajednicke); l++)
	{
		a.push_back(dajBrojStajalista(stajaliste2, zajednicke[l]));
	}
	for (int i = 0; i < size(zajednicke); i++)
	{
		v1.push_back(dajBrojStajalistaDrugiSmer(stajaliste1, zajednicke[i]));
	}
	vector<int> vremenaPristizanja;
	/*for (int k = 0; k < size(zajednicke); k++)
	{
		if (v[k] < a[k])
		{
			int j = 0;
			while (zajednicke[k]->vremenaKretanja[j] + v[k] * 3 < vremeStanice[stanica(stajaliste1->sifra)])
			{
				j++;
			}
			vremenaPristizanja.push_back(zajednicke[k]->vremenaKretanja[j] + v[k] * 3 - vremeStanice[stanica(stajaliste1->sifra)]);
		}
		else
		{
			int j = 0;
			while (zajednicke[k]->vremenaKretanja[j] + v1[k] * 3 < vremeStanice[stanica(stajaliste1->sifra)])
			{
				j++;
			}
			vremenaPristizanja.push_back(zajednicke[k]->vremenaKretanja[j] + v1[k] * 3 - vremeStanice[stanica(stajaliste1->sifra)]);
		}
	}
	*/
	int x = minIndex(vremenaPristizanja);
	return zajednicke[x]->ime;

}

vector<int> Mreza::bitniSusedi(Stajaliste* s)
{
	vector<vector<int>> graf = praviGraf();
	int i = redniStajalista(s);
	vector<int> susedi;
	for (int j = 0; j < size(stajalista); j++)
	{
		if (graf[i][j] && stajalista[j]->jelBitna()) susedi.push_back(stajalista[j]->sifra);
	}
	return susedi;
}

int Mreza::stanica(int sifra)
{
	for (int i = 0; i < brojStajalista; i++)
	{
		if (stajalista[i]->sifra == sifra) return i;
	}

}

void Mreza::inicijalizacija()
{
	roditelj.clear();
	for (int i = 0; i < brojStajalista; i++)
	{
		dist.push_back(9999);
		prosao.push_back(false);
		vremeStanice.push_back(2000);
		roditelj.push_back(i);
	}
	dist[stanica(pocetak)] = 0;
	vremeStanice[stanica(pocetak)] = trenutnoVreme;
}

int Mreza::najbliza()
{
	int minnode = 0;
	int min = 10000;
	for (int i = 0; i < brojStajalista; i++)
	{
		if (prosao[i] == false && dist[i]<min)
		{
			min = dist[i];
			minnode = i;
		}
	}
	return minnode;
}

void Mreza::djikstra()
{
	vector<vector<int>> graf = praviGraf();
	for (int i = 0; i < brojStajalista; i++)
	{
		int najblizi = najbliza();
		prosao[najblizi] = true;
		for (int adj = 0; adj < brojStajalista; adj++)
		{
			if (graf[najblizi][adj] && dist[adj] > dist[najblizi] + graf[najblizi][adj]) //vremecekanja->graf
			{
				/*vremeStanice[najblizi] += vremeCekanja(stajalista[najblizi], stajalista[adj]);*/
				dist[adj] = dist[najblizi] + graf[najblizi][adj];
				//vremeStanice[adj] = vremeStanice[najblizi] + vremeCekanja(stajalista[najblizi], stajalista[adj]) + 3;
				roditelj[adj] = najblizi;

			}
		}
	}
}

void Mreza::prikaziPut()
{
	int parnode = roditelj[stanica(kraj)];
	vector<int> ruta;
	vector<string> uzeteLinije;
	ruta.push_back(stajalista[stanica(kraj)]->sifra);

	cout << stajalista[stanica(kraj)]->sifra << "<-";
	
	while (parnode!=stanica(pocetak))
	{
		cout << stajalista[parnode]->sifra << "<-" ;
		ruta.push_back(stajalista[parnode]->sifra);
		parnode = roditelj[parnode];
	}
	ruta.push_back(pocetak);
	
	reverse(ruta.begin(), ruta.end());

	string imeFajla = "putanja_";
	imeFajla += to_string(pocetak);
	imeFajla += "_";
	imeFajla += to_string(kraj);

	ofstream fajl(imeFajla);
	cout << pocetak;
	cout << "\n";
	cout << vremeStanice[stanica(pocetak)] / 60 << ":" << vremeStanice[stanica(pocetak)] % 60 << "-" << vremeStanice[stanica(kraj)] / 60 << ":" << vremeStanice[stanica(kraj)] % 60;
	cout << "\n";
	for (int i = 0; i < size(ruta) - 1; i++)
	{
		uzeteLinije.push_back(najkracaLinija(ruta[i], ruta[i + 1]));
	}
	uzeteLinije.push_back(uzeteLinije[size(uzeteLinije) - 1]);
	cout << "->" << uzeteLinije[0];
	cout << "\n";
	cout << ruta[0] << " ";
	for (int i = 1; i < size(uzeteLinije); i++)
	{
		if (uzeteLinije[i-1] == uzeteLinije[i])
		{
			cout << ruta[i] << " ";
		}
		else
		{
			cout << ruta[i] << " ";
			cout << "\n";
			cout << uzeteLinije[i - 1] << "->" << uzeteLinije[i]<<"\n";
			cout << ruta[i] << " ";
		}
	}
	fajl << "->" << uzeteLinije[0];
	fajl << "\n";
	fajl << ruta[0] << " ";
	for (int i = 1; i < size(uzeteLinije); i++)
	{
		if (uzeteLinije[i - 1] == uzeteLinije[i])
		{
			fajl << ruta[i] << " ";
		}
		else
		{
			fajl << ruta[i] << " ";
			fajl << "\n";
			fajl << uzeteLinije[i - 1] << "->" << uzeteLinije[i] << "\n";
			fajl << ruta[i] << " ";
		}
	}

}

vector<int> Mreza::najmanjePresedanjaRuta(int prva, int poslednja)
{
	vector<int> obidjen;
	vector<int> obidjen2;
	vector<vector<int>> graf = praviPresedanjaGraf();
	for (int i = 0; i < size(stajalista); i++)
	{
		obidjen.push_back(0);
		roditelj.push_back(-1);
	}
	obidjen[prva] = 1;
	obidjen2 = obidjen;
	stack<int> stek;
	stek.push(prva);
	int brojac = 1;
	while (size(stek) < size(obidjen))
	{

		for (int i = 0; i < size(obidjen); i++)
		{
			//int prosli = -1;
			//sve do for-a na gore mozda u prvi if dole? 
			if (obidjen[i] == brojac)
			{
				vector<int> v1 = dodajNenulte(i, graf);
				vector<int> v2;
				for (int k = 0; k < size(v1); k++)
				{
					v2.push_back(udaljenost(stajalista[v1[k]], stajalista[i]));
				}
				vector<vector<int>> v = sortirajApsolutne(v2, v1);
				v2 = v[0];
				v1 = v[1];

				bool prviNeg = true;
				bool prviPoz = true;
				int prosliNeg = -1;
				int prosliPoz = -1;
				int j = 0;
				while (j < size(v1))//dodati drugi uslov tipa neobidjene //stajalista[i]->linije
				{
					if (obidjen[v1[j]] == 0)//sredi smerovegraf[i][j] && i!=j && 
					{
						/*if (prosli == -1 || (prviNeg && prviPoz))
						{



						}
						else
						{
							if (v2[j] < 0)
							{
							}
						}*/
						if (v2[j] < 0)
						{
							if (prviNeg)
							{
								roditelj[v1[j]] = i;
								prviNeg = false;
								prosliNeg = v1[j];
							}
							else
							{
								roditelj[v1[j]] = prosliNeg;
							}

						}
						else
						{
							if (prviPoz)
							{
								roditelj[v1[j]] = i;
								prviPoz = false;
								prosliPoz = v1[j];
							}
							else
							{
								roditelj[v1[j]] = prosliPoz;
							}
						}


						obidjen2[v1[j]] = brojac + 1;
						stek.push(j);
						j++;
						//prosli = j;
					}
					else
					{
						j++;
					}
				}
				//brojac++;
			}


		}
		obidjen = obidjen2;
		brojac++;

	}
	stack<int> putanja;
	putanja.push(poslednja);
	int i = poslednja;
	while (roditelj[i] != prva)
	{
		putanja.push(roditelj[i]);
		i = roditelj[i];
	}
	putanja.push(prva);
	
	vector<int> ruta;
	while (!putanja.empty())
	{
		int a = putanja.top();
		putanja.pop();
		ruta.push_back(a);
		//fajl << stajalista[a]->sifra << "->";
	}
	int j = 0;
	int presedanje = 0;
	int start = true;
	string prosla;
	vector<int> put;
	while (j < size(ruta))
	{
		if (povezanaStajalista2(stajalista[ruta[presedanje]], stajalista[ruta[j]]))
		{
			j++;
		}
		else
		{
			//vector<int> v = direktanPut(stajalista[ruta[presedanje]], stajalista[ruta[j-1]]);
			//string l = linijaVeze(stajalista[ruta[presedanje]], stajalista[ruta[j - 1]]);
			if (start)
			{
				vector<int> v = direktanPut(stajalista[ruta[presedanje]], stajalista[ruta[j - 1]]);
				string l = linijaVeze(stajalista[ruta[presedanje]], stajalista[ruta[j - 1]]);
				start = false;
				prosla = l;
				//fajl << "->" << l << '\n';
				put.push_back(v[0]);

				for (int i = 1; i < size(v); i++)
				{
					put.push_back(v[i]);
				}
				//fajl << '\n';
			}
			else
			{
				vector<int> v = direktanPut(stajalista[ruta[presedanje - 1]], stajalista[ruta[j - 1]]);
				string l = linijaVeze(stajalista[ruta[presedanje - 1]], stajalista[ruta[j - 1]]);
				//fajl << prosla << "->" << l << '\n';
				put.push_back(v[0]);

				for (int i = 1; i < size(v); i++)
				{
					put.push_back(v[i]);
				}
				//fajl << '\n';
			}
			presedanje = j;
			j++;
		}

	}
	if (start)
	{
		vector<int> v = direktanPut(stajalista[ruta[presedanje]], stajalista[ruta[size(ruta) - 1]]);
		string l = linijaVeze(stajalista[ruta[presedanje]], stajalista[ruta[size(ruta) - 1]]);
		start = false;
		prosla = l;
		//fajl << "->" << l << '\n';
		put.push_back(v[0]);

		for (int i = 1; i < size(v); i++)
		{
			put.push_back(v[i]);
		}
		//fajl << '\n';
	}
	else
	{
		vector<int> v = direktanPut(stajalista[ruta[presedanje - 1]], stajalista[ruta[size(ruta) - 1]]);
		string l = linijaVeze(stajalista[ruta[presedanje - 1]], stajalista[ruta[size(ruta) - 1]]);
		//fajl << prosla << "->" << l << '\n';
		put.push_back(v[0]);

		for (int i = 1; i < size(v); i++)
		{
			put.push_back(v[i]);
		}
		//fajl << '\n';
	}
	vector<int> putic;
	for (int i = 0; i < size(put) - 1; i++)
	{
		putic.push_back(put[i]);
	}
	return putic;
}

void Mreza::najbrziPut(int prva, int poslednja, string vreme)
{
	pocetak = prva;
	kraj = poslednja;
	//postaviVreme(vreme);
	inicijalizacija();
	djikstra();
	prikaziPut();
}

void Mreza::najmanjePresedanja(int prvaSifra, int poslednjaSifra)
{
	roditelj.clear();
	int prva = redniStajalista(nadjiStanicu(prvaSifra));
	int poslednja = redniStajalista(nadjiStanicu(poslednjaSifra));
	vector<int> obidjen;
	vector<int> obidjen2;
	vector<vector<int>> graf = praviPresedanjaGraf();
	for (int i = 0; i < size(stajalista); i++)
	{
		obidjen.push_back(0);
		roditelj.push_back(-1);
	}
	obidjen[prva] = 1;
	obidjen2 = obidjen;
	stack<int> stek;
	stek.push(prva);
	int brojac = 1;
	while (size(stek) < size(obidjen))
	{

		for (int i = 0; i < size(obidjen); i++)
		{
			//int prosli = -1;
			//sve do for-a na gore mozda u prvi if dole? 
			if (obidjen[i] == brojac)
			{
				vector<int> v1 = dodajNenulte(i, graf);
				vector<int> v2;
				for (int k = 0; k < size(v1); k++)
				{
					v2.push_back(udaljenost(stajalista[v1[k]], stajalista[i]));
				}
				vector<vector<int>> v = sortirajApsolutne(v2, v1);
				v2 = v[0];
				v1 = v[1];

				bool prviNeg = true;
				bool prviPoz = true;
				int prosliNeg = -1;
				int prosliPoz = -1;
				int j = 0;
				while (j < size(v1))//dodati drugi uslov tipa neobidjene //stajalista[i]->linije
				{
					if (obidjen[v1[j]] == 0)//sredi smerovegraf[i][j] && i!=j && 
					{
						/*if (prosli == -1 || (prviNeg && prviPoz))
						{



						}
						else
						{
							if (v2[j] < 0)
							{
							}
						}*/
						if (v2[j] < 0)
						{
							if (prviNeg)
							{
								roditelj[v1[j]] = i;
								prviNeg = false;
								prosliNeg = v1[j];
							}
							else
							{
								roditelj[v1[j]] = prosliNeg;
							}

						}
						else
						{
							if (prviPoz)
							{
								roditelj[v1[j]] = i;
								prviPoz = false;
								prosliPoz = v1[j];
							}
							else
							{
								roditelj[v1[j]] = prosliPoz;
							}
						}


						obidjen2[v1[j]] = brojac + 1;
						stek.push(j);
						j++;
						//prosli = j;
					}
					else
					{
						j++;
					}
				}
				//brojac++;
			}


		}
		obidjen = obidjen2;
		brojac++;
		
	}
	stack<int> putanja;
	putanja.push(poslednja);
	int i = poslednja;
	while (roditelj[i]!= prva)
	{
		putanja.push(roditelj[i]);
		i = roditelj[i];
	}
	putanja.push(prva);
	string imeFajla = "putanja_";
	imeFajla += to_string(prvaSifra);
	imeFajla += "_";
	imeFajla += to_string(poslednjaSifra);
	ofstream fajl(imeFajla);
	vector<int> ruta;
	while (!putanja.empty()) 
	{
		int a = putanja.top();
		putanja.pop();
		ruta.push_back(a);
		//fajl << stajalista[a]->sifra << "->";
	}
	int j = 0;
	int presedanje = 0;
	int start = true;
	string prosla;
	while (j < size(ruta))
	{
		if (povezanaStajalista2(stajalista[ruta[presedanje]],stajalista[ruta[j]]))
		{
			j++;
		}
		else
		{
			//vector<int> v = direktanPut(stajalista[ruta[presedanje]], stajalista[ruta[j-1]]);
			//string l = linijaVeze(stajalista[ruta[presedanje]], stajalista[ruta[j - 1]]);
			if (start) 
			{
				vector<int> v = direktanPut(stajalista[ruta[presedanje]], stajalista[ruta[j - 1]]);
				string l = linijaVeze(stajalista[ruta[presedanje]], stajalista[ruta[j - 1]]);
				start = false;
				prosla = l;
				fajl << "->" << l << '\n';
				fajl << v[0];
				
				for (int i = 1; i < size(v); i++)
				{
					fajl << "->" << v[i];
				}
				fajl << '\n';
			}
			else
			{
				vector<int> v = direktanPut(stajalista[ruta[presedanje - 1]], stajalista[ruta[j - 1]]);
				string l = linijaVeze(stajalista[ruta[presedanje - 1]], stajalista[ruta[j - 1]]);
				fajl << prosla << "->" << l << '\n';
				fajl << v[0];

				for (int i = 1; i < size(v); i++)
				{
					fajl << "->" << v[i];
				}
				fajl << '\n';
			}
			presedanje = j;
			j++;
		}
		
	}
	if (start)
	{
		vector<int> v = direktanPut(stajalista[ruta[presedanje]], stajalista[ruta[size(ruta) - 1]]);
		string l = linijaVeze(stajalista[ruta[presedanje]], stajalista[ruta[size(ruta) - 1]]); 
		start = false;
		prosla = l;
		fajl << "->" << l << '\n';
		fajl << v[0];

		for (int i = 1; i < size(v); i++)
		{
			fajl << "->" << v[i];
		}
		fajl << '\n';
	}
	else
	{
		vector<int> v = direktanPut(stajalista[ruta[presedanje - 1]], stajalista[ruta[size(ruta) - 1]]);
		string l = linijaVeze(stajalista[ruta[presedanje - 1]], stajalista[ruta[size(ruta) - 1]]);
		fajl << prosla << "->" << l << '\n';
		fajl << v[0];

		for (int i = 1; i < size(v); i++)
		{
			fajl << "->" << v[i];
		}
		fajl << '\n';
	}
	
	//fajl.close();
}

void Mreza::terminal()
{
	while (true)
	{
		cout << "0. EXIT" << '\n';
		cout << "1.FAJLOVI" << '\n';
		int input;
		cin >> input;
		switch (input)
		{
		case 0:
			return;
		case 1:
			cout << "Enter za podrazumevana stajalista ili unesi svoje" << '\n';
			string in, s, l;
			fgetc(stdin);
			//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			char temp = getchar();
			if (temp == '\n')
			{
				//ucitajFajlove("stajalista.txt","linije.txt");
				s = "stajalista.txt";
			}
			else
			{
				
				string in;
				cin >> in;
				s = temp + in;
			}
			cout << "Enter za podrazumevane linije ili unesi svoje" << '\n';
			fgetc(stdin);
			//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			char temp2 = getchar();
			if (temp2 == '\n')
			{
				l = "linije.txt";
			}
			else
			{
				
				string in;
				cin >> in;
				l = temp2 + in;

				
			}
			ucitajFajlove(s, l);
			while (true)
			{
				cout << "0.exit" << '\n';
				cout << "1.staniceinfo" << '\n';
				cout << "2.linijeinfo" << '\n';
				cout << "3.putanja" << '\n';
				int i;
				cin >> i;
				if (i == 0)
				{
					return;
				}
				else if (i == 1)
				{
					int sifra;
					cin >> sifra;
					stajalisteInfo(sifra);
				}
				else if (i == 2)
				{
					string linija;
					cin >> linija;
					linijaInfo(linija);
				}
				else if (i == 3)
				{
					int s1, s2;
					cin >> s1;
					cin >> s2;
					najmanjePresedanja(s1, s2);
					//sveBitne(s1, s2);
				}
			}
			
		}
	}
}

