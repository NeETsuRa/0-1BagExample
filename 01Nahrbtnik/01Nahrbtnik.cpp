// 01Nahrbtnik.cpp : Defines the entry point for the console application.
//
/* Karmen Unuk
OA_N0000819_sklop3_naloga1: 0/1 nahrbtnik */

/* Napišite program, ki reši problem preprostega in 0/1 nahrbtnika. */


#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
using namespace std;

class CPredmet
{
public:
	CPredmet(int aV, int aC);
	~CPredmet(void);
	int volumen;
	int cena;
	float frek;
};

class CNahrbtnik
{
public:
	CNahrbtnik(int aN, int aVo);
	~CNahrbtnik(void);
	int Volumen;
	int n;
	vector<CPredmet*> predmeti;
	void NapPred(CPredmet* aP);
	vector<int> polniNahrbtnik;
	void Napolni(int &aVs);
	void VstaviPredmet(CPredmet* aP);
	void IzpisPredmetov();
	void IzpisNapNahrbtnika();
	void IzpisFrekvenc();
};

CPredmet::CPredmet(int aV, int aC)
{
	volumen = aV;
	cena = aC;
	frek = (float)(aC/aV);
}

CPredmet::~CPredmet(void)
{
}

CNahrbtnik::CNahrbtnik(int aN, int aVo)
{
	Volumen = aVo;
	n = aN;
	vector<CPredmet*> predmeti;
	vector<int>	polniNahrbtnik;
}

CNahrbtnik::~CNahrbtnik(void)
{
}
void CNahrbtnik:: Napolni(int &aVs)
{
	int prostor = Volumen;
	for(int i = 0; i< predmeti.size(); i++){
		if(prostor >= predmeti.at(i)->volumen){
			polniNahrbtnik.push_back(1);
			aVs = aVs + predmeti.at(i)->volumen;
			prostor = prostor - (predmeti.at(i)->volumen);
		}else{
			polniNahrbtnik.push_back(0);
		}
	}
}
void CNahrbtnik::VstaviPredmet(CPredmet* aP)
{
	predmeti.push_back(aP);
}
void CNahrbtnik::NapPred(CPredmet* aP)
{
	VstaviPredmet(aP);
	int j = 0;
	while(j < predmeti.size()){
		int i = predmeti.size()-1;
		while(i>j){
			if(predmeti.at(i)->frek > predmeti.at(i-1)->frek){
				CPredmet* aK = predmeti.at(i);
				predmeti.at(i) = predmeti.at(i-1);
				predmeti.at(i-1) = aK;
			}else{
				if(predmeti.at(i)->frek == predmeti.at(i-1)->frek){
					if(predmeti.at(i)->volumen > predmeti.at(i-1)->volumen){
						CPredmet* aK = predmeti.at(i);
						predmeti.at(i) = predmeti.at(i-1);
						predmeti.at(i-1) = aK;
					}
				}
			}
			i--;
		}
		j++;
	}
}

void CNahrbtnik:: IzpisPredmetov()
{
	for(int j = 0; j< predmeti.size(); j++){
		cout << j << ". predmet ";
		cout <<"V "<<  predmeti.at(j)->volumen << ' ';
		cout <<"C "<< predmeti.at(j)->cena << ' '; 
		cout << endl;
	}
}
void CNahrbtnik::IzpisNapNahrbtnika()
{
	for(int k = 0; k< polniNahrbtnik.size(); k++){
		cout << polniNahrbtnik.at(k) << " ";
	}
}

void CNahrbtnik:: IzpisFrekvenc()
{
	for(int i = 0; i< predmeti.size(); i++){
		cout << i << ". predmet " << predmeti.at(i)->frek << endl;	
	}
}


