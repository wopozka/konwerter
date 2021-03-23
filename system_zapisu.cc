
 /***************************************************************************
 *                                                                          * 
 *   Copyright (C) 2005 Piotr Wawrzyniak (piti@piti.vsv.pl                  *
 *   This program is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation; either version 2 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 ***************************************************************************/
  

//The class and functions responsible for conversions to various numbering styles

#include"system_zapisu.h"
#include <iostream>
using namespace std;
extern int ignore_formating;
extern int language;
//constructor
r_numerow::r_numerow(int a, int b, int c, int d, int e)
{
  zwroc_num_etykiet[0]=a;
  zwroc_num_etykiet[1]=b;
  zwroc_num_etykiet[2]=c;
  zwroc_num_etykiet[3]=d;
  zwroc_num_etykiet[4]=e;
  domyslny_styl_numeracji=2;
}

int r_numerow::ustaw_zmienna_numer_etykietki(char *etykieta)
{

  if(etykieta[0]==':'&&strlen(etykieta)>=3&&!ignore_formating)
    {
      switch (etykieta[1])
	{
	case 'r':
	  zwroc_numer_etykiety(0);
	  break;
	case 'R':
	  zwroc_numer_etykiety(1);
	  break;
	case 'a':
	  zwroc_numer_etykiety(2);
	  break;
	case 'l':
	  zwroc_numer_etykiety(3);
	  break;
	case 'L':
	  zwroc_numer_etykiety(4);
	  break;
	default:
	  zwroc_numer_etykiety(domyslny_styl_numeracji);
	}
    }
  else
    zwroc_numer_etykiety(domyslny_styl_numeracji);
  return 0;
}


int r_numerow::set_up_all(int roman,int Roman,int arabic,int letters,int Letters,int def)
{
  zwroc_num_etykiet[0]=roman;
  zwroc_num_etykiet[1]=Roman;
  zwroc_num_etykiet[2]=arabic;
  zwroc_num_etykiet[3]=letters;
  zwroc_num_etykiet[4]=Letters;
  domyslny_styl_numeracji=def;
  
  return 0;
}

int r_numerow::set_up_all(int what, int what_number)
{
  if(what==5)
    {
      domyslny_styl_numeracji=what_number;
      return 0;
    }
  else
    {
      zwroc_num_etykiet[what]=what_number;
      return 0;
    }
}

int r_numerow::zwroc_numer_etykiety(int numer)
{

  zeruj_numer_etykietki();
  //wartosci_num_etykiet[numer]++;
  //  zwroc_num_etykiet[numer]++;
  switch(numer)
    {
    case 0:
      if(int_na_rom_char(zwroc_num_etykiet[0],0))
	return 2;;//By³ problem z zalokowaniem pamiêci
      break;
    case 1:
      if(int_na_rom_char(zwroc_num_etykiet[1],1))
	return 2;;//By³ problem z zalokowaniem pamiêci
      break;
    case 2:
      if(int_na_char(zwroc_num_etykiet[2]))
	return 2;//By³ problem z zaalokowaniem pamiêci
      break;
    case 3:
      if(int_na_lit_char(zwroc_num_etykiet[3],0))
	return 2;//By³ problem z zaalokowaniem pamiêci
      break;
    case 4:
      if(int_na_lit_char(zwroc_num_etykiet[4],1))
	return 2;//By³ problem z zaalokowaniem pamiêci
      break;
    };
  zwroc_num_etykiet[numer]++;  
  return 0;
}

int r_numerow::int_na_char(int a)

{
  kol_liczb *pierwszy=NULL;
  kol_liczb *ostatni=NULL;
  kol_liczb *pomocnicza=NULL;
  //	kol_liczb *poprzedni=NULL;
  
  
  int b=a;
  int d;
  
  float c;
  
  while(b>0.1)
    {
      c=b/10;
      pomocnicza=new kol_liczb;
      if (!pomocnicza) 
	{
	  if(language==0)
	    {
	      cout<<"Problem z zaalokowaniem wolnej pamiêci"<<endl;
	    }
	  else
	    {
	      cout<<"Error! Couldn't allocate free memory."<<endl;
	    }
	  return 1;//B³±d alokacji pamiêci
	}
      
      if(!pierwszy)
	{
	  pierwszy=ostatni=pomocnicza;
	  pierwszy->next=pierwszy->prev=NULL;
	}
      
      else
	{
	  
	  ostatni->next=pomocnicza;
	  pomocnicza->prev=ostatni;
	  pomocnicza->next=NULL;
	  ostatni=pomocnicza;

	}
      
      d=(int)c;
      pomocnicza->liczba=b-d*10;
      //cout<<pomocnicza->liczba<<endl;
      b=d;
      
    }
  
  pomocnicza=ostatni;
  b=0;
  while(pomocnicza)
    {
      //	    cout<<pomocnicza->liczba<<endl;
      switch (pomocnicza->liczba)
	{
	case 0:
	  numer_etykietki[b]='0';
	  numer_etykietki[b+1]='\0';
	  break;
	case 1:
	  numer_etykietki[b]='1';
	  numer_etykietki[b+1]='\0';
	  break;
	case 2:
	  numer_etykietki[b]='2';
	  numer_etykietki[b+1]='\0';
	  break;
	case 3:
	  numer_etykietki[b]='3';
	  numer_etykietki[b+1]='\0';
	  break;
	case 4:
	  numer_etykietki[b]='4';
	  numer_etykietki[b+1]='\0';
	  break;
	case 5:
	  numer_etykietki[b]='5';
	  numer_etykietki[b+1]='\0';
	  break;
	case 6:
	  numer_etykietki[b]='6';
	  numer_etykietki[b+1]='\0';
	  break;
	case 7:
	  numer_etykietki[b]='7';
	  numer_etykietki[b+1]='\0';
	  break;
	case 8:
	  numer_etykietki[b]='8';
	  numer_etykietki[b+1]='\0';
	  break;
	case 9:
	  numer_etykietki[b]='9';
	  numer_etykietki[b+1]='\0';
	  break;
	};
      pierwszy=pomocnicza;
      pomocnicza=pomocnicza->prev;
      delete pierwszy;
      b++; 
    }
  
  return 0;  
}

