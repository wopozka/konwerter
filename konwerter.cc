
 /***************************************************************************
 *                                                                          * 
 *   Copyright (C) 2005 Piotr Wawrzyniak (piti@eliksir.ch.pw.edu.pl)        *
 *   This program is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation; either version 2 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 ***************************************************************************/

/*
  Tutaj tylko analizujê linie poleceñ i sprawdzam co nale¿y zrobiæ ponumerowaæ czy 
  wróciæ do etykiet.

  Here I analyze only commandline and check what is to do.
*/

#include<string.h>
#include"operacje.h"
#include"dl_wiersza.h"
#include<stdlib.h>
#include"operacje_na_tex.h"
#include"system_zapisu.h"
#define Def_version "0.1.99 (16.02.2005)"
#define Def_email "piti@eliksir.ch.pw.edu.pl"

kol_etykiet*wierzcholek;

r_numerow klasa_obslugi_etykiet(1,1,1,1,1);

char numer_czy_etykieta='n';
int zacznij_numery_od=1;
char polecenie[DL_WIERSZA]; //what latex command will be use for label inserting
char jezyk[3]="pl"; //language 

int srf=1;
int sRf=1;
int saf=1;
int slf=1;
int sLf=1;
int dns=2;
int debug_level=0;
int ignore_set_counter_to=0;
int ignore_formating=0;

void pomoc(); //help function declaration

