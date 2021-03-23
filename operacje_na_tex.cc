
 /***************************************************************************
 *                                                                          * 
 *   Copyright (C) 2005 Piotr Wawrzyniak (piti@eliksir.ch.pw.edu.pl)        *
 *   This program is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation; either version 2 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 ***************************************************************************/


#include"operacje_na_tex.h"
#include"czyt_zapis.h"
#include"prz_string.h"

int przeszukaj_linie_tex(char*);
int przed_etykieta_po(char,char*,char*,char*,char);
int podaj_etykiete_liczbe(char *, char *, int *);//linia etykieta kolejnosc
int zwroc_numer_etykiety(kol_etykiet*,char*,kol_etykiet**);
extern int language;
extern char polecenie[DL_WIERSZA];

int operacje_na_tex(char *nazwa_pliku, kol_etykiet*wierzcholek)
{
  char drugi_plik_tex[DL_WIERSZA];
  drugi_plik_tex[DL_WIERSZA-1]=drugi_plik_tex[0]=drugi_plik_tex[1]='\0';
  
  strcat(drugi_plik_tex,nazwa_pliku);
  strcat(drugi_plik_tex,".auto.tex");


  ofstream plik_tex_wy(drugi_plik_tex);
  if(!plik_tex_wy)
    {
      if(language==0)
	{
	  cout<<"Nie mog³em otworzyæ pliku wyj¶ciowego"<<endl;
	}
      else
	{
	  cout<<"I couldn't open "<<drugi_plik_tex<<"file."<<endl;
	}
      return 1;
    }

  ifstream plik_tex_we(nazwa_pliku);
  if(!plik_tex_we)
    {
      if(language==0)
	{
	  cout<<"Nie mog³em otworzyæ pliku wej¶ciowego"<<endl;
	}
      else
	{
	  cout<<"I couldn't open "<<nazwa_pliku<<" file."<<endl;
	}
      return 1;
    }

  char c[DL_WIERSZA];
  c[DL_WIERSZA-1]='\0';
  int dl_lini;

  while(!wczytaj_linie_tex(c,&dl_lini,DL_WIERSZA,plik_tex_we))
    {
      switch(przeszukaj_linie_tex(c))
	{
	case 0:{plik_tex_wy<<c;break;}  
	case 1://znalaz³ etykietê
	  {
	    char przed[DL_WIERSZA];
	    char po[DL_WIERSZA];
	    char etykieta[DL_WIERSZA];
	    przed[DL_WIERSZA-1]=po[DL_WIERSZA-1]=etykieta[DL_WIERSZA-1]='\0';
	    int kolejnosc;
	    podaj_etykiete_liczbe(c,etykieta,&kolejnosc);//zwraca etykietê
	     kol_etykiet *zmienna_tymczasowa1;
	     kol_etykiet**zmienna_tymczasowa=&zmienna_tymczasowa1;
	    kolejnosc=zwroc_numer_etykiety(wierzcholek,etykieta,zmienna_tymczasowa);//zwraca numer etykiety
	    if(kolejnosc==0)
	      {
		if(language==0)
		  {
		    cout<<endl<<"Nieznana etykieta: "<<etykieta<<endl;
		    cout<<"Pozostawiam niezmienione."<<endl;
		  }
		else
		  {
		    cout<<"Unknown label in tex file: "<<etykieta<<endl
			<<"Leave unchanged."<<endl;
		  }
		plik_tex_wy<<c;
	      }
	    else
	      {
		przed_etykieta_po('{',c,przed,po,'}');//zwraca co jest przed a co po etykiecie
		   
		//to pó¼nej bêdzie mo¿na usun±æ
		//cout<<przed<<kolejnosc<<po<<endl;
		   
		//plik_tex_wy<<'\\'<<przed<<kolejnosc<<po;
		plik_tex_wy<<'\\'<<przed<<(*zmienna_tymczasowa)->kolejny_numer_string<<po;
	      }
	    break;
	  }
	case 2://znalaz³ nazwê pliku
	  {
	    char nazwa_pliku[DL_WIERSZA];
	    int kolejnosc;
	    char przed[DL_WIERSZA];
	    char po[DL_WIERSZA];
	    nazwa_pliku[DL_WIERSZA-1]=przed[DL_WIERSZA-1]=po[DL_WIERSZA-1]='\0';
	    podaj_etykiete_liczbe(c,nazwa_pliku,&kolejnosc);
	    przed_etykieta_po('{',c,przed,po,'}');
	    operacje_na_tex(nazwa_pliku,wierzcholek);
	    plik_tex_wy<<'\\'<<przed<<nazwa_pliku<<".auto.tex"<<po;
	    break;
	  }
	}
      
    }





plik_tex_we.close();
plik_tex_wy.close();

  return 0;
}

int przeszukaj_linie_tex(char *linia)
{
  
  if(bm(polecenie,linia)==0)
    {
        return 1;
    }

  else
    if(bm("\\input{",linia)==0)return 2;

return 0;

}