int r_numerow::int_na_rom_char(int liczba,int mal_duz)
{
  char tablica_liczb_rzymskich[33][5]={"i","ii","iii","iv","v","vi","vii","viii","ix","x","x","xx","xxx","xl","l","lx","lxx","lxxx","xc","c","c","cc","ccc","cd","d","dc","dcc","dccc","cm","m","m","mm","mmm"};


  int ile_cyfr=0;
  kol_liczb *pierwszy=NULL;
  kol_liczb *ostatni=NULL;
  kol_liczb *pomocnicza=NULL;
  //  kol_liczb *poprzedni=NULL;

  int b=liczba;
  int d;
  float c;
  if(liczba>3899)
    {
      if(language==0)
	{
	  cout<<"Przekroczony maksymalny zakres dla liczb rzymskich. Maksymalnie mo¿na przypisaæ 3899"<<endl;
	}
      else
	{
	  cout<<"Maximal range for Roman numbers is 3899. Yours numbers are to high. Sorry dude.";
	}
      return 1;

    }
  while(b>0.1)
    {
      c=b/10;
      pomocnicza=new kol_liczb;
      if (!pomocnicza)
	{
	  if(language==0)
	    {
	      cout<<"B³ad!. Problemy z zaalokowaniem pamiêci!"<<endl;
	    }
	  else
	    {
	      cout<<"Error!. Memory allocation problem.!"<<endl;
	    }
	  return 1;
	}
      if(!pierwszy)
	{
	  pierwszy=ostatni=pomocnicza;
	  pierwszy->next=pierwszy->prev=NULL;
	}
      
      else
	{
	  
	  ostatni->next=pomocnicza;
	  pomocnicza->prev=ostatni;
	  pomocnicza->next=NULL;
	  ostatni=pomocnicza;
	  
	}

      ile_cyfr++;
      d=(int)c;
      pomocnicza->liczba=b-d*10;

      //cout<<pomocnicza->liczba<<endl;
      b=d;

    }

  pomocnicza=ostatni;
  while(pomocnicza)
    {
      //cout<<pomocnicza->liczba;
      //	cout<<(ile_cyfr-1)*10+pomocnicza->liczba;
      if(pomocnicza->liczba)//Tutaj tak musi byæ bo je¶li liczba wychodzi³a 0 to by³y szopki
	//cout<<tablica_liczb_rzymskich[(ile_cyfr-1)*10+pomocnicza->liczba-1];
	strcat(numer_etykietki,tablica_liczb_rzymskich[(ile_cyfr-1)*10+pomocnicza->liczba-1]);
      
	//	cout<<pomocnicza->liczba;
	pierwszy=pomocnicza;
	pomocnicza=pomocnicza->prev;
	delete pierwszy;
	ile_cyfr--;
  
    }

  //If mal_duz=1 then change small roman number to capital ones
  if (mal_duz==1)
    {
      int unsigned dupa=0;
      while(dupa<strlen(numer_etykietki))
	{
	  numer_etykietki[dupa]-=('a'-'A');
	  dupa++;
	}
    }
  return 0;
}

int r_numerow::int_na_lit_char(int liczba,int mal_duz)
{
  
char tablica_liter[26][2]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

//char liczba_rzymska[256];
//int ile_cyfr=0;


  //for(int aaa=0;aaa<10;aaa++)
  // { cout<<tablica_liter[aaa]<<endl;}

 kol_liczb *pierwszy=NULL;
 kol_liczb *ostatni=NULL;
 kol_liczb *pomocnicza=NULL;
 // kol_liczb *poprzedni=NULL;

 int b=liczba;
 b--;//trzeba znmiejszyæ o 1 bo wychodz± bzdury. Problem z konwersj± system dziesiêtny - dwódziestoszóstkowy
 int d;
 float c;
 do
   {
     c=b/26;
     pomocnicza=new kol_liczb;
     if (!pomocnicza)
	{
	  if(language==0)
	    {
	      cout<<"B³ad!. Problemy z zaalokowaniem pamiêci!"<<endl;
	    }
	  else
	    {
	      cout<<"Error!. Memory allocation problem.!"<<endl;
	    }
	  return 1;
	}
     if(!pierwszy)
       {
	 pierwszy=ostatni=pomocnicza;
	 pierwszy->next=pierwszy->prev=NULL;
       }
     
     else
       {
	 ostatni->next=pomocnicza;
	 pomocnicza->prev=ostatni;
	 pomocnicza->next=NULL;
	 ostatni=pomocnicza;
       }
     
     d=(int)c;
     
     pomocnicza->liczba=b-d*26;
     
     b=d;
     
   }
 while(b>1/26);
 
pomocnicza=ostatni;
while(pomocnicza)
{

  strcat(numer_etykietki,tablica_liter[pomocnicza->liczba]);
  pierwszy=pomocnicza;
  pomocnicza=pomocnicza->prev;
  delete pierwszy;
	  
}

//If mal_duz=1 then change small letter r to capital ones
 if(mal_duz==1)
   {
     int unsigned dupa=0;
     while(dupa<strlen(numer_etykietki))
       {
	 numer_etykietki[dupa]-=('a'-'A');
	 dupa++;
       }
   }

  return 0;
}
