
 /***************************************************************************
 *                                                                          * 
 *   Copyright (C) 2005 Piotr Wawrzyniak (piti@eliksir.ch.pw.edu.pl)        *
 *   This program is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation; either version 2 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 ***************************************************************************/


#include"operacje.h"
#include"czyt_zapis.h"
#include"dl_wiersza.h"
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<unistd.h>
#include"num_na_etyk.h"
#include"prz_string.h"
#include"system_zapisu.h"

int przeszukaj_linie(char*,char*,ifstream&); //przeszukuje linie eps
int przetworz_eps(char*,kol_etykiet**);
int przeszukaj_linie_eps(char*,char*,int&);
int podaj_etykiete_liczbe(char *, char *, int *);
int zwroc_numer_etykiety(kol_etykiet*,char*,kol_etykiet**);
int przed_etykieta_po(char,char*,char*,char*,char);
int check_counter_to_set(char*);

struct kolejka_w_eps
{
  int numer;
  char etykieta[DL_WIERSZA];
  kolejka_w_eps*nast;
  
};

int wloz_na_liste(kolejka_w_eps*,kol_etykiet**);

//ifstream czyt;
//ofstream pisz;


extern char numer_czy_etykieta;//przyjmuje dwie warto¶ci n-numeruje e-nadaje etykiety;
extern int zacznij_numery_od;//od jakiej liczby zacz±æ numeracjê
extern r_numerow klasa_obslugi_etykiet;
extern int debug_level;
extern int ignore_set_counter_to;


//Funkcja przetwarzaj plik zajmuje siê szukaniem etykiet i plików eps w pliku texowym
//je¶li znajdzie podejmuje akcje w zale¿no¶ci co znalaz³a
int przetwarzaj_plik(char *argv1, /*char *argv2,*/kol_etykiet **wierzcholek)
{
  ifstream czyt;
  czyt.open(argv1);
  if(!czyt)
    {
      cout<<"Nie moge otworzyæ pliku "<<argv1<<endl
	  <<"Couldn't open file "<<argv1<<endl;
      return 1;
    }
  char c[DL_WIERSZA];//zmienna zawieraj±ca linie
  c[DL_WIERSZA-1]='\0';//tak na wszelki wypadek aby zapobiec przepe³nieniu bufora
  int dl_lini;
  char nazwa_pliku[DL_WIERSZA];
  nazwa_pliku[DL_WIERSZA-1]='\0';
  while(!wczytaj_linie(c,&dl_lini,DL_WIERSZA,czyt)) //wczytaj_linie belongs to czyt_zapis.cc
    {
      if(numer_czy_etykieta!='e'&&!ignore_set_counter_to)
	check_counter_to_set(c);
      switch(przeszukaj_linie(c,nazwa_pliku,czyt)) 
	{
	case 0://Znalaz³em plik eps wiêc musz± go przetworzyæ.
	  {
	    //odtwarzam etykiety w plikach eps
	    if(numer_czy_etykieta=='e') 
	      num_na_etyk(nazwa_pliku);//change numbers to lables
	    //przetwarzam eps, tzn zamieniam etykiety na numery
	    else 
	      przetworz_eps(nazwa_pliku,wierzcholek); //change labels to numbers
	    break;
	  }
	case 6://if input command was found in tex file
	  {
	    if(przetwarzaj_plik(nazwa_pliku,/*argv2,*/wierzcholek)) 
	      return 1;
	    break;
	  }
	}
    }
  if(!czyt.eof()) //if we did not finish reading file
    {
      cout<<"B³±d czytania"<<endl<<"Reading mistake"<<endl;
      return 1;
    }
  czyt.close();
  return 0;
}


