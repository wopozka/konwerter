
 /***************************************************************************
 *                                                                          * 
 *   Copyright (C) 2005 Piotr Wawrzyniak (piti@piti.vsv.pl                  *
 *   This program is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation; either version 2 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 ***************************************************************************/
  

/*
  W tym pliku zawarta jest procedura odpowiedzialna za przeszukiwanie
  stringu. Procedure przepisana wprost z ksi±¿ki z algorytmami.
  In this file there is procedure that looks for any patern in given 
  string. Procedure taken directry from book.
*/



#include<iostream>
#include<string.h>
#include<ctype.h>
#include"prz_string.h"
using namespace std;

//const int K=26*2+2*2+1+1+1;// znaki ASCII+polskie litery+spacja+dwukropek+srednik
const int K=256;

int shift[K];
//-------------------------------------------------------
int indeks(char c)
{
switch(c)
 {
 case ' ':return 0;         // spacja=0
 case '.':return 46;
 case 'ê':return 53;
 case 'Ê':return 54;     // polskie litery
 case '³':return 55;
 case '£':return 56;     // itd. dla pozosta³ych polskich liter
 case '?':return 63;
 case ':':return 58;
 case ';':return 59;
 case '{':return 123;
 case '}':return 125;
 default:
		if(islower(c))
			return c-'a'+1;
		else return c-'A'+27;
 }
}
//-------------------------------------------------------
int init_shifts(char *w)
{
int M=strlen(w);
for(int i=0;i<K;i++) shift[i]=M;
for(int i=0;i<M;i++)
  shift[indeks(w[i])]=M-i-1;
 return 0;
}
//-------------------------------------------------------
int bm(char *w,char *t)
{
init_shifts(w);
int i, j,N=strlen(t),M=strlen(w);
for(i=M-1,j=M-1;j>0;i--,j--)
  while(t[i]!=w[j])
	{
	int x=shift[indeks(t[i])];
	if(M-j>x) i+=M-j;else
		  i+=x;
	if (i>=N) return -1;
	j=M-1;
	}
return i;
}
//-------------------------------------------------------
/*void main()
 {
 char *t,*w;
 cout<<"Napisz tekst do przeszukania ";
 cin>>t;
 cout<<"Napisz wzorzec do znalezienia ";
 cin>>w;
 
 cout << "Wynik poszukiwañ="<<bm(w,t)<<endl;
 }

*/