int main(int argc,char *argv[])
{

  if(argc<2)
    {
      pomoc();
      return 1;
    }
  strcpy(polecenie,"\\nrzw{");//Initialization command default is \nrzw
  if(!strcmp(argv[0],"konwerter"))numer_czy_etykieta='n';
  if(!strcmp(argv[0],"etykietuj"))numer_czy_etykieta='e';
  int i;

  //============================================================================
  //Command line analyzing
  for (i=1;i<argc&&argv[i][0]=='-';i++)
    {
      if(argv[i][0]=='-')
	{
	  //Paremeters without argument
	  
	  int czy_znalazlem=0;
	  
	  if(!strcmp(argv[i],"-ltn")){numer_czy_etykieta='n';czy_znalazlem=1;}

	  if(!strcmp(argv[i],"-ntl")){numer_czy_etykieta='e';czy_znalazlem=1;}

	  if(!strcmp(argv[i],"--labels-to-numbers")){numer_czy_etykieta='n';czy_znalazlem=1;}

	  if(!strcmp(argv[i],"--numbers-to-labels")){numer_czy_etykieta='e';czy_znalazlem=1;}

	  if(!strcmp(argv[i],"-v")){debug_level=1;czy_znalazlem=1;}

	  if(!strcmp(argv[i],"--verbose")){debug_level=1;czy_znalazlem=1;}
	  
	  if(!strcmp(argv[i],"-is")){ignore_set_counter_to=1;czy_znalazlem=1;}
	  
	  if(!strcmp(argv[i],"--ignore-switches")){ignore_set_counter_to=1;czy_znalazlem=1;}

	  if(!strcmp(argv[i],"-if")){ignore_formating=1;czy_znalazlem=1;}

	  if(!strcmp(argv[i],"--ignore-formating")){ignore_formating=1;czy_znalazlem=1;}


	  
	  	  	  	  
	  //**************************************************************;
	  //Parameters with argument;
	  //Start roman from analyzis;
	  if(!strcmp(argv[i],"-srf"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)srf=atoi(argv[i]);
	      else
		{
		    cout<<"B³±d opcji."<<endl;
		    cout<<"Wrong parameter of option."<<endl;		     
		     return 1;
		}
	      if(srf==0)
		{
		  
		  cout<<"Z³y argument opcji -srf."<<endl;
		  cout<<"Wrong -srf option argument."<<endl;
		  return 1;
		}
	    }
      
	  if(!strcmp(argv[i],"--start-roman-from"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)srf=atoi(argv[i]);
	      else
		{
		  cout<<"B³±d opcji."<<endl;
		  cout<<"Wrong parameter."<<endl;
		  return 1;
		}
	      if(srf==0)
		{
		  cout<<"Z³y argument opcji --start-roman-from."<<endl;
		  cout<<"Wrong --start-roman-from option argument."<<endl;
		  return 1;
		}

	    }

	  //************************************************************************;
	  //Start Roman from analyzis;
	      
	  if(!strcmp(argv[i],"-sRf"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)sRf=atoi(argv[i]);
	      else
		{
		    cout<<"B³±d opcji."<<endl;
		    cout<<"Wrong parameter of option."<<endl;		     
		     return 1;
		}
	      if(srf==0)
		{
		  
		  cout<<"Z³y argument opcji -sRf."<<endl;
		  cout<<"Wrong -sRf option argument."<<endl;
		  return 1;
		}
	    }
      
	  if(!strcmp(argv[i],"--start-Roman-from"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)sRf=atoi(argv[i]);
	      else
		{
		  cout<<"B³±d opcji."<<endl;
		  cout<<"Wrong parameter."<<endl;
		  return 1;
		}
	      if(srf==0)
		{
		  cout<<"Z³y argument opcji --start-Roman-from."<<endl;
		  cout<<"Wrong --start-Roman-from option argument."<<endl;
		  return 1;
		}

	    }

	  //*****************************************;
	  //Start arabic from analyzis;
	  
	  if(!strcmp(argv[i],"-saf"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)saf=atoi(argv[i]);
	      else
		{
		    cout<<"B³±d opcji."<<endl;
		    cout<<"Wrong parameter of option."<<endl;		     
		     return 1;
		}
	      if(saf==0)
		{
		  
		  cout<<"Z³y argument opcji -saf."<<endl;
		  cout<<"Wrong -srf option argument."<<endl;
		  return 1;
		}
	    }
      
	  if(!strcmp(argv[i],"--start-arabic-from"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)saf=atoi(argv[i]);
	      else
		{
		  cout<<"B³±d opcji."<<endl;
		  cout<<"Wrong parameter."<<endl;
		  return 1;
		}
	      if(srf==0)
		{
		  cout<<"Z³y argument opcji --start-arabic-from."<<endl;
		  cout<<"Wrong --start-arabic-from option argument."<<endl;
		  return 1;
		}

	    }


	  //*****************************************;
	  //Start letter from

	  if(!strcmp(argv[i],"-slf"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)slf=atoi(argv[i]);
	      else
		{
		    cout<<"B³±d opcji."<<endl;
		    cout<<"Wrong parameter of option."<<endl;		     
		     return 1;
		}
	      if(slf==0)
		{
		  
		  cout<<"Z³y argument opcji -slf."<<endl;
		  cout<<"Wrong -slf option argument."<<endl;
		  return 1;
		}
	    }
      
	  if(!strcmp(argv[i],"--start-letter-from"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)slf=atoi(argv[i]);
	      else
		{
		  cout<<"B³±d opcji."<<endl;
		  cout<<"Wrong parameter."<<endl;
		  return 1;
		}
	      if(slf==0)
		{
		  cout<<"Z³y argument opcji --start-letter-from."<<endl;
		  cout<<"Wrong --start-letter-from option argument."<<endl;
		  return 1;
		}

	    }

	  //*****************************************;
	  //Start Letters from;

	  if(!strcmp(argv[i],"-sLf"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)sLf=atoi(argv[i]);
	      else
		{
		    cout<<"B³±d opcji."<<endl;
		    cout<<"Wrong parameter of option."<<endl;		     
		     return 1;
		}
	      if(sLf==0)
		{
		  
		  cout<<"Z³y argument opcji -sLf."<<endl;
		  cout<<"Wrong -sLf option argument."<<endl;
		  return 1;
		}
	    }
      
	  if(!strcmp(argv[i],"--start-Letter-from"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc)sLf=atoi(argv[i]);
	      else
		{
		  cout<<"B³±d opcji."<<endl;
		  cout<<"Wrong parameter."<<endl;
		  return 1;
		}
	      if(sLf==0)
		{
		  cout<<"Z³y argument opcji --start-Letter-from."<<endl;
		  cout<<"Wrong --start-Letter-from option argument."<<endl;
		  return 1;
		}

	    }

	  //************************************************************;
	  //Default numbering style - dns

	  if(!strcmp(argv[i],"-dns")||!strcmp(argv[i],"--default-numbering-style"))
	    {
	      i++;czy_znalazlem=1;
	      if(i<argc&&strlen(argv[i])==1)
		{
		  switch(argv[i][0])
		    {
		    case 'r':
		      dns=0;
		      break;
		    case 'R':
		      dns=1;
		      break;
		    case 'a':
		      dns=2;
		      break;
		    case 'l':
		      dns=3;
		      break;
		    case 'L':
		      dns=4;
		      break;
		    default:
		      dns=-1;
		      break;
		    }
		}
		 else
		   {
		    cout<<"B³±d opcji -dns/--default-numbering-style."<<endl;
		    cout<<"Wrong parameter of -dns/--default-numbering-style option."<<endl;		     
		    return 1;
		   }
	    }



	  //*************************************************************;
	  // -ln, --label-name analyzis
	  if(!strcmp(argv[i],"-ln"))
	    {
	      i++;czy_znalazlem=1;
	      if(argv[i][0]=='\\')
		{
		  if(strlen(argv[i])>DL_WIERSZA-2)
		    {
		      cout<<"Ha. Nie uda ci siê przepe³niæ tutaj bufora hakerze!"
			  <<endl
			  <<"Polecenie za d³ugie."<<endl
			  <<"To long -ln option parameter"<<endl;
		      return 1;
		    }
		  else
		    {strcpy(polecenie,argv[i]);strcat(polecenie,"{");}
		}
	      else
		{
		  cout<<"Je¶li w pliku LaTeX polecenie wygl±da \\nrzw"<<endl 
		      <<"to opcja -ln musi wygl±daæ \\\\nrzw"<<endl
		      <<"If in LaTeX file command is \\nrzw"<<endl
		      <<"so option -ln must be \\\\nrzw"<<endl;
		  return 1;
		}
	    }

	  if(!strcmp(argv[i],"--label-name"))
	    {
	      i++;czy_znalazlem=1;
	      if(argv[i][0]=='\\')
		{
		  if(strlen(argv[i])>DL_WIERSZA-2)
		    {
		      cout<<"Ha. Nie uda ci siê przepe³niæ tutaj bufora hakerze!"
			  <<endl
			  <<"Polecenie za d³ugie."<<endl
			  <<"argv[i] command to long"<<endl;
		      return 1;
		    }
		  else
		    {strcpy(polecenie,argv[i]);strcat(polecenie,"{");}
		}
	      else
		{
		  cout<<"Je¶li w pliku LaTeX polecenie wygl±da \\nrzw"<<endl
		      <<"to opcja --label-name musi wygl±daæ \\\\nrzw"<<endl
		      <<"If in LaTeX file command is \\nrzw"<<endl
		      <<"so option -ln must be \\\\nrzw"<<endl;
		  return 1;
		}
	    }

	  //**********************************************************;
	  //language analyzis;
	  if(!strcmp(argv[i],"-l")||!strcmp(argv[i],"--language"))
	    {
	      i++;czy_znalazlem=1;
	      
	      if (!strcmp(argv[i],"en")) strcpy(jezyk,"en");

	    }
	  
	  
	  
	  if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"--help"))
	    {
	      pomoc();
	      return 1;
	    }

	  if(!czy_znalazlem)
	    {

	      cout<<"Nieznana opcja "<<argv[i]<<endl
		  <<"Unknown option "<<argv[i]<<endl;
	      return 1;

	    }
	}     
    }

  //*****************************************************;
  //Maybe you nead help?
  if(!strcmp(argv[1],"-h")||!strcmp(argv[1],"--help"))
    {
      pomoc();
      return 1;
    }

  if(i<argc)

    if(argv[i][0]=='-')
      {
	cout<<"Brakuje argumentu opcji: "<<argv[i]<<endl
	    <<"Missing option argument: "<<argv[i]<<endl;
	return 1;
      }
 
  if(i>=argc){cout<<"Brak nazwy pliku"<<endl<<"Missing filename"<<endl;return 1;}  
  
  if(srf<=0)
    {
      cout<<"B³êdna opcja -srf albo --start-roman-from "<<srf<<". Numer musi byæ  wiêkszy od zera."<<endl
	  <<"Wrong option -srf or --start-roman-from parametr "<<srf<<". Number must be greater than 0."<<endl;
      return 1;
    }
  
  if(sRf<=0)
    {
      cout<<"B³êdna opcja -sRf albo --start-Roman-from "<<sRf<<". Numer musi byæ  wiêkszy od zera."<<endl
	  <<"Wrong option -sRf or --start-Roman-from parametr "<<sRf<<". Number must be greater than 0."<<endl;
      return 1;
    }
 
  if(saf<=0)
    {
      cout<<"B³êdna opcja -saf albo --start-arabic-from "<<saf<<". Numer musi byæ  wiêkszy od zera."<<endl
	  <<"Wrong option -saf or --start-arabic-from parametr "<<saf<<". Number must be greater than 0."<<endl;
      return 1;
    }

  if(slf<=0)
    {
      cout<<"B³êdna opcja -slf albo --start-letter-from "<<slf<<". Numer musi byæ  wiêkszy od zera."<<endl
	  <<"Wrong option -slf or --start-letter-from parametr "<<slf<<". Number must be greater than 0."<<endl;
      return 1;
    }

  if(sLf<=0)
    {
      cout<<"B³êdna opcja -sLf albo --start-Letter-from "<<sLf<<". Numer musi byæ  wiêkszy od zera."<<endl
	  <<"Wrong option -sLf or --start-Letter-from parametr "<<sLf<<". Number must be greater than 0."<<endl;
      return 1;
    }

  if(dns<=0)
    {
      cout<<"B³êdna opcja -dns albo --default-numbering-style "<<endl
	  <<"Wrong option -dns or --default-numbering-style parameter "<<endl;
      cout<<"Dozwolone warto¶ci to (Allowed walues are): r, R, a, l, L"<<endl;
      return 1;
    }

  klasa_obslugi_etykiet.set_up_all(srf,sRf,saf,slf,sLf,dns);

  //end of the command line analyzis
  //========================================================================================

  //Funkcja z operacje.cc. Zajmuje siê przetwarzaniem pliku texowego tzn szuka etykiet
  //sprawdza czy ma byæ zamiana etykiet na numery czy odwrotnie. Je¶li znajdzie etykiety 
  //w plikach eps wtedy zamienia je na numery.
  if(przetwarzaj_plik(argv[i],/*argv[2],*/&wierzcholek))return 1;//zwrócenie 1 oznacza b³±d

  if(numer_czy_etykieta=='n')//czy mamy zamieniaæ etykiety na numery
    {
      if(!wierzcholek)
	{
	  cout<<"Nie znaleziono ¿adnej etykiety w plikach eps."<<endl
	      <<"No label was found"<<endl;
	  return 1;
	}
      //zmieniamy etykiety na numery w plikach tex
      //we change labels to numbers in tex files
      operacje_na_tex(argv[i],wierzcholek); 
    }

  //memory cleaning
  kol_etykiet*usuwany=wierzcholek;
  while(usuwany)
    {
      usuwany=wierzcholek->nast;
      delete wierzcholek;
      wierzcholek=usuwany;
      
    }
  //end of memory cleaning
  
  cout<<endl<<"Program zakoñczy³ siê pomy¶lnie."<<endl
      <<"Program finished successfuly"<<endl;
  return 0;
}