//function that search for tex files and input command in tex file
int przeszukaj_linie(char *linia,char *nazwa_pliku,ifstream &czyt)
{//1  
  char pom_nazwa_pliku[DL_WIERSZA];
  pom_nazwa_pliku[DL_WIERSZA-1]='\0';
  char polecenie[]="?plik";//definiuje nazwê polecenia do znalezienia
  char polecenie2[]="input{";//definiuje nzawê do znalezienia
  int a;// zero je¶li uda³o siê skopiowaæ string
  if (*linia=='%')
    { //2
      linia++;
      a=strncmp(linia,polecenie,5);
      if(!a)
	{//3
	  linia=linia+5;
	  if (*linia!='{')
	    return 1; //je¶li nie ma nawiasu zwróæ b³±d 
	  else
	    {//4
	      linia++;
	      int licznik=0;
	      if (*linia=='}')return 2;//je¶li nie ma nazwy pliku zwróæ b³±d przypadek  %?{}
	      int czykoniec=0;
	      do
		{//5
		  if(*(linia+licznik)=='}')
		    {//skopiuj nazwê pliku
		      strncpy(pom_nazwa_pliku,linia,licznik); 
		      pom_nazwa_pliku[licznik]='\0';
		      czykoniec=1;}
		  else
		    if(*(linia+licznik)=='\n')
		      {
			return 3;
		      }
		  //je¶li nie ma
		    else
		      licznik++;
		}//5
	      while(!czykoniec);
	      strcpy(nazwa_pliku,pom_nazwa_pliku); 
	      nazwa_pliku[licznik]='\0';
	      return 0;//je¶li sukces to zwróæ to   
	    }//4
	}//3
      else return 4; //to nie jest polecenia
    }//2
  else 
    if(*linia=='\\')
      {//6
	linia++;
	if(!strncmp(linia,polecenie2,6))
	  {//7
	    linia+=6;
	    int licznik=0;
	    if (*linia=='}')return 2;//je¶li nie ma nazwy pliku zwróæ b³±d przypadek  %?{}
	    int czykoniec=0;
	    do
	      {//5
	        if(*(linia+licznik)=='}')
		  {strncpy(pom_nazwa_pliku,linia,licznik); czykoniec=1;}//skopiuj nazwê pliku
		else
		  if(*(linia+licznik)=='\n')
		    {
		      return 3;
		    }//je¶li nie ma }
		  else
		    licznik++;
	      }//5
	    while(!czykoniec);
	    strcpy(nazwa_pliku,pom_nazwa_pliku); 
	    nazwa_pliku[licznik]='\0';
	    return 6;//zwraca nazwê pliku LaTeXa 
	  }//7
	else 
	  return 4;//nie rób nic
      }//6
  return 4;//linia nie zaczyna siê od % ani backlsasha
}//1

