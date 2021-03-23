/*
Copyright (C) 2004 Piotr Wawrzyniak (piti@piti.vsv.pl)

Plik zawiera definicjê klasy przechowuj±cej informacje i funkcje, 
które bêd± definiowa³y odpowiednie numerowanie

In this file, there is class defined, that handles number types.
I know that this can be made much easies, without class definition etc,
but I wanted to write alittle with classes to lern them allitle.

*/

#include<string.h>

struct kol_liczb{
        int liczba;
        kol_liczb* next;
        kol_liczb* prev;
};



  const int dl=20;//d³ugo¶æ linii przechowuj±cej numerk kolejnej etykietki 
//klasa rekord_numerow zawieraj±ce kolejne numery dla poszczegolnych sk³adowych
class r_numerow{

 public:
  char numer_etykietki[dl]; //np 111, ab, XV, xv itd.
  int set_up_all(int,int,int,int,int,int);
  int set_up_all(int, int);

  /*
    zwróci numerek etykiety w liczbach rzymskich, arabskich czy literkach
    dok³adnie to tylko zmodyfikuje warto¶æ numer_etykietki[], któr± trzeba
    bêdzie odzielnie odczytaæ po wywo³aniu tej funkcji na rzecz etykietki.
    Przy czym dozwolone warto¶ci s± nastêpuj±ce"
    0 - roman numbers small :r
    1 - roman numbers bigg  :R
    2 - arabic numbers      :a
    3 - small letters       :l
    4 - big letters         :L
  */

  int zwroc_numer_etykiety(int numer);
  int domyslny_styl_numeracji;
  r_numerow(int,int,int,int,int);//konstruktor, constructor
  int ustaw_zmienna_numer_etykietki(char *);
 private:
  
  /*
    default numbering scheme. There are 5 possible values
    0 - roman numbers small :r
    1 - roman numbers bigg  :R
    2 - arabic numbers      :a
    3 - small letters       :l
    4 - big letters         :L
  */

  /*
    tablica przechowuj±ca kolejny numer dla ka¿dej etykietki
    table that contains the last number for given group of labels
  */
  int zwroc_num_etykiet[5];
  
  int int_na_rom_char(int,int);//zamiana numeru na romanski ma³y i duzy, change to roman small and big
  int int_na_char(int); //zamiana numeru na char zawieraj±cy numer, change int to char
  int int_na_lit_char(int,int);//zamiana numeru na litery male i du¿e, change to small and capital letters

  /*
    The inline function that fill in with zeros the variable numer_etykietki
    Generally it is better to have everywhere there zeros.
  */
  int zeruj_numer_etykietki()
  {
    for(int dupa=0;dupa<dl;dupa++)
      numer_etykietki[dupa]='\0';
    return 0;
  }
  
};