CNahrbtnik* Izpisi (char* ime){
 ifstream dat(ime);
 int aS;
 int aVO;
 int aV;
 int aC;
 if (dat.is_open()){
	dat>>aS;
	dat>>aVO;
	cout << "Stevilo elementov: " << aS << endl;
	cout << "Volumen nahrbtnika: " << aVO << endl;
	cout << endl;
	CNahrbtnik* nahr = new CNahrbtnik(aS,aVO);
	if (dat.good()){
	 for(int i = 0; i< aS; i++){
		 cout << "predmet(cena volumen)" << endl;
		 cout << i <<". ";
			dat>>aC;
		    dat>>aV;
			cout << aC << " " << aV << endl;
 			CPredmet* p = new CPredmet(aV, aC);
			nahr->NapPred(p);
	 }
	}
	dat.close();
	return nahr;
 }
 else 
	 cout<<"Napaka pri odpiranju datoteke!";
}
vector<CNahrbtnik*> Izpisi1 (char* ime){
 ifstream dat(ime);
 if (dat.is_open()){
	 int aS;
	 int aVO;
	 int aV;
	 int aC;
	 vector<CNahrbtnik*> aNa;
	while(!dat.eof()){
		dat>>aS;
		dat>>aVO;
		cout << "Stevilo elementov: " << aS << endl;
		cout << "Volumen nahrbtnika: " << aVO << endl;
		cout << endl;
		CNahrbtnik* nahr = new CNahrbtnik(aS,aVO);
		if (dat.good()){
		 for(int i = 0; i< aS; i++){
			 cout << "predmet(cena volumen)" << endl;
			 cout << i <<". ";
				dat>>aC;
			    dat>>aV;
				cout << aC << " " << aV << endl;
 				CPredmet* p = new CPredmet(aV, aC);
				nahr->NapPred(p);
		 }
		 aNa.push_back(nahr);
		}	
	}
		dat.close();
	return aNa;
 }
 else	
	 cout<<"Napaka pri odpiranju datoteke!";
}



int _tmain(int argc, _TCHAR* argv[])
{
/*
	cout << "Vnesi Volumen Nahrbtnika: ";
	int V;
	int st;
	cin >> V;
	cout << "Vnesi stevilo elementov, med katerimi lahko izbiramo: ";
	cin >> st;

	CNahrbtnik* nahr = new CNahrbtnik(st, V);
	for(int i = 0; i< st; i++){
		int vo;
		cout << "volumen " << i << "-tega predmeta: ";
		cin >> vo;
		int ce;
		cout << "cena " << i << "-tega predmeta: ";
		cin >> ce;
		CPredmet* p = new CPredmet(vo, ce);
		nahr->NapPred(p);
		nahr->Napolni(vo);
		nahr->IzpisFrekvenc();
		nahr->IzpisNapNahrbtnika();
		cout << endl;
		nahr->IzpisPredmetov();
		cout<< endl << "Nahrbtnik je napolnjen z volumnom :" << vo;
		cout << endl;
	}*/


	cout<<"IZ DATOTEKE:"<<endl<<endl;
	//prvi izpis
	CNahrbtnik* N = Izpisi("N.txt");
	int vs = 0;
	N->Napolni(vs);
	N->IzpisFrekvenc();
	N->IzpisNapNahrbtnika();
	cout << endl;
	N->IzpisPredmetov();

	cout<< endl << "Nahrbtnik je napolnjen z volumnom :" << vs;
	cout << endl;
	cout << endl;
	cout << endl;
	//drugi izpis, ko tvoriš vektor CNahrbtnikov, da prebereš celotno datoteko
	cout << "CELOTNA DATOTEKA: " << endl << endl;
	vector<CNahrbtnik*> DatNah = Izpisi1("N.txt");
	for(int k = 0; k< DatNah.size(); k++){
		int vs = 0;
		DatNah.at(k)->Napolni(vs);
		cout << "Volumen nahrbtnika: " << DatNah.at(k)->Volumen <<endl;
		cout << "Vektor frekvenc: "<< endl;
		DatNah.at(k)->IzpisFrekvenc();
		cout << "Napolnjen nahrbtnik: ";
		DatNah.at(k)->IzpisNapNahrbtnika();
		cout << endl;
		DatNah.at(k)->IzpisPredmetov();
		cout<< "Nahrbtnik je napolnjen z volumnom :" << vs;
		cout << endl;
		cout << endl;
	}

	
	cin.ignore();
	cin.get();

	return 0;
}