//change labels to numbers in eps file
int przetworz_eps(char *nazwa_pliku,kol_etykiet**wierzcholek)
{
  kolejka_w_eps*pierwszy_element=NULL;
  char nazwa_eps_tymcz[]="konwXXXXXX";//temporary file name
  mkstemp(nazwa_eps_tymcz);//creation of temporary file

  if(debug_level)
    {
      cout<<"The eps file copied to "<<nazwa_eps_tymcz<<" file"<<endl;
      cout<<"Opening the temporary file for writing"<<endl;
    }
  
  ofstream plik_tymcz(nazwa_eps_tymcz);//temporary file opening 
  if(!plik_tymcz)
    {
      cout<<"Nie uda³o mi siê otworzyæ pliku tymczasowego"<<endl
	  <<"Couldn't open temporary file"<<endl;
      return 1;
    }
    
  ifstream plik_eps(nazwa_pliku); //eps file opening
  if(!plik_eps)
    {
      cout<<"Brakuje pliku "<<nazwa_pliku<<", lub brak praw."<< endl
	  <<"Missing file "<<nazwa_pliku<<", or access forbidden"<<endl;
      return 1;
    }
  cout<<"Znalaz³em plik "<<nazwa_pliku<<"."<<endl<<"File "<<nazwa_pliku<<" found."<<endl;
  
  int dl_lini;
  int kolejnosc;
  char c[DL_WIERSZA];
  char etykieta[DL_WIERSZA];

  //local label queue building
  while(!wczytaj_linie(c,&dl_lini,DL_WIERSZA,plik_eps))//reads line from eps file
    {
      //searching eps line for labels. Returning 1  means label
      if(przeszukaj_linie_eps(c,etykieta,kolejnosc))//je¶li zwróci 1  oznacza ¿e znalaz³ etykietê
	{//pocz±tek if
	  if(*c!='%')plik_tymcz<<'%'<<c;
	  plik_tymcz<<c;
	  if(!pierwszy_element)//if 2
	    {//1
	      pierwszy_element=new kolejka_w_eps;
	      pierwszy_element->nast=NULL;
	      strcpy(pierwszy_element->etykieta,etykieta);
	      pierwszy_element->numer=kolejnosc;
	    }//1
	  //W przeciwnym wypadku je¶li lista ma ju¿ przynajmniej pierwszy element zrób to co poni¿ej tzn
	  else//if 2
	    {
	      kolejka_w_eps*nowy_element=new kolejka_w_eps;//tworze nowy element
	      nowy_element->numer=kolejnosc;//nadaje mu warto¶ci pocz±tkowe - kolejno¶æ
	      nowy_element->nast=NULL;//nadaje mu warto¶ci pocz±tkowe - nastêpny
	      strcpy(nowy_element->etykieta,etykieta);//nadaje mu warto¶ci pocz±tkowe - etykieta
	      //je¶li nowy element jest mniejszy lub równy pierwszemu z listy to wstaw go przed niego
	      if((nowy_element->numer)<=(pierwszy_element->numer))
		{
		  nowy_element->nast=pierwszy_element;
		  pierwszy_element=nowy_element;
		}

	    //no dobrze nie jest mniejszy ani równy wobec tego wstaw go w odpowiedie miejsce w li¶cie
	      else//2
		{
		  //tworze wska¼nik do zmiennej który wskazuje na pierwszy element
		  kolejka_w_eps*bierzacy_element=pierwszy_element;//pomocnicza zmnienna
		  //tworze wska¼nik to zmiennej który wskazuje na bierzacy_element
		  kolejka_w_eps*pomocnicza=bierzacy_element;//pomocnicza zmnienna
		  //do czasu a¿ kolejno¶æ z nowego bêdzie wiêksza od kolejno¶ci z bierz±cego i jednocze¶nie
		  //bierz±cy element nie bêdzie ostatnim wykonuj tê pêtlê
		  while(((nowy_element->numer)>(bierzacy_element->numer))&&(bierzacy_element->nast))
		    {
		      pomocnicza=bierzacy_element;//pomocnicza wskazuje na 1 element bli¿ej ni¿ bierz_element
		      //bierzacy_element przeskakuje o jedno pole dalej
		      bierzacy_element=bierzacy_element->nast;
		    }
		  {
		    //je¶li bierz±cy element jest ostatnim elementem na li¶cie i jednocze¶nie jest mniejszy
		    //lub równy od nowego to nowy dostaw na koñcu listy
		    if(!bierzacy_element->nast&&((bierzacy_element->numer)<=(nowy_element->numer)))
		      {
			bierzacy_element->nast=nowy_element;
		      }
		    
		    //w przeciwnym wypadku wstaw go w znalezione miejsce
		    else
		      {
			pomocnicza->nast=nowy_element;
			nowy_element->nast=bierzacy_element;
		      }
		  }
		}//koniec else 2
	    }//koniec else 1
	  if(debug_level)
	    {
	      cout<<"Readed line from eps file: "<<c<<endl;
	      cout<<"The label: "<<etykieta<<endl;
	      cout<<"The number: "<<kolejnosc<<endl;
	    }
	}
      else  plik_tymcz<<c;
    }//koniec while;

  //zakoñczy³o siê budowanie kolejki etykiet z pliku eps teraz nale¿y je wprowadziæ na listê etykiet
  //globalnych
  //global queue building
  //wk³adanie na globaln± kolejkê etykiet
  if(debug_level)
    cout<<"Global label queue building"<<endl;
  {
    kolejka_w_eps*pomocnicza=pierwszy_element;
    while(pomocnicza)
      {
	wloz_na_liste(pomocnicza,wierzcholek);
	pierwszy_element=pomocnicza;
	pomocnicza=pomocnicza->nast;
	delete pierwszy_element;
      }
  }

  if(debug_level)
    {
      cout<<endl<<"The global label queue printing: "<<endl;
      kol_etykiet*pomocnicza_2=*wierzcholek;
      while(pomocnicza_2)
	{
	  cout<<"Label "<<pomocnicza_2->etykieta<<endl;
	  cout<<"Number "<<pomocnicza_2->kolejny_numer<<endl;
	  cout<<"String number "<<pomocnicza_2->kolejny_numer_string<<endl;
	  pomocnicza_2=pomocnicza_2->nast;
	}
      cout<<"I have finished "<<nazwa_pliku<<" file"<<endl;
    }
  plik_eps.close();
  plik_tymcz.close();

  //Kopiowanie pliku tymczasowego na eps
  //Copying temporary file to eps file.

  {

    //plik_eps.open(nazwa_eps_tymcz);
    ifstream plik_eps(nazwa_eps_tymcz);//otwieram plik tymczasowy do odczytu aby go skopiowaæ na pierwotny eps. Nie sugerowaæ siê nazw± zmiennej.
    if (!plik_eps)
      {
	cout<<"Nie mogê otworzyæ pliku tymczasowego "<<nazwa_eps_tymcz<<" do czytania"<<endl
	    <<"Couldn't open temporary file: "<<nazwa_eps_tymcz<<" for reading"<<endl;
	return 1;
      }
    //plik_tymcz.open(nazwa_pliku);
    ofstream plik_tymcz(nazwa_pliku);//otwieram plik g³ówny eps do zapisu aby skopiowaæ do niego zawarto¶æ pliku tymczasowego. Nie sugerowaæ siê nazw± zmiennej. 
    //Brak logiki wynika z lenistwa. Nie chcia³o mi siê poprawiaæ parê linii wiêc jest jak jest.
    if (!plik_tymcz)
      {
	cout<<"Nie mogê otworzyæ pliku "<<nazwa_pliku<<" do zapisu"<<endl
	    <<"Couldn't open file: "<<nazwa_pliku<<" for writing"<<endl;
	return 1;
      }

    int numer_etykiety;
    char przed[DL_WIERSZA];
    char po[DL_WIERSZA];
    przed[DL_WIERSZA-1]=po[DL_WIERSZA-1]='\0';
    while(!wczytaj_linie(c,&dl_lini,DL_WIERSZA,plik_eps))
      {
	if(debug_level)
	  cout<<"Copying the temporary file to main eps. The read line is: "<<c<<endl;
	if(przeszukaj_linie_eps(c,etykieta,kolejnosc))//je¶li zwróci 1 oznacza ¿e znalaz³ etykietê
	  {
	    if(debug_level)
	      {
		cout<<"I found the line with label. Analyzing."<<endl;
		cout<<"The etykieta variable is equal: "<<etykieta<<endl;
		cout<<"The c variable - the line is equal: "<<c<<endl;
	      }
	    kol_etykiet *zmienna_tymczasowa1;
	    kol_etykiet**zmienna_tymczasowa=&zmienna_tymczasowa1;
	    plik_tymcz<<c;//zapisz linie etykiety z %
	    if(debug_level)
	      {
		cout<<"Checking whitch number has the label. ";
		cout<<"The data for function calling:"<<endl;
		cout<<"*wierzcholek->etykieta: "<<(*wierzcholek)->etykieta<<endl;
		cout<<"zmienna_tymczasowa: "<<zmienna_tymczasowa<<endl;
	      }
	    numer_etykiety=zwroc_numer_etykiety(*wierzcholek,etykieta,zmienna_tymczasowa);
	    if(debug_level)
	      cout<<"The number is checke and is equal: "<<numer_etykiety<<endl<<endl;
	    if(przed_etykieta_po('{',c,przed,po,'}')) numer_etykiety=0;//je¶li funkcja zwróci 1 to oznacza b³±d
	    if(debug_level)
	      cout<<"Function przed_etykieta_po has checked the label. Variable kolejny_numer_string is equal: "<<(*zmienna_tymczasowa)->kolejny_numer_string<<endl;
	    
	    if(numer_etykiety)//je¶li numer_etykiety=0 oznacza to ¿e nie znalaz³ etykiety na li¶cie
	      {//pocz±tek if
		char przed1[DL_WIERSZA];
		int taka_sobie=strlen(przed);
		strncpy(przed1,przed,taka_sobie-4);
		przed1[taka_sobie-4]='\0';
		//char *po1=&po[1];
		char *po1=&po[1];
		if(debug_level)
		  {
		    cout<<"The folowing line is saved in eps file:"<<endl
			<<"przed1: "<<przed<<endl
			<<"(*zmienna_tymczasowa)->kolejny_numer_string: "<<(*zmienna_tymczasowa)->kolejny_numer_string<<endl
			<<"po1: "<<po1<<endl;
	       }
		
		plik_tymcz<<przed1<<(*zmienna_tymczasowa)->kolejny_numer_string<<po1;//zapisz numer etykiety
		wczytaj_linie(c,&dl_lini,DL_WIERSZA,plik_eps);//w pliku pom za etykiet± z % jest zwyk³a 
		//wiêc j± wont
		/**************************************************************************/
		
	      }//koniec if
	    else //je¶li nie zalaz³e¶ etykiety na li¶cie zapisz jej nazwê do pliku. Nazwa ukryta pod zmienn±  c
	      {
		if(debug_level)
		  {
		    cout<<"The label was not found on the list. Writing all in eps file."<<endl
			<<"Writing the following line "<<c<<endl; 
		  }
		char*ggg=c;
		if(debug_level)
		  cout<<"The ggg variable: "<<ggg<<endl;
		ggg++;
		if(debug_level)
		  cout<<"The ggg++ variable: "<<ggg<<endl;
		plik_tymcz<<ggg;
	      }
	  }
	else 
	  {
	    if(debug_level)
	      {
		cout<<"The label was not found. Writing to eps file line:"<<endl
		    <<"linia c: "<<c<<endl;
	    }
	    plik_tymcz<<c;//je¶li nie ma etykiety to zapisz linie
	  }
      }
    plik_tymcz.close();
    plik_eps.close();
  }
  unlink(nazwa_eps_tymcz);
  if(debug_level)
    cout<<"Zakoñczone kopiowanie pliku tymczasowego eps na g³ówny eps."<<endl;
  return 0;
}

