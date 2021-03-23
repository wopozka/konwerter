
 /***************************************************************************
 *                                                                          * 
 *   Copyright (C) 2005 Piotr Wawrzyniak (piti@eliksir.ch.pw.edu.pl)        *
 *   This program is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation; either version 2 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 ***************************************************************************/

/*procedury zamieniaj�ce pliki eps z numerami na etykiety*/

#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include"czyt_zapis.h"
#include<stdio.h>
#include"dl_wiersza.h"
#include<unistd.h>
#include"num_na_etyk.h"
using namespace std;

int przeszukaj_linie_eps(char*,char*,int&);
extern int language;




int num_na_etyk(char*nazwa_pliku)
{
  //cout<<"Otwieram plik eps do czytania "<<endl;
  ifstream plik_eps(nazwa_pliku);
  if(!plik_eps)
    { 
      if(language==0)
	{
	  cout<<"Nie uda�o si� otworzy� pliku "<<nazwa_pliku<<" do czytania. "<<endl<<"Sprawd� prawa."<<endl;
	}
      else
	{
	  cout<<"Couldn't open "<<nazwa_pliku<<" file for reading. Check permissions."<<endl;
	}
      return 1;
    }
  //char nazwatymcz[L_tmpnam];
  //char *nazwa_eps_tymcz;
 char nazwa_eps_tymcz[]="konwXXXXXX";
  //nazwa_eps_tymcz=tmpnam(nazwatymcz);
  mkstemp(nazwa_eps_tymcz);
  ofstream plik_tymcz_eps(nazwa_eps_tymcz);
  if(!plik_tymcz_eps)
    {
      if(language==0)
	{
	  cout<<"Nie mog� utworzy� pliku tymczasowego. Sprawd� prawa."<<endl;
	}
      else
	{
	  cout<<"Couldn't open temporary file. Check permissions."<<endl;
	}
      return 1;
    }
  
  int dl_lini;
  int kolejnosc;
  char c[DL_WIERSZA];
  char etykieta[DL_WIERSZA];
  etykieta[DL_WIERSZA-1]=c[DL_WIERSZA-1]='\0';
  while(!wczytaj_linie(c,&dl_lini,DL_WIERSZA,plik_eps))
    {

      if(przeszukaj_linie_eps(c,etykieta,kolejnosc))//je�li zwr�ci 1 lub 2 oznacza �e znalaz� etykiet�
      {//pocz�tek if
	
	if(*c=='%')//je�li na pocz�tku linii z etykiet� znajduje si� procent
	  {
	    for(int zmienna=1;c[zmienna]!='\0';zmienna++)
	    plik_tymcz_eps<<c[zmienna];//i zapisujemy do pliku
	    wczytaj_linie(c,&dl_lini,DL_WIERSZA,plik_eps);//za tym powinien by� numer wi�c go wczytaj i zgub

	  }
	else plik_tymcz_eps<<c;//Je�li nie ma procentu to po prosu zapisz linie
	
	
      }
      
      else plik_tymcz_eps<<c;//nie znalaz� etykiety wi�c zapisuje linie

    }


  //Cz�� kopiuj�ca plik tymczasowy na pierwotny eps
  
{

  plik_tymcz_eps.close();//zamykanie plik�w
  plik_eps.close();//zamykanie plik�w
  //cout<<"otwieram plik do zapisu"<<endl;

  ofstream plik_tymcz_eps(nazwa_pliku);//plik wyj�ciowy nie sugerowa� si� nazw� zmiennej. Pozostawione aby nie psu� dalszych zale�no�ci.

  if(!plik_tymcz_eps)
    {
      if(language==0)
	{
	  cout<<"Nie mog� otworzy� pliku "<<nazwa_pliku<<" do zapisu."<<endl;
	}
      else
	{
	  cout<<"Couldn;t open "<<nazwa_pliku<<" file for writing."<<endl;
	}
      return 1;
    }

  ifstream plik_eps(nazwa_eps_tymcz);//plik wej�ciowy nie sugerowa� si� nazw� zmiennej. Pozostawione aby nie psu� dalszych zale�no�ci.
  if(language==0)
    {
      cout<<"Zmieniam numery na etykiety w pliku: "<<nazwa_pliku<<endl;
    }
  else
    {
      cout<<"Changing numbers to labels in "<<nazwa_pliku<<" file"<<endl;
    }
  if(!plik_eps)
    {
      if(language==0)
	{
	  cout<<"Nie moge otworzy� pliku tymczasowego do odczytu. Co� posz�o nie tak."
	      <<endl
	      <<"Zawarto�� pliku "<<nazwa_pliku<<" mo�esz znale�� w "<<nazwa_eps_tymcz<<"."<<endl;
	}
      else
	{
	  cout<<"I couldn't open temporary file for reading. Something has gone wrong."<<endl
	      <<"Content of the "<<nazwa_pliku<<" can be found in "<<nazwa_eps_tymcz<<" file."<<endl;
	}
      return 1;
    }

  while(!wczytaj_linie(c,&dl_lini,DL_WIERSZA,plik_eps))
    {
      plik_tymcz_eps<<c;

    }
  

  plik_eps.close();
  plik_tymcz_eps.close();
}
  //cout<<nazwa_eps_tymcz<<endl;
  unlink(nazwa_eps_tymcz);

  return 0;

}