void pomoc()
{
  if(!strcmp(jezyk,"pl"))
  {
    cout<<endl;
    cout<<"Automatyczna zmiana etykiet w pliku LaTeX-owym na numery."<<endl;
    cout<<"Wersja "<<Def_version<<". Napisany i rozpowszechniany przez Piotra Wawrzyniaka."<<endl<<endl;
    cout<<"Je¶li podoba ci siê ten program albo masz inne uwagi napisz:"<<endl;
    cout<<Def_email<<endl<<endl;
    cout<<"Program rozpowszechniany na licencji GPL (patrz www.gnu.org)."<<endl<<endl;
    cout<<"PROGRAM NIE POSIADA ¿ADNEJ GWARACJI. U¿YWASZ NA W³ASNE RYZYKO."<<endl<<endl;
    cout<<"POLECAM ZROBIENIE KOPII ZAPASOWEJ PLIKU(ÓW) PRZED U¿YCIEM PROGRAMU."<<endl<<endl;
    
    cout<<"U¿ycie: konwerter/numeruj [opcje] nazwa_pliku_latexowego"<<endl;
    cout<<"Wspierane opcje [domy¶lne w nawiasach]"<<endl;
    cout<<"-ltn, --labels-to-numbers           zamiana etykiet na liczby [-ltn]"<<endl;
    cout<<"-ntl, --numbers-to-labels           zamiana liczb na etykiety"<<endl
	<<"                                    (tylko w plikach *.eps)"<<endl;
    cout<<"-srf n, --start-roman-from n        rozpocznij numerowanie ma³ymi cyframi"<<endl
	<<"                                    rzymskimi od n [-srf 1]"<<endl;
    cout<<"-sRf n, --start-Roman-from n        rozpocznij numerowanie wielkimi cyframi"<<endl
	<<"                                    rzymskimi od n [-sRf 1]"<<endl;
    cout<<"-saf n, --start-arabic-from n       rozpocznij numerowanie cyframi arabskimi"<<endl
	<<"                                    od n [-saf 1]"<<endl;
    cout<<"-slf n, --start-letter-from n       rozpocznij numerowanie ma³ymi literami"<<endl
	<<"                                    od n [-rlf 1]"<<endl;
    cout<<"-sLf n, --start-Letter-from n       rozpocznij numerowanie wielkimi literami"<<endl 
	<<"                                    od n [-rLf 1]"<<endl;
    cout<<"-dns n, --default-numbering-style n ustaw domy¶lny styl numeracji. Mo¿liwe"<<endl
	<<"                                    warto¶ci to :r, R, a, l, L [-dns a]"<<endl;
    cout<<"-ln, --label-name                   nazwa polecenia LaTeXowego wstawiaj±cego"<<endl
	<<"                                    numer [-ln \\nrzw] przy tej opcji zawsze "<<endl
	<<"                                    nale¿y podawaæ -ln \\\\xyz"<<endl;
    cout<<"-l, --language                      jêzyk komunikatów. Dostêpne parametry"<<endl 
	<<"                                    [pl] i en. Nieznany parametr traktowany"<<endl
	<<"                                    jako pl"<<endl;
    cout<<"-is, --ignore-switches              zignoruj prze³±czniki %--set-X-to"<<endl;
    cout<<"-if, --ignore-formating             u¿yj dla wszystkich etykiet domy¶lnego"<<endl
	<<"                                    typu formatowania"<<endl;
    cout<<"-v, --verbose                       wy¶wietlaj du¿o brzydkich komunikatów"<<endl;
    cout<<"-h, --help                          to co teraz czytasz"<<endl;
    cout<<"Type \"konwerter -l en -h\" for help in English."<<endl;
  }
  else
    {
      cout<<endl;
      cout<<"Automatic conwersion labels in LaTeX and EPS files to numbers."<<endl;
      cout<<"Version "<<Def_version<<". Written by Piotr Wawrzyniak."<<endl<<endl;
      cout<<"If you like this program, or have any sugestions please sent me an e-mail to:"<<endl;
      cout<<Def_email<<endl<<endl;
      cout<<"Program spreads under conditions of GPL (see www.gnu.org)."<<endl<<endl;
      cout<<"THIS SOFTWARE COMES WITH ABSOLUTELY NO WARRANTY! USE AT YOUR OWN RISK!"<<endl<<endl;
      cout<<"IT IS GOOD IDEA TO DO COPY OF ALL FILES BEFORE USE."<<endl<<endl;
      cout<<"Usage: konwerter/numeruj [options] LaTeX_filename"<<endl;
      cout<<"Supported  options [default in brackets]:"<<endl;
      cout<<"-ltn, --labels-to-numbers           change labels to numbers [-n]"<<endl;
      cout<<"-ntl, --numbers-to-labels           change numbers to labels"<<endl
	  <<"                                    (only in eps files)"<<endl;
      cout<<"-srf n, --start-roman-from n        start number with small roman"<<endl
	  <<"                                    numbers from n [-srf 1]"<<endl;
      cout<<"-sRf n, --start-Roman-from n        start number with capital roman"<<endl
	  <<"                                    numbers from n [-sRf 1]"<<endl;
      cout<<"-saf n, --start-arabic-from n       start number with arabic numbers"<<endl
	  <<"                                    from n [-saf 1]"<<endl;
      cout<<"-slf n, --start-letter-from n       start number with small letters"<<endl
	  <<"                                    from n [-rlf 1]"<<endl;
      cout<<"-sLf n, --start-Letter-from n       start number with capital letters"<<endl 
	  <<"                                    from n [-rLf 1]"<<endl;
      cout<<"-dns n, --default-numbering-style n set default number style. Possible"<<endl
	  <<"                                    walues: r, R, a, l, L  [-dns a]"<<endl;
      cout<<"-ln, --label-name                   LaTeX command for numbers inserting"<<endl
	  <<"                                    [\\nrzw]. There must be always 2"<<endl
	  <<"                                    backslashes ie. -ln \\\\xyz"<<endl;
      cout<<"-l, --language                      set language. There are 2 possible"<<endl
	  <<"                                    parameters: [pl] and en. Unknown"<<endl
	  <<"                                    parameter is handle as pl"<<endl;
      cout<<"-is, --ignore-switches              ignore switches %--set-X-to"<<endl;
      cout<<"-if, --ignore-formating             use for all labels default number"<<endl
	  <<"                                    style"<<endl;
      cout<<"-v, --verbose                       be verbose"<<endl;
      cout<<"-h, --help                          short help"<<endl;
    }
}