int przeszukaj_linie_eps(char *linia, char *etykieta, int &kolejnosc)
{
  /*funkcja zwróci warto¶æ 0, je¶li nie znajdzie etykiety w linii
    funkcja zwróci warto¶æ 1, je¶li znajdzie etykietê w linii. Etykieta nie by³a komentarzem
    funkcja zwróci warto¶æ 2, je¶li znajdzie etykietê w linii. Etykieta by³a komentarzem.*/
  int czy_znalazlem;

  /*funkcja bm() jest funkcj± obecn± w pliku prz_string.cc. Jej zadaniem jest szukanie wzorca w stringu.
    je¶li znajdzie zwraca pozycjê w której siê znajduje, je¶li nie to zwraca -1*/
  czy_znalazlem=bm("?et{",linia);//zwraca numer na którym znalaz³ wzorzec zaczyna od 0
  if(czy_znalazlem>-1)
    {
      int *taka_sobie_zmienna=&kolejnosc;
      podaj_etykiete_liczbe(linia,etykieta,taka_sobie_zmienna);
      return 1;
    }
  else  
    return 0;
}

int podaj_etykiete_liczbe(char *linia, char *etykieta, int *kolejnosc)
{
  char pomocnicza[DL_WIERSZA];
  pomocnicza[DL_WIERSZA-1]='\0';
  int pozycja=0; 

  strcpy(pomocnicza,linia);
  int n=0;
  while(pomocnicza[n]!='{')
    n++;
  n++;
  while((pomocnicza[n]!=';')&&(pomocnicza[n]!='}')&&(pomocnicza[n]!=')')&&(pomocnicza[n]!='\0'))
    {
      etykieta[pozycja]=pomocnicza[n];
      n++;pozycja++;
    }
  etykieta[pozycja]='\0';
  if (pozycja==0)
    return 0;
  n++;
  *kolejnosc=0;
  while(pomocnicza[n]!='}'&&isdigit(pomocnicza[n]))
    {
      *kolejnosc=*kolejnosc*10+pomocnicza[n]-'0';
      n++;
    } 
  return 0;
}


