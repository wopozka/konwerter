/*
Copyright (C) 2005 Piotr Wawrzyniak (piti@piti.vsv.pl)


Tutaj zawarte s? procedury odpowiedzialne za wczytanie lini z pliku
eps (wczytaj_linie) i pliku tex (wczytaj_linie_tex).

Here there are procedures that read line from eps file (wczytaj_linie)
and tex file (wczytaj_linie_tex)

*/
#include"czyt_zapis.h"
extern int debug_level;
extern int language;
int liczsobie;

int wczytaj_linie(char *linia,int *dlugosc, int DL_WIERSZA, ifstream &czyt)
{
  //miejmy pewno?? ?e linia jest jednak naprawde wyzerowana
  for(liczsobie=0;liczsobie<DL_WIERSZA;liczsobie++)
    {
      linia[liczsobie]='\0';
    }

  
  if(debug_level)
    {
      if(language==0)
	{
	  cout<<"**********************************"<<endl;
	  cout<<"Funkcjon wczytaj_linie"<<endl;
	}
      else
	{
	  cout<<"**********************************"<<endl;
	  cout<<"Function wczytaj_linie"<<endl;
	}
    }
  char pomocnicza[DL_WIERSZA],c;
  pomocnicza[0]=pomocnicza[1]=pomocnicza[2]='\0';
  int licznik=0;
  //    if(czyt.eof())return 1;
  //if(czyt) cout<<"Nie moge znale~~ pliku"<<endl;
  if(debug_level)
    {
      if(language==0)
	{
	  cout<<"Czytam z pliku z pozycji "<<endl<<czyt.tellg()<<endl;
	}
      else
	{
	  cout<<"I am reading from file at the position: "<<czyt.tellg()<<endl;
	}
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
      if(language==0)
	{
	  cout<<"Linia zosta?a przeczytana. Pozycja w pliku: "
	      <<(czyt.tellg())<<endl
	      <<"Przeczytana linia: "<<linia<<endl
	      <<"Koniec funkcji czytaj?cej linie."<<endl
	      <<"==========================================";

	}
      else
	{      
	  cout<<"The line is now read. The position in the file: "
	      <<(czyt.tellg())<<endl
	      <<"The read line: "<<linia<<endl
	      <<"End of reading line function."<<endl
	      <<"==========================================";
	}
    }
  return 0;
}

int wczytaj_linie_tex(char *linia,int *dlugosc, int dl_WIERSZA, ifstream &czyt)
{
  char pomocnicza[dl_WIERSZA],c[2],b[2];
  int licznik=0;
  
  if(debug_level)
    {
      if(language==0)
	{
	  cout<<"*************************************************"<<endl
	      <<"Funkcja wczytaj_linie_tex"<<endl;
	}
      else
	{
	  cout<<"*************************************************"<<endl
	      <<"Function wczytaj_linie_tex"<<endl;
	}
    }
  //wczytaj pierwszy znak ewentualnie mo?e to by? koniec pliku
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
      if(language==0)
	{
	  cout<<"Przeczytana linia w pliku TeX: "<<linia<<endl
	      <<"Koniec funkcji wczytaj_linie_tex"<<endl
	      <<"==========================================="<<endl;
	}
      else
	{
	  cout<<"Read line in TeX file: "<<linia<<endl
	      <<"The end of the wczytaj_linie_tex function"<<endl
	      <<"==========================================="<<endl;
	}
    }
  linia[licznik]='\0';
  return 0;
}
