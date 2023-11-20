#pragma once
#include <exception>
using namespace std;

class LosiFajlovi:public exception
{
public:
	LosiFajlovi() : exception("Ne postoje fajlovi sa datim imenom") {}
	LosiFajlovi(const char* s ): exception(s){}

};