//function that puts label to label queue
int wloz_na_liste(kolejka_w_eps*rekord,kol_etykiet**wierzcholek)
{
  //Putting label into global label queue
  if(debug_level)
    {
      cout<<"Putting the label to the global label queue."<<endl;
      cout<<"The label: "<<rekord->etykieta<<endl;
    }

  if(!*wierzcholek)//There is no global label queue
    { 
      //pobieramy numerek etykietki
      //we are taking label number
      //after function klasa_obslugi_etykiet.zwroc_numer_etykiety() will be ready
      //one can find label in klasa_obslugi_etykiet.numer_etykietki variable
      if(debug_level)
	{
	  cout<<"No label on the list. The first label will be placed."<<endl;
	  cout<<"The label: "<<rekord->etykieta<<" is placed."<<endl;
	}
      klasa_obslugi_etykiet.ustaw_zmienna_numer_etykietki(rekord->etykieta);
      if(debug_level)
	{
	  cout<<"Setting the klasa_obslugi_etykiet.numer_etykietki variable: "
	      <<klasa_obslugi_etykiet.numer_etykietki<<endl;
	}

      kol_etykiet*wierzcholek1=new kol_etykiet;
      //check, if labels looks like :mbla.a.The label must be longer that 5 leters: :ba.d
      int dlugosc=strlen(rekord->etykieta);
      if(rekord->etykieta[dlugosc-2]=='.'&&dlugosc>=5)
	{
	  if(debug_level)
	    {
	      cout<<"The label look like: :mblah.a."<<endl; 
	      cout<<"Putting the core to the queue"<<endl;
	    }
	  wierzcholek1->kolejny_numer=zacznij_numery_od;//historical meaning, to delete soon
	  //copy label to global label queue
	  strncpy(wierzcholek1->etykieta,rekord->etykieta,dlugosc-2);
	  //copy number as a string to global label queue
	  strcpy(wierzcholek1->kolejny_numer_string,klasa_obslugi_etykiet.numer_etykietki);
	  wierzcholek1->nast=NULL;
	  *wierzcholek=wierzcholek1;

	  //W³o¿ony do kolejki rdzeñ etykiety, tzn :ba, teraz czas w³o¿yæ ca³± etykietê:
	  if(debug_level)
	    {
	      cout<<"The core of the label is already there."<<endl;
	      cout<<"Time to  put there all label"<<endl;
	    }
	  kol_etykiet*dada=wierzcholek1;
	  //kol_etykiet*wierzcholek1=new kol_etykiet;
	  wierzcholek1=new kol_etykiet;
	  dada->nast=wierzcholek1;
	  wierzcholek1->nast=NULL;
	  
	  wierzcholek1->kolejny_numer=zacznij_numery_od;
	  strcpy(wierzcholek1->etykieta,rekord->etykieta);
	  strcpy(wierzcholek1->kolejny_numer_string,klasa_obslugi_etykiet.numer_etykietki);

	  //Jak na razie numer numer jest bez literki, czas j± dodaæ
	  char pom[3];
	  if(debug_level)
	    cout<<"Adding the letter to the label"<<endl;
	  pom[0]=rekord->etykieta[dlugosc-1];pom[1]='\0';
	  strcat(wierzcholek1->kolejny_numer_string,pom);
	}
      else
	{
	  wierzcholek1->kolejny_numer=zacznij_numery_od;
	  strcpy(wierzcholek1->etykieta,rekord->etykieta);
	  strcpy(wierzcholek1->kolejny_numer_string,klasa_obslugi_etykiet.numer_etykietki);
	  *wierzcholek=wierzcholek1;
	  if(debug_level)
	    {
	      cout<<"************************************************************"<<endl;
	      cout<<"Label has more than 3 letters and doesn't exist on the list."<<endl;
	      cout<<"That what is putted:"<<endl;
	      cout<<"Number: "<<wierzcholek1->kolejny_numer<<endl;
	      cout<<"Label: "<<wierzcholek1->etykieta<<endl;
	      cout<<"Next string number: "<<wierzcholek1->kolejny_numer_string<<endl;
	      cout<<"============================================================"<<endl;
	    }
	}
    }

  else
    {//pocz±tek else
      
      if(debug_level)
	cout<<"There are already labels on the list. Building forward."<<endl;
      //Lets look if the label exists in global label queue
      kol_etykiet*nowy_element=*wierzcholek;
      if(debug_level)
	cout<<"Looking if the label: "<<rekord->etykieta<<" exists on the lobal label queue.";
      while(strcmp(nowy_element->etykieta,rekord->etykieta)&&nowy_element->nast)
       	nowy_element=nowy_element->nast;
      if(!strcmp(nowy_element->etykieta,rekord->etykieta)) 
	{
	  if(debug_level)
	    cout<<"Label: "<<rekord->etykieta<<" found on the global label queue. Living function."<<endl;
	  return 0;
	}
      //find the last queue element
      kol_etykiet*ostatni_element=*wierzcholek;
      while(ostatni_element->nast)
	ostatni_element=ostatni_element->nast;
      
      //So we didn't find a label in global label queue, so lets put it there
      if(debug_level)
	cout<<"The label: "<<rekord->etykieta<<" not found in the queue. Putting."<<endl;
      if(!nowy_element->nast)
	{
	  int dlugosc=strlen(rekord->etykieta);
      	  //Lets look how does label look like
	  //the label can be as: blach.a
	  if(dlugosc>=3&&rekord->etykieta[dlugosc-2]=='.')
	    {
	      if(debug_level)
		{
		  cout<<"****************************"<<endl;
		  cout<<"The label looks like blach.a"<<endl;
		}
	      char root_label[dlugosc];
	      strncpy(root_label,rekord->etykieta,dlugosc-2);
	      root_label[dlugosc-2]='\0';
	      
	      if(debug_level)
		{
		  cout<<"root_label wygl±da: "<<root_label<<endl;
		  cout<<"==========================="<<endl;
		}
	      //wyszukaj root_label na globalnej kolejce etykiet
	      kol_etykiet*iteruj=*wierzcholek;
	      while(strcmp(iteruj->etykieta,root_label)&&iteruj->nast)
		iteruj=iteruj->nast;
	      //znalaz³e¶, czy skoñczy³a siê kolejka
	      //za³ó¿my ¿e znalaz³e¶, wiêc pobierz jej numer, a now± dodaj do koñca kolejki
	      if(!strcmp(iteruj->etykieta,root_label))
		{
		  kol_etykiet*dodaj=new kol_etykiet;
		  dodaj->nast=NULL;
		  strcpy(dodaj->etykieta,rekord->etykieta);
		  strcpy(dodaj->kolejny_numer_string,iteruj->kolejny_numer_string);
		  dodaj->kolejny_numer_string[strlen(dodaj->kolejny_numer_string)]=rekord->etykieta[dlugosc-1];
		  ostatni_element->nast=dodaj;   
		  if(debug_level)
		    cout<<"The label: "<<rekord->etykieta<<" found in the global label quere. Its number was copied."<<endl;
		}

	      else //nie znale¼li¶my, wiêc trzeba dodaæ dwie: root_label i tê now± rozszerzon±
		{
		  if(debug_level)
		    {
		      cout<<"****************************************************************"<<endl;
		      cout<<"The label doesn't exist on the global list.Must be added."<<endl;
		    }
		  klasa_obslugi_etykiet.ustaw_zmienna_numer_etykietki(rekord->etykieta);
		  if(debug_level)
		    {
		      cout<<"The label number was taken using funkcjon ustaw_zmienn±_numer_etykietki"<<endl;
		      cout<<"That is the result klasa_obslugi_etykiet.numer_etykietki: "<<klasa_obslugi_etykiet.numer_etykietki<<endl;
		      cout<<"================================================================"<<endl;
		    }
		   
		  kol_etykiet*dodaj=new kol_etykiet;
		  dodaj->nast=NULL;
		  strcpy(dodaj->etykieta,root_label);
		  strcpy(dodaj->kolejny_numer_string, klasa_obslugi_etykiet.numer_etykietki);
		  ostatni_element->nast=dodaj;
		  ostatni_element=dodaj;
		  dodaj=new kol_etykiet;
		  strcpy(dodaj->etykieta,rekord->etykieta);
		  strcpy(dodaj->kolejny_numer_string,ostatni_element->kolejny_numer_string);
		  dodaj->kolejny_numer_string[strlen(dodaj->kolejny_numer_string)]=rekord->etykieta[dlugosc-1];
		  ostatni_element->nast=dodaj;
		}
	    }
	  //the label doesn't have dot there at proper place
	  else
	    {
	      kol_etykiet*dodaj=new kol_etykiet;
	      klasa_obslugi_etykiet.ustaw_zmienna_numer_etykietki(rekord->etykieta);
	      strcpy(dodaj->etykieta,rekord->etykieta);
	      strcpy(dodaj->kolejny_numer_string,klasa_obslugi_etykiet.numer_etykietki);
	      nowy_element->nast=dodaj;
	      if(debug_level)
		{
		  cout<<"****************************************************************"<<endl;
		  cout<<"The label looks like blach"<<endl;
		  cout<<"The label doesn't exist on the global queue. Must be added."<<endl;
		  cout<<"The number of the label was taking using ustaw_zmienn±_numer_etykietki function"<<endl;
		  cout<<"Here is what klasa_obslugi_etykiet.numer_etykietki looks like: "<<klasa_obslugi_etykiet.numer_etykietki<<endl;
		  cout<<"================================================================"<<endl;
		}
	    }
	}
    }//koniec else
  return 0;
}

