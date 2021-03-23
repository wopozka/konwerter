#ifndef DL_L
#define DL_L

#define DL_WIERSZA 256
#endif

#ifndef KOL_W_EPS
#define KOL_W_EPS

class kol_etykiet
{
 public:
  int kolejny_numer;
  char kolejny_numer_string[DL_WIERSZA];
  char etykieta[DL_WIERSZA];
  kol_etykiet*nast;
  kol_etykiet(void)
  {
    nast=NULL;
    int a;
    for(a=0;a<DL_WIERSZA;a++)
      {
	kolejny_numer_string[a]='\0';
	etykieta[a]='\0'  ;
	
      }
  }

};

#endif

