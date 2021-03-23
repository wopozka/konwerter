/*
Copyright (C) 2005 Piotr Wawrzyniak (piti@eliksir.ch.pw.edu.pl)


Tutaj zawarte s± procedury odpowiedzialne za wczytanie lini z pliku
eps (wczytaj_linie) i pliku tex (wczytaj_linie_tex).

Here there are procedures that read line from eps file (wczytaj_linie)
and tex file (wczytaj_linie_tex)

*/
#include"czyt_zapis.h"
extern int debug_level;

int wczytaj_linie(char *linia,int *dlugosc, int DL_WIERSZA, ifstream &czyt)

{
  if(debug_level)
    {
      cout<<"**********************************"<<endl;
      cout<<"Funkcjon wczytaj_linie"<<endl;
    }
  char pomocnicza[DL_WIERSZA],c;
  pomocnicza[0]=pomocnicza[1]=pomocnicza[2]='\0';
  int licznik=0;
  //    if(czyt.eof())return 1;
  //if(czyt) cout<<"Nie moge znale~~ pliku"<<endl;
  if(debug_level)
    {
      cout<<"I am reading from file at the position: "<<czyt.tellg()<<endl;
    }
  do
    {
      if(!czyt.get(c))
	return 1; 
      else
	pomocnicza[licznik++]=c;
      pomocnicza[licznik]='\0'; 
    }

  while((c!='\n')&&(c!=EOF)&&(licznik<(DL_WIERSZA-17)));

  *dlugosc=licznik;
  strcpy(linia,pomocnicza);
  linia[licznik]='\0';
  if(debug_level)
    {
      cout<<"The line is now read. The position in the file: "
	  <<(czyt.tellg())<<endl
	  <<"The read line: "<<linia<<endl
	  <<"End of read line function"<<endl
	  <<"==========================================";
    }
  return 0;
}

int wczytaj_linie_tex(char *linia,int *dlugosc, int dl_WIERSZA, ifstream &czyt)
{
  char pomocnicza[dl_WIERSZA],c[2],b[2];
  int licznik=0;
  
  if(debug_level)
    {
      cout<<"*************************************************"<<endl
	  <<"Function wczytaj_linie_tex"<<endl;
    }
  //wczytaj pierwszy znak ewentualnie mo¿e to byæ koniec pliku
  if(!czyt.get(c[0]))
    return 1;
  else 
    {
      pomocnicza[licznik++]=c[0];
      pomocnicza[licznik]='\0';
    }
  int czy_skonczyc=1;
  do
    {
      if(!czyt.get(c[0]))
	return 1; 
      else
	{    
	  pomocnicza[licznik++]=c[0];
	  pomocnicza[licznik]='\0';
	}
      if (c[0]=='\\')
	{
	  czy_skonczyc=0;
	  licznik--;
	  czyt.seekg(-1,ios::cur);
	}
      //char b[2]	;
      if(!czyt.get(b[0])) 
	czy_skonczyc=0;
      else
	czyt.seekg(-1,ios::cur);
  }

  while((c[0]!='\n')&&(licznik<(dl_WIERSZA-17))&&czy_skonczyc);
  *dlugosc=licznik;
  strcpy(linia,pomocnicza);
  if(debug_level)
    {
      cout<<"Read line in tex file: "<<linia<<endl
	  <<"The end of the wczytaj_linie_tex function"<<endl
	  <<"==========================================="<<endl;
    }
  linia[licznik]='\0';
  return 0;
}