//function that returns label number
int zwroc_numer_etykiety(kol_etykiet*wierzcholek,char*etykieta,kol_etykiet**zmienna_tymczasowa)
{
  kol_etykiet*bierzacy=wierzcholek;
  if(debug_level)
    {
      cout<<endl<<endl<<endl;
      cout<<"***********************************************"<<endl;
      cout<<"The function zwroc_numer_etykiety is speaking. Below the arguments I got:"<<endl;
      cout<<"bierzacy->etykieta: "<<bierzacy->etykieta<<endl;
      cout<<"etykieta: "<<etykieta<<endl;
    }
  while(strcmp(bierzacy->etykieta,etykieta)&&bierzacy->nast)
	bierzacy=bierzacy->nast;

	if(strcmp(bierzacy->etykieta,etykieta))
	  {
	    if(debug_level)
	      {
		cout<<"Leaving function zwroc_numer_etykiety with 0 error."<<endl;
		cout<<"=========================================="<<endl;
	      }
	    return 0;
	  }
	else
	  {
	  //return bierzacy->kolejny_numer;
	    (*zmienna_tymczasowa)=bierzacy;
	    if(debug_level)
	      {
		cout<<"Leaving function zwroc_numer_etykiety with 1 error."<<endl;
		cout<<"=========================================="<<endl;
	      }
	    return 1;
	  }

}


//funkcja zwracaj±ca string który by³ przed etykiet±
int przed_etykieta_po(char zn_przed,char*linia,char*przed,char*po,char zn_po)
{
  char pomocnicza[DL_WIERSZA];
  char pprzed[DL_WIERSZA];
  char ppo[DL_WIERSZA];
	int q=DL_WIERSZA-1;
	pomocnicza[q]=pprzed[q]=ppo[q]='\0';
  strcpy(pomocnicza,linia);
  int i=1;
  int dl_linii=strlen(linia);
  while(pomocnicza[i]!=zn_przed)
    {
      pprzed[i-1]=pomocnicza[i];
      i++;
      if(i>dl_linii) return 1;
    }
  pprzed[i-1]=zn_przed;//dopisz nawias do pomocniczej
  pprzed[i]='\0';//dopisz koniec linii do pomocniczej
  i++;
  while(pomocnicza[i]!=zn_po)
    {
      i++;
      if (i>dl_linii)return 1;
    }
  int i_dwa=0;
  while(pomocnicza[i]!='\0')
    {
      ppo[i_dwa]=pomocnicza[i];
      i++; i_dwa++;
    }
  ppo[i_dwa]='\0';
  strcpy(przed,pprzed);
  strcpy(po,ppo);
  return 0;
}

//checking if we shuld change label counters
int check_counter_to_set(char*linia)
{
  int counter;
  // counter=0 %--set-r-to
  // counter=1 %--set-R-to
  // counter=2 %--set-a-to
  // counter=3 %--set-l-to
  // counter=4 %--set-L-to
  char switches[5][12]={"%--set-r-to", "%--set-R-to", "%--set-a-to", "%--set-l-to", "%--set-L-to"};
  char *tymcz;
  char *checking;
  int dlugosc=strlen(linia);
  //tymcz=new char[dlugosc];
  if(dlugosc>=13&&linia[11]==' ')
    {
      tymcz=new char[dlugosc];
      for(counter=0;counter<5;counter++)
	{
	  if(!strncmp(linia,switches[counter],11))
	    break;
	}
      if(counter==5)
	return 1;
      for(int a=12;a<dlugosc;a++)
	{
	  if (linia[a]=='\n')
	    tymcz[a-12]='\0';
	  else
	    tymcz[a-12]=linia[a];
	}
      //we don't nead dlugosc variable anymore, so we can use it for other purpose
      dlugosc=strtol(tymcz,&checking,10);
      if(*checking!='\0'||dlugosc<=0)
	{
	  cout<<endl<<"***************Error******************"<<endl;
	  cout<<"You have given "<<switches[counter]<<" option, but wrong argument: "<<tymcz<<endl;
	  cout<<"**************************************"<<endl;
	  return 1;
	}
      klasa_obslugi_etykiet.set_up_all(counter,dlugosc);
      delete tymcz;
      return 0;
    }

/*
      switch(counter)
	{
	case 0:
	  {
	    
	    break;
	  }
	case 1:
	  {
	    
	    
	    break;
	  }
	case 2:
	  {
	    
	    
	    break;
	  }
	case 4:
	  {
	    
	    
	    break;
	  }
	default:
	  return 0;
	}
 */

  return 0;
}
